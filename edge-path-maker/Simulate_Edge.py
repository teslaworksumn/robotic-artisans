import turtle
import cv2
import edge_bitmap_generator
import numpy as np
import settings

def makeTurtle(edges, width, height):
    turtle.setup(width = width, height = height)
    wn = turtle.Screen()
    turtle.tracer(0,0)
    turtle.penup()
    for edge in edges:
        for point in edge:
            turtle.goto(point[0] - width/2, -point[1] + height/2)
            turtle.pendown()
        turtle.penup()
    turtle.update()
    turtle.exitonclick()

# Not working yet
def testEdges(imageName):
    img = cv2.imread(imageName)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cv2.StartWindowThread()
    cv2.imshow("test", img)
    cv2.waitKey(0)

if __name__ == "__main__":
    imgName = input("Input name of image to be drawn: ")
    raw_drawing, width, height = edge_bitmap_generator.prepEdgePainter(settings.IMAGES_DIRECTORY + imgName, 100)
    makeTurtle(raw_drawing, width, height)
    img = cv2.imread(imgName, 0)
    edges = cv2.Canny(img,100,100*2, False)
    cv2.imshow("original" , edges)
    cv2.waitKey(0)