import cv2
import PIL
import numpy as np
from matplotlib import pyplot as plt
import copy
import sys

sys.setrecursionlimit(3000)

def prepEdgePainter(imgName, threshold = 100):
    #FIX: allow input of jpg and other file formats, from web address or file
    img = cv2.imread(imgName, 0)
    edges = cv2.Canny(img,threshold,threshold*2, False)
    image_pil = PIL.Image.fromarray(np.uint8(plt.cm.gist_earth(edges)*255))
    image_pil = image_pil.convert('1')

    width, height = image_pil.size

    p = image_pil.load()

    return (edgePaint(p, width, height), width, height)

def removeMinimalStrokes(strokes):
    reduced_strokes = strokes
    for stroke in strokes:
        if (len(stroke) <= 5):
            print(reduced_strokes.pop(strokes.index(stroke)))
    return reduced_strokes

def edgePaint(pixels, width, height):
    strokes = []
    for y in range(height):
        for x in range(width):
            if pixels[x, y] == 255:
                newPoint = [x,y]
                newEdge, pixels = recurse([newPoint], pixels)
                strokes += [newEdge]
    reduced_strokes = removeMinimalStrokes(strokes)
    return reduced_strokes

# check if any surrounding pixels are of the same color value
def counterclockwiseSearch(point, pixels):
    # FIX: images with edges that touch go to the bounds of the image throw a ArrayIndexOutOfBounds
    # FIX: sometimes line breaks unnecisarily

    adjacentPoints = []

    if(pixels[point[0], point[1] - 1] == 255):
        adjacentPoints.append([point[0], point[1] - 1])

    if(pixels[point[0] - 1, point[1] - 1] == 255):
        adjacentPoints.append([point[0] - 1, point[1] - 1])

    if(pixels[point[0] - 1, point[1]] == 255):
        adjacentPoints.append([point[0] - 1, point[1]])

    if(pixels[point[0] - 1, point[1] + 1] == 255):
        adjacentPoints.append([point[0] - 1, point[1] + 1])

    if(pixels[point[0], point[1] + 1] == 255):
        adjacentPoints.append([point[0], point[1] + 1])

    if(pixels[point[0] + 1, point[1] + 1] == 255):
        adjacentPoints.append([point[0] + 1, point[1] + 1])

    if(pixels[point[0] + 1, point[1]] == 255):
        adjacentPoints.append([point[0] + 1, point[1]])

    if(pixels[point[0] + 1, point[1] - 1] == 255):
        adjacentPoints.append([point[0] + 1, point[1] - 1])

    if(pixels[point[0], point[1] - 1] == 255):
        adjacentPoints.append([point[0], point[1] - 1])
    else:
        return adjacentPoints

def recurse(points, pixels):
    if (counterclockwiseSearch(points[-1], pixels)):
        newPoint = []
        for pixel in counterclockwiseSearch(points[-1], pixels):
            pixelSearch = (counterclockwiseSearch(pixel, pixels))
            if (pixelSearch and len(pixelSearch) >= 1):
                newPoint = pixel
                break
        # hide the pixels that have already been accounted for
        if (newPoint):
            pixels[newPoint[0], newPoint[1]] = 0
            return recurse(points + [newPoint], pixels)
    return points, pixels

def test_repeated_points():
    points = edgePaint(p)
    seen = set()
    uniq = []
    for x in points:
        if x not in seen:
            uniq.append(x)
            seen.add(x)
    assert seen
