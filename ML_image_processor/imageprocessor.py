# from https://stackoverflow.com/questions/21517879/python-pil-resize-all-images-in-a-folder
from PIL import Image
import os, sys


def batch_resize(folder, w, h):
    path = '../data/' + folder + '/'
    dirs = os.listdir( path )
    resized_img_path = '../data/' + folder + '_resized/'
    if not os.path.exists(resized_img_path):
        os.makedirs(resized_img_path)
    for item in dirs:
        if os.path.isfile(path + item):
            im = Image.open(path + item)
            imResize = im.resize((w,h), Image.ANTIALIAS)
            filename = os.path.basename(path + item)
            filename, extension = os.path.splitext(filename)
            imResize.save(resized_img_path + filename + '_resized.png', 'png')

batch_resize('triangle', 500, 500)
