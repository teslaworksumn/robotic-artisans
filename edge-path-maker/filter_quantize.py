'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import numpy as np
from sklearn.cluster import MiniBatchKMeans
import matplotlib.pyplot as plt
import cv2

''' Given a quantized image, split image into a set of images that only include
    one of the single colors.
    input : 
        image : a quantized image represented as a numpy array
        bins  : number of colors within the image
    output : 
        a numpy array with bins number of images each of the same size as image.
'''
def splitQuantize(quant, bins):
    # find all the unique colors calculated as a cluster
    uniques = np.unique(quant.reshape(-1, quant.shape[2]), axis=0)

    # Array to hold all layers of the quantized image
    quants = np.zeros(shape=(bins, quant.shape[0], quant.shape[1], quant.shape[2]))
    # Split up an image into multiple arrays based on its color
    for i in range(bins):
        bin = uniques[i]
        binimg = np.array(quant)
        binimg[np.where((binimg != bin).all(axis=2))] = [0,0,0]
        quants[i] = binimg
    return quants

''' quantize an image with a given number of colors
    input : 
        imgName : string name of file path
        bins    : number of colors within quantized image. default is 8
    output : 
        an quantized image represented as a numpy array
'''
def filterQuantize(imgName, bins = 8):
    image = cv2.imread(imgName)
    h, w = image.shape[:2]
    bins = 8
    sigma = 0.33

    image = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)

    image = image.reshape((image.shape[0] * image.shape[1], 3))

    clt = MiniBatchKMeans(n_clusters = bins)
    labels = clt.fit_predict(image)
    quant = clt.cluster_centers_.astype("uint8")[labels]

    quant = quant.reshape((h, w, 3))
    image = image.reshape((h, w, 3))
    quant = cv2.cvtColor(quant, cv2.COLOR_LAB2RGB)

    return quant
