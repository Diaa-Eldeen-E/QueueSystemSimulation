/*
 * queueStruct.h
 *
 *      Author: Diaa Eldeen
 */

#ifndef QUEUESTRUCT_H_
#define QUEUESTRUCT_H_


#include <bits/stdc++.h>

using namespace std;


//Contains customer's parameters used to calculate probability
typedef struct {

	uint32_t ui32WaitTime;
	uint32_t ui32QLength;	//number of customers in the queue when he arrived

}customer_t;



//Contains server's parameters
typedef struct {

    double dServiceRate;	//server service rate

    uint32_t ui32StartTime;		//shift start time
    uint32_t ui32EndTime;		//shift end time

    //The files that contains the server's served customers and their timings
    fstream fFile;
    string sFileName;

    uint32_t ui32ServedCustomers;	//number of served customers
    uint64_t ui64TotalServiceTime;	//The busy time (idle time not included)

}server_t;


//Contains the queue system essential parameters
typedef struct {

	uint64_t ui64TotalWaitTime; //total wait time
	uint32_t ui32LongestWait;  //longest wait
	uint32_t ui32MaxQLength;
	uint64_t ui64LastCustomerEntry;
	uint64_t ui64LastCustomerExit;

	//A file that contains the raw sample(The Real one or the generated one in simulation)
	fstream fRawData;
	string sFileName;

	double dArrivalRate;
	double dServiceRate;

	vector <customer_t> vCustomers;		//vector of customers
	vector <server_t> vServers;		//vector of servers

}queueSystem_t;



#endif /* QUEUESTRUCT_H_ */
