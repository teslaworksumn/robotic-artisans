LIFT = "1"#z axis value, only has two possible values
COLOR_POS={"1":(-2,0),"2":(-2,2.5),"3":(-2,5),"4":(-2,7.5),"5":(10,0),"6":(10,2.5),"7":(10,5),"8":(10,7.5)}# It will look something like this {"Red":(0,0),"Blue":(1,0),...}
#

ratioFile = open("Ratio.txt",'r')
Ra = ratioFile.readline()
R = float(Ra)
ratioFile.close()
def makeGCODE(filePathIn, filePathOut):
    fileIn = open(filePathIn,'r')
    fileOut  = open(filePathOut,'a')
    cur_XY=(0,0)
    
    for line in fileIn:
        line = line.replace("\n","")
        if(len(line)==0):
            print('Not valid line')
        elif(line[1] == '1'):#Move
            splitLine = line.split(" ")
            fileOut.write(move(splitLine[1],splitLine[2]))
            cur_XY=(int(splitLine[1]),int(splitLine[2]))
        elif(line[1]=='2'):#Lift
            fileOut.write(lift(cur_XY))
        elif(line[1] =='3'):#Drop brush
            fileOut.write(drop(cur_XY))
        elif(line[1] == '4'):#Refill
            splitLine = line.split(" ")
            fileOut.write(refill(splitLine[1],splitLine[2],splitLine[3],cur_XY))
        elif(line[1] =='5'):#change color
            splitLine = line.split(" ")
            fileOut.write(changeColor(splitLine[1],splitLine[2],splitLine[3],splitLine[4],cur_XY))
            
def move(x,y):
    
    s = "G1 X "+str(int(x)*R)+" Y "+str(int(y)*R)+" Z "+LIFT+' \n'
    #print("G1X"+str(x)+"Y"+str(y)+"Z"+LIFT+'\n')
    return s
def lift(cur_XY):
    LIFT = str(1)
    s = "G1 X "+str(cur_XY[0]*R)+" Y "+str(cur_XY[1]*R)+" Z "+LIFT+' \n'
    #print("G1X"+str(cur_XY[0])+"Y"+str(cur_XY[1])+"Z"+LIFT+'\n')
    return s
def drop(cur_XY):
    LIFT = '0'
    s = "G1 X "+str(cur_XY[0]*R)+" Y "+str(cur_XY[1]*R)+" Z "+LIFT+' \n'
    #print("G1X"+str(cur_XY[0])+"Y"+str(cur_XY[1])+"Z"+LIFT+'\n')
    return s
def refill(xi,yi,color,cur_XY):
    x = COLOR_POS.get(color)[0]
    y = COLOR_POS.get(color)[1]
    s = ''
    s+=goHome()
    s+=move(x,y)
    s+=drop(cur_XY)
    s+=lift(cur_XY)
    s+=move(xi,yi)
    return s
def changeColor(xi,yi,colori,colorf,cur_XY):
    print(colori)
    print(colorf)
    #s=move(COLOR_POS.get(colori)[0]/R,COLOR_POS.get(colori)[1]/R)
    #s+=drop()
    #s+=move(COLOR_POS.get(colori)[0]+1,COLOR_POS.get(colori)[1])
    #s+=lift()
    s=''
    s+=goHome()
    s+=move(COLOR_POS.get(colorf)[0],COLOR_POS.get(colorf)[1])
    s+=drop(cur_XY)
    s+=lift(cur_XY)
    s+=move(xi,yi)
    return s
def makeGCodeInput(
):
    fi = "brushstrokes.txt"
    fo = "xyz.gcode"
    makeGCODE(fi, fo)
def goHome():
    s = "G1 X -99 Y -99 Z -99 \n"
    return s
makeGCodeInput()
