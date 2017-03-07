from PIL import Image
import IP1

COLORS = [(255, 255, 255), (0, 0, 0), (255, 0, 0), (0, 255, 0), (0, 0, 255),
          (255, 255, 0), (0, 128, 0), (0, 128, 128)]
#WHITE, BLACK, RED, GREEN, BLUE, YELLOW, DARK_GREEN, TEAL
#1      2       3     4     5       6       7          8

def getArrayFromPTG(PTGp):
    PTG = open(PTGp,"r")
    PTg = [line for line in PTG]
    a = []
    ptg = PTg[1:]
    y = len(ptg)
    for line in ptg:
        l = line.split(" ")
        for d in l:
            if(d in "12345678"):
                a.append(d)
    PTG.close()
    x = len(a)//y
    print(x)
    print(y)
    return a,x,y

def getRGBList(l):
    b= [COLORS[int(i)-1] for i in l]
    return b

def writeImage(listOfRGB,x,y,filePath):
    im = Image.new("RGB",(x,y))
    p = im.load()
    count=0
    for j in range(y):
        for i in range(x):
            p[i,j] = listOfRGB[count]
            count+=1
    im.save(filePath)

def ptgToImage(ptg):
    output = ptg[:len(ptg)-4]+".jpg"
    a = getArrayFromPTG(ptg)
    writeImage(getRGBList(a[0]),a[1],a[2],output)

#ptgToImage(IP1.getPTGInput())
