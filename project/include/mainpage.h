/*! \mainpage CSCI 3081 Delivery Simulation project
* **Extra Credit** This version does run on the extra credit files, including: multiple_drones.json, 
* multiple_customers.json, multiple_packages.json, and multiple_deliveries.json \n
*
*
* **To obtain the code**, in the terminal, type:
* \code $ git clone https://github.umn.edu/umn-csci-3081-s21/repo-huynh365.git \endcode
* This will prompt you to sign in into your Github. If you have the right access, 
* you would be able to obtain the code. To compile the code, navigate to the 
* "repo-huynh365" directory that you just download from github by typing:
* \code $ cd repo-huynh365 \endcode
* **To compile the code**, in the terminal, type:
* \code $ make \endcode
* **To run the simulation**, there are two ways: 
* - If you are using **Docker**, after install all of the Docker software needed
* for your environment, in directory "repo-huynh365", type the following commands 
* to the terminal:
* \code $ bin/build-env.sh \endcode
* This will help build the docker image. To run docker image:
* \code bin/run-env.sh \endcode
* Build project web server (inside docker image), navigate to the "repo-huynh365"
* directory, then:
* \code $ make \endcode
* To run the web server (inside docker image), inside "repo-huynh365" directory:
* \code $ ./bin/run.sh \endcode
*
* - If you are using **VOLE**, navigate to "repo-huynh365" directory, then 
* \code $ cd project \endcode
* \code $ make \endcode
* \code $ ./bin/run.sh \endcode 
*
* - Note that the project is not designed to work on SSH yet \n
* 
* **Dicussion of concrete factory pattern vs. abstract factory pattern vs. composite
* factory pattern**

<CENTER>
\image html ConF.png "Figure 1. Concrete Factory Pattern" 
</CENTER>

* First, we begin with the concrete factory pattern. As we can see in Figure 1, there
* is a new class call EntityFactory that is responsible for creating Entity. This prevents 
* the program to have a lot of different Entity derived classes and to not know which one
* would be created until runtime. This is good; however, there is still tight coupling. 
* Everytime we have a new Entity derived class, we have to add new case/ new if else 
* statement in EntityFactory. Here is how Abstract Factory come to the story. 

<CENTER>
\image html AF.png "Figure 2. Abstract Factory Pattern" 
</CENTER>

* Figure 2 depicts how the UML of this program would look like if we employ Abstract 
* Factory pattern. EntityFactory becomes an abstract class, pushing the creation of
* each Entity derived class into subclasses. For example, Drone object is created by
* DroneFactory. With this model, every time we create a new Entity derived class, we
* just need to create a new subclass of EntityFactory. However, even with this pattern,
* the CreateEntity function of DeliverySimulation still contains a thread of if-else
* statement to decide which Entity to create. This is not idea, since every time we
* add a new Entity derived class, we still have to edit our CreateEntity function in
* DeliverySimulation. This is where Composite Factory Pattern helps.  

<CENTER>
\image html Com.png "Figure 3. Composite Factory Pattern"
</CENTER>

* With the Composite Factory pattern, we can just create a CompositeFactory attribute
* in DeliverSimulation class, then use that to link to the other attribute. This would
* eliminate the long list of if and else statement anywhere in the code, and allow 
* easy addition of new Entity derived as well as EntityFactory derived classes. 


* **Discussion about the composite factory pattern** implemented in the package 
* delivery system:

* So we have discussed about the advantage of Composite Factory Pattern in the previous
* section. This pattern is excellent; however, it does have some disadvantages. The
* most obvious cons of composite factory pattern is that it might be difficult to provide
* a common interface for classes whose functionality differs too much. We might need 
* to overgeneralize the componenent interface, making it harder to comprehend. In
* addition, the cons from this package delivery simulation, the composite factory 
* pattern requires more classes to be created. It is hard to see the relationship
* between these classes even with a UML diagram. 

*/