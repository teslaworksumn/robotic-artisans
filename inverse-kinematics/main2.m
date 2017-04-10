% Barebones solver, only finds the angles we need (angle1, angle2, angle3)
%   This script uses InverseKinematicsSolverLITE and only needs the length
%   of links 1 and 5, the two links with a full parallelogram and 3 bars 
%   each. This script uses the original GCode Spitter.

totalOutput = [0 0 0];
% Setting the link lengths
l1 = 261.5;
l5 = 285.75;

y = 50;
for i=1:50
    x = 100+i; 
    z = 100;
    
    [angle1, angle2, angle3] = ...
        InverseKinematicsSolverLITE(l1, l5, x, y, z);
    
    totalOutput = GCodeSpitter2(totalOutput,[angle1 angle2 angle3],0); 
end

totalOutput = GCodeSpitter2(totalOutput, [0 0 0], 0);

GCodeSpitter2(totalOutput, [0 0 0],1);