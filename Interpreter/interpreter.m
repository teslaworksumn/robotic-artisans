%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Gcode Interpreter
% C3-P0 and R2-D2
% Developed by Sam Finnegan
% March 2016
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function interpreter
    xyzId = fopen('xyz.gcode');
    xyz = textscan(xyzId, '%*s %*s %f %*s %f %*s %f');
    angleID = fopen('angle.gcode','w');
    formatSpec = 'G1 T1 %3.3f T2 %3.3f T3 %3.3f\r\n';
    for n=1:length(xyz{1})
        if(xyz{1}(n)==-99 && xyz{2}(n)==-99 && xyz{3}(n)==-99)
            t1=144.0;
            t2=106.0;
            t3=153.0;
        else
        [t1,t2,t3]=interpreter_123(xyz{1}(n),xyz{2}(n),xyz{3}(n));
        end
        fprintf(angleID,formatSpec,t1,t2,t3);
        %pause(.125);
    end
    fclose(xyzId);
    fclose(angleID);
end

function [T1,T2,T3] = interpreter_123(x,y,z)
    A0x=-9; A0y=5; A0z=3.375;
    x0=x-A0x-3.5; y0=y-A0y; z0=z-A0z+1;
    R=sqrt((x0)^2+(y0)^2)-1.5;
    [T1,T2]=interpreter_12(R+z0*1i);
    T3=atan2(x0,y0)*180/pi;
end

function [Theta1,Theta2]= interpreter_12(P)
%Parameter Constants
A0=0+0i; %B0=-2.345+.5i;
%a1=2.378; b1=3.841; c1=1.978; %ternary 1
a2=10.75; b2=14.0; c2=3.430; %ternary 2
%a3=2.0; b3=3.0; c3=2.0; %ternary 3
%r2=8.875; r3=10.125;
r1=7.75; r4=2.625; r5=9.25;
%Theta1_max = 106*pi/180; Theta1_min = 65*pi/180;
Theta2_max = 153*pi/180; %Theta2_min = 110*pi/180;
% Theta = Theta*pi/180;

% p3=P+b3*exp(1i*(Theta+pi));
% tp4 = acos((c3^2-a3^2-b3^2)/(-2*a3*b3));
% p4=P+a3*exp(1i*(Theta+pi-tp4));

p1 = isect2(A0,r1,P,a2);
Theta1 = angle(p1,A0)*180/pi;
% [p2(1),p2(2)] = isect(p1(1),a1,p4,r3);
% [p2(3),p2(4)] = isect(p1(2),a1,p4,r3);

% [q1(1),q1(2)]= isect(p1(1),c1,B0,r2);
% [q1(3),q1(4)]= isect(p1(2),c1,B0,r2);

q3 = isect1(P,b2,p1,c2);

q2 = isect1(q3,r5,A0,r4);
%[q2(3),q2(4)] = isect(q3(2),r5,A0,r4);
t2=angle(q2,A0);
if(t2<Theta2_max)
    Theta2 = t2*180/pi;
else
    q2=isect2(q3,r5,A0,r4);
    Theta2 = angle(q2,A0);
end

hold off;
iplot(A0,p1);
axis([-5 20 -5 15]);
hold on;
itriangle(p1,P,q3,'b');
%itriangle(p2(4),q1(3),p1(2),'r');
%iplot(p2(4),p4);
%iplot(q1(3),B0);
iplot(q3,q2);
iplot(q2,A0);
%itriangle(P,p3,p4,'g');
end

function ans1 = isect1(comp1,r1,comp2,r2)
x1=real(comp1); y1=imag(comp1);
x2=real(comp2); y2=imag(comp2);

d=sqrt((x1-x2)^2+(y1-y2)^2);
l=(r1^2-r2^2+d^2)/(2*d);
h=sqrt(r1^2-l^2);

ans1=l/d*(x2-x1)+h/d*(y2-y1)+x1 +(l/d*(y2-y1)-h/d*(x2-x1)+y1)*1i;
%ans2=l/d*(x2-x1)-h/d*(y2-y1)+x1 +(l/d*(y2-y1)+h/d*(x2-x1)+y1)*1i;
end

function ans2 = isect2(comp1,r1,comp2,r2)
x1=real(comp1); y1=imag(comp1);
x2=real(comp2); y2=imag(comp2);

d=sqrt((x1-x2)^2+(y1-y2)^2);
l=(r1^2-r2^2+d^2)/(2*d);
h=sqrt(r1^2-l^2);

%ans1=l/d*(x2-x1)+h/d*(y2-y1)+x1 +(l/d*(y2-y1)-h/d*(x2-x1)+y1)*1i;
ans2=l/d*(x2-x1)-h/d*(y2-y1)+x1 +(l/d*(y2-y1)+h/d*(x2-x1)+y1)*1i;
end

% function d = dist(comp1,comp2)
% d = sqrt((real(comp1)-real(comp2))^2+(imag(comp1)-imag(comp2))^2);
% end

function a = angle(comp1,comp2)
ang=atan2((imag(comp1)-imag(comp2)),(real(comp1)-real(comp2)));
if(ang<0)
    a=-ang;
else
    a=ang;
end
end

% function iplot3(comp1,comp2,Theta)
% plot([real(comp1),real(comp2)],[imag(comp1),imag(comp2)]);
% end
% 
% function iplot(comp1,comp2)
% plot([real(comp1),real(comp2)],[imag(comp1),imag(comp2)]);
% end
% 
% function itriangle(comp1,comp2,comp3,color)
% fill([real(comp1),real(comp2),real(comp3)],[imag(comp1),imag(comp2),imag(comp3)],color);
% end