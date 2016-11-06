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


def find_left_right_patch(image, patch, color, debug=False):
	"""
	Find the first group of one or more (x,y) = (row#,col#) coordinates
 	that are of specified color, along the same row, and consecutive.
 	Then set those spots to 0 in img.
 	Add the locations to the list patch
 
 	return false  :    Could not find any coordinates of specified color
 	return true   :    Could find coordinates of specified color
 	"""

	def find_all_consecutive_pixels_to_its_right(i, j):
		row = image[i]
		while j < len(row) and image[i][j] == color:
			patch.append ( Pixel(i,j) )
			image[i][j] = 0
			j += 1

	def find_first_occurence_of_color():
		for i, row in enumerate(image):
			for j, entry in enumerate(row):
				if entry == color:
					find_all_consecutive_pixels_to_its_right(i, j)
					return True
		return False

	return find_first_occurence_of_color()


# IN PROGRESS
def left_right(oFile, img, row, col, debug):
	strokes = []
	patch = []
	start = Pixel(-1,-1)
	previous_stroke = Stroke(
		action=INIT, # I think this is a garbage value that will be overwritten
		end=start, 
		oldcolor=0,
		newcolor=0
	)

	# loop through colors from brightest to darkest
	for color in range(1, MAX_COLORS):
		previous_stroke = Stroke.copy(previous_stroke)

		if previous_stroke.action != INIT:
			previous_stroke.action = LIFT
			strokes.add(previous_stroke)

		previous_stroke.action = SWITCH_BRUSH;
		previous_stroke.newcolor = color
		tank = MAX_TANK
		strokes.add(previous_stroke)

		# find all patches of the current color
		while find_left_right_patch(image,patch,color):
			newpatch = True
			# create stroke until the entire patch is painted

def left_right_stroke(patch, previous_stroke, strokes, tank, newpatch):
	previous_stroke = Stroke.copy(previous_stroke)
	lifted = False
	moved = False

	# If Patch is empty, do nothing.
	if not patch:
		return False

	# If this is the first time the patch is being touch after leaving findlrpatch then ...
	if (newpatch):
		# If the last action was to MOVE or DROP the brush then LIFT the brush
		if previous_stroke.action == MOVE or previous_stroke.action == DROP:
			previous_stroke.action = LIFT
			strokes.append(previous_stroke)
			previous_stroke = Stroke.copy(previous_stroke)
		# Then move to the first position in patch.




class Stroke(object):


	@classmethod
	def copy(cls, other):
		""" Copy another stroke. """
		return cls(other.action, other.end, other.oldcolor, other.newcolor)

	@staticmethod
	def output_strokes(out, strokes):
		""" Save list of strokes to a file. """
		for stroke in strokes:
			out.write(stroke.output())
			
	def __init__(self, action, end, oldcolor, newcolor):
		self.action = action;
		self.end = end;
		self.oldcolor = oldcolor;
		self.newcolor = newcolor;

	
	def output(self):
		""" Represent stroke as brush comsmand. """
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

class StrokeStack(object):

	def __init__(self, start_stroke):
		self.strokes = []
		self.strokes.append(start_stroke)

	def push_instruction(self, action=None, end=None, oldcolor=None, newcolor=None):
		current = self.strokes[-1]
		new_stroke = Stroke.copy(current)
		if action is not None:
			new_stroke.action = action
		if end is not None:
			new_stroke.end = end
		if oldcolor is not None:
			new_stroke.oldcolor = oldcolor
		if newcolor is not None:
			new_stroke.newcolor = newcolor
		self.strokes.append(new_stroke)

	def peek(self):
		return self.strokes[-1]








