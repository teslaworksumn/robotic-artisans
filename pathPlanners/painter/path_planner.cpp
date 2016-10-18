//This program is to alter ptg to txt.

#include "path_planner.h"

/******************************************************************************
 * main funtions
 *****************************************************************************/

/******************
 * By Chaeeun Lee
 *
 * This will take in the file and the original image pointer will take the
 * istream and the original_img array, the row # and the column #
 *
 * return 0   if all of original_img is filled
 * return -1  if problem with reading in img
 *****************/
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

/******************
 * By Brooke Padilla
 *
 * Will print out usage statement.
 *****************/
void USAGE_STATEMENT(char* filename)
{
  cout << "Usage: " << filename << " [options]" << endl;
  cout << "-h \t\tPrint this message and exit" << endl;
  cout << "-ci\t\tWill ask for input file other than default" << endl;
  cout << "-co\t\tWill ask for output file other than default" << endl;
  cout << "-d \t\tWill turn on debug mode" << endl;
}

/******************
 * By Brooke Padilla
 *
 * Will set all the flags given to us from the command line arguments
 *****************/
bool set_flags( int argc , char *argv[] , char iFileName[] , char oFileName[], bool &debug )
{
  int i ;
  bool changed_of = false ;

  for( i = 1 ; i < argc ; i++)
  {
    if(strcmp(argv[i],"-h") == 0 )
    {
      USAGE_STATEMENT(argv[0]);
      return false;
    }
    else if( strcmp(argv[i],"-ci") == 0 )
    {
      strncpy( iFileName , argv[++i] , 64);
      if( !changed_of )
      {
		    strncpy( oFileName , iFileName , 64 );
		    oFileName[strlen(oFileName)-3] = 't';
        oFileName[strlen(oFileName)-2] = 'x';
        oFileName[strlen(oFileName)-1] = 't';
	    }
    }
    else if( strcmp(argv[i],"-co") == 0  )
    {
      changed_of=true;
      strncpy( oFileName , argv[++i] , 64);
    }
    else if( strcmp(argv[i],"-d") == 0  )
    {
      debug=true;
    }
    else
    {
      cout << "ERROR: UNKNOWN ARGUEMENT: " << argv[i] << endl << endl;
      USAGE_STATEMENT(argv[0]);
      return false;
    }
  }
  return true;
}

bool open_files( ifstream &iFile, ofstream &oFile,  char iFileName[] , char oFileName[], bool debug )
{
  if( debug )
  {
    cout << iFileName << endl << oFileName << endl;
  }
	iFile.open(iFileName); //read the file and make sure the file is open.
	if(iFile.fail())
	{
		cout<< "ERROR: " << iFileName << " failed to open" << endl;
		return false;
	}

	oFile.open(oFileName); //open the desired output file.
 	if(oFile.fail())
	{
 		cout<< "ERROR: " << oFileName << " failed to open" << endl;
		return false;
	}
	return true;
}

/******************
 * By Chaeeun Lee
 *
 * Will output the vector of actions and their appropriate information
 *
 * return 0   SUCCESS
 * return -1  if action is not valid
 *****************/
