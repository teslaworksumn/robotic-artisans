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
  pixel start;
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

//function prototypes
int initialize_original( ifstream &iFile, int ** original_img, int row, int col );
//void initialize_final( int ** final_img, int row, int col );
bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color );
bool make_stroke( vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank , int color);
void output_stroke( ofstream &oFile , vector<stroke> stks , bool flag );
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

 /*Just commenting it out so it doesn't interfere with compiling. 
  //will loop through to check for every color
  for ( i = 1 ; i < MAX_COLORS ; ++i ){
    //will loop through until every patch of color i is found
    while( find_patch() != -1 ){
      //will loop through until all strokes are a made from patch 
      while( find_stroke() != -1 ){
        //output instruction to file 
        prepare_for_stroke();
        output_stroke();
      }
    }//end: while(find_patch() != -1)
  }//end: for ( i = 1 ; i < MAX_COLORS ; ++i )
  */
  
	//findConsecutivePosition(vector, color, original)
	//output vector
	
	//Split up the vector into instructions 
	//Output the instructions.
  
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
  int test;
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
/*
bool find_strokes( vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank, int color ){
  bool made_stroke = false;
  bool lifted = false;
  stroke tmp_strk;
  
  //if patch isn't empty then procede with making the stroke instructions
  if(!patch.empty()){
    made_stroke = true;
    if( tank == EMPTY ){
      if( prv_strk.action == MOVE ){
        tmp_strk.action = LIFT;
        strks.push_back(tmp_strk);
      }//if( prv_strk.action == MOVE )
      tmp_strk.action = REFILL;
      strks.push_back(tmp_strk);
      tank = MAX_TANK; 
      lifted = true;
    }//if( 
    
    tank == 0 )
    
    if( prv_strk.action == EMPTY ){
      
    }//if( prv_strk.action == MOVE )
    
    
  }//if(!patch.empty())
  
  return made_stroke;
}//end make_stroke
*/

void output_stroke( ofstream &oFile , vector<stroke> stks , bool flag ){
	for(i=0; i<stks.size(); i++){
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
				oFile<<-4<<" "<<stks[i].

bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank)
{
	bool found_stroke = false;
	vector<pixel> line 
	if( !patch.empty() )
	{
		
	}
	
	return found_stroke;
}

	







/*
//Pixel struct 
struct pixel{
  int x;
  int y; 
  int color;
};

struct stroke{
  int action;
  pixel start;
  pixel end;
  int oldcolor;
  int newcolor;
};

//Global constants
#define MAX_COLORS 9 // including no paint 0 + 1-8 colors =9
#define MAX_TANK 5

#define EMPTY 0
#define MOVE -1 // -1 xf yf
#define LIFT -2 // -2 
#define DROP -3 // -3
#define REFILL -4 // -4 x0 y0 color
#define SWITCH_BRUSH -5 // -5 x0 y0 color_prev color_next 
*/










