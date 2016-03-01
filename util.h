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
#define INIT -99 // -99
#define END -100 // -100

//function prototypes
int initialize_original(ifstream &iFile, int ** original_img, int row, int col);
bool find_patch( int ** img , int row , int col , vector<pixel> &patch , int color , bool debug_flag );
bool output_stroke( ofstream &oFile , vector<stroke> stks , bool debug_flag );
bool left_right_stroke(vector<pixel> &patch , stroke &prv_strk , vector<stroke> &strks , int &tank , bool debug_flag);
void fill_stroke( stroke &new_strk , const int action , pixel p , int oldcolor , int newcolor , bool debug_flag);
void find_xline( vector<pixel> &patch , vector<pixel> &line , vector<int> &line_indexes , bool debug_flag);
void get_consec_xline( vector<pixel> &line , vector<int> &line_indexes, bool debug_flag);
void sort_line(vector<pixel>& line, vector<int>& line_indexes,bool debug_flag);
void USAGE_STATEMENT(char* filename);