'''
Copyright Max Omdal 2018. All Rights Reserved.
'''
import numpy as np
import cv2

''' Convert an image to a bitmap of its edges using OpenCV's
    Canny
    input : 
        imgName : string name of file path
        lower   : lower bound of the threshold. If not provided, it will be
                  calculated based on the median color of the image
        upper   : upper bound of the threshold. If not provided, it will be
                  calculated based on the median color of the image
'''
def filterEdges(imgName, lower = None, upper = None):
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    v = np.median(gray_image)

    if (lower == None or upper == None):
        lower = int(max(0, (1.0 - sigma) * v))
        upper = int(min(255, (1.0 + sigma) * v))
    edges = cv2.Canny(gray_image, lower, upper)
    edges = cv2.cvtColor(edges, cv2.COLOR_GRAY2RGB)
    return edges