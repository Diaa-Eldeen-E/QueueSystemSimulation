/*
 * simulation.h
 *
 *      Author: Diaa Eldeen
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_



#include <bits/stdc++.h>
#include <queue>

#include "queueStruct.h"

using namespace std;



//This is the actual algorithm for serving customers, generating servers timing information
//and calculates essential statistics
void simulateSystem(queueSystem_t* pQueue);

//generates the arrival times sample, opens files and initializes some values
void simulationInit(queueSystem_t* pQ);

//updates final stats and closes opened files
void simulationEnd(queueSystem_t* pQ, uint32_t* pui32ServerEndTime, uint32_t ui32LastArrival);



//function takes ArrivalRate and outputs to a file arrival times of n customers
string generateArrivalTimes(uint32_t ui32NoOfCustomers, double dArrivalRate);

//takes a parameter dLambda and returns a random number based on the exponential distribution of dLambda
uint32_t randExpDist(double dLambda);



//takes an unsigned int array and returns the maximum value
uint32_t findMax(uint32_t array[], uint32_t size);

//takes an unsigned int array and returns the index of the minimum element
uint32_t indexOfMin(uint32_t array[], int size);


#endif /* SIMULATION_H_ */
