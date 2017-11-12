import unittest
from PIL import Image
class Image_processor_test(unittest.TestCase):
    def ImageFileSize_test(self):
        img = Image.open('data/circle_resized/banner-9_resized.png')
        assert(img.size == (500,500))
    def runTest(self):
        # run tests
        self.ImageFileSize_test()

if __name__ == '__main__':
    unittest.main()
