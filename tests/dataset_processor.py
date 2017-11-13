import unittest
import os
from PIL import Image

class dataset_processor_test(unittest.TestCase):
    # test the size of the first image in the circle directory
    def ImageFileSize_test(self):
        path = 'data/circle_resized/'
        img = Image.open(path + os.listdir(path)[0])
        self.assertEqual(img.size[0], img.size[1])
        self.assertEqual(img.size, (100,100))
    # test the lengths of the images and labels files
    def trainingData_test(self):
        with open('train/images_test.csv') as a, open('train/labels_test.csv') as b:
            self.assertEqual(len(a.readlines()), len(b.readlines()))
        with open('train/images_train.csv') as a, open('train/labels_train.csv') as b:
            self.assertEqual(len(a.readlines()), len(b.readlines()))

    def runTest(self):
        # run tests
        self.ImageFileSize_test()
        self.trainingData_test()

if __name__ == '__main__':
    unittest.main()
