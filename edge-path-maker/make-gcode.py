import Edge_Detection

def makeGCode(edges, width, height):
    commands = []
    oldpoint = (0,0)
    commands += ["G90 (Set to absolute positioning)\n"]
    commands += ["G21 (set to mm units)\n"]
    commands += ["$22=1 $23=2(home)\n"] # this probably needs to be fixed
    for edge in edges:
        commands += ["G1 " + "X" + str(edge[0][0]) + " " + "Y" + str(edge[0][1]) + " Z0 F100"]
        commands += ["G1 X0 Y0 Z5"]
        for point in edge:
            x = point[0]# - oldpoint[0]
            y = point[1]# - oldpoint[1]
            commands += ["G1 " + "X" + str(x) + " " + "Y" + str(y) + " Z0 F100"]
            oldpoint = point
        commands += ["G1 X0 Y0 Z50"]

    return commands

def writeToFile(fileName, gcode):
    fin = open(fileName, "w+")
    for line in gcode:
        fin.write("%s\n" % line)
    fin.close()

if __name__ == '__main__':
    imgName = input("Image name: ")
    fileName = input("GCode file name: ")
    raw_drawing, width, height = Edge_Detection.prepEdgePainter(imgName)
    gcode = makeGCode(raw_drawing, width, height)
    writeToFile(fileName, gcode)
