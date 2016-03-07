/******************************************************************************
 * main functions 
 * 
 * This function will take a ptg img and will give out a set of instruction in
 * the form of a txt file that will hold instruction to how to paint it. 
 * 
 *****************************************************************************/

//This program is to alter ptg to txt.
#include "newpainterhelper.h"

int main( int argc , char *argv[] ){
	//declare variables
	int i;
	int row;
	int col;
	int **img = NULL;
	ifstream iFile;
	ofstream oFile;
  bool flag[] = {false, false, false};
  

  /* set flags */
  if( !set_flags(argc,argv,flag ) ) 
    return -1;
  
  /* open files */
  if( !open_files(iFile, oFile, flag) ) 
    return -1;
  
  /* read in rows and columns */
	iFile>>row>>col;
 
  /* initialize img 2d array */
  img = new (nothrow)int * [row];
  for( i = 0 ; i < row ; i++ ) {
    img[i] = new (nothrow) int [col];
  }
	initialize_original(iFile, img, row, col);
  
  /* We will hopefully start being able to switch between styles here */
  /* run left_right function that will print out instructions of a certain style */
  if( !left_right( oFile , img , row , col , flag[2] ) )
    return -1;

  /* free up pointer */
  for ( i = 0 ; i < row ; i++ ){
    delete [] img [i];
  }  
  delete [] img;
  
  /* close files */
  iFile.close();
  oFile.close();
  
  /* return success */
	return 0;
}
