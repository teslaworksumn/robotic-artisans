"""
Take in strokes file from pathPlanner.py and return cartesian GCode.
This GCode still needs to be processed with code in inverse-kinematics.
"""

LIFT = "1"  # z axis value, only has two possible values of 1 or 0

# It will look something like this {"Red":(0,0),"Blue":(1,0),...}
COLOR_POS = {
    # pylint: disable=C0326
    "1": (-2, 0),
    "2": (-2, 2.5),
    "3": (-2, 5),
    "4": (-2, 7.5),
    "5": (10, 0),
    "6": (10, 2.5),
    "7": (10, 5),
    "8": (10, 7.5)
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
                      split_line[4], position_xy))


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
    LIFT = str(1)
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
    s = move(x, y)
    s += drop(position_xy)
    s += lift(position_xy)
    s += move(xi, yi)
    return s


def change_color(xi, yi, colori, colorf, position_xy):
    """
    Change the color of the brush.
    """
    print colori
    print colorf
    command = ''
    command += move(COLOR_POS.get(colorf)[0], COLOR_POS.get(colorf)[1])
    command += drop(position_xy)
    command += lift(position_xy)
    command += move(xi, yi)
    return command


if __name__ == "__main__":
    make_gcode("brushstrokes.txt", "xyz.gcode")
