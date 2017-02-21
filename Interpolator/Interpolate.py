# Imports
import re

# Functions to generate more points linearly

FREQUENCY_OF_POINTS = 1 / 16

#absolute value function
def abs(x):
    if(x > 0):
        return x
    return -1 * x


def make_gcode(point):
    return "G1 X " + str(point[0]) + " Y " + str(point[1]) + " Z " + str(point[2])


def generate_points(p1,p2):
    new_points = []
    mx = p2[0] - p1[0] #the slopes for each dimension
    my = p2[1] - p1[1]
    mz = p2[2] - p1[2]
    tend = (p2[0]-p1[0]) / FREQUENCY_OF_POINTS
    t = 0
    while(t < tend):
        t = t + FREQUENCY_OF_POINTS
        new_points.append((p1[0] + (t * mx), p1[1] + (t * my), p1[2] + (t * mz)))
    return new_points

def read_file(file_path_in, file_path_out):
    file_in = open(file_path_in, 'r')
    file_out = open(file_path_out, 'a')
    previous_point = False
    current_point = (0,0,0)
    for line in file_in:
        matchObj = re.match( r'[0-9]+', line)
        if(!previous_point):
            previous_point = (matchObj.group(1), matchObj.group(2), matchObj.group(3))
        else:
            current_point = (matchObj.group(1), matchObj.group(2), matchObj.group(3))
            new_points = generate_points(previous_point, current_point)
            file_out.write(make_gcode(previous_point))
            for point in new_points:
                file_out.write(make_gcode(point))
    file_in.close()
    file_out.close()
