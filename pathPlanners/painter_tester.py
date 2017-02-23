"""
This module tests the code in pathPlanner by executing the strokes in the output file
using a "turtle" image simulation.
"""

import turtle

COLOR = {1: "white", 2: "black", 3: "teal", 4: "red", 5: "green",
         6: "blue", 7: "yellow", 8: "dark green"}


def read_strokes(file_path):
    """
    Execute strokes from file `file_path`.
    """
    file_in = open(file_path, "r")
    ratio = 10
    for line in file_in:
        line = line.replace("\n", " ")
        if len(line) == 0:
            print 'Not valid line'
        elif line[1] == '1':  # Move
            split_line = line.split(" ")
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)
        elif line[1] == '2':  # Lift
            CANVAS.penup()
        elif line[1] == '3':  # Drop brush
            CANVAS.pendown()
        elif line[1] == '4':  # Refill
            split_line = line.split(" ")
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)
        elif line[1] == '5':  # change color
            split_line = line.split(" ")
            CANVAS.pencolor(COLOR.get(int(split_line[4])))
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)


# initialize the CANVAS
CANVAS = turtle.Turtle()
CANVAS.penup()
CANVAS.pensize(10)

CANVAS.pencolor(COLOR.get(1))
read_strokes("germany.txt")
# for x in range (1,9):
#    CANVAS.pencolor(COLOR.get(x))

turtle.done()

print "I got to past Turtle"
