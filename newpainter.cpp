//This program is to alter processed image to ptg.
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
	int row;
	int col;
	int **original_img;
	int **final_img;
	char iFileName[64];
	ifstream iFile;
	char oFileName[64];
	ofstream oFile;
	vector<int[2]> patch;//patch is the color patch
	


	cout<<"Input the original image file: ";
	cin>>iFileName;
	cout<<"Input the desired output file name:";
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
	
	initialize_original(iFile, original_img, row, col);
	initialize_final(final_img, row, col);


	/*
	for(int i=0; i<5; i++){
		for(int j=0; j<3;j++){
			a[i][j]=0;
			cout << a[i][j];
		}
		cout << endl;
	}
	*/
	

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
int initialize_original(ifstream &iFile, int ** original_img, int row, int col)
{
	for(int i=0; i<=row; i++){
		for(int j=0; j<=col; i++){
			if(iFile.eof())
				return -1;
			else
				iFile>>original_img[i][j];
		}
	}
	return 0; //SUCCESS
}

void initialize_final( int ** final_img, int row, int col ){
	

}

