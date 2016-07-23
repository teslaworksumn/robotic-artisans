#include <iostream>

using namespace std;

class Painter {
	public:
		virtual ~Painter();
		virtual void updateCanvas(Canvas canvas);
		virtual Canvas getCanvas();
		virtual void setGoal();
		virtual Stroke getNextStroke();
};