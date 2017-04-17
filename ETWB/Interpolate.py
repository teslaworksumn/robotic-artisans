# Imports
import math

# Functions to generate more points linearly

FREQUENCY_OF_POINTS = .25

# absolute value function


def abs(x):
    if(x > 0):
        return x
    return -1 * x


def make_gcode(point):
    return "G1 X " + str(point[0]) + " Y " + str(point[1]) \
            + " Z " + str(point[2])


def generate_points(p1, p2):
    new_points = []
    dx = p2[0] - p1[0]   # the slopes for each dimension
    dy = p2[1] - p1[1]
    dz = p2[2] - p1[2]
    distance = math.sqrt(dx**2 + dy**2 + dz**2)
    if(distance == 0):
        print(p1)
        print(p2)
        print("ZERO Distance")
    else:
        mx = dx / distance
        my = dy / distance
        mz = dz / distance
        t = 0
        while(t < distance - FREQUENCY_OF_POINTS):
            t = t + FREQUENCY_OF_POINTS
            new_points.append((p1[0] + (t * mx), p1[1] + (t * my), p1[2]
                              + (t * mz)))
    return new_points


def interpolate(file_in, file_path_out):
    file_out = open(file_path_out, 'w')
    previous_point = False
    current_point = (0, 0, 0)
    for line in file_in:
        split_line = line.split()
        if(not previous_point):
            previous_point = (float(split_line[2]), float(split_line[4]),
                              float(split_line[6]))
        else:
            current_point = (float(split_line[2]), float(split_line[4]),
                             float(split_line[6]))
            new_points = generate_points(previous_point, current_point)
            file_out.write(make_gcode(previous_point) + '\n')
            for point in new_points:
                file_out.write(make_gcode(point) + '\n')
            previous_point = current_point
    file_out.write(make_gcode(current_point) + '\n')
    file_out.close()


def read_file(file_path_in, file_path_out):
    file_in = open(file_path_in, 'r')
    interpolate(file_in, file_path_out)
    file_in.close()


if __name__ == "__main__":
    # pylint: disable=C0103
    # pylint: disable=C0330
    import argparse
    parser = argparse.ArgumentParser(
        description='Convert an image file to 8-color ptg')
    parser.add_argument('file_in', help='input xyz file')
    parser.add_argument('file_out', help='output xyz file')
    args = parser.parse_args()
    read_file(args.file_in, args.file_out)
