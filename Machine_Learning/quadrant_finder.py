import PIL
from PIL import Image
import cv2
import numpy as np
import SVM_model_creator as model #import shape predictor

# split an image up into x quadrants, then check for a shape in that quadrant
def split_pic(nrows, ncols, imgPath = None, PILimg = None, edges = False):
    img = None
    if (imgPath == None):
        img = PILimg
    else:
        ##img = Image.open(imgPath)
        img = cv2.imread(imgPath, 0)
    height, width = img.shape
    ##img = img.convert('L')
    ##img = img.resize((nrows*50,ncols*50), PIL.Image.ANTIALIAS)
    img_small = cv2.resize(img, (nrows*50, ncols*50), interpolation = cv2.INTER_AREA)
    if(edges == True):
        img_small = make_edge_img(img_small)
    imgArr = img_small
    ##width, height = img.size
    height_small, width_small = img_small.shape
    split_width = width_small//nrows
    split_height = height_small//ncols
    imgarr = imgArr.reshape((width_small, height_small))
    h, w = imgArr.shape
    return (imgArr.reshape(h//split_width, split_width, -1, ncols)
               .swapaxes(1,2)
               .reshape(-1, split_width, split_height))

def make_edge_img(image):
    edges = cv2.Canny(image,100,200)
    return edges

def predict_quadrant_shapes(nrows, ncols, imgPath = None, PILimg = None, edges = False):
    split_arr = np.array([])
    # try with one input, and use other if needed
    if (imgPath == None):
        split_arr = split_pic(nrows, ncols, PILimg = PILimg, edges = edges)
    else:
        split_arr = split_pic(nrows, ncols, imgPath = imgPath, edges = edges)
    split_arr.shape = [nrows*ncols, 2500]

    # predict shapes in each quadrant
    shapes_arr = []
    i = 0
    while(i < split_arr.shape[0]):
        prediction = model.predict([split_arr[[i]]])
        cv2.imshow(str(prediction), split_arr[[i]])
        shapes_arr += [prediction]
        i += 1


    # should return array of size nrows*ncols
    return shapes_arr

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(
        description='Split an image into x number of rows and y number of columns, and predict shape in each sub-image'
    )
    parser.add_argument('rows', type=int, help='rows to be subdivided')
    parser.add_argument('columns',type=int, help='columns to be subdivided')
    parser.add_argument('image_path', help='path of the image to be subdivided')
    args = parser.parse_args()
    print(predict_quadrant_shapes(args.rows, args.columns, imgPath = args.image_path, edges = False))
