//This program is to alter ptg to txt.
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <istream>
#include "newpainterhelper.h"

using namespace std;


/******************************************************************************
 * By Chaeeun Lee
 *
 * This will take in the file and the original image pointer 
 * Will take the istream and the original_img array, 
 * the row # and the column #
 *
 * return 0   if all of original_img is filled
 * return -1  if problem with reading in img
 *****************************************************************************/
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

/******************************************************************************
 * By Brooke Padilla
 *
 * This will take in an image (a 2d array of ints representing colors) and will
 * search for the first pixel that matches that color.  Once it has found that
 * pixel it will add it to a vector called.  The function will then go through
 * and find all pixels that are adjacent to that pixel who have the same color.   
 * It will then repeat this process with all the pixels found. At the locations
 * in the original image the pixels will be set to 0 signifying that those 
 * spots no longer need painting.
 *
 * return true   if patch found
 * return false  if no patch is found
 *****************************************************************************/
bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color , bool debug ){
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
    
    for( i = max( curr.x - 1 , 0.0 ) ; i < min( curr.x + 2 , row ) ; ++i ){
      for( j = max( curr.y - 1 , 0.0 ) ; j < min( curr.y + 2 , col ) ; ++j ){
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
  //if(debug){cout << "util.c:90 function find_patch:\t\t exit " << endl;}
  return found_patch;
}//end find_patch

/******************************************************************************
 * By Chaeeun Lee
 *
 * Will output the vector of actions and their appropriate information
 *
 * return 0   SUCCESS
 * return -1  if action is not valid
 *****************************************************************************/
bool output_stroke( ofstream &oFile , vector<stroke> stks , bool debug_flag ){
  int i;
  cout << "entering output_stroke" << endl;
	for(i=0; i<(int)stks.size(); i++){
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
  cout << "exiting output_stroke" << endl;
  //if(debug_flag){cout << "util.c:125 function output_stroke:\t\t exit " << endl;}
	return true;
}



/******************************************************************************
 * By Brooke Padilla
 *
 * This will take in a vector of pixels, the previous stroke, a vector of 
 * strokes, and the paint tank level.  It will then find a stroke that the 
 * robot can do. It will also add on all other commands associated with 
 * stroke such as a refill if the tank is empty and moving to and from 
 * location. All paint strokes outputted will be from left to right. 
 * 
 * return true   if stroke found
 * return false  if patch is empty
 *****************************************************************************/
bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank , bool debug )
{
  /* variable declaration and initialization */
  bool refill = false;
	vector<pixel> line;
	vector<int> line_indexes; 
  pixel start;
  stroke new_strk;
  start.x = -1;
  start.y = -1;
  fill_stroke(new_strk,INIT,start, prv_strk.newcolor , prv_strk.newcolor);
  
  /* return false if patch is empty */
  if ( patch.empty() ) 
    return false;
  
  /* see if the last stroke was to paint */
  if( prv_strk.action == MOVE )
  {
    /* if tank is empty go fill it */ 
    cout << "inside move " << endl;
    if(tank == 0)
    {
      refill = true;
      refill_tank (tank , prv_strk , strks);
    }
    /* check to see if there is a stroke longer then length 1 starting from prv_strk */
    line.push_back( prv_strk.end );
    line_indexes.push_back( -1 );
    find_xline( patch , line , line_indexes , debug );
    if( line.size() != 1 )
    {
      patch.push_back(line[0]);
      line_indexes.at(0) = patch.size() - 1;
    }
  }//end if( prv_strk.action == PAINT
  
  /* if previous action was to switch the brush or you could not find a path for the brush */
  if( prv_strk.action == SWITCH_BRUSH || line.size() == 1 )
  {
    cout << "inside bad decisions" << endl;
    /* add in a lift for if last move was and had to refill */
    if( prv_strk.action == MOVE && !refill )
    {
      line.pop_back();
      line_indexes.pop_back();
      fill_stroke( new_strk , LIFT , line[0] ,  prv_strk.newcolor ,  prv_strk.newcolor );
      strks.push_back( new_strk );
    }
    /* find new line to hit up */
    line.push_back( patch[0] );
    patch.erase(patch.begin());
    line_indexes.push_back( -1 );
    find_xline( patch , line , line_indexes , debug );
    patch.push_back(line[0]);
    line_indexes.at(0) = patch.size() - 1;
    fill_stroke( new_strk , MOVE , line[0] ,  prv_strk.newcolor ,  prv_strk.newcolor );
    strks.push_back( new_strk );
    fill_stroke( new_strk , DROP , line[0] ,  prv_strk.newcolor ,  prv_strk.newcolor );
    strks.push_back( new_strk );
    cout << "exiting bad decisions" << endl;
  }
  else if( refill )
  {
    fill_stroke(new_strk, DROP, prv_strk.end,  prv_strk.newcolor ,  prv_strk.newcolor);
    strks.push_back(new_strk);
  }
    
  sort_line( line , line_indexes , debug );
  get_consec_xline( line , line_indexes , debug );

  find_last_strk (new_strk , patch , line , line_indexes , tank);
  if( debug && ( new_strk.oldcolor == 0 || new_strk.oldcolor > 8 )){ 
    cout << new_strk.action << " " << new_strk.oldcolor << " " << new_strk.newcolor << endl;
    cout << prv_strk.action << " " << refill << endl << endl;
  }
  strks.push_back( new_strk );
  set_stroke( prv_strk , new_strk );

	return true;
}


/******************************************************************************
 * By Brooke Padilla
 *
 * Fills given stroke with provided information.
 *****************************************************************************/
void fill_stroke( stroke &new_strk , const int action , pixel p , int oldcolor , int newcolor  )
{ 
  new_strk.action = action;
  //if(debug_flag){cout << "util.c:210 function fill_stroke:\t\t filled action " << endl;} 
  new_strk.end.x = p.x;
  //if(debug_flag){cout << "util.c:210 function fill_stroke:\t\t filled x " << endl;} 
  new_strk.end.y = p.y;
  //if(debug_flag){cout << "util.c:210 function fill_stroke:\t\t filled y " << endl;} 
  new_strk.oldcolor = oldcolor;
  //if(debug_flag){cout << "util.c:210 function fill_stroke:\t\t filled oldcolor " << endl;} 
  new_strk.newcolor = newcolor;
}

/******************************************************************************
 * By Brooke Padilla
 *
 * Set two strokes equal.
 *****************************************************************************/
 void set_stroke(stroke &dest, stroke &src)
 {
   dest.action = src.action;
   dest.end.x = src.end.x;
   dest.end.y = src.end.y;
   dest.oldcolor = src.oldcolor;
   dest.newcolor = src.newcolor;
 }
 
void find_last_strk (stroke &strk , vector<pixel> &patch , vector<pixel> &line , vector<int> &indexes , int &tank) 
 {
   int d_ind,i;
   while( tank != EMPTY && line.size() != 0 )
    {
      d_ind = indexes[0];
      fill_stroke( strk , MOVE , line[0] , strk.newcolor , strk.newcolor );
      line.erase(line.begin());
      patch.erase(patch.begin() + indexes[0]);
      indexes.erase(indexes.begin());
      tank--;
      // redo indexes
      for (i = 0 ; i < (int) indexes.size() ; i++){
        if(indexes.at(i) > d_ind){
          indexes.at(i)--;
        }
      }
    }
 }
 
 
/******************************************************************************
 * By Brooke Padilla
 *
 * Find all pixels in patch that are in the same line as it 
 *****************************************************************************/
void find_xline( vector<pixel> &patch , vector<pixel> &line , vector<int> &line_indexes , bool debug_flag )
{
  unsigned int i;
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

/******************************************************************************
 * By Brooke Padilla
 *
 * Will reduce line to only pixels that are consecutive.
 *****************************************************************************/
void get_consec_xline( vector<pixel> &line , vector<int> &line_indexes , bool debug_flag )
{
  bool consec = true;
  int i = 0;
  
  while(i < ((int) line.size()-1 ))
  {
      if( consec && ( line.at(i).y + 1 ) != line.at(i+1).y )
      {
        consec = false;
        i++;
      }
      else if( !consec )
      {
        line.erase(line.begin()+i);
        line_indexes.erase(line_indexes.begin()+i);
      }
      else
      {
        i++;
      }
  }
}

/******************************************************************************
 * By Chaeeun Lee
 *
 * Sorts a vector of pixels from lowest y to highest.
 *****************************************************************************/
void sort_line(vector<pixel>& line, vector<int>& line_indexes, bool debug_flag)
{
  int i, j, temp, temp2;

	for(i=0; i<((int)line.size()-1); i++){
		cout << "inside for loop1" << endl;
		for(j=0; j<((int)line.size()-i-1); j++){
			cout << "inside for loop2" << endl;
			if(line.at(j).y>line.at(j+1).y){
				temp=line.at(j+1).y;
				line.at(j+1).y=line.at(j).y;
				line.at(j).y=temp;
				temp2=line_indexes.at(j+1);
				line_indexes.at(j+1)=line_indexes.at(j);
				line_indexes.at(j)=temp2;
			}
		}
	}

	return;
}

void output_image(int ** img , int row , int col){
  int i , j ; 
  
  for ( i = 0 ; i < row ; i++ ){
    for ( j = 0 ; j < col ; j++ ) {
      cout << img[i][j] << " ";
    }
    cout << endl;
  }
}

int min(int x , int y){ 
  if (x < y){return x;}
  return y;
}
int max(int x , int y){ 
  if (x > y){return x;}
  return y;
}
void USAGE_STATEMENT(char* filename)
{
  cout << "Usage: " << filename << " [options]" << endl;
  cout << "-h \t\tPrint this message and exit" << endl;
  cout << "-ci\t\tWill ask for input file other than default" << endl;
  cout << "-co\t\tWill ask for output file other than default" << endl;
  cout << "-d \t\tWill turn on debug mode" << endl;
}

void refill_tank ( int & tank , stroke & prv_strk , vector<stroke> &strks) {
  stroke new_strk;
  tank = MAX_TANK;
  fill_stroke(new_strk, LIFT, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor );
  strks.push_back(new_strk);
  fill_stroke(new_strk, REFILL, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor );
  strks.push_back(new_strk);
}













