#include <cstdio>
#include <exception>

using namespace std;

class Canvas {
	private:
		int** canvas;
		int row;
		int col;
			
	public:
		Canvas(int,int);
		~Canvas();
		int* operator[](int);
		int getRow();
		int getCol();
		inline bool operator==(Canvas);
};

Canvas::Canvas(int row , int col){
	this->row = row;
	this->col = col;

	try{
		this->canvas = new int*[row];
		for(int i = 0 ; i < row ; i++){
			this->canvas[i] = new int[col];
		}
	}catch(exception& e){
		//Clean up after it.
		if(this->canvas != NULL){
			for(int i = 0 ; (i < row) && (this->canvas[i] != NULL) ; i++){
				delete[] this->canvas[i];
			}
			delete[] this->canvas;
		}
		perror("Unable to to Allocate space for canvas");
	}
}

Canvas::~Canvas(){
	for(int i = 0 ; (i < row) ; i++){
		delete[] this->canvas[i];
	}
	delete[] this->canvas;
}

int* Canvas::operator[](int row){ return this->canvas[row]; }
int Canvas::getRow(){ return this->row; }
int Canvas::getCol(){ return this->col; }

inline bool Canvas::operator==(Canvas canvas){
	if((this->row != canvas.getRow()) || (this->col != canvas.getCol())){
		return false;
	}
	for(int i = 0 ; i < this->row ; i++){
		for(int j = 0 ; j < this->col ; j++){
			if(this->canvas[i][j] != canvas[i][j]){
				return false;
			}			
		}
	}
	return true;
}

int main (){
	return 0;
}


