'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import numpy as np
import cv2 as cv
import sys

'''
A Zhang Suen thinning algorithm. Given a bitmap, it converts an area to a skeleton
'''
def thinning(im):
	changing1 = changing2 = [(-1, -1)]
	while changing1 or changing2:
		# Step 1
		changing1 = []
		for y in range(1, im.shape[1] - 1):
			for x in range(1, im.shape[0] - 1):
				P2,P3,P4,P5,P6,P7,P8,P9 = n = neighbours(x, y, im)
				if (im[x,y] == 1 and    # (Condition 0)
					P4 * P6 * P8 == 0 and   # Condition 4
					P2 * P4 * P6 == 0 and   # Condition 3
					transitions(n) == 1 and # Condition 2
					2 <= sum(n) <= 6):      # Condition 1
					changing1.append((x,y))
		for x, y in changing1: im[x,y] = 0
		# Step 2
		changing2 = []
		for y in range(1, im.shape[1] - 1):
			for x in range(1, im.shape[0] - 1):
				P2,P3,P4,P5,P6,P7,P8,P9 = n = neighbours(x, y, im)
				if (im[x,y] == 1 and    # (Condition 0)
					P2 * P6 * P8 == 0 and   # Condition 4
					P2 * P4 * P8 == 0 and   # Condition 3
					transitions(n) == 1 and # Condition 2
					2 <= sum(n) <= 6):      # Condition 1
					changing2.append((x,y))
		for x, y in changing2: im[x,y] = 0
			#print changing1
			#print changing2
	return im

def transitions(neighbours):
	n = neighbours + neighbours[0:1]    # P2, ... P9, P2
	return sum((n1, n2) == (0, 1) for n1, n2 in zip(n, n[1:]))

def neighbours(x, y, image):
	i = image
	x1, y1, x_1, y_1, = x+1, y-1, x-1, y+1
	return [i[x,y1], i[x1,y1], i[x1,y], i[x1,y_1], i[x,y_1], i[x_1,y_1], i[x_1,y], i[x_1,y1]]