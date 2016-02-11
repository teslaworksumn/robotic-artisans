#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;


//********************************************************************//
//                            CLASSES                                 //
//********************************************************************//

class Painter
{
	private:
		int rows, cols, size;
		int x, y;
		int color, tank, capacity;
		int parentIndex;
		bool down;
		double cost;
		double heur;
		string action;
		int canvas[5000];
	public:
		Painter(int rows, int cols, int capacity);

		int getRows() {return rows;}
		int getCols() {return cols;}
		int getSize() {return size;}
		int XPos() {return x;}
		int YPos() {return y;}
		int Color() {return color;}
		int Tank() {return tank;}
		double Cost() {return cost;}
		double Heur() {return heur;}
		bool IsDown() {return down;}
		void Drop();
		void Lift() {down = false; cost = cost + 10;}

		string getAction() {return action;}
		void setAction(string str) {action = str;}
		int getParent() {return parentIndex;}
		void setParent(int index) {parentIndex = index;}

		//debugging commands
		void setCost(double c) {cost = c;}
		void setHeur(double h) {heur = h;}
		void setXPos(int new_x) {x = new_x;}
		void setYPos(int new_y) {y = new_y;}
		void setcanvas(int i, int color) {canvas[i] = color;}
		void setTank(int t) {tank = t;}

		int Canvas(int i) {return canvas[i];}
		int Canvas(int x, int y) {return canvas[(x-1)*cols+(y-1)];}

		void Print();
		void GoTo(int q, int r);
		void GoandPaint(int q, int r);
		void ChangeColor(int g);
};

bool Goal_Test(Painter current_state);


//********************************************************************//
//                            MAIN                                    //
//********************************************************************//

