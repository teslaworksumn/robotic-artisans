//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
using namespace std;
int initialize_original(ifstream &iFile, int ** original_img, int row, int col);
void initialize_final( int ** final_img, int row, int col );





int main(){
	//declare variables
	int i,j;
	int row;
	int col;
	int **original_img = NULL;
	int **final_img = NULL;
	char iFileName[64] = "test.ptg";
	ifstream iFile;
	char oFileName[64] = "test.txt";
	ofstream oFile;
	vector<int[2]> patch;//patch is the color patch
	


	cout<<"Input the original image file: ";
	cin>>iFileName;
	cout<<"Input the desired output file name: ";
	cin>>oFileName;
	
	iFile.open(iFileName); //read the file and make sure the file is open.
	if(iFile.fail()){
		cout<<"Input file opening failed."<<endl;
		return -1;
	}
	
	oFile.open(oFileName); //open the desired output file.
	if(oFile.fail()){
		cout<<"Output file opening failed."<<endl;
		return -1;
	}
 
	iFile>>row>>col;
 
  original_img = new (nothrow)int * [row];
  for( i = 0 ; i < row ; i++ ) {
    original_img[i] = new (nothrow) int [col];
  }

	final_img = new (nothrow) int * [row];
	for (i=0; i<row;i++){
		final_img[i] = new (nothrow) int[col];
	}
	
	initialize_original(iFile, original_img, row, col);
	initialize_final(final_img, row, col);
  for ( i = 0 ; i < row ; i++ ){
    for ( j = 0 ; j < col ; j++ ){
      cout << original_img[i][j] << " ";
    }
    cout << endl;
  }

	//put image into source image
	//int rows, int columns, int original[rows][columns];
	//int altered[rows][columns];
	//output txt.
	
	//findConsecutivePosition(vector, color, original)
	//output vector
	
	//Split up the vector into instructions 
	//Output the instructions.
  
  //free up pointers
  for ( i = 0 ; i < row ; i++ ){
    delete [] original_img [i];
    delete [] final_img [i];
  }  
  delete [] original_img ;
  delete [] final_img;
  
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

void initialize_final( int ** final_img, int row, int col ){

}