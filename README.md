Hello# RoboticArtisans

This repo translates an image file into a Gcode for the robot.
Codestyle: pylint linter should be used for all source files.
![](master-repo-uml.png?raw=true)

## General Information:

**Arduino**:
Holds the current code for the arduino to control the arms

**Droids**:
Will eventually be the repos for the droid automated and droid teleoperated

**ImageProcessor**:
Contains code for transforming a .jpg to .ptg (a matrix of numbers that correspond to a color to a brush placement)

**pathPlanners**:
code that takes the ptg and tries to find an optimal path for the brush to take

**strks_to_GCode**:
code that simply converts a text file of brushstrokes to GCode movements

Github: https://github.com/teslaworksumn/guild-master.git
