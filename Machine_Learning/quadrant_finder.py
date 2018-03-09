import PIL
from PIL import Image
import cv2
import numpy as np
import tensorflow as tf
from CNN_model_creator import cnn_model_fn

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
    img_small = cv2.resize(img, (nrows*48, ncols*48), interpolation = cv2.INTER_AREA)
    if(edges == True):
        img_small = make_edge_img(img_small)
    imgArr = img_small
    #change image pizels from 0-255 to 0-1 float
    imgArr = np.array(list(map((lambda x: x/255), imgArr)), dtype=np.float32)
    ##width, height = img.size
    height_small, width_small = img_small.shape
    split_width = width_small//ncols
    split_height = height_small//nrows
    imgarr = imgArr.reshape((width_small, height_small))
    h, w = imgArr.shape
    split = (imgArr.reshape(h//split_height, split_height, -1, split_width)
               .swapaxes(1,2)
               .reshape(-1, split_height, split_width))
    return split

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
    print(split_arr.shape)

    # predict shapes in each quadrant
    shapes_arr = []
    i = 0
    while(i < split_arr.shape[0]):

        test_img = split_arr[i]
        test_img.shape = (1,-1)
        print(test_img)
        prediction = []
        #prediction = model.predict(test_img)
        sess = tf.Session()
        #load meta graph and restore weights
        clf = tf.estimator.Estimator(model_fn=cnn_model_fn, model_dir="/tmp/model")

        #evaluate the model and print results
        input_fn = tf.estimator.inputs.numpy_input_fn(
            x={"x": test_img},
            num_epochs=1,
            shuffle=False
        )
        prediction = list(clf.predict(input_fn=input_fn))
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
    print(predict_quadrant_shapes(args.rows, args.columns, imgPath = args.image_path))
