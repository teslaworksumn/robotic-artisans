LIFT = "1"#z axis value, only has two possible values
COLOR_POS={"0":(3,3),"1":(0,0),"2":(1,1),"3":(2,2)}# It will look something like this {"Red":(0,0),"Blue":(1,0),...}
#
cur_XY =(0,0)
def makeGCODE(filePathIn, filePathOut):
    fileIn = open(filePathIn,'r')
    fileOut  = open(filePathOut,'a')
    for line in fileIn:
        line = line.replace("\n","")
        if(line[1] == '1'):#Move
            splitLine = line.split(" ")
            fileOut.write(move(splitLine[1],splitLine[2]))
        elif(line[1]=='2'):#Lift
            fileOut.write(lift())
        elif(line[1] =='3'):#Drop brush
            fileOut.write(drop())
        elif(line[1] == '4'):#Refill
            splitLine = line.split(" ")
            fileOut.write(refill(splitLine[1],splitLine[2],splitLine[3]))
        elif(line[1] =='5'):#change color
            splitLine = line.split(" ")
            fileOut.write(changeColor(splitLine[1],splitLine[2],splitLine[3],splitLine[4]))
            
def move(x,y):
    cur_XY=(x,y)
    s = "G1 X "+str(x)+" Y "+str(y)+" Z "+LIFT+' \n'
    #print("G1X"+str(x)+"Y"+str(y)+"Z"+LIFT+'\n')
    return s
def lift():
    LIFT = '1'
    s = "G1 X "+str(cur_XY[0])+" Y "+str(cur_XY[1])+" Z "+LIFT+' \n'
    #print("G1X"+str(cur_XY[0])+"Y"+str(cur_XY[1])+"Z"+LIFT+'\n')
    return s
def drop():
    LIFT = '0'
    s = "G1 X "+str(cur_XY[0])+" Y "+str(cur_XY[1])+" Z "+LIFT+' \n'
    #print("G1X"+str(cur_XY[0])+"Y"+str(cur_XY[1])+"Z"+LIFT+'\n')
    return s
def refill(xi,yi,color):
    x = COLOR_POS.get(color)[0]
    y = COLOR_POS.get(color)[1]
    s = move(x,y)
    s+=drop()
    s+=lift()
    s+=move(xi,yi)
    return s
def changeColor(xi,yi,colori,colorf):
    print(colori)
    print(colorf)
    s=move(COLOR_POS.get(colori)[0],COLOR_POS.get(colori)[1])
    s+=drop()
    s+=move(COLOR_POS.get(colori)[0]+1,COLOR_POS.get(colori)[1])
    s+=lift()
    #s+=move(COLOR_POS.get(colorf)[0],COLOR_POS.get(colorf)[1])
    s+=drop()
    s+=lift()
    s+=move(xi,yi)
    return s
def makeGCodeInput():
    fi = "text1.txt"
    fo = "xyz.gcode"
    makeGCODE(fi, fo)
makeGCodeInput()
