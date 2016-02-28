LIFT = ""#z axis value, only has two possible values
COLOR_POS={}# It will look something like this {"Red":(0,0),"Blue":(1,0),...}

def makeGCODE(filePathIn, filePathOut):
    fileIn = open(filePathIn,'r')
    fileOut  = open(filePaathOut,'a')
    for line in fileIn:
        if(line[1] == '1'):#Move
            splitLine = line.split(" ")
            move(splitLine[1],splitLine[2])
        elif(line[1]=='2'):#Lift
            lift()
        elif(line[1] =='3'):#Drop brush
            drop()
        elif(line[1] == '4'):#Refill
            splitLine = line.split(" ")
            refill(splitLine[1],splitLine[2],splitLine[3])
        elif(line[1] =='5'):#change color
            splitLine = line.split(" ")
            changeColor(splitLine[1],splitLine[2],splitLine[3],splitLine[4])
            
def move(x,y):
    fileOut.write("G1X"+str(splitLine[1])+"Y"+str(splitLine[2])+'\n')
def lift():
    LIFT = 'liftValue'
    fileOut.write("G1Z"+LIFT+'\n')
def drop():
    LIFT = 'dropValue'
    fileOut.write("G1Z"+LIFT+'\n')
def refill(xi,yi,color):
    move(COLOR_POS.get(color)[0],COLOR_POS.get(color)[1])
    drop()
    lift()
    move(xi,yi)
def changeColor(xi,yi,colori,colorf):
    move(COLOR_POS.get(colori)[0],COLOR_POS.get(colori)[1])
    drop()
    move(COLOR_POS.get(colori)[0]+1'''<---change this''',COLOR_POS.get(colori)[1])
    lift()
    move(COLOR_POS.get(colorf)[0],COLOR_POS.get(colorf)[1])
    drop()
    lift()
    move(xi,yi)

            
