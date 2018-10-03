import os
import settings

gcodeHeader = """G21 (set to mm units)
M3 S225 (initalize servo control)
"""

def prepend(fileName):
    with open(os.path.join(settings.GCODE_DIRECTORY, fileName), "r+") as fin:
        fileData = fin.read()
        fin.seek(0,0)
        fin.write(gcodeHeader.rstrip('\r\n') + '\n' + fileData)