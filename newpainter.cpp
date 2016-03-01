//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <istream>
#include <string.h>

#include "util.h"

using namespace std;

int main( int argc , char *argv[] ){
	//declare variables
	int i,j;
	int row;
	int col;
	int **img = NULL;
	int tank = MAX_TANK;
	char iFileName[64] = "lisa.ptg";
	ifstream iFile;
	char oFileName[64] = "newpainter_result.txt";
	ofstream oFile;
	vector<pixel> patch;//patch is the color patch
	stroke prv_strk;
  vector<stroke> strks;
  pixel start;
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
  
  start.x = -1;
  start.y = -1;
  fill_stroke(prv_strk,INIT,start,0,0,flag[2]);
  
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
  if(flag[2]){cout<<"line 73: \tinput file opened"<<endl;}
  
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
  if(flag[2]){cout<<"line 86: \toutput file opened"<<endl;}
  
	iFile>>row>>col;
 
  img = new (nothrow)int * [row];
  for( i = 0 ; i < row ; i++ ) {
    img[i] = new (nothrow) int [col];
  }

  //puts image from source file into original_img
	initialize_original(iFile, img, row, col);
  if(flag[2]){cout<<"line 97: \tinitialized img"<<endl;}
  
  //will loop through to check for every color
  for ( i = 1 ; i < MAX_COLORS ; ++i ){
    if( prv_strk.action != INIT){
      fill_stroke( prv_strk , LIFT , prv_strk.end , prv_strk.newcolor , prv_strk.newcolor , flag[2]);
      if(flag[2]){cout<<"newpainter.c:210 function main:\t\t able to fill prv_strk with information"<<endl;}
      strks.push_back(prv_strk);
      if(flag[2]){cout<<"newpainter.c:105 function main:\t\t able to push INIT stroke onto strks vector"<<endl;}
    }
    fill_stroke( prv_strk , SWITCH_BRUSH , prv_strk.end , prv_strk.newcolor , i ,flag[2]);
    strks.push_back(prv_strk);
    if(flag[2]){cout<<"newpainter.c:110 function main:\t\t able to push SWITCH BRUSH color: " << i <<endl;}
    //will loop through until every patch of color i is found
    while( find_patch( img , row , col , patch , i , flag[2] ) != -1 )
    {
      if(flag[2]){cout<<"newpainter.c:105 function main:\t\t able to find patch"<<endl;}
      //will loop through until all strokes are a made from patch 
      while( left_right_stroke(patch,prv_strk, strks, tank , flag[2]) != -1 )
      {
        //output instruction to file 
        if( !output_stroke( oFile , strks , flag[2] ) ){ return -1;}
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