bool output_stroke( ofstream &oFile , vector<stroke> stks ){
  int i;
	for(i=0; i<(int)stks.size(); i++){
		switch(stks.at(i).action){
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

/******************************************************************************
 * end main funtions
 *****************************************************************************/

/******************************************************************************
 * left_right funtions
 *****************************************************************************/

/******************
 * By Brooke Padilla
 *
 * Core function for this painting style. Will take in an image and a ofstream
 * file and will out put instructions to make this image to the specified file.
 *
 * return false      Some instructions were not understood by output_stroke
 * return true       SUCCESS
 *****************/
bool left_right( ofstream &oFile , int **img , int row , int col , bool debug )
{
  vector<pixel> patch;
  stroke prv_strk;
  vector<stroke> strks;
  int i , tank;
  bool newpatch;
  pixel start;

  start.x = -1;
  start.y = -1;
  fill_stroke(prv_strk,INIT,start,0,0);

  /* Will loop through colors and paint from brightest to darkest */
  for ( i = 1 ; i < MAX_COLORS ; ++i ){
    /* Switch brush */
    if( prv_strk.action != INIT){
      fill_stroke( prv_strk , LIFT , prv_strk.end , prv_strk.newcolor , prv_strk.newcolor );
      strks.push_back(prv_strk);
    }
    fill_stroke( prv_strk , SWITCH_BRUSH , prv_strk.end , prv_strk.newcolor , i );
    tank = MAX_TANK;
    strks.push_back(prv_strk);

    /* find all patches of the current color */
    while( find_left_right_patch( img , row , col , patch , i , debug ) )
    {
      newpatch = true;

      /* create stroke until entire patch is painted */
      while( left_right_stroke(patch , prv_strk , strks , tank , newpatch , debug ) )
      {
        newpatch = false;
        /* convert the stroke coordinates to xy coordinates instead of row column */
        rc_to_xy(strks,row,col);
        /* output strokes */
        if( !output_stroke( oFile , strks ) )
			    return false;
        /* empty stroke vector */
		    while(!strks.empty())
		    {
			    strks.pop_back();
	      }
      }
    }//end: while(find_patch() != -1)
  }//end: for ( i = 1 ; i < MAX_COLORS ; ++i
  return true;
}

/******************
 * By Brooke Padilla
 *
 * Will find a group of (x,y) = (row#,col#) coordinates
 * that are of specified color , along the same row, and consecutive.
 * It will then set those spots to 0 in img.
 *
 * return false      Could not find any coordinates of specified color
 * return true       Could find coordinates of specified color
 *****************/
bool find_left_right_patch( int ** img , int row , int col , vector<pixel> &patch , int color , bool debug )
{
  int i,j;
  pixel curr;
  bool found_patch = false;

  /* find first occurance of color in image */
  for ( i = 0 ; i < row && !found_patch ; ++i ){
    for ( j = 0 ; j < col && !found_patch ; ++j ) {
      if( img[i][j] == color ){
        //set
        found_patch = true;

        curr.x = i ;
        curr.y = j ;
        patch.push_back(curr);
        img[i][j] = 0 ;
      }//if( img[i][j] == color )
    }//for ( j =
  }//for ( i=

  if( found_patch )
  {
    i = patch.at(0).x;
    j = patch.at(0).y + 1;
    /* find all consecutive pixels to its right of the same color */
    while( ( j < col ) && ( img[i][j] == color ) )
    {
      curr.x = i ;
      curr.y = j;
      patch.push_back( curr ) ;
      img[i][j] = 0 ;
    }
  }

  return found_patch;
}
/******************
 * By Brooke Padilla
 *
 * Will take a patch of coordinates found from the find_left_right_patch
 * and will attempt to paint along this patch until either the patch
 * or the tank run out. It will also push on any actions that need to
 * take place for the stroke to work.
 *
 * return false  patch is empty
 * return true   stroke found
 *****************/
bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank , bool newpatch , bool debug )
{
  bool lifted = false;
  bool moved = false;

  /* return false if patch is empty */
  if ( patch.empty() )
    return false;

  /* if this is the first time the patch is being touch after leaving findlrpatch then...*/
  if( newpatch ) {
    /* if last move was to move or drop the brush lift */
    if( prv_strk.action == MOVE || prv_strk.action == DROP )
    {
      fill_stroke(prv_strk, LIFT, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
      strks.push_back(prv_strk);
    }
    /* then move to the first position in patch */
    fill_stroke(prv_strk, MOVE , patch.at(0) , prv_strk.newcolor, prv_strk.newcolor);
    strks.push_back(prv_strk);
    patch.erase(patch.begin());
    lifted = true;
  }

  /* if tank is empty refill*/
  if ( tank == EMPTY )
  {
    /* if brush is touching canvas lift before refilling */
    if( !lifted )
    {
      fill_stroke(prv_strk, LIFT, prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
      strks.push_back(prv_strk);
    }
    fill_stroke(prv_strk, REFILL , prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
    strks.push_back(prv_strk);
    tank = MAX_TANK;
    lifted = true;
  }

  /* if the brush is currently lifted then drop */
  if( lifted )
  {
    fill_stroke(prv_strk, DROP , prv_strk.end, prv_strk.newcolor, prv_strk.newcolor);
    strks.push_back(prv_strk);
    tank--;
  }

  /* find the end of stroke: will be when either the tank is empty or patch is empty */
  while( tank != EMPTY && !patch.empty() )
  {
    tank--;
    fill_stroke(prv_strk, MOVE , patch.at(0) , prv_strk.newcolor, prv_strk.newcolor);
    patch.erase(patch.begin());
    moved = true;
  }
  if ( moved )
    strks.push_back(prv_strk);

  return true;
}

/******************************************************************************
 * End of left_right funtions
 *****************************************************************************/

/******************************************************************************
 * Beginning of possibly helpful functions
 *****************************************************************************/

/******************
 * By Brooke Padilla
 *
 * Set two strokes equal.
 *****************/
void set_stroke(stroke &dest, stroke &src)
{
  dest.action = src.action;
  dest.end.x = src.end.x;
  dest.end.y = src.end.y;
  dest.oldcolor = src.oldcolor;
  dest.newcolor = src.newcolor;
}

/******************
 * By Brooke Padilla
 *
 * Will convert vectors that have x = row # y = col # to a regular xy
 * coordinate system with the (0,0) on the bottom left corner.
 *****************/
void rc_to_xy(vector <stroke> &strks, int row , int col)
{
  int x;
  int y;
  int i;

  for ( i = 0 ; i < (int) strks.size() ; i++ ) {
    x = strks.at(i).end.y;
    y = row - 1 - strks.at(i).end.x;
    strks.at(i).end.x = x;
    strks.at(i).end.y = y;
  }
}

/******************
 * By Brooke Padilla
 *
 * Will output the current image. Useful for debugging.
 *****************/
void output_image(int ** img , int row , int col){
  int i , j ;

  for ( i = 0 ; i < row ; i++ ){
    for ( j = 0 ; j < col ; j++ ) {
      cout << img[i][j] << " ";
    }
    cout << endl;
  }
}

/******************
 * By Brooke Padilla
 *
 * A general patch finder that will find a group of coordinates (x,y) = (row#,col#)
 * of the specified color that are next to eachother.
 *
 * return true   if patch found
 * return false  if no patch is found
 *****************/
bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color , bool debug ){
  vector<pixel> unexplored_pixels;
  int i,j;
  bool found_patch = false;
  pixel curr , edge , temp;

  /* find first occurence of color in img */
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

  /* find all connected pixels */
  while( !unexplored_pixels.empty() ){
    temp = unexplored_pixels.back() ;
    curr.x = temp.x;
    curr.y = temp.y;
    unexplored_pixels.pop_back() ;
    patch.push_back(curr) ;

    for( i = fmax( (float)curr.x - 1 , 0.0 ) ; i < fmin( (float)curr.x + 2 , (float) row ) ; ++i ){
      for( j = fmax( (float) curr.y - 1 , 0.0 ) ; j < fmin( (float) curr.y + 2 , (float) col ) ; ++j ){
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

/******************
 * By Chaeeun Lee
 *
 * Will take a vector of pixels and a vector of ints. Each int in the int
 * vector cooresponds with a pixel in the pixel vector.  This int represents
 * the pixels index within a patch of color. This function sorts the pixels
 * by its y value in increasing order. It will also make sure the corresponding
 * index int is moved with it.
 *****************/
void sort_line(vector<pixel>& line, vector<int>& line_indexes, bool debug_flag)
{
  int i, j, temp, temp2;

	for(i=0; i<((int)line.size()-1); i++){
		for(j=0; j<((int)line.size()-i-1); j++){
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
}

/******************
 * By Brooke Padilla
 *
 * Fills given stroke with provided information.
 *****************/
void fill_stroke( stroke &new_strk , const int action , pixel p , int oldcolor , int newcolor  )
{
  new_strk.action = action;
  new_strk.end.x = p.x;
  new_strk.end.y = p.y;
  new_strk.oldcolor = oldcolor;
  new_strk.newcolor = newcolor;
}
