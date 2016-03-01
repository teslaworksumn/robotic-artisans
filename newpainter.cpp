//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <istream>
using namespace std;

//Pixel struct 
struct pixel{
  int x;
  int y; 
};

struct stroke{
  int action;
  pixel end;
  int oldcolor;
  int newcolor;
};

//Global constants
#define MAX_COLORS 9 // including no paint 0 + 1-8 colors =9
#define MAX_TANK 5
#define EMPTY 0

#define MOVE -1 // -1 x y
#define LIFT -2 // -2 
#define DROP -3 // -3
#define REFILL -4 // -4 x0 y0 color
#define SWITCH_BRUSH -5 // -5 x0 y0 color_prev color_next 
#define INIT -99 // -99
#define END -100 // -100

//function prototypes
int initialize_original(ifstream &iFile, int ** original_img, int row, int col);
bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color );
bool output_stroke( ofstream &oFile , vector<stroke> stks , bool flag );
bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank);
void fill_stroke( stroke &new_strk , const int action , pixel p , int oldcolor , int newcolor );
void find_xline( vector<pixel> &patch , vector<pixel> &line , vector<int> &line_indexes );
void sort_line(vector<pixel>& line, vector<int>& line_indexes);
void USAGE_STATEMENT();


int main( int argc , char *argv[] ){
	//declare variables
	int i,j;
	int row;
	int col;
	int **img = NULL;
	int tank = MAX_TANK;
	//int **final_img = NULL;
	char iFileName[64] = "test.ptg";
	ifstream iFile;
	char oFileName[64] = "test.txt";
	ofstream oFile;
	vector<pixel> patch;//patch is the color patch
	stroke prv_strk;
  vector<stroke> strks;
  pixel start;
  start.x = -1;
  start.y = -1;
  
  fill_stroke(prv_strk,INIT,start,0,0);
   
  cout<<"Input the original image file: ";
	cin>>iFileName;
	iFile.open(iFileName); //read the file and make sure the file is open.
	if(iFile.fail()){
		cout<<"Input file opening failed."<<endl;
		return -1;
	}
 
	cout<<"Input the desired output file name: ";
	cin>>oFileName;
	oFile.open(oFileName); //open the desired output file.
	if(oFile.fail()){
		cout<<"Output file opening failed."<<endl;
		return -1;
	}
 
	iFile>>row>>col;
 
  img = new (nothrow)int * [row];
  for( i = 0 ; i < row ; i++ ) {
    img[i] = new (nothrow) int [col];
  }

  //puts image from source file into original_img
	initialize_original(iFile, img, row, col);

  //will loop through to check for every color
  for ( i = 1 ; i < MAX_COLORS ; ++i ){
    if( prv_strk.action != INIT){
      fill_stroke( prv_strk , LIFT , prv_strk.end , prv_strk.newcolor , prv_strk.newcolor );
      strks.push_back(prv_strk);
    }
    fill_stroke( prv_strk , SWITCH_BRUSH , prv_strk.end , prv_strk.newcolor , i );
    strks.push_back(prv_strk);
    
    //will loop through until every patch of color i is found
    while( find_patch( img , row , col , patch , i ) != -1 )
    {
      //will loop through until all strokes are a made from patch 
      while( left_right_stroke(patch,prv_strk, strks, tank) != -1 )
      {
        //output instruction to file 
        output_stroke( oFile , strks , false );
      }
      //empty strks
      while(!strks.empty())
      {
        strks.pop_back();
      }
    }//end: while(find_patch() != -1)
  }//end: for ( i = 1 ; i < MAX_COLORS ; ++i ) 
  
  //free up pointers
  for ( i = 0 ; i < row ; i++ ){
    delete [] img [i];
    //delete [] final_img [i];
  }  
  delete [] img ;
  //delete [] final_img;
  
  //close files
  iFile.close();
  oFile.close();
  
  //return sucess
	return 0;
}

//This will take in the file and the original image pointer 
//Will take the istream and the original_img array, 
//the row # and the column #
//return 0 if all of original_img is filled
//return -1 if problem with reading in img
int initialize_original(ifstream &iFile, int ** original_img, int row, int col)
{
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(iFile.eof())
				return -1;
			else
				iFile>> original_img[i][j];
    }
	}
	return 0; //SUCCESS
}

bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color ){
  vector<pixel> unexplored_pixels;
  int i,j;
  bool found_patch = false;
  pixel curr , edge , temp; 
  
  //find the first pixel of indicated color in image
  for ( i = 0 ; i < row && !found_patch ; ++i ){
    for ( j = 0 ; j < col && !found_patch ; ++j ) {
      if( img[i][j] == color ){
        //set 
        found_patch = true; 
        
        curr.x = i ; 
        curr.y = j ; 
        unexplored_pixels.push_back(curr);
        img[i][j] = 0 ;
      }//if( img[i][j] == color )
    }//for ( j = 
  }//for ( i=
  
  while( !unexplored_pixels.empty() ){
    temp = unexplored_pixels.back() ;
    curr.x = temp.x;
    curr.y = temp.y;
    unexplored_pixels.pop_back() ;
    patch.push_back(curr) ;
    
    for( i = fmax( (float) (curr.y - 1) , 0.0 ) ; i < fmin( (float) (curr.y - 1) , (float) row ) ; ++i ){
      for( j = fmax( (float) (curr.y - 1) , 0.0 ) ; j < fmin( (float) (curr.x - 1) , (float) col ) ; ++j ){
        if( img[i][j] == color ){
          found_patch = true; 
          edge.x = i ; 
          edge.y = j ;
          unexplored_pixels.push_back(edge);
          img[i][j] = 0 ;
        }//if( img[i][j] == color )
      }//for( j =
    }//for( i =
  }//while( !unexplored_pixels.empty() )
  return found_patch;
}//end find_patch

