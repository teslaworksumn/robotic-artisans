function [ angle1, angle2, angle3 ] = InverseKinematicsSolverLITE( l1, l5, ex, ey, ez )
%INVERSEKINEMATICSSOLVERLITE Finds the three angles given the link lengths 
%   and end effector.
%   The x and y axis are to the left and up respectively and z axis is 
%   is inward (really only corresponds to angel3)
B = sqrt(ex^2 + ey^2 + ez^2);
theta = atand(ey/ex) + acosd((l5^2-l1^2-B^2)/(-2*l1*B));
angle1 = 140 - theta;   
angle2 = 185 - (acosd((B^2 - l1^2 - l5^2)/(-2 * l1 * l5)) + theta);
angle3 = 20.9 - atand(ez/ex);
end

