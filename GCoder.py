"""
Take in strokes file from pathPlanner.py and return cartesian GCode.
This GCode still needs to be processed with code in inverse-kinematics.
"""

LIFT = "2"  # z axis value, only has two possible values of 1 or 0

# It will look something like this {"Red":(0,0),"Blue":(1,0),...}
COLOR_POS = {
    # pylint: disable=C0326
    "1": (-1, 0),
    "2": (-1, 2.5),
    "3": (-1, 5),
    "4": (-1, 7.5),
    "5": (11, 0),
    "6": (11, 2.5),
    "7": (11, 5),
    "8": (11, 7.5)
}
#

# Read ratio from ratio file
# TODO: this needs to be refactored into paramater-passing instead
# of reading and writing from a file.
ratio_file = open("Ratio.txt", 'r')
string_ratio = ratio_file.readline()
R = float(string_ratio)
ratio_file.close()


def make_gcode(input_file, output_file):
    """
    Read strokes from filePathin and write cartesian gcode to filePathOut
    """

    # TODO close file descriptors
    input_stream = open(input_file, 'r')
    out = open(output_file, 'a')
    position_xy = (0, 0)

    for line in input_stream:
        line = line.replace("\n", "")
        split_line = line.split(" ")
        if len(line) == 0:
            print 'error: invalid, empty line'
        elif line[1] == '1':  # Move
            out.write(move(split_line[1], split_line[2]))
            position_xy = int(split_line[1]), int(split_line[2])
        elif line[1] == '2':  # Lift
            out.write(lift(position_xy))
        elif line[1] == '3':  # Drop brush
            out.write(drop(position_xy))
        elif line[1] == '4':  # Refill
            out.write(refill(split_line[1], split_line[2], split_line[3],
                             position_xy))
        elif line[1] == '5':  # change color
            out.write(change_color(split_line[1], split_line[2], split_line[3],
                                   position_xy))
    input_stream.close()
    out.close()


def move(x, y):
    """
    Move the brush to specified position.
    """
    s = "G1 X "+str(int(x)*R)+" Y "+str(int(y)*R)+" Z "+LIFT+' \n'
    # print("G1X"+str(x)+"Y"+str(y)+"Z"+LIFT+'\n')
    return s


def lift(position_xy):
    """
    Lift the brush
    """
    # FIXME test this bug and fix it.
    LIFT = str(2)
    command = "G1 X " + str(position_xy[0]*R) + " Y " + \
              str(position_xy[1]*R) + " Z " + LIFT+' \n'
    # print("G1X"+str(position_xy[0])+"Y"+str(position_xy[1])+"Z"+LIFT+'\n')
    return command


def drop(position_xy):
    """
    Drop the brush
    """
    LIFT = '0'
    command = "G1 X " + str(position_xy[0]*R) + " Y " + \
              str(position_xy[1]*R) + " Z " + LIFT + ' \n'
    # print("G1X"+str(position_xy[0])+"Y"+str(position_xy[1])+"Z"+LIFT+'\n')
    return command


# TODO add comments
def refill(xi, yi, color, position_xy):
    x = COLOR_POS.get(color)[0]
    y = COLOR_POS.get(color)[1]
    s = lift(position_xy)
    s += move(x, y)
    s += drop((x, y))
    s += lift((x, y))
    s += move(xi, yi)
    print s
    return s


def change_color(xi, yi, colorf, position_xy):
    """
    Change the color of the brush.
    """
    print colorf
    command = lift(position_xy)
    command += move(COLOR_POS.get(colorf)[0], COLOR_POS.get(colorf)[1])
    command += drop(position_xy)
    command += lift(position_xy)
    command += move(xi, yi)
    return command


if __name__ == "__main__":
    make_gcode("apx2.txt", "xyzi.txt")
