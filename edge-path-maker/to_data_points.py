'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import numpy as np

'''
Convert a numpy 2D bit array to a series of data points
corresponding to the location of each `1` in the array
'''
def toDataPoints(imgArray):
    y_data = np.array([])
    x_data = np.array([])
    for y in range(0, len(imgArray)):
        for x in range(0, len(imgArray[0])):
            if(imgArray[y, x] != 0):
                y_data = np.append(y, y_data)
                x_data = np.append(x, x_data)
    return (x_data, y_data)