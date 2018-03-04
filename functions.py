import cv2
import numpy as np
import os

# to choose a different image, set file_name = "image path"

source_folder = "data/circle/"
destination_folder = "imgs_out/"
os.getcwd()
os.path.exists(source_folder)
#==================================


"""
def dark(filename): #darkens and blurs img
	img = cv2.imread(filename)
	kernel = np.ones((1,5), np.float32) / 50
	dst = cv2.filter2D(img, -1, kernel)
	darke = cv2.filter2D(img, -1, kernel)
	cv2.imwrite(destination_folder + "Darkened_" + filename, darke)
"""
def reflect(filename): #reflects borders of img, expands it
	img = cv2.imread(source_folder + filename)
	reflect = cv2.copyMakeBorder(img,30,30,30,30,cv2.BORDER_REFLECT)
	cv2.imwrite(destination_folder + "Reflected_" + filename, reflect)
def blend(filename, filename2): #adds "noise.png" image to original "file_name" image
	img = cv2.imread(source_folder + filename)
	img2 = cv2.imread(filename2)
	blended = cv2.addWeighted(img,0.5,img2,0.5,0)
	cv2.imwrite(destination_folder + "Blended_" + filename, blended)
def splash(filename): #makes image appears as "splashed" -- mixes colors
	img = cv2.imread(source_folder + filename)
	splashed = cv2.medianBlur(img,21)
	cv2.imwrite(destination_folder + "Splashed_" + filename, splashed)
def vflip(filename): # mirrors img using vertical axis
	img = cv2.imread(source_folder + filename)
	vfliped = cv2.flip(img, 1)
	cv2.imwrite(destination_folder + "Vertical_fliped_" + filename, vfliped)
def hflip(filename): # mirrors img using horizontal axis
	img = cv2.imread(source_folder + filename)
	hfliped = cv2.flip(img, 0)
	cv2.imwrite(destination_folder + "Horizontal_fliped_" + filename, hfliped)
def bothflip(filename): # mirrors img using both vertical and horizontal axes
	img = cv2.imread(source_folder + filename)
	bfliped = cv2.flip(img, -1)
	cv2.imwrite(destination_folder + "Both_fliped_" + filename, bfliped)
#  === MAIN ===

for file in os.listdir(source_folder):
	#dark(file)
	print(file)
	splash(file)

# ==============
