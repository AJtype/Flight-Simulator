# Flight-Simulator
This project will simulate the flight of multiple vehicles circling a point.  
The vehicles will all start from a given location and fly to the center of the circle. 
from there, they will start to circle the point at a specific distance from the point.  

## Input
The system will read from 2 files called SimParams.ini and SimCmds.txt  

## Params
The params will include:  
1. Dt [sec] - The time between iterations  
2. N_uav - The amount of vehicles to simulate  
3. R - Radius of the flight cirlce of the vehicles  
4. X - Starting X location of vehicles, before getting to there standart flight pattern in meters  
5. Y - Starting Y location of vehicles, before getting to there standart flight pattern in meters  
6. H - Starting height of the vehicles in meters  
7. V - Starting speed of all the vehicles in meters per second  
8. Az - The initial direction that all tools face. azimuth 0 is parallel to the X axis  
9. TimeLim - Length of the simulation in seconds.  

### Commands
This file will have multiple lines of commands.  
Each line has new instruction for a specified vehicle to change his circle center.  
He must first get to the new center, than start to circle it.  
The params for each line will include: (time num x y).  
1. time - when to start the new command.  
2. num - the id of the target vehicle.  
3. x - x coordinations for the new center.  
4. y - y coordinations for the new center.  

## Output
* The location of each vehicle will be written to a seperate file.  
File name example: UAV1.txt for the first vehicle.  
* On each iteration a new line will be added to each file.  
The line will be in the following format: time x y azimuth  
* Each number will be a floating point with 2 integers after the dot  

## Notes
* Azimuth 0.0 is pointing right. can be changed in func updateVelocity