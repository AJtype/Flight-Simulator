# Flight-Simulator
This project will simulate the flight of multiple UAVs circling a point.  
The UAVs will all start from a given location and fly to the center of the circle. 
from there, they will start to circle the point at a specific distance from the point.  

## Input
The system will read from 2 files called SimParams.ini and SimCmds.txt  

### Params
The params will include:  
1. Dt - The time between iterations  
2. N_uav - The amount of UAVs to simulate  
3. R - Radius of the flight cirlce of the UAVs  
4. X0 - Starting X location of UAVs, before getting to there standart flight pattern in meters  
5. Y0 - Starting Y location of UAVs, before getting to there standart flight pattern in meters  
6. Z0 - Starting height of the UAVs in meters  
7. V0 - Starting speed of all the UAVs in meters per second  
8. Az - The initial direction that all tools face. azimuth 0 is parallel to the X axis  
9. TimeLim - Length of the simulation in seconds.  

### Commands
The code allows to check the target of UAV with a command read from a file called SimCmds.txt.  
This file will have multiple lines.    
Each line has new instruction for a specified UAV to change his circle center.  
He must first get to the new center, than start to circle it.  
The params for each line will include: (time num x y).  
1. time - when to start the new command.  
2. num - the id of the target UAV.  
3. x - x coordinations for the new center.  
4. y - y coordinations for the new center.  

## Output
* The location of each UAV will be written to a seperate file.  
File name example: UAV1.txt for the first UAV.  
* On each step a new line will be added to each file.  
The line will be in the following format: time x y azimuth  
* Each number will be a floating point with 2 integers after the dot 
* The output files can be animated using the python scripts.   

### Show Course
To path of the UAVs you can use the python scripts.  
To show the final result of the path, use endResult.py:  
python .\endResult.py  
To show the animated path you may use draw.py:  
python .\draw.py  

## Compilation Lines
for compiling the whole project from src:  
g++ .\main.c++ .\UAV\UAV.c++ .\Utils\utils.c++ .\SimParams\SimParams.c++  
  
for compiling the whole project from base folder:  
g++ .\src\main.c++ .\src\UAV\UAV.c++ .\src\Utils\utils.c++ .\src\SimParams\SimParams.c++  
  
for compiling SimParamsTests:
g++ .\SimParamsTests.c++ ..\src\SimParams\SimParams.c++ ..\src\Utils\utils.c++

for compiling UAVTests:
g++ .\UAVTests.c++ ..\src\UAV\UAV.c++ ..\src\Utils\utils.c++ ..\src\SimParams\SimParams.c++

for compiling utilsTests:
g++ .\utilsTests.c++ ..\src\Utils\utils.c++

## Notes
* Azimuth 0.0 is pointing right. can be changed in func updateVelocity

### Ideas to improve
* Right now there is a bug if a dt is input that is too big. The UAV may miss its target.  
   There are two options on how to solve it.  
   1. Check after each movement if the UAV has moved passed the target (Unefficient, too many repeating checks).  
   2. When heading towards a target (or finding the path to it) check if the UAV will pass it in the next dt.  
        If it will, calculate how much of the dt it will take to get to the target.  
        Call update again with the right amount of dt to get to the target. Than change to the next state.  
        Than call update again with the remaining dt.  
        it will look something like this:  
```C++  
if (get to target before end of dt)  
   double remainingDt = calcTimeToGetToTarget();  
   update(dt - remainingDt);  
   state = NEXTSTATE // not a real state  
   update(remainingDt);  
   break;  
```
      "I didnt do this solution out of time constraints."