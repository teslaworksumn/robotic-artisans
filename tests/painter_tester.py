"""
This module tests the code in pathPlanner by executing the strokes in the
output file using a "turtle" image simulation.
"""

import turtle

FILENAME = "strokes.txt"

COLOR = {1: "white", 2: "yellow", 3: "coral", 4: "red", 5: "green",
         6: "blue", 7: "dark green", 8: "black"}


def read_strokes(file_path):
    """
    Execute strokes from file `file_path`.
    """
    file_in = open(file_path, "r")
    ratio = 2
    for line in file_in:
        line = line.replace("\n", " ")
        if len(line) == 0:
            print('Not valid line')
        elif line[1] == '1':  # Move
            split_line = line.split(" ")
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)
        elif line[1] == '2':  # Lift
            CANVAS.up()
        elif line[1] == '3':  # Drop brush
            CANVAS.pendown()
        elif line[1] == '4':  # Refill
            split_line = line.split(" ")
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)
        elif line[1] == '5':  # change color
            split_line = line.split(" ")
            CANVAS.pencolor(COLOR.get(int(split_line[3])))
            x_val = (int(split_line[1])) * ratio
            y_val = (int(split_line[2])) * ratio
            CANVAS.goto(x_val, y_val)


# initialize the CANVAS
CANVAS = turtle.Turtle()
CANVAS.penup()
CANVAS.pensize(6)

CANVAS.pencolor(COLOR.get(1))
read_strokes(FILENAME)
# for x in range (1,9):
#    CANVAS.pencolor(COLOR.get(x))


turtle.done()

print("I got to past Turtle")
