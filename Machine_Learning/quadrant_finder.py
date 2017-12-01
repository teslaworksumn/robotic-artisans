from PIL import Image
import numpy as np
import model_creator as model #import shape predictor

# split an image up into x quadrants, then check for a shape in that quadrant
def split_pic(nrows, ncols, imgPath = None, PILimg = None):
    img = None
    if (imgPath == None):
        img = PILimg
    else:
        img = Image.open(imgPath)

    img = img.convert('L')
    imgArr = np.array(img)
    width, height = img.size
    imgArr.reshape((height, width))

    h, w = imgArr.shape
    return (imgArr.reshape(h//nrows, nrows, -1, ncols)
               .swapaxes(1,2)
               .reshape(-1, nrows, ncols))

def predict_quadrant_shapes(nrows, ncols, imgPath = None, PILimg = None):
    split_arr = []
    # try with one input, and use other if needed
    try:
        split_arr = split_pic(nrows, ncols, imgPath = imgPath)
    except(ValueError):
        split_arr = split_pic(nrows, ncols, PILimg = PILimg)

    # predict shapes in each quadrant
    shapes_arr = []
    for i in split_arr:
        shapes_arr += model.predict(i)
    # should return array of size nrows*ncols
    return shapes_arr
