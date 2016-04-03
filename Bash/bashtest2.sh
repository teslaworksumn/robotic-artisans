#!/bin/bash
python3 ImageProcessor/IP1.py | tee text0.txt

PTG=$(tail -1 text0.txt)
echo ----------
echo $PTG
echo ----------
./painter_trim_modified  > brushstrokes.txt <<END
$PTG
END

python3 GCoder.py 
#> xyz.gcode

#newpainter -ci $PTG
echo "Which arm are you using: Droid(1), Ultamira(2), DaVinci(3)"
read arm
if [ $arm == '1' ]; then
  Inter="interpreter"
elif [ $arm == "2" ]; then 
  echo Ultamira interpreter
elif [ $arm == "3" ]; then
  echo DaVinci Interpreter
else
  echo not an arm
fi

octave <<End2
$Inter
quit()
End2


