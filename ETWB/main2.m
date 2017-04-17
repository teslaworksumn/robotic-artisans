% Barebones solver, only finds the angles we need (angle1, angle2, angle3)
%   This script uses InverseKinematicsSolverLITE and only needs the length
%   of links 1 and 5, the two links with a full parallelogram and 3 bars 
%   each. This script uses the original GCode Spitter.

totalOutput = [0 0 0];
% Setting the link lengths
l1 = 257.2;%261.5;
l5 = 279.4;%285.75;

 y = 40;
% for i=1:150
%     x = 270+i; 
%     z = -100 + (2 * i);
%     
%     [angle1, angle2, angle3] = ...
%         InverseKinematicsSolverLITE(l1, l5, x, y, z);
%     
%     totalOutput = GCodeSpitter2(totalOutput,[angle1 angle2 angle3],0); 
% end
%[a1, a2, a3] = InverseKinematicsSolverLITE(l1, l5, 18*25.4, 40, -5.5*25.4);
%totalOutput = GCodeSpitter2(totalOutput, [a1, a2, a3], 0);

% Reading in from a file 
file_name = 'xyzi.txt';
file_in = fopen(file_name);
tline = fgetl(file_in);
while ischar(tline)
    disp(line);
    line = strsplit(tline);
    [angle1, angle2, angle3] = ...
        InverseKinematicsSolverLITE(l1, l5, (16.5-str2double(line{5}))*25.4, ...
        (str2double(line{7})*50.8)+30, (str2double(line{3})-3.875)*20.4);
    totalOutput = GCodeSpitter2(totalOutput,[angle1 angle2 angle3],0);
    tline = fgetl(file_in);
end
fclose(file_in);

totalOutput = GCodeSpitter2(totalOutput, [0 0 0], 0);

GCodeSpitter2(totalOutput, [0 0 0],1);