import unittest
import os
from PIL import Image
import numpy as np
import quadrant_finder

class split_pic_test(unittest.TestCase):

    def check_even_split(self):
        img = np.arange(64).reshape((8,8))
        img = Image.fromarray(img, 'L')
        img.show()
        r = quadrant_finder.split_pic(2, 2, PILimg = img)
        for i in r:
            imgPart = Image.fromarray(i, 'L')
            imgPart.show()

    def runTest(self):
        # run tests
        self.check_even_split()

if __name__ == '__main__':
    unittest.main()
