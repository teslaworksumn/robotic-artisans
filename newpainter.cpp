//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
using namespace std;

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
  int color;
};

//Global constants
#define MAX_COLORS 9 // including no paint 0 + 1-8 colors =9
#define MAX_TANK 5

#define PAINT -1
#define LIFT -2
#define LOWER -3
#define REFILL -4

//function prototypes
int initialize_original( ifstream &iFile, int ** original_img, int row, int col );
//void initialize_final( int ** final_img, int row, int col );
bool find_patch( int ** img , int row , int col , vector<pixel> * patch , int color );
bool make_stroke( vector<pixel> * patch , stroke * strk , int tank );
void output_stroke ( stroke * strk , bool flag );
void USAGE_STATEMENT();



int main( int argc , char *argv[] ){
	//declare variables
	int i,j;
	int row;
	int col;
	int **img = NULL;
  int max_tank = 5;
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
      while( make_stroke() != -1 ){
        //output instruction to file 
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

bool find_patch( int ** img , int row , int col , vector<pixel> * patch , int color ){
  vector<pixel> unexplored_pixels;
  int i,j;
  bool found_patch = false;
  pixel curr; 
  
  return found_patch;
}