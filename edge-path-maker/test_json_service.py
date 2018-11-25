'''
Copyright Max Omdal 2018. All Rights Reserved.
'''

import unittest
import json_service
import os
import json
import settings

class JsonServiceTestCase(unittest.TestCase):

    def test_formatJSON(self):
        pass

    def test_bulkFormatJSON(self):
        pass
        
    def test_writeToFile(self):
        pass

    def test_readFromFile(self):
        testFilename = "test_read_from_file.json"
        testFileContents = {
            "strokes": [
                {
                    "strokeid": 0,
                    "points": [[1, 1], [2, 2], [1, 4], [5, 2]],
                    "color": "black"
                },
                {
                    "strokeid": 1,
                    "points": [[1, 1], [2, 2], [1, 4], [5, 2]],
                    "color": "black"
                },
                {
                    "strokeid": 2,
                    "points": [[1, 1], [2, 2], [1, 4], [5, 2]],
                    "color": "black"
                }
            ]
        }
        with open(os.path.join(settings.JSON_DIRECTORY, testFilename), "w+") as testFile:
            json.dump(testFileContents, testFile)
        result = json_service.readJSONfromFile(testFilename)
        os.remove(os.path.join(settings.JSON_DIRECTORY, testFilename))
        self.assertEqual(result, testFileContents)

    

if __name__ == '__main__':
    unittest.main()