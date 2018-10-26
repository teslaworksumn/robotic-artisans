import json
from curve import Curve
import os
import settings

def formatJSON(curve):
    data = {
        "strokeid": curve.STROKEID,
        "points": curve.getPoints(),
        "color": curve.getColor()
    }
    return data

def bulkFormatJSON(curves, colors):
    data = {
        "strokes": []
    }
    for curve in curves:
        data["strokes"].append(formatJSON(curve))
    return data

def writeJSONtoFile(filename, json):
    if fileCheck(filename):
        confirm = userConfirmation("A file with this name already exists. Overwrite? (y/n)")
        if confirm:
            with open(os.path.join(settings.JSON_DIRECTORY, filename), "w+") as writeFile:
                json.dump(data, writeFile)
        else:
            print("No files have been modified")

def readJSONfromFile(filename):
    if fileCheck(filename):
        with open(os.path.join(settings.JSON_DIRECTORY, filename)) as readFile:
            data = json.load(readFile)
            if data != None:
                return data
            else:
                print("The file ", filename, " is empty.")
                
    else:
        print("The file", filename, "does not exist in", settings.JSON_DIRECTORY + ".")

def fileCheck(filename):
    try:
        f = open(os.path.join(settings.JSON_DIRECTORY, filename), "r")
        f.close()
        return 1
    except IOError:
        return 0
    
def userConfirmation(question):
    reply = str(input(question+' (y/n): ')).lower().strip()
    if reply[0] == 'y':
        return True
    if reply[0] == 'n':
        return False
    else:
        userConfirmation("please confirm...")