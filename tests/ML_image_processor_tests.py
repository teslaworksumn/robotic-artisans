import unittest

class Image_processor_test(unittest.TestCase):
    def runTest(self):
        # run tests

    def ImageFileSize_test(self):
        
        for image in images


def suite():
    suite = unittest.TestSuite()
    # add all the tests to suite
    suite.addTest(Image_processor_test)
    return suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    test_suite = suite()
    runner.run(test_suite)
