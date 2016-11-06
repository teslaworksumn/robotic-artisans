import collections
Pixel = collections.namedtuple('Pixel', 'x y')

# Global constants
MAX_COLORS = 9 # including no paint 0 + 1-8 colMAX_EMOVE -1 # -1 x y
MAX_TANK = 5
EMPTY = 0

MOVE = -1 # -1 x y
LIFT = -2 # -2 
DROP = -3 # -3
REFILL = -4 # -4 x0 y0 color
SWITCH_BRUSH = -5 # -5 x0 y0 color_prev color_next 
INIT = -99 # -99
END = -100 # -100

class Stroke(object):

	@staticmethod
	def output_stroke(out, strokes):
		""" save strokes to file """
		for stroke in strokes:
			out.write(stroke.output())
			
	def __init__(self, action, end, oldcolor, newcolor):
		self.action = action;
		self.end = end;
		self.oldcolor = oldcolor;
		self.newcolor = newcolor;

	def output(self):
		""" represent stroke as brush command """
		action = self.action
		end = self.end
		if action == MOVE:
			output = "%d %d %d\n" % (action, end.x, end.y)
		elif action == REFILL:
			output = "%d %d %d %d\n" % (action, end.x, end.y, self.oldcolor)
		elif action	== SWITCH_BRUSH:
			output = "%d %d %d %d %d\n" % (action, end.x, end.y, self.oldcolor, self.newcolor)
		elif action == LIFT or action == DROP:
			output = "%d\n" % action
		else:
			raise ValueError("stroke.action had invalid value of %d" % action)
		return output
