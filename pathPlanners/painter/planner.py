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


def find_left_right_patch(image, patch, color, debug):
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



				

				# this seems like opposite of what it should be.



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
