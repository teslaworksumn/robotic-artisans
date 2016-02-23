//This program is to alter processed image to ptg.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
using namespace std;

int initialize_original();

void initialize_final( int ** final_img, int row, int col );









int main(){
	//declare variables
	int row;
	int col;
	int **original_img;
	int **final_img;
	string iFileName;
	ifstream iFile;
	string oFileName;
	ofstream oFile;
	vector<int[2]> patch;//patch is the color patch
	int a[5][3];
	
	
	
	
	
	
	/*
	for(int i=0; i<5; i++){
		for(int j=0; j<3;j++){
			a[i][j]=0;
			cout << a[i][j];
		}
		cout << endl;
	}
	*/
	
	
	//read the file and make sure the file is open.
	//put image into source image
	//int rows, int columns, int original[rows][columns];
	//int altered[rows][columns];
	//output txt.
	
	//findConsecutivePosition(vector, color, original)
	//output vector
	
	//Split up the vector into instructions 
	//Output the instructions. 
	

	return 0;
}

//This will take in the file and the original image pointer 
//Will take the istream and the original_img array, 
//the row # and the column #
//return 0 if all of original_img is filled
//return -1 if problem with reading in img
int initialize_original(istream &iFile, int ** original_img, int row, int col)
{
	
	return 0; //SUCCESS
}

void initialize_final( int ** final_img, int row, int col ){
	
}

