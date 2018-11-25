'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import numpy as np
from curve import Curve

''' Generates a stroke path that uses straight lines across the image
    by grouping strips of same colored pixels into one stroke. 
    input :
        image : a numpy array of at least 2 dimensions
        skip  : number of rows to skip between each stroke generation. Default is 0
'''
def printInline(image, skip = 0):
    h, w = image.shape[:2]
    strokes = []
    for y in range(0, h, skip + 1):
        start = None
        stop = None
        for x in range(w):
            pixel = image[y, x]
            if start == None and np.any(pixel):
                start = (y, x)
            # break at edge or at end of color
            elif start != None and not np.all(pixel):
                stop = (y, x - 1)
                strokes.append([start, stop])
                start = None
                stop = None
            elif start != None and x == w - 1:
                stop = (y, x)
                strokes.append([start, stop])
    if len(strokes) > 0:
        colors = [strokes[0][0]] * len(strokes)
        Curve.createAndAddCurves(strokes, colors)

''' Generates a stroke path that uses straight lines across the image
    by grouping strips of same colored pixels into one stroke. Breaks
    lines when there is an edge.
    input :
        image : a numpy array of at least 2 dimensions
        edges : a numpy array of at least 2 dimensions. Expects all non-edge
                cases to be zero vectors
        skip  : number of rows to skip between each stroke generation.
                Default is 0
'''
def printInlineEdges(image, edges, skip = 0):
    h, w = image.shape[:2]
    strokes = []
    for y in range(0, h, skip + 1):
        start = None
        stop = None
        for x in range(w):
            pixel = image[y, x]
            if start == None and np.any(pixel):
                start = (y, x)
            # break at edge or at end of color
            elif start != None and (np.all(edges[y, x]) or not np.all(pixel)):
                stop = (y, x - 1)
                strokes.append([start, stop])
                start = None
                stop = None
            elif start != None and x == w - 1:
                stop = (y, x)
                strokes.append([start, stop])
    if len(strokes) > 0:
        colors = [strokes[0][0]] * len(strokes)
        Curve.createAndAddCurves(strokes, colors)