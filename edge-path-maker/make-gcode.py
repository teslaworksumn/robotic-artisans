import edge_detection
import gcode_postprocessing
import settings
import os

def makeGCode(edges, width, height):
    commands = []
    oldpoint = (0,0)
    for edge in edges:
        commands += ["S225"]
        i = 0
        for i in range(0, len(edge) - 2, 2):
            point = edge[i]
            x = point[0]# - oldpoint[0]
            y = point[1]# - oldpoint[1]
            commands += ["G91 G0 " + "X" + str((x - oldpoint[0])/settings.SCALE_FACTOR) + " " + "Y" + str((y - oldpoint[1])/settings.SCALE_FACTOR)]
            oldpoint = point
            if(i == 0):
                commands += ["S255"]
        for i in range(len(edge)-2, len(edge)):
            point = edge[i]
            x = point[0]# - oldpoint[0]
            y = point[1]# - oldpoint[1]
            commands += ["G91 G0 " + "X" + str((x - oldpoint[0])/settings.SCALE_FACTOR) + " " + "Y" + str((y - oldpoint[1])/settings.SCALE_FACTOR)]
            oldpoint = point
    return commands

def writeToFile(fileName, gcode):
    with open(os.path.join(settings.GCODE_DIRECTORY, fileName), "w+") as fin:
        for line in gcode:
            fin.write("%s\n" %line)
    gcode_postprocessing.prepend(fileName)

if __name__ == '__main__':
    imgName = input("Image name: ")
    fileName = input("GCode file name: ")
    if (imgName == ""):
        imgName = "tesla_works_logo.png"
        print("No image name given. Using default image")
        if (fileName == ""):
            fileName = "tesla_works_logo.gcode"
            print("no file name given. Using default file name")
    elif (fileName == ""):
        raise ValueError("you must give a file name")
    raw_drawing, width, height = Edge_Detection.prepEdgePainter(settings.IMAGES_DIRECTORY + imgName)
    gcode = makeGCode(raw_drawing, width, height)
    writeToFile(fileName, gcode)