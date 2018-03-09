import cv2
import numpy as np
import os

# to choose a different image, set file_name = "image path"

source_folder = "../data/"
destination_folder = "../modified_data/"
folders = ['square/', 'circle/', 'triangle/']
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
def reflect(filename, path): #reflects borders of img, expands it
	img = cv2.imread(path + filename)
	reflect = cv2.copyMakeBorder(img,30,30,30,30,cv2.BORDER_REFLECT)
	cv2.imwrite(path + "Reflected_" + filename, reflect)
def blend(filename, filename2, path): #adds "noise.png" image to original "file_name" image
	img = cv2.imread(path + filename)
	img2 = cv2.imread(filename2)
	blended = cv2.addWeighted(img,0.5,img2,0.5,0)
	cv2.imwrite(path + "Blended_" + filename, blended)
def splash(filename, path): #makes image appears as "splashed" -- mixes colors
	img = cv2.imread(path + filename)
	splashed = cv2.medianBlur(img,21)
	cv2.imwrite(path + "Splashed_" + filename, splashed)
def vflip(filename, path): # mirrors img using vertical axis
	img = cv2.imread(path + filename)
	vfliped = cv2.flip(img, 1)
	cv2.imwrite(path + "Vertical_fliped_" + filename, vfliped)
def hflip(filename, path): # mirrors img using horizontal axis
	img = cv2.imread(path + filename)
	hfliped = cv2.flip(img, 0)
	cv2.imwrite(path + "Horizontal_fliped_" + filename, hfliped)
def bothflip(filename, path): # mirrors img using both vertical and horizontal axes
	img = cv2.imread(path + filename)
	bfliped = cv2.flip(img, -1)
	cv2.imwrite(path + "Both_fliped_" + filename, bfliped)
#  === MAIN ===

for folder in folders:
	path = source_folder + folder
	files = []
	for file in os.listdir(path):
		files += [file]
	for file in files:
		if(file != ".DS_Store"):
			print(file)
			reflect(file, path)
			#blend(file, file2)
			splash(file, path)
			vflip(file, path)
			hflip(file, path)
			bothflip(file, path)

# ==============
