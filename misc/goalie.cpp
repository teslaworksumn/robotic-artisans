#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	ofstream output;
	string name;
	int rows, cols, colors;
	srand(time(NULL));
	
	cout << "What shall this work of art be named? ";
	getline(cin,name);
	output.open(name.c_str());
	if(output.fail())
	{
		cout << "Welp, you suck at naming.\n";
		return 0;
	}
	cout << "How tall? ";
	cin >> rows;
	cout << "How wide? ";
	cin >> cols;
	cout << "How many colors? ";
	cin >> colors;
	cout << "Lets begin shall we\n";
	
	output << rows << " " << cols << endl;
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			output << rand()%colors+1 << " ";
		}
		output << endl;
	}
	
	output.close();
	cout << "Your painting is available in " << name << " thank you.\n";
}
