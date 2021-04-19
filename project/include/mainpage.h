/*! \mainpage CSCI 3081 Delivery Simulation project
* **Extra Credit** 
This version does run on the extra credit files, including: multiple_drones.json, 
multiple_customers.json, multiple_packages.json, and multiple_deliveries.json \n


* **To obtain the code**, in the terminal, type:
<PRE> $ git clone https://github.umn.edu/umn-csci-3081-s21/repo-iter2-10-22.git </PRE>
This will prompt you to sign in into your Github. If you have the right access, 
you would be able to obtain the code. To compile the code, navigate to the 
"repo-iter2-10-22" directory that you just download from github by typing:
<PRE> $ cd repo-iter2-10-22 </PRE>
**To compile the code**, in the terminal, type:
<PRE> $ make </PRE>
* **To run the simulation**, there are two ways: 
- If you are using **Docker**, after install all of the Docker software needed
for your environment, in directory "repo-iter2-10-22", type the following commands 
to the terminal:
<PRE> $ bin/build-env.sh </PRE>
This will help build the docker image. To run docker image:
<PRE> bin/run-env.sh </PRE>
Build project web server (inside docker image), navigate to the "repo-iter2-10-22"
directory, then:
<PRE> $ make </PRE>
To run the web server (inside docker image), inside "repo-iter2-10-22" directory:
<PRE> $ ./bin/run.sh </PRE>
*
- If you are using **VOLE**, navigate to "repo-iter2-10-22" directory, then 
<PRE> $ cd project </PRE>
<PRE> $ make </PRE>
<PRE> $ ./bin/run.sh </PRE> 
*
- Note that the project is not designed to work on SSH yet \n

* **Dicussion of concrete factory pattern vs. abstract factory pattern vs. composite
factory pattern**

<CENTER>
\image html ConF.png "Figure 1. Concrete Factory Pattern" 
</CENTER>

First, we begin with the concrete factory pattern. As we can see in Figure 1, there
is a new class call EntityFactory that is responsible for creating Entity. This prevents 
the program to have a lot of different Entity derived classes and to not know which one
would be created until runtime. This is good; however, there is still tight coupling. 
Everytime we have a new Entity derived class, we have to add new case/ new if else 
statement in EntityFactory. Here is how Abstract Factory come to the story. 

<CENTER>
\image html AF.png "Figure 2. Abstract Factory Pattern" 
</CENTER>

Figure 2 depicts how the UML of this program would look like if we employ Abstract 
Factory pattern. EntityFactory becomes an abstract class, pushing the creation of
each Entity derived class into subclasses. For example, Drone object is created by
DroneFactory. With this model, every time we create a new Entity derived class, we
just need to create a new subclass of EntityFactory. However, even with this pattern,
the CreateEntity function of DeliverySimulation still contains a thread of if-else
statement to decide which Entity to create. This is not idea, since every time we
add a new Entity derived class, we still have to edit our CreateEntity function in
DeliverySimulation. This is where Composite Factory Pattern helps.  

<CENTER>
\image html Com.png "Figure 3. Composite Factory Pattern"
</CENTER>

With the Composite Factory pattern, we can just create a CompositeFactory attribute
in DeliverSimulation class, then use that to link to the other attribute. This would
eliminate the long list of if and else statement anywhere in the code, and allow 
easy addition of new Entity derived as well as EntityFactory derived classes. 


* **Discussion about the composite factory pattern** implemented in the package 
delivery system:

So we have discussed about the advantage of Composite Factory Pattern in the previous
section. This pattern is excellent; however, it does have some disadvantages. The
most obvious cons of composite factory pattern is that it might be difficult to provide
a common interface for classes whose functionality differs too much. We might need 
to overgeneralize the componenent interface, making it harder to comprehend. In
addition, the cons from this package delivery simulation, the composite factory 
pattern requires more classes to be created. It is hard to see the relationship
between these classes even with a UML diagram. 

* **Designing and Implementing Strategy Pattern** <br>

In order to implement the strategy pattern in regards to choosing which route strategy 
for the drone to follow, we had to make several changes to our existing code. First, 
we had to create the interface which the concrete strategies would override. This abstract 
interface class is called RouteStrategy and it has the method GetRoute. We also have three 
concrete strategy classes; SmartRoute, BeelineRoute, and ParabolicRoute. These concrete 
classes inherit from RouteStrategy, and they implement the GetRoute method to their own 
specifications. Once we had this structure in place, we had to alter the drone and robot 
classes to extract the path type information from the json details. Once the constructor 
was aware of which type of path was specified, it would store a pointer to that class type 
in it’s routeStrategy attribute. This way, when we are in the delivery simulation, we can 
call the GetRoute method from the routeStrategy attribute of the carrier. The default route 
is set to smart path, and for the robots, only smart path is implemented (as robots cannot 
fly).

<CENTER>
\image html StrategyPattern.png "Figure 4. Strategy Pattern used to develop Route Strategy, including 
BeelineRoute, SmartRoute and ParabolicRoute"
</CENTER>

At first it was difficult to understand the strategy pattern for us, but after working 
through different examples in class and online (https://www.geeksforgeeks.org/strategy-pattern-set-2/), 
we were able to better apply the strategy pattern to our own code.

* **Designing and Implementing Observer Pattern** <br>

In this project, **observer Pattern** is implemented to notify the observers (the WebSceneViewers and the 
EntityConsoleLogger) about change(s) in subjects (drones, robots, or packages). For the drones and robots, 
notifications are sent when they become idle or moving. For the packages, notifications are sent when the 
package is scheduled to be delivered, is en route (picked up), or is delivered. 

We are given the implementation of the Observer classes (including the WebSceneViewers and the 
EntityConsoleLogger classes), and therefore only need to write implementations for ASubject class, as well
as its functionaility, and relate it to Drone, Package and Robot class. Following is the UML depecting the
relationship of the Observer pattern that we implement. 

<CENTER>
\image html Observer_Pattern.png "Figure 4. Observer Pattern used to send notification about drones, robots, 
and package to selected observers"
</CENTER>

* **Designing and Implementing Different Route** <br>

Drones and Robots are carriers, where they can deliver from a source to the designated location. 
When a carrier moves, it notifies to all the observers the path of its current destination. 
Likewise, when a carrier stops moving, it also notifies all the observers. To go to the destination, 
there are three different route options that carriers can use, such as the SmartRoute, BeelineRoute, 
and ParabolicRoute, all of which are handled by RouteStrategy. However, the only strategy for the 
robots to deliver is the smart route since they cannot fly whereas the drones can use all three 
strategies since they are able to move in any 3D space (except buildings). The default strategy for 
the deliveries is the SmartRoute.

The **SmartRoute** uses the A* algorithm to find the shortest path, which uses the IGraph::GetPath() 
function. This path allows both the robot and the drone to deliver on the specified "roads" without 
having to worry about colliding into buildings.

For the **BeelineRoute**, the only type of carrier that can use this beeline path is for the drone, 
where it flies up to a height of 400 from its source location. It then flies horizontally to its 
destination. Lastly, it flies down to the ground to reach the destination. The beeline route uses 
the height of 400 so it prevents the drones to not hit any building that crosses its path from one 
place to another.

For the last strategy, **ParabolicRoute,** only the drones can use the parabolic path where it 
followed by a smooth projectile curve. The calculation is as follows:

<PRE>
y = (1 - distance(V, Vm)^2 / distance(Vo, Vm)^2) * j (2), where

Vo is our source point
V is the point we are moving to
Vm is our midpoint equal to distance(source, destination) / 2
T is the number of steps we are estimating
Vt is our step interval equal to distance(source, destination) / T
j is a tuning parameter that we can use to avoid building collision and scale the parabola's slope
</PRE>

Right now, when the package is somewhat in a building, drone clips that building a little bit in the 
scene when getting the package on its descent

* **General roles of members**
| Roles 	        | Member Name       |  Priority Task
| :---------------: |:-----------------:|:-------------------------------------------------------
|-------------------|-------------------|--------------------------------------------------------
| Development Lead  | Lin Huynh         | - Make major decisions for design and implementation
|                   |                   | such as how the drone/robot should behave when battery 
|                   |                   | is out (drone should free fall into the ground before 
|                   |                   | releasing the package)
|-------------------|-------------------|--------------------------------------------------------
| Scheduler         | Aunya Mukherjee   | - First use when2meet.com to figure out a time that all 
|                   |                   | team members are available to meet, then make Google
|                   |                   | Calendar events and invites
|-------------------|-------------------|--------------------------------------------------------
| Reporter          | Dustin Zhang      | - In charge of making meeting minutes and taking notes
|                   |                   | during team's meetings
|-------------------|-------------------|--------------------------------------------------------
| Project Manager   | Wiley Bui         | - Keep team members on track and make sure group 
|                   |                   | deadlines are being met. Manage the project timeline 
|                   |                   | using trello and plan

* **Gantt Chart**
<CENTER>
\image html Gantt_chart.png "Figure 5. Gantt chart to show work progress"
</CENTER>

* **Distribution of tasks among members**

| Members	        |   Priority Task	                                                    |   Github Issue number |	Collaborate with (if any)
| :---------------: | :-------------------------------------------                          | :-------------------: | :-----------------------------
|-------------------|-----------------------------------------------------------------------|-----------------------|----------------------------------------------
| Wiley Bui         | Add a Robot entity to deliver packages                                | 1                     | n/a
|                   | Refactor: move Update() from IEntity to ASubject & misc. work         | 22                    | n/a
|                   | Test: add additional Google Tests on untested functions               | 29                    | Dustin Zhang
|                   | Refactor entities' unique IDs                                         | 33                    | n/a
|                   | Implement BeelinePath() for Drone	                                    | 38                    | n/a
|                   | Adding Documentation	                                                | 48	                | Dustin Zhang, Aunya Mukherjee, Lin Huynh
|-------------------|-----------------------------------------------------------------------|-----------------------|----------------------------------------------
| Dustin Zhang	    | Test: Make Google tests for the robot class                           | 11                    | n/a	
|                   | Refactor: Moving Robot Update function to Carrier Class	            | 15                    | n/a	
|                   | Test: add additional Google Tests on untested functions	            | 29	                | Wiley Bui
|                   | Implement Parabolic Path for Drone	                                | 40                    | n/a
|                   | Adding Documentation	                                                | 48	                | Wiley Bui, Aunya Mukherjee, Lin Huynh
|-------------------|-----------------------------------------------------------------------|-----------------------|----------------------------------------------
| Aunya Mukherjee	| Create ASubject Class for the Observer Pattern	                    | 3	                    | Lin Huynh
|                   | Test: Making Google Tests for ASubject Class	                        | 7                     | n/a	
|                   | Feature: change package to inherit from Asubject 	                    | 23                    | n/a	
|                   | Bug: Package left undelivered in all_scenes.json simulation	        | 24	                | n/a
|                   | Implement General Strategy Pattern	                                | 37                    | n/a
|                   | Adding Documentation	                                                | 48	                | Dustin Zhang, Wiley Bui, Lin Huynh
|-------------------|-----------------------------------------------------------------------|-----------------------|----------------------------------------------
| Lin Huynh	        | Create Carrier class to be the base class of Drone and Robot	        | 2                     | n/a		
|                   |	Bug: two drones move if there is one package	                    | 5                     | n/a		
|                   |	Update Drone class to adopt ASubject class	                        | 9                     | n/a	
|                   |	Observer Info does not showing up in Simulation	                    | 13                    | n/a	
|                   |	Inherit Robot class to ASubject	                                    | 18                    | n/a	
|                   |   Refactor SetRoute of Carrier	                                    | 20                    | n/a	
|                   |	Battery Capacity for Robot 	                                        | 44                    | n/a	
|                   |   Adding Documentation	                                            | 48            	    | Dustin Zhang, Aunya Mukherjee, Wiley Bui
|                   |   Gantt chart                                                         | n/a                   | n/a


* **Summary of Team Meetings** <br>

Team usually meets 1 or 2 times a week. The following only contains meetings for iteration 2, but we also had meetings for iteration 1
| Meeting Date      |   Objective Summary
| :---------------: | :---------------------------------------------------------------------------------------------------   
|-------------------|-----------------------------------------------------------------------------------------------------
| 3/23/2021         | - Finish in-class exercise #9
|                   | - Discuss what version of code to use (Lin's version)
|                   | - Discuss the requirement for iteration 2 (including abstract ASubject, concerte subject, etc)
|                   | - Set up a timeline for work
|                   | 1. Implement ASubject  abstract class
|                   | 2. Implement Robot
|                   | 3. Implement Inheritance to existing classes (Drone, package, robot)
|                   | 4. Write Google Test
|                   | - Delegate work
|                   | + Lin and Aunya: ASubject class, Update Drone and Package to have inheritance 
|                   | + Wiley and Dustin: Implement Robot class and create google tests
|                   | - Next Meeting: Friday 3/26/21 (1PM - 2PM)
|-------------------|-----------------------------------------------------------------------------------------------------
| 3/26/2021         | - Update from members
|                   | + Lin:
|                   | 1. Create Carrier class and test
|                   | 2. Implement GetStatus for Drone
|                   | 3. Implement AddObserver and RemoveObserver in DeliverSimulation
|                   | 4. Fix bug where two drones fly together when there is only one package
|                   | 5. Get Battery pattern to work for Drone (check test drone_low_battery a and b json)
|                   | 6. Work with Aunya to finish ASubject
|                   | + Aunya:
|                   | 1. Finish ASubject
|                   | + Wiley and Dustin:
|                   | 1. Finished robot class and gtest 
|                   | - Answer questions from members
|                   | - Fix segmentation fault together
|                   | - Delegate work: keep working on tasks from 3/23
|-------------------|-----------------------------------------------------------------------------------------------------
| 3/30/2021         | - Update from members
|                   | + Lin:
|                   | 1. Refactor AddPosition to SetRoute
|                   | + Aunya:
|                   | 1. Finish Package inherited from ASubject
|                   | + Wiley and Dustin:
|                   | 1. Fixed some google tests together. 
|                   | - Answer questions from members
|                   | - Run Devel again with all simulations and see if all notifications are printed out correctly
|                   | - Next meeting: 
|                   | 1. Split work for documentation and mainpage.h
|                   | 2. Figure out UML's subcription
|                   | 3. Start brainstorming for next iteration
|                   | - Action items:
|                   | + Dustin and Wiley:
|                   | 1. Implement Beeline
|                   | + Aunya and Lin:
|                   | 1. Start building strategy pattern structure
|-------------------|-----------------------------------------------------------------------------------------------------
| 4/13/2021         | - Finish in class exercise 11
|                   | - Update from members
|                   | + Aunya:
|                   | 1. Implemented the strategy pattern
|                   | + Wiley and Dustin:
|                   | 1. Implemented Beeline but needs to fix all_features.json
|                   | 2. Implement parabolic path
|                   | - Answer questions from members
|                   | - Action items:
|                   | + Wiley:
|                   | 1. Fix the beeline - all_features.json
|                   | 2. Add beeline Google test
|                   | 3. Drop the drone & its package if it’s out of battery
|                   | 4. Write about beeline and parabolic route in documentation
|                   | + Dustin:
|                   | 1. Implement Parabolic Path
|                   | 2. Write about beeline and parabolic route in documentation
|                   | + Aunya
|                   | 1. Write about strategy structure 
|                   | 2. Add strategy route in drone constructor
|                   | + Lin
|                   | 1. Do team documentation in mainpage.h
|                   | 2. Add test for path in drone and robot constructor
|                   | 3. Fix UML
|-------------------|-----------------------------------------------------------------------------------------------------
| 4/16/2021         | - Update from members
|                   | + Aunya:
|                   | 1. Add the strategy route in the drone constructor
|                   | 2. Design & Documentation discussion about strategy pattern
|                   | + Wiley:
|                   | 1. Fix the beeline - all_features.json
|                   | 2. Drop the drone & its package if it’s out of battery
|                   | 3. SmartRoute, BeelineRoute, and ParabolicRoute Design & Documentation
|                   | + Dustin:
|                   | 1. Parabolic path 
|                   | + Lin:
|                   | 1. Create Task table
|                   | 2. Update Robot to die when run out of battery
|                   | - Answer questions from members
|                   | - Run all simulation together
|                   | - Check in for documentation
|                   | - Action items:
|                   | + Wiley:
|                   | 1. Adding test for beeline path
|                   | 2. Check if every single file has documentation
|                   | + Dustin:
|                   | 1. Add height in parabolic path
|                   | 2. Adding test for parabolic path
|                   | + Aunya
|                   | 1. Test the observer pattern  
|                   | + Lin
|                   | 1. Discuss about Observer Pattern in mainpage.h
|                   | 2. Check every github’s README file only has name of the person who works on it

*/