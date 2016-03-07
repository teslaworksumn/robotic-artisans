/******************************************************************************
 * main functions 
 * 
 * This function will take a ptg img and will give out a set of instruction in
 * the form of a txt file that will hold instruction to how to paint it. 
 * 
 *****************************************************************************/

//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <istream>
#include <string.h>

#include "newpainterhelper.h"

using namespace std;

int main( int argc , char *argv[] ){
	//declare variables
	int i;
	int row;
	int col;
	int **img = NULL;
	char iFileName[64] = "lisa.ptg";
	ifstream iFile;
	char oFileName[64] = "newpainter_result.txt";
	ofstream oFile;
  int flag[] = {false, false, false};
  

  
  for( i = 1 ; i < argc ; i++)
  {
    if(strcmp(argv[i],"-h") == 0 )
    {
      USAGE_STATEMENT(argv[0]);
      return -1;   
    }
    else if( strcmp(argv[i],"-ci") == 0 )
    {
      flag[0]=true;
    }
    else if( strcmp(argv[i],"-co") == 0  )
    {
      flag[1]=true;
    }
    else if( strcmp(argv[i],"-d") == 0  )
    {
      flag[2]=true;
    }
    else
    {
      cout << "ERROR: UNKNOWN ARGUEMENT: " << argv[i] << endl << endl;
      USAGE_STATEMENT(argv[0]);
      return -1;
    }  
  }
  
  if(flag[0])
  {
    cout<<"Input the original image file: ";
	  cin>>iFileName;
  }
  iFile.open(iFileName); //read the file and make sure the file is open.
  if(iFile.fail())
  {
	  cout<< "ERROR: " << iFileName << " failed to open" << endl;
	  return -1;	  
  }
  //if(flag[2]){cout<<"line 73: \tinput file opened"<<endl;}
  
  if(flag[1])
  {
	  cout<<"Input the desired output file name: ";
	  cin>>oFileName;
  }
  oFile.open(oFileName); //open the desired output file.
 	if(oFile.fail())
  {
 		cout<< "ERROR: " << oFileName << " failed to open" << endl;
		return -1;
  }
  //if(flag[2]){cout<<"line 86: \toutput file opened"<<endl;}
  
	iFile>>row>>col;
 
  img = new (nothrow)int * [row];
  for( i = 0 ; i < row ; i++ ) {
    img[i] = new (nothrow) int [col];
  }

  //puts image from source file into original_img
	initialize_original(iFile, img, row, col);
  
  if( !left_right( oFile , img , row , col , flag[2] ) )
    return -1;

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
