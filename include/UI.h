/*
 * UI.h
 *
 *  Created on: Apr 18, 2020
 *      Author: Diaa Eldeen
 */

#ifndef UI_H_
#define UI_H_


#include "realQ.h"
#include "stats.h"
#include "Simulation.h"


//main user interface
void userInterface();


//This functions initializes important values inside the queue structure
void queueInit(queueSystem_t* pQ);


//This function is a user interface to specify the simulation parameters
void simulationUI(queueSystem_t* pQ);


//initializes the real sample specific values
void realSampleInit(queueSystem_t* pQ);

//This function is a user interface to get any probability
void probabilityUI(queueSystem_t* pQ);


bool getPositiveNum(uint32_t& ui32Num);

#endif /* UI_H_ */