bool output_stroke( ofstream &oFile , vector<stroke> stks , bool flag ){
	for(int i=0; i<stks.size(); i++){
		switch(stks[i].action){
			case MOVE:
				oFile<<-1<<" "<<stks[i].end.x<<" "<<stks[i].end.y<<endl;
				break;
			case LIFT:
				oFile<<-2<<endl;
				break;
			case DROP:
				oFile<<-3<<endl;
				break;
			case REFILL:
				oFile<<-4<<" "<<stks[i].end.x<<" "<<stks[i].end.y<<" "<<stks[i].oldcolor<<endl;
				break;
			case SWITCH_BRUSH:
				oFile<<-5<<" "<<stks[i].end.x<<" "<<stks[i].end.y<<" "<<stks[i].oldcolor<<" "<<stks[i].newcolor<<endl;
				break;
			default:
				return false;
		}
	}
	return true;
}

bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank)
{
	bool found_stroke = false;
  bool refill = false;
	vector<pixel> line;
	vector<int> line_indexes; 
  stroke new_strk;
	int row,i; 
	
	if( !patch.empty() )
	{
		found_stroke = true;
    if( prv_strk.action == MOVE )
    {
      if(tank == EMPTY)
      {
        refill = true;
        tank = MAX_TANK;
        fill_stroke(new_strk, LIFT, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
        strks.push_back(new_strk);
        fill_stroke(new_strk, REFILL, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
        strks.push_back(new_strk);
      }
      line.push_back( prv_strk.end );
      line_indexes.push_back( -1 );
      find_xline( patch , line , line_indexes );
    }//end if( prv_strk.action == PAINT
    
    if( prv_strk.action == SWITCH_BRUSH || line.size() == 1 )
    {
      if(prv_strk.action == MOVE )
      {
        line.pop_back();
        line_indexes.pop_back();
        fill_stroke( new_strk , LIFT , line[0] , prv_strk.newcolor , prv_strk.newcolor );
        strks.push_back( new_strk );
      }
      line.push_back( patch[0] );
      line_indexes.push_back( -1 );
      find_xline( patch , line , line_indexes );
      fill_stroke( new_strk , MOVE , line[0] , prv_strk.newcolor , prv_strk.newcolor );
      strks.push_back( new_strk );
      fill_stroke( new_strk , DROP , line[0] , prv_strk.newcolor , prv_strk.newcolor );
      strks.push_back( new_strk );
    }
    else
    {
      fill_stroke(new_strk, DROP, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
      strks.push_back(new_strk);
    }
    sort_line( line , line_indexes );
    
    while( tank != EMPTY && line.size() != 0 )
    {
      fill_stroke( new_strk , MOVE , line[0] , prv_strk.newcolor , prv_strk.newcolor );
      line.erase(line.begin());
      patch.erase(patch.begin() + line_indexes[0]);
      line_indexes.erase(line_indexes.begin());
      tank--;
    }
    strks.push_back( new_strk );
    fill_stroke( prv_strk , MOVE , line[0] , prv_strk.newcolor , prv_strk.newcolor );
  }//end if( !patch.empty() )
	return found_stroke;
}

void fill_stroke( stroke &new_strk , const int action , pixel p , int oldcolor , int newcolor )
{
  new_strk.action = action;
  new_strk.end.x = p.x;
  new_strk.end.y = p.y;
  new_strk.oldcolor = oldcolor;
  new_strk.newcolor = newcolor;
}

void find_xline( vector<pixel> &patch , vector<pixel> &line , vector<int> &line_indexes )
{
  int i;
  int row;
  
  row = line[0].x;
		
  for(i = 0 ; i < patch.size() ; i++ )
  {
    if( patch[i].x == row )
    {
		  line.push_back(patch[i]);
      line_indexes.push_back(i);
		}//if( patch[i].x
  }//for(i = 0 
}

void sort_line(vector<pixel>& line, vector<int>& line_indexes)
{
	for(int i=0; i<line.size(); i++){
		for(int j=0; j<line.size()-1; j++){
			if(line[j].y>line[j+1].y){
				int temp=line[j+1].y;
				line[j+1].y=line[j].y;
				line[j].y=temp;
				int temp2=line_indexes[j+1];
				line_indexes[j+1]=line_indexes[j];
				line_indexes[j]=temp2;
			}
			else
				break;
		}
	}
	return;
}
