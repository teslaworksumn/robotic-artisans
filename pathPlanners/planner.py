"""
This script takes a ptg file and converts it to a sequence of "stroke"
instructions, which can easily be converted to GCODE.
"""

import collections
Pixel = collections.namedtuple('Pixel', 'y x')

# global constants
# Commented are how the commands will operate.
MAX_COLORS = 9  # including no paint 0 + 1-8 colMAX_EMOVE -1 # -1 x y
MAX_TANK = 5
EMPTY = 0

MOVE = -1  # -1 x y
LIFT = -2  # -2
DROP = -3  # -3
REFILL = -4  # -4 x0 y0 color
SWITCH_BRUSH = -5  # -5 x0 y0 color_prev color_next
INIT = -99  # -99
END = -100  # -100


def find_left_right_patch(image, patch, color):
    """
    Find the first group of one or more (x,y) = (row#,col#) coordinates
    that are of specified color, along the same row, and consecutive.
    Then set those spots to 0 in img.
    Add the locations to the list patch

    return false  :    Could not find any coordinates of specified color
    return true   :    Could find coordinates of specified color
    """

    def find_consecutive_to_right(i, j):
        """
        Find pixels to the right (increasing x coordinate)
        of the pixel with the same color.
        """
        row = image[i]
        while(j < len(row) and image[i][j] == color):
            patch.append(Pixel(i, j))
            image[i][j] = 0
            j += 1

    def find_first_occurence_of_color():
        """
        Find the first pixel with the color.
        'First' is evaluated first by minimzing x and second by minimzing y.
        """
        for i, row in enumerate(image):
            for j, entry in enumerate(row):
                if entry == color:
                    find_consecutive_to_right(i, j)
                    return True
        return False

    return find_first_occurence_of_color()


def left_right_output(image, output_file):
    """
    (main function). Plan strokes from the ptg file and save
    to the output file.
    """
    left_right(image).output_strokes(output_file)


def left_right(image):
    """
    @param image: a 2D array of python lists of images
    Return the strokes for the image.

    The algorithm is, in pseudocode:
      for each color in the image
        for each contigous block of pixels along the x-axis:
            output strokes to paint the pixels
    Returns a list of Stroke objects.
    """
    patch = []
    start = Pixel(-1, -1)
    previous_stroke = Stroke(
        action=INIT,  # I think this is a bad value that will be overwritten
        end=start,
        oldcolor=0,
        newcolor=0
    )
    strokes = StrokeStack(previous_stroke)

    # loop through colors from brightest to darkest
    for color in range(1, MAX_COLORS):
        previous_stroke = strokes.peek()

        if previous_stroke.action != INIT:
            strokes.push_instruction(action=LIFT)

        tank = Tank()
        strokes.push_instruction(
            action=SWITCH_BRUSH,
            newcolor=color
        )

        # find all patches of the current color
        while(find_left_right_patch(image, patch, color)):
            newpatch = True
            while(left_right_stroke(patch, strokes, tank, newpatch)):
                newpatch = False

    return strokes

# create stroke until the entire patch is painted


def left_right_stroke(patch, strokes, tank, newpatch):
    """
    Take a patch of coordinates found from the find_left_right_patch
    and attempt to paint along this patch until either the patch
    or the tank run out. Execute any other actions needed to do the stroke.

    return False : patch is empty
    return True  : stroke executed
    """
    previous_stroke = strokes.peek()
    lifted = False
    moved = False

    # If Patch is empty, do nothing.
    if not patch:
        return False

    # If this is the first time the patch is being touched after leaving findlr
    # patch then ...
    if newpatch:
        # If the last action was to MOVE or DROP the brush then LIFT the brush
        if previous_stroke.action == MOVE or previous_stroke.action == DROP:
            strokes.push_instruction(action=LIFT)
        # Then move to the first position in patch.
        strokes.push_instruction(action=MOVE, end=patch[0])
        lifted = True
        patch.pop(0)

    # if tank is empty, refill
    if tank.empty():

        # if brush is touching canvas lift before refilling
        if not lifted:
            strokes.push_instruction(action=LIFT)
        strokes.push_instruction(action=REFILL)
        tank.refill()
        lifted = True

    # if brush is lifted then drop
    if lifted:
        strokes.push_instruction(action=DROP)
        tank.decrement()

    # find the end of stroke: will be either when the tank is empty or the
    # patch is empty
    while(patch and not tank.empty()):
        tank.decrement()
        end = patch.pop(0)
        moved = True
    if moved:
        strokes.push_instruction(action=MOVE, end=end)

    return True


class Stroke(object):
    """
    Single stroke instruction. See mach_code_output.txt for stroke semantics.

    Records a stroke to be executed in the style of python's turtle module.
    Strokes can lift or drop the brush, move the brush to a different (x,y)
    position, or change the color.
    """

    @classmethod
    def copy(cls, other):
        """ Copy another stroke. """
        return cls(other.action, other.end, other.oldcolor, other.newcolor)

    def __init__(self, action, end, oldcolor, newcolor):
        self.action = action
        self.end = end
        self.oldcolor = oldcolor
        self.newcolor = newcolor

    def output(self):
        """ Represent stroke as brush command. """
        action = self.action
        end = self.end
        if action == MOVE:
            output = "%d %d %d\n" % (action, end.x, end.y)
        elif action == REFILL:
            output = "%d %d %d %d\n" % (action, end.x, end.y, self.oldcolor)
        elif action == SWITCH_BRUSH:
            output = "%d %d %d %d\n" % (action, end.x, end.y, self.newcolor)
        elif action == LIFT or action == DROP:
            output = "%d\n" % action
        else:
            raise ValueError("stroke.action had invalid value of %d" % action)
        return output

    def __repr__(self):
        try:
            return self.output()
        except ValueError:
            if self.action == INIT:
                return "INIT"
            else:
                raise

    def __eq__(self, other):
        return self.action == other.action and \
            self.end == other.end and \
            self.oldcolor == other.oldcolor and \
            self.newcolor == other.newcolor


class StrokeStack(object):

    """ Stores strokes that are to be executed.
        This is a buffer that will be emptied by being written to the output
        file.
    """

    def __init__(self, start_stroke):
        self.strokes = []
        self.strokes.append(start_stroke)

    # This is horrible. please simplify.
    def push_instruction(self, action=None, end=None, oldcolor=None,
                         newcolor=None):
        """ Push another instruction onto the stack.
            Arguments default to that of the current instruction"""
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
        if oldcolor is None and newcolor is None:
            new_stroke.oldcolor = new_stroke.newcolor
        self.strokes.append(new_stroke)

    def peek(self):
        """
        Return the last pushed stroke.
        """
        return self.strokes[-1]

    def output_strokes(self, output_file):
        """
        Write all strokes the output_file
        @param output_file the open file to be written to
        """
        # discard init stroke
        for stroke in self.strokes[1:]:
            output_file.write(stroke.output())

    def __str__(self):
        result = ""
        for stroke in self.strokes[1:]:
            result += stroke.output()
        return result


class Tank(object):
    """
    Tracks the amount of paint left in the arm's tank of paint.

    The robot's tank must be periodically refiled with the REFILL instruction,
    so we have to keep track of the amount of paint left.
    """

    def __init__(self):
        self.amount = MAX_TANK

    def decrement(self):
        """
        Decrement tank by 1.
        """
        if self.amount <= 0:
            raise ValueError("cannot decrement tank to value less than 0")
        self.amount -= 1

    def refill(self):
        """
        Refill tank to max value
        """
        self.amount = MAX_TANK

    def empty(self):
        """
        Set the tank to be empty.
        """
        return self.amount == 0
