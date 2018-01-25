from PIL import Image
import image_processor

COLORS = [(255, 255, 255), (255, 255, 0), (255, 20, 147), (50, 60, 150),
          (0, 255, 0), (0, 0, 255), (0, 128, 0), (0, 0, 0)]
# WHITE, BLACK, skyblue, RED, GREEN, BLUE, YELLOW, DARK_GREEN
# 1      8       3     4     5       6       2          7


def getArrayFromPTG(PTGp):
    PTG = open(PTGp, "r")
    print(PTG)
    PTg = [line for line in PTG]
    a = []
    ptg = PTg[1:]
    y = len(ptg)
    for line in ptg:
        split_line = line.split(" ")
        for d in split_line:
            if(d in "12345678"):
                a.append(d)
    PTG.close()
    x = len(a)//y
    print(x)
    print(y)
    return a, x, y


def getRGBList(l):
    b = [COLORS[int(i)-1] for i in l]
    return b


def writeImage(listOfRGB, x, y, filePath):
    im = Image.new("RGB", (x, y))
    p = im.load()
    count = 0
    for j in range(y):
        for i in range(x):
            p[i, j] = listOfRGB[count]
            count += 1
    im.save(filePath)


def ptgToImage(ptg):
    output = ptg[:len(ptg)-4]+"R.jpg"
    a = getArrayFromPTG(ptg)
    writeImage(getRGBList(a[0]), a[1], a[2], output)


if __name__ == "__main__":
    # pylint: disable=C0103
    # pylint: disable=C0330
    import argparse
    parser = argparse.ArgumentParser(
        description='Convert an 8-color ptg to an image')
    parser.add_argument('ptg', help='input ptg file')
    args = parser.parse_args()
    ptgToImage(args.ptg)
