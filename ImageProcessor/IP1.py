from PIL import Image
import math

COLORS = [(255, 255, 255), (0, 0, 0), (0, 128, 128), (255, 0, 0),
          (0, 255, 0), (0, 0, 255), (255, 255, 0), (0, 128, 0)]
# WHITE, BLACK, TEAL, RED, GREEN, BLUE, YELLOW, DARK_GREEN
# 1      2       3     4     5       6       7          8


# Return list of rgb values for each pixel in the image
def getArrayOfPixels(image):
    a = []
    p = image.load()
    for i in range(image.size[1]):
        for j in range(image.size[0]):
            a.append(p[j, i])
    return a


# Writes a list of single digits to a txt file in .ptg format
def writeToFile(oArray, filePath, rows, cols):
    file = open(filePath, 'a')
    file.write(str(rows)+" "+str(cols)+"\n")
    oArrayPointer = 0
    for j in range(rows):
        for i in range(cols):
            file.write(str(oArray[oArrayPointer])+" ")
            oArrayPointer += 1
        file.write("\n")
    file.close()
    print(filePath)


def rgb2lab(inputColor):
    # Found @ https://stackoverflow.com/questions/
    # 13405956/convert-an-image-rgb-lab-with-python

    num = 0
    RGB = [0, 0, 0]

    for value in inputColor:
        value = float(value) / 255

        if value > 0.04045:
            value = ((value + 0.055) / 1.055) ** 2.4
        else:
            value = value / 12.92

        RGB[num] = value * 100
        num = num + 1

    XYZ = [0, 0, 0, ]

    X = RGB[0] * 0.4124 + RGB[1] * 0.3576 + RGB[2] * 0.1805
    Y = RGB[0] * 0.2126 + RGB[1] * 0.7152 + RGB[2] * 0.0722
    Z = RGB[0] * 0.0193 + RGB[1] * 0.1192 + RGB[2] * 0.9505
    XYZ[0] = round(X, 4)
    XYZ[1] = round(Y, 4)
    XYZ[2] = round(Z, 4)
    # ref_X =  95.047 Observer= 2°, Illuminant= D65
    XYZ[0] = float(XYZ[0]) / 95.047
    XYZ[1] = float(XYZ[1]) / 100.0          # ref_Y = 100.000
    XYZ[2] = float(XYZ[2]) / 108.883        # ref_Z = 108.883

    num = 0
    for value in XYZ:

        if value > 0.008856:
            value = value ** (0.3333333333333333)
        else:
            value = (7.787 * value) + (16 / 116)

        XYZ[num] = value
        num = num + 1

    Lab = [0, 0, 0]

    L = (116 * XYZ[1]) - 16
    a = 500 * (XYZ[0] - XYZ[1])
    b = 200 * (XYZ[1] - XYZ[2])

    Lab[0] = round(L, 4)
    Lab[1] = round(a, 4)
    Lab[2] = round(b, 4)

    return Lab

COLORS_LAB = [rgb2lab(color) for color in COLORS]


def getDistance(lab1, lab2):  # Formula for distance found on Wikipedia
    l1, a1, b1 = lab1
    l2, a2, b2 = lab2
    dl = l1 - l2   # delta L
    # c1 = math.sqrt(a1**2+b1**2)
    # c2 = math.sqrt(a2**2+b2**2)
    # dc = c1-c2
    da = a1-a2
    db = b1-b2
    # dH = math.sqrt(da**2+db**2-dc**2)
    # SL = 1
    # SC = 1+.045*c1
    # SH = 1+.015*c1
    # dE = math.sqrt((dl/SL)**2+(dc/SC)**2+(dH/SH)**2)
    return math.sqrt(da**2+db**2+dl**2)


def matchColor(lab):  # mathces color to one of 8 paint colors
    distances = [getDistance(lab, color_lab) for color_lab in COLORS_LAB]
    minimum = distances[0]
    pos = 0  # the color number is its position in the list COLORS
    count = 1
    for d in distances:
        if d <= minimum:
            minimum = d
            pos = count
        count += 1
    return pos


def getPTG(imagePath, fRows, fCols):
    im = Image.open(imagePath).resize((fCols, fRows))
    pixels = getArrayOfPixels(im)
    outputPath = imagePath[:len(imagePath)-4] + ".ptg"
    paints = [matchColor(rgb2lab(px)) for px in pixels]
    writeToFile(paints, outputPath, fRows, fCols)
    # print(outputPath)
    return outputPath


def getPTGInput():
    a = input("Enter Image(Use double slashes): ")
    c = input("Enter number of rows: ")
    d = input("Enter number of columns: ")
    ratioFile = open("Ratio.txt", 'a') 
    ratioFile.write(str(8.0 / int(c)))
    ratioFile.close()
    print("\n")
    return getPTG(a, int(c), int(d))


getPTGInput()
