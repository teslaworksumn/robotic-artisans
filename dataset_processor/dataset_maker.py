'''
    given a folder with images of triangles, squares, and circles of any size,
    resize images and write out pixel values as a csv
'''


from __future__ import print_function
from PIL import Image
import numpy as np
import os, sys

SHAPE_LABELS = {'triangle': [1,0,0], 'square': [0,1,0], 'circle': [0,0,1]}

# Resize all the images in the data folder and put them in a new sub-directory
def batch_resize(folders, w, h):
    for folder in folders:
        path = 'data/' + folder + '/'
        dirs = os.listdir( path )
        resized_img_path = 'data/' + folder + '_resized/'
        if not os.path.exists(resized_img_path):
            os.makedirs(resized_img_path)
        for item in dirs:
            if os.path.isfile(path + item):
                f, e = os.path.splitext(item)
                # make sure there only te right file types are used
                if (e == 'png' or e == 'jpg'):
                    # create a PIL Image with the file
                    im = Image.open(path + item)
                    # resize
                    imResize = im.resize((w,h), Image.ANTIALIAS)
                    # save
                    filename = os.path.basename(path + item)
                    filename, extension = os.path.splitext(filename)
                    imResize.save(resized_img_path + filename + '_resized.png', 'png')

# creates a file with all the pixels of each image written out with ' ' delimiter
# images parameter is an array of PIL Images

def createDataset(images):
    if not os.path.exists('train/'):
        os.makedirs('train/')

    random_train = np.arange(len(images))

    np.random.shuffle(random_train)

    # write out files for images
    with open('train/images_train.csv', 'w+') as a, open('train/images_test.csv', 'w+') as b:
        for index in range(len(images)):
            image_index = random_train[index]
            image = images[image_index]
            pixels = list(image[1].getdata())
            pixels_string = ','.join(map(str, pixels))
            classification = SHAPE_LABELS[image[0]]
            if (index < len(images)*3/4):
                a.write(pixels_string + '\n')
            else:
                b.write(pixels_string + '\n')

    # write out files for labels
    with open('train/labels_train.csv', 'w+') as a, open('train/labels_test.csv', 'w+') as b:
        for index in range(len(images)):
            image_index = random_train[index]
            image = images[image_index]
            classification = SHAPE_LABELS[image[0]]
            if (index < len(images)*3/4):
                a.write(','.join(repr(e) for e in classification) + '\n')
            else:
                b.write(','.join(repr(e) for e in classification) + '\n')

# make a PIL Image instance for each image and return a list of images
def createImages(folders):
    images = []
    for folder in folders:
        path = 'data/' + folder + '_resized/'
        if os.path.exists(path):
            for item in os.listdir(path):
                new_image = Image.open(path + item)
                new_image = new_image.convert('L')
                images = images + [(folder, new_image)]
    return images


if __name__ == '__main__':
    # create a list of file names where the images are stored
    folders = ['triangle', 'circle', 'square']

    # create new directories of images (500, 500) for the given directories of images
    batch_resize(folders, 500, 500)
    createDataset(createImages(folders))
