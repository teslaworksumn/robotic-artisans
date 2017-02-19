function DroboticArmSim(angleC1,angleC2,L1,GL1,L5,L6,angle6,L8,angleC3)


    clf;
    title('Parallelagram Robotic arm simulation 1.0');
    
    %this is cause of a weird thing with the graphing window, see line 121
    %for explanation
    xlabel('Z');
    ylabel('X');
    zlabel('Y');
    grid on;
    %define the window size, maybe this will work for 3d? I think so?
    axis([-350 350 -350 350 -200 500]);
    view([45 45]);

    %we're going to do this the right way and put all the endpoints and
    %angles into matrices

    endpt = zeros(10,3);
    angle = zeros(10,1);
   
    L2 = L1; 
    endpt(2,1) = -60; 
    endpt(2,2) = 20; 
    %modify for 3D 
    endpt(2,3)= endpt(2,1)*cosd(angleC3);
    endpt(2,1)= endpt(2,1)*sind(angleC3);
  
    %solve for end point of L1; 
    endpt(3,2) = sind(angleC1)*L1;
    endpt(3,1) = cosd(angleC1)*L1;
    %modify for 3d 
    endpt(3,3)= endpt(3,1)*cosd(angleC3);
    endpt(3,1)= endpt(3,1)*sind(angleC3);
   

    % we found our L1 point in space, now we can make a triangle between that
    % point,the ground point, and use the length of GL1and L2, then solve for
    % angles
   
    diff = endpt(3,:)-endpt(2,:);
   
    tempSide=(sqrt(diff(1)^2+diff(2)^2+diff(3)^2));
    angle(1)=atand(diff(2)/diff(1));
    %law of cosines 
    angle(2) = acosd((L2^2-GL1^2-tempSide^2)/(-2*GL1*tempSide));
    %law of sines 
    angle(3) = asind(sind(angle(2))*GL1/L2);
    angle(4) = angleC1;

    %solve for endpt of L2 modify for 3d 
    endpt(4,2) = sind(angle(4))*L2;
    endpt(4,1) = cosd(angle(4))*L2;
    %modify for 3d 
    endpt(4,3)= endpt(4,1)*cosd(angleC3);
    endpt(4,1)= endpt(4,1)*sind(angleC3);
    endpt(4,:) = endpt(4,:)+ endpt(2,:);

    % now we need to add the second control parallelagram, 
    L3=GL1;
    L4=L1; %because parallagrams
    angle(5)=angleC1; 

    % solve for links 3 and 4 in box2, plot 
   
    endpt(5,2) = sind(angleC2)*L3;
    endpt(5,1) = cosd(angleC2)*L3;
    %modify for 3d 
    endpt(5,3)= endpt(5,1)*cosd(angleC3);
    endpt(5,1)= endpt(5,1)*sind(angleC3);
 
    
 
    endpt(6,2) = sind(angle(5))*L4;
    endpt(6,1) = cosd(angle(5))*L4;
    %modify for 3d 
    endpt(6,3)= endpt(6,1)*cosd(angleC3);
    endpt(6,1)= endpt(6,1)*sind(angleC3);
   
    endpt(6,:) = endpt(6,:)+endpt(5,:); 

    angle(6)= angleC2+180; %because parallalagrams 
  
    endpt(7,2) = sind(angle(6))*L5;
    endpt(7,1) = cosd(angle(6))*L5;
    %modify for 3d 
    endpt(7,3)= endpt(7,1)*cosd(angleC3);
    endpt(7,1)= endpt(7,1)*sind(angleC3);
    endpt(7,:) = endpt(7,:)+endpt(6,:); 

    angle(7)=angle6; %this angle is defined in rArmsimulator
    
    endpt(8,2) = sind(angle(7))*L6;
    endpt(8,1) = cosd(angle(7))*L6;
    %modify for 3d 
    endpt(8,3)= endpt(8,1)*cosd(angleC3);
    endpt(8,1)= endpt(8,1)*sind(angleC3);
    endpt(8,:) = endpt(8,:)+endpt(3,:); 

    L7 = L5-L3; 
    angle(8) = angle(6); 
    
    endpt(9,2) = sind(angle(8))*L7;
    endpt(9,1) = cosd(angle(8))*L7;
    %modify for 3d 
    endpt(9,3)= endpt(9,1)*cosd(angleC3);
    endpt(9,1)= endpt(9,1)*sind(angleC3);
    endpt(9,:) = endpt(9,:)+endpt(8,:); 

    %define end effector -- pretty much arbitray 
    angle(9) = angle(7)-75; 
 
    endpt(10,2) = sind(angle(9))*L8;
    endpt(10,1) = cosd(angle(9))*L8;
    %modify for 3d 
    endpt(10,3)= endpt(10,1)*cosd(angleC3);
    endpt(10,1)= endpt(10,1)*sind(angleC3);
    endpt(10,:) = endpt(10,:)+endpt(9,:); 

    
    
    % i did this to make the graph work better, new order [Z X Y] 
    temp = endpt(:,2);
    endpt(:,2)=endpt(:,3);
    endpt(:,3)=temp;
    
    %control link is red 
    line([endpt(1,1) endpt(3,1)],[endpt(1,2) endpt(3,2)],[endpt(1,3) endpt(3,3)] ,'color',[1 0 0]);
    line([endpt(2,1) endpt(4,1)],[endpt(2,2) endpt(4,2)],[endpt(2,3) endpt(4,3)]); 
    % ground link is black
    line([endpt(1,1) endpt(2,1)], [endpt(1,2) endpt(2,2)],[endpt(1,3) endpt(2,3)],'color',[0 0 0]);
    line([endpt(3,1) endpt(4,1)], [endpt(3,2) endpt(4,2)],[endpt(3,3) endpt(4,3)],'color',[0 0 0]);
    %control link 2 is red 
    line([endpt(1,1) endpt(5,1)],[endpt(1,1) endpt(5,2)],[endpt(1,1) endpt(5,3)],'color',[1 0 0]);
    line([endpt(5,1) endpt(6,1)],[endpt(5,2) endpt(6,2)],[endpt(5,3) endpt(6,3)]);
    % just connect the last link, this link leads into box3
    line([endpt(6,1) endpt(3,1)],[endpt(6,2) endpt(3,2)],[endpt(6,3) endpt(3,3)],'color',[0 1 0]);
    line([endpt(6,1) endpt(7,1)],[endpt(6,2) endpt(7,2)],[endpt(6,3) endpt(7,3)],'color', [1 0 0]);
    line([endpt(3,1) endpt(8,1)],[endpt(3,2) endpt(8,2)],[endpt(3,3) endpt(8,3)],'color',[0 0 0]);
    % connect the mid link 
    line([endpt(4,1) endpt(8,1)],[endpt(4,2) endpt(8,2)],[endpt(4,3) endpt(8,3)],'color',[0 0 0]);
    line([endpt(8,1) endpt(9,1)],[endpt(8,2) endpt(9,2)],[endpt(8,3) endpt(9,3)]);
    %fill in end effector link 
    line([endpt(7,1) endpt(9,1)],[endpt(7,2) endpt(9,2)],[endpt(7,3) endpt(9,3)],'color',[0 0 0]);
    line([endpt(7,1) endpt(10,1)],[endpt(7,2) endpt(10,2)],[endpt(7,3) endpt(10,3)],'color',[0 0 0]);
    %complete the end effector
    line([endpt(10,1) endpt(9,1)],[endpt(10,2) endpt(9,2)],[endpt(10,3) endpt(9,3)],'color',[0 0 0]);
    hold on
    scatter3(0,0,0);
    hold on
    endpt

    % for GcodeSpitter.m
    controlAngle3 = atand(endpt(3,1)/endpt(3,2));
    lengthCarm1 = sqrt(endpt(3,1)^2+endpt(3,2)^2);
    controlAngle1 = atand(endpt(3,3)/lengthCarm1);

    lengthCarm2 = sqrt(endpt(5,1)^2+endpt(5,2)^2);
    controlAngle2 = atand(endpt(5,3)/lengthCarm2);

    outputAngles = [controlAngle1, controlAngle2, controlAngle3];
    GcodeSpitter(outputAngles,0); 

    drawnow;
end 