int main()
{
	string painting;
	cout << "What shall we paint today? \n";
	getline(cin,painting);
	cout << "\n Let's Begin \n";
	
	ifstream in_stream;
	in_stream.open(painting.c_str());
	if(in_stream.fail())
	{
		cout << "You uncouth lout, I can't paint this!\n";
		return 0;
	}

	int prows, pcols;
	in_stream >> prows >> pcols;

	int goal[prows * pcols];

	for(int i=0; i < prows*pcols; i++)
	{
		in_stream >> goal[i];
	}
	int u=0;
	//display goal canvas state
	cout << "Goal State:" << endl;
	for(int i=0; i<prows; i++)
	{
		for(int j=0; j<pcols; j++)
		{
			cout << goal[u] << " " ;
			u++;
		}
		cout << endl;
	}

	Painter davinci(prows,pcols,10);
	//display initial canvas state
	cout << endl << "Initial State:" << endl;
	davinci.Print();

	vector<Painter> Explored_Painters;
	int Explored_Painter_counter = 0;
	vector<Painter> Unexplored_Painters;
	int Unexplored_Painter_counter = 0;

	Unexplored_Painters.push_back(davinci);	//add painter to end of vector
	Unexplored_Painter_counter++;

	Painter Current_Painter = davinci;
	Painter Child_Painter = davinci;
	int cycle_counter = 0;

	stringstream string_stream;	//generate string stream for creating action commands

	while (Goal_Test(Current_Painter) && (cycle_counter < 100000))
	{
	   	int current_painter_cost;
	   	int current_painter_index = 0;
	   	int minimum_painter_cost = Unexplored_Painters[0].Cost() + Unexplored_Painters[0].Heur();
	   	Current_Painter = Unexplored_Painters[0];
	   	//select painter for expansion
	   	for(int i = 0; i < Unexplored_Painter_counter; i++)
	   	{
	   		current_painter_cost = Unexplored_Painters[i].Cost() + Unexplored_Painters[i].Heur();
	   		if(current_painter_cost < minimum_painter_cost)
	   		{
	   		   	minimum_painter_cost = current_painter_cost;
	   		   	Current_Painter = Unexplored_Painters[i];
	   		   	current_painter_index = i;
	   		}
	    }


	   	//expand node and generate children
	   	//first check if paint is on the brush, if not generate only available child node
	   	if(Current_Painter.Color() == 0)
	    {
	   		Child_Painter = Current_Painter;
	   		Child_Painter.ChangeColor(Child_Painter.Color()+1);
	   		//store action command for new child based on parent painter
	   		string_stream << "Change color to " << Child_Painter.Color();
	   		Child_Painter.setAction(string_stream.str());
	   		string_stream.str("");	//clear the string stream
	   		Child_Painter.setParent(Explored_Painter_counter);
	   		Unexplored_Painters.push_back(Child_Painter);
	   		Unexplored_Painter_counter++;
	   	}
	   	//if some kind of paint is on the brush, the following action options are available
	    else
	    {
	    	//if brush is down
	    	if(Current_Painter.IsDown())
	    	{
  				//checks for changing color only need to be done when brush is down
  				//since tank will run out, or valid elements will run out only when
  				//brush is in down position
  				//check if any elements still need to be colored
  				//first claim that no elements need a color
  				bool elements_dont_need_color = 1;
  				//loop through all elements
  				for(int j = 0; j < Current_Painter.getSize(); j++)
  				{
  					//check if current color on brush is same as a goal element
  					if(Current_Painter.Color() == goal[j])
  					{
  						//check if that same position in current canvas state is already painted, if not, valid move
  					   	if(Current_Painter.Color() != Current_Painter.Canvas(j))
  					   	{
  					   		//if element color is in goal, and it isn't currently that color, then it is false
  					   	    //that no elements need that color
  					   	   	elements_dont_need_color = 0;
  					   	}
  					 }
  				}


  				//if the tank is empty or there are no remaining elements needing this color, then refill or change color
  				//no other actions can be executed until this is done
  				if((Current_Painter.Tank() == 0) || elements_dont_need_color)
  				{
  					//if no elements need a color, then change color
  					if(elements_dont_need_color)
  					{
  						Child_Painter = Current_Painter;
  						Child_Painter.ChangeColor(Child_Painter.Color()+1);
  				   		string_stream << "Move back to base and change color to " << Child_Painter.Color();
  				   		Child_Painter.setAction(string_stream.str());
  				   		string_stream.str("");	//clear the string stream
  				   		//cout << Child_Painter.getAction() << endl;
  				   		Child_Painter.setParent(Explored_Painter_counter);
  						Unexplored_Painters.push_back(Child_Painter);
  						Unexplored_Painter_counter++;
  					}
  					//if not true that no elements need color, then keep same color, refill
  					else
  					{
  						Child_Painter = Current_Painter;
  						Child_Painter.ChangeColor(Child_Painter.Color());
  				   		string_stream << "Move back to base and refill color " << Child_Painter.Color();
  				   		Child_Painter.setAction(string_stream.str());
  				   		string_stream.str("");	//clear the string stream
  				   		//cout << Child_Painter.getAction() << endl;
  				   		Child_Painter.setParent(Explored_Painter_counter);
  						Unexplored_Painters.push_back(Child_Painter);
  						Unexplored_Painter_counter++;
  					}
  				}
  				//if above not true, then all the following actions are valid
  				else
  				{
				//add action for alternating up/down as long as above canvas
					if((Current_Painter.XPos() != -1) && (Current_Painter.YPos() != -1))
					{
						Child_Painter = Current_Painter;
						Child_Painter.Lift();
  				   		string_stream << "Lift brush";
  				   		Child_Painter.setAction(string_stream.str());
  				   		string_stream.str("");	//clear the string stream
  				   		//cout << Child_Painter.getAction() << endl;
  				   		Child_Painter.setParent(Explored_Painter_counter);
						Unexplored_Painters.push_back(Child_Painter);
						Unexplored_Painter_counter++;
					}

					//add action for moving when down, can only move vertically or horizontally one element
					//first need to detirmine the index of the four neighboring elements

					int new_index;
					//test if the space above current position is valid
					//not valid would be an x of zero since smallest x = 1 on canvas
					if(Current_Painter.XPos()-1 != 0)
					{
						//then check if color at that location matches brush color
						//to do this, must convert x and y at this new location to an index value
						//left index should be one index value less
						//based on algorithm i = (x-1)*cols + (y-1)
						new_index = (((Current_Painter.XPos() - 1) - 1) * Current_Painter.getCols()) + (Current_Painter.YPos() - 1);

						if(Current_Painter.Color() == goal[new_index])
						{
		    				if(Current_Painter.Color() != Current_Painter.Canvas(new_index))
		    				{
								Child_Painter = Current_Painter;
								Child_Painter.GoTo(Current_Painter.XPos()-1,Child_Painter.YPos());
								string_stream << "Move to " << Child_Painter.XPos() << "," << Child_Painter.YPos() << " painting it " << Child_Painter.Color() << " without lifting";
								Child_Painter.setAction(string_stream.str());
								string_stream.str("");	//clear the string stream
								//cout << Child_Painter.getAction() << endl;
								Child_Painter.setParent(Explored_Painter_counter);
								Unexplored_Painters.push_back(Child_Painter);
								Unexplored_Painter_counter++;
							}
						}
					}

					//repeat process for element below
					//this will not be valid if x exceeds the number of rows
					if(Current_Painter.XPos()+1 < (Current_Painter.getRows()+1))
					{
						//find index of element below
						new_index = (((Current_Painter.XPos() + 1) - 1) * Current_Painter.getCols()) + (Current_Painter.YPos() - 1);
						if(Current_Painter.Color() == goal[new_index])
						{
		    				if(Current_Painter.Color() != Current_Painter.Canvas(new_index))
		    				{
								Child_Painter = Current_Painter;
								Child_Painter.GoTo(Current_Painter.XPos()+1,Child_Painter.YPos());
								string_stream << "Move to " << Child_Painter.XPos() << "," << Child_Painter.YPos() << " painting it " << Child_Painter.Color() << " without lifting";
								Child_Painter.setAction(string_stream.str());
								string_stream.str("");	//clear the string stream
								//cout << Child_Painter.getAction() << endl;
								Child_Painter.setParent(Explored_Painter_counter);
								Unexplored_Painters.push_back(Child_Painter);
								Unexplored_Painter_counter++;
		    				}
						}
					}

					//repeat process for element to the left
					//this will not be valid if y is less than 1
					if(Current_Painter.YPos()-1 != 0)
					{
						new_index = ((Current_Painter.XPos() - 1) * Current_Painter.getCols()) + ((Current_Painter.YPos() - 1) - 1);

						if(Current_Painter.Color() == goal[new_index])
						{
		    				if(Current_Painter.Color() != Current_Painter.Canvas(new_index))
		    				{
								Child_Painter = Current_Painter;
								Child_Painter.GoTo(Current_Painter.XPos(),Child_Painter.YPos()-1);
								string_stream << "Move to " << Child_Painter.XPos() << "," << Child_Painter.YPos() << " painting it " << Child_Painter.Color() << " without lifting";
								Child_Painter.setAction(string_stream.str());
								string_stream.str("");	//clear the string stream
								//cout << Child_Painter.getAction() << endl;
								Child_Painter.setParent(Explored_Painter_counter);
								Unexplored_Painters.push_back(Child_Painter);
								Unexplored_Painter_counter++;
		    				}
						}
					}

					//finally repeat for element to the right
					//will not be valid if y exceeds the number of coloumns
					if(Current_Painter.YPos()+1 < (Current_Painter.getCols()+1))
					{
						//find index of element below
						new_index = ((Current_Painter.XPos() - 1) * Current_Painter.getCols()) + ((Current_Painter.YPos() + 1) - 1);
						if(Current_Painter.Color() == goal[new_index])
						{
		    				if(Current_Painter.Color() != Current_Painter.Canvas(new_index))
		    				{
								Child_Painter = Current_Painter;
								Child_Painter.GoTo(Current_Painter.XPos(),Child_Painter.YPos()+1);
								string_stream << "Move to " << Child_Painter.XPos() << "," << Child_Painter.YPos() << " painting it " << Child_Painter.Color() << " without lifting";
								Child_Painter.setAction(string_stream.str());
								string_stream.str("");	//clear the string stream
								//cout << Child_Painter.getAction() << endl;
								Child_Painter.setParent(Explored_Painter_counter);
								Unexplored_Painters.push_back(Child_Painter);
								Unexplored_Painter_counter++;
		    				}
						}
					}
  				}

	    	}
	    	//if brush is not down
	    	else if(!Current_Painter.IsDown())
	    	{
	    		/*  Do not really need this as painter will always move down after moving
	    		 *  and you will never move to -1,-1 unless changing color which won't happen when
	    		 *  the brush is up, so made new action that combines these to decrease search nodes.
	    		//add action for alternating up/down as long as above canvas
	    		if((Current_Painter.XPos() != -1) && (Current_Painter.YPos() != -1))
	    		{
	    			Child_Painter = Current_Painter;
	    		   	Child_Painter.Drop();
	    		   	Unexplored_Painters.push_back(Child_Painter);
	    		   	Unexplored_Painter_counter++;
	    		}
	    		*/

	    		//loop through all elements in canvas and check if element color matches brush color
	    		for(int i=0; i<Current_Painter.getSize(); i++)
	    		{
	    			//check if current color on brush is same as a goal element
	    			if(Current_Painter.Color() == goal[i])
	    			{
	    				//check if that same position in current canvas state is already painted, if not, valid move
	    				if(Current_Painter.Color() != Current_Painter.Canvas(i))
	    				{
							int x_position_from_index = (i / Current_Painter.getCols()) + 1;
							int y_position_from_index = (i % Current_Painter.getCols()) + 1;
							Child_Painter = Current_Painter;
							Child_Painter.GoandPaint(x_position_from_index,y_position_from_index);
							string_stream << "Move to " << Child_Painter.XPos() << "," << Child_Painter.YPos() << " and move down to color it " << Child_Painter.Color();
					   		Child_Painter.setAction(string_stream.str());
					   		//cout << Child_Painter.getAction() << endl;
					   		string_stream.str("");	//clear the string stream
					   		Child_Painter.setParent(Explored_Painter_counter);
							Unexplored_Painters.push_back(Child_Painter);
							Unexplored_Painter_counter++;
						}
	    			}
	    		}
	    	}
	    }

	   	//move fully expanded node into the explored vector and delete it from unexplored vector
	   	Explored_Painters.push_back(Current_Painter);
	   	Explored_Painter_counter++;
	   	Unexplored_Painters.erase(Unexplored_Painters.begin() + current_painter_index);
	   	Unexplored_Painter_counter--;
		cycle_counter = cycle_counter + 1;
		cout << endl << cycle_counter;
		cout << endl << endl;
		Current_Painter.Print();
	}
	cout << endl << "solution found with " << cycle_counter << " Painters expanded" << endl << "Final State" << endl;
	Current_Painter.Print();
	//now reassemble the list of actions in solution
	vector<string> reverse_Action_list;
	cout << "Solution action cost: " << Current_Painter.Cost() <<endl << endl;
	double action_count = 0;
	while(Current_Painter.getParent() != 0)
	{
		reverse_Action_list.push_back(Current_Painter.getAction());
		action_count++;
		Current_Painter = Explored_Painters[Current_Painter.getParent()];
	}

	reverse_Action_list.push_back(Current_Painter.getAction());
	action_count++;
	cout << "Total actions: " << action_count << endl << endl;
	for(double i = action_count-1; i > -1; i--)
	{
		cout << reverse_Action_list[i] << endl;
	}

	return 0;
}

//********************************************************************//
//                            CLASS FUNCTIONS                         //
//********************************************************************//

Painter::Painter(int irows, int icols, int icapacity)
{
	rows=irows;
	cols=icols;
	size=rows*cols;
	for(int i=0; i<rows*cols; i++)
	{
		canvas[i]=0;
	}
	capacity = icapacity;
	x=-1;
	y=-1;
	color=0;
	tank=0;
	cost =0;
	heur=50*rows*cols;
	parentIndex = 0;
	action = "stretch canvas";
	down = false;
}
void Painter::Drop()
{
	down = true;
	canvas[(x-1)*cols+(y-1)]=color;
	tank--;
	heur = heur - 50;
	cost++;
}
void Painter::Print()
{
	int p=0;
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			cout << canvas[p] << " ";
			p++;
		}
		cout << endl;
	}
	cout << endl;
}


void Painter::GoTo(int xNew, int yNew)
{
	if(down == false)
	{
		cost += round(sqrt((xNew-x)*(xNew-x)+(yNew-y)*(yNew-y)));
		x=xNew;
		y=yNew;
	}
	else
	{
		x=xNew;
		y=yNew;
		cost++;
		canvas[(x-1)*cols+(y-1)]=color;
		tank--;
		heur = heur - 50;
	}
}

void Painter::GoandPaint(int xNew, int yNew)
{
	if(down == false)
	{
		cost += round(sqrt((xNew-x)*(xNew-x)+(yNew-y)*(yNew-y)));
		x=xNew;
		y=yNew;
		Drop();
	}
	else
	{
		x=xNew;
		y=yNew;
		cost++;
		canvas[(x-1)*cols+(y-1)]=color;
		tank--;
		heur = heur - 50;
	}
}

void Painter::ChangeColor(int g)
{
	if(down)
	{
	Lift();
	}
	GoTo(-1,-1);
	color=g;
	tank=capacity;
	cost++;
}

//********************************************************************//
//                            GLOBAL FUNCTIONS                        //
//********************************************************************//

bool Goal_Test(Painter current_state)
{
	for(int i = 0; i<current_state.getSize(); i++)
	{
		if(current_state.Canvas(i) == 0)	//check if element of current node is 0
		{
			return 1;	//if at least one element is 0, return true
		}

	}
return 0;	//otherwise return 0 if no elements found equal 0
}
