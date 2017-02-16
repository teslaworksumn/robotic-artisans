import turtle

# f = open('germany.txt','r')

COLOR = {1: "white", 2: "black", 3: "teal", 4: "red", 5: "green",
         6: "blue", 7: "yellow", 8: "dark green"}


def read_strokes(file_path):
    fileIn = open(file_path, "r")
    ratio = 10
    for line in fileIn:
        line = line.replace("\n", " ")
        if(len(line) == 0):
            print('Not valid line')
        elif(line[1] == '1'):  # Move
            splitLine = line.split(" ")
            x = (int(splitLine[1])) * ratio
            y = (int(splitLine[2])) * ratio
            canvas.goto(x, y)
        elif(line[1] == '2'):  # Lift
            canvas.penup()
        elif(line[1] == '3'):  # Drop brush
            canvas.pendown()
        elif(line[1] == '4'):  # Refill  
            splitLine = line.split(" ")
            x = (int(splitLine[1])) * ratio
            y = (int(splitLine[2])) * ratio
            canvas.goto(x, y)
        elif(line[1] == '5'):  # change color
            splitLine = line.split(" ")
            canvas.pencolor(COLOR.get(int(splitLine[4])))
            x = (int(splitLine[1])) * ratio
            y = (int(splitLine[2])) * ratio
            canvas.goto(x, y)


# initialize the canvas
canvas = turtle.Turtle()
canvas.penup()
canvas.pensize(10)

canvas.pencolor(COLOR.get(1))
read_strokes("germany.txt")
# for x in range (1,9):
#    canvas.pencolor(COLOR.get(x))

turtle.done()


print "I got to past Turtle"
