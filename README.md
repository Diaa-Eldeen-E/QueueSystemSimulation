
[![Build Status](https://travis-ci.com/diaa3007/QueueSystemSimulation.svg?branch=master)](https://travis-ci.com/diaa3007/QueueSystemSimulation/)

## **Abstract**

 This project is mainly an application on statistics and probability which includes:
- Collecting a sample from a real queue
- Writing a software to calculate the queue properties and service statistics.
- Simulating any virtual queue system and calculating it’s statistics. 

 This should give us a way to optimize the system by predicting and estimating the effects of any possible change.  
 
&nbsp;
&nbsp;
&nbsp;
&nbsp;  


## **Usage example:**  
### **Simulation input:**
![Simulation picture](https://github.com/diaa3007/QueueSystemSimulation/blob/master/sim.png?raw=true)  


### **Output:**  
![Output picture](https://ibb.co/BB3514s)  

&nbsp;
&nbsp; 

## **User interface commands:**

- **Real sample**:
 This command is used to generate a statistics report about the real sample found in the file &quot;convertedRealSample.txt&quot;. It also writes a file for each server containing the timing information for each served customer.
 The server file contains the following columns: CustomerNumber, ArrivalTime, StartTime, EndTime, ServiceTime, WaitTime and QueueLength.   
 The file &quot;convertedRealSample.txt&quot; must be in the same directory before executing this command.

- **Simulation**:
This command is used to enter the simulation program.

- **Probability**:
This command is used to enter the probability calculator program.
Using this command before real sample or simulation command gives an error.

- **Exit**:
Exit the program

&nbsp;

## **Simulation program:**

    1. The user is prompted to enter the following:

- **Number of customers**  
This is the number of customer at which the simulation ends

- **Arrival rate**  
The average number of customers entering the system per hour.

- **Number of servers**  
Number of servers in the simulted system.

- **Service rate of each server**  
The average number of customers served by that server per hour.
&nbsp;

All of the above numbers must be positive integer numbers.


    2. The program then produces the following:

- A statistics report which describes that specified system.
- A file containing all the customers arrival times
- A file for each server containing the timing information for each customer served by that server.
 The server file contains the following columns: CustomerNumber, ArrivalTime, StartTime, EndTime, ServiceTime, WaitTime and QueueLength.

&nbsp;
&nbsp;

## **Probability program**:  
 A user interface has the following commands:   
- **Q length at most**:
Prompts the user for a number x and then prints the probability that a customer enters the system and finds x customers or less in the queue, i.e. P (X ≤ x).
This number x includes all customers in the queue whether waiting or being served and without considering the order.  
The entered number must be a positive integer value.

- **Q length at least**:
This Prompts the user for a number x and then prints the probability that a customer enters the system and finds x customers or more in the queue, i.e. P (X ≥ x).
This number x includes all customers in the queue whether waiting or being served and without considering the order.  
 The entered number must be a positive integer value.

- **Wait time at most**:
Prompts the user for a number x and then prints the probability that a customer enters the system and waits x seconds or less in the queue, i.e. P (X ≤ x).  
The entered number must be a positive integer value.

- **Wait time at least**:
Prompts the user for a number x and then prints the probability that a customer enters the system and waits x seconds or more in the queue, i.e. P (X ≥ x).  
The entered number must be a positive integer value.

- **Exit**:
Exit the program

- **Back**:
Go back to the main user interface

&nbsp;  
&nbsp;  
&nbsp;  

## **Software structure**  

The software is divided into 5 major files:  

- **Data structures header file**  
     Contains the structures and objects used in the project:
	1. Customer data structure
	2. Server data structure
	3. Queue system data structure  
&nbsp;  

- **Real sample source file**  
This file contains the functions responsible for:

	1. Converting the raw collected sample format into an easier format.
	2. Processing the sample i.e. :  
		- Reading the data from the sample file
		- Generating detailed timing information for each server
		- Calculating essential parameters such as _total service time_  
&nbsp;  
  
- **Simulation source file**  
	 This file contains the functions responsible for:
	1. Generating exponential distribution random variable
	2. Generating a sample file of arrival times
	3. Processing that sample file i.e. :
		- Reading the data from the sample file
		- Simulating the servers
		- Generating detailed timing information for each server
		- Calculating essential parameters such as _total service time_  
&nbsp;  

- **Statistics and probability source file**   
	 This file contains the functions responsible for:
	1. Calculating the statistics from the data given in the queue data structure
	2. Calculating the probabilities from the data given in the queue data structure
	3. Print major statistics and probabilities to a report file
	4. Provide easy get functions to use in user interface  
&nbsp;  

- **User interface source file**   
	 This file contains the functions responsible for:
	1. User interface
	2. Initializing the queue system
