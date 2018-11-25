'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import cv2

# default 100% scale value makes no changes
def resizeImg(image, scale_percent = 100):
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    dim = (width, height)
    # resize image
    resizedImg = cv2.resize(image, dim, cv2.INTER_AREA)
    return resizedImg

def resizeImg(image, width, height):
    dim = (width, height)
    # resize image
    resizedImg = cv2.resize(image, dim, cv2.INTER_AREA)
    return resizedImg
