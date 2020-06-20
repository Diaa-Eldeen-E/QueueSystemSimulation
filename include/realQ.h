/*
 * realQ.h
 *
 *      Author: Diaa Eldeen
 */

#ifndef REALQ_H_
#define REALQ_H_


#include <bits/stdc++.h>
#include <queue>

#include "queueStruct.h"

using namespace std;


//Creates a file for each server containing timing information of served customers
//and calculates essential statistics
void realSampleProcess(queueSystem_t* pQ);


//This function opens the sample file and creates the servers files
void systemInit(queueSystem_t* pQ);


//updates final stats and closes opened files
void systemExit(queueSystem_t* pQ);





//this function is performed to convert the raw data i collected from the pharmacy
//to more easier format for processing and to remove invalid entries
//this function is very specific to the data i collected and cannot be used for any other sample
string covertCustomersData(string sFileName);


//function takes a string time format (00:10:15) as an input and returns the time as
// an unsigned integer seconds format (615)
uint32_t to_secs(string sTime);


#endif /* REALQ_H_ */
