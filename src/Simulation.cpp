/*
 * simulation.cpp
 *
 *      Author: Diaa Eldeen
 */




#include "Simulation.h"



//This is the actual algorithm for serving customers, generating servers timing information
//and calculates essential statistics
void simulateSystem(queueSystem_t* pQ){

	simulationInit(pQ);

	//Variables
	uint32_t ui32NoOfServers = pQ->vServers.size();
	queue <uint32_t> q;	//this contains customers that are currently being served or waiting
	uint32_t ui32LineNum, ui32ArrivalTime, ui32StartTime, ui32ServiceTime, ui32EndTime, ui32WaitTime, ui32Qlength;
	string sLine;
	uint32_t* pui32ServerEndTime = new uint32_t[ui32NoOfServers] (); //The end time of the last customer served by a server



	//Algorithm
	getline(pQ->fRawData, sLine);		//Ignore the title line

	while(getline(pQ->fRawData, sLine)){

		//read a line and parse it using string stream
		stringstream ssParse(sLine);
		ssParse >> ui32LineNum >> ui32ArrivalTime;


		//find the next idle server by picking the server that has the least end time
		uint32_t idleSv = indexOfMin(pui32ServerEndTime, ui32NoOfServers);

		//if the previous customer hadn't finished yet when the current one arrived
		if(ui32ArrivalTime < pui32ServerEndTime[idleSv] )
			ui32StartTime = pui32ServerEndTime[idleSv];  //the customer waits until the previous one is served
		else
			ui32StartTime = ui32ArrivalTime;    //the customer starts immediately


		ui32ServiceTime = randExpDist(pQ->vServers[idleSv].dServiceRate);	//generate random service time
		ui32EndTime = ui32StartTime + ui32ServiceTime;
		ui32WaitTime = ui32StartTime - ui32ArrivalTime;

		q.push(ui32EndTime);	//add the current customer to the queue

		//if the customers in the front of the queue have finished their service remove them from the queue
		while((!q.empty()) &&  (ui32ArrivalTime > q.front()) )
			q.pop();

		ui32Qlength = q.size();
        pQ->vServers[idleSv].ui32ServedCustomers++;


        //Printing data to the file
        pQ->vServers[idleSv].fFile << left;	//Align left
		pQ->vServers[idleSv].fFile << setw(12) << pQ->vServers[idleSv].ui32ServedCustomers ;	//line number
		pQ->vServers[idleSv].fFile << setw(13) << ui32ArrivalTime ;
        pQ->vServers[idleSv].fFile << setw(11) << ui32StartTime ;
		pQ->vServers[idleSv].fFile << setw(9)  << ui32EndTime ;
		pQ->vServers[idleSv].fFile << setw(13) << ui32ServiceTime ;
		pQ->vServers[idleSv].fFile << setw(10) << ui32WaitTime ;
		pQ->vServers[idleSv].fFile << setw(9)  << ui32Qlength <<endl;


		//updating stats
		pQ->vCustomers[ui32LineNum-1].ui32WaitTime = ui32WaitTime;
		pQ->vCustomers[ui32LineNum-1].ui32QLength = ui32Qlength;
		pQ->vServers[idleSv].ui64TotalServiceTime += ui32ServiceTime;
		pQ->ui64TotalWaitTime += ui32WaitTime;

		if(pQ->ui32LongestWait < ui32WaitTime)	//Record the longest wait
			pQ->ui32LongestWait = ui32WaitTime;

		if(pQ->ui32MaxQLength < ui32Qlength)	//Record the longest queue length
			pQ->ui32MaxQLength = ui32Qlength;


		pui32ServerEndTime[idleSv] = ui32EndTime;	//used for finding the next idle server
	}

	simulationEnd(pQ, pui32ServerEndTime, ui32ArrivalTime);
}



//generates arrival times sample, opens files and initializes some values
void simulationInit(queueSystem_t* pQ){

	//Arrival time sample generation
	pQ->sFileName =  generateArrivalTimes(pQ->vCustomers.size(), pQ->dArrivalRate);
	pQ ->fRawData.open(pQ->sFileName, ios::in);

	//check that the file has opened correctly
	if(!pQ ->fRawData.is_open()){
		cerr << "Error opening the file " << pQ ->sFileName << endl;
		exit(1);
	}

	//this sections creates and opens each server 's file
	for(uint32_t i=0; i<pQ->vServers.size(); ++i){

		//open a file for writing and reading for each server
		pQ->vServers[i].sFileName = "Server" + to_string(i+1) + ".txt";	//Server name depends on the server no.

		pQ->vServers[i].fFile.open(pQ->vServers[i].sFileName, ios::out );   //create the file if it isn't created
		pQ->vServers[i].fFile.close();
		pQ->vServers[i].fFile.open(pQ->vServers[i].sFileName, ios::out | ios::in);
		//reopened the file because the file must be created before we can open it for read and write

		//this is used in case we want to make server shifts
		pQ->vServers[i].ui32StartTime =0;	//it means that this server started from the beginning

		//title line
		pQ->vServers[i].fFile << "CustomerNo  ArrivalTime  StartTime  EndTime  ServiceTime  WaitTime  QLength"<<endl;
	}
}


//updates final stats and closes opened files
void simulationEnd(queueSystem_t* pQ, uint32_t* pui32ServerEndTime, uint32_t ui32LastArrival){

	pQ->ui64LastCustomerEntry = ui32LastArrival;
	pQ->ui64LastCustomerExit = findMax(pui32ServerEndTime, pQ->vServers.size());

	//loop to close all the opened files and update server end time
	for(uint32_t i=0; i<pQ->vServers.size(); ++i){

		pQ->vServers[i].ui32EndTime = pui32ServerEndTime[i];
		pQ->vServers[i].fFile.close();
	}
	pQ ->fRawData.close();

	cout << "\nCreated servers successfully" <<endl;
}




//function takes ArrivalRate and outputs to a file arrival times of n customers
string generateArrivalTimes(uint32_t ui32NoOfCustomers, double dArrivalRate){

	string sFileName = "Sample.txt";
	fstream fSample;
	fSample.open(sFileName, ios::out);

	fSample << "CustomerNo  ArrivalTime" <<endl;		//title line
	fSample << left;	//Align left

	uint32_t ui32ArrivalTime =0, ui32RandNo;

	for(uint32_t i =0; i<ui32NoOfCustomers; ++i){

		fSample << setw(12) << i+1 ;		//line number
		fSample << setw(13) << ui32ArrivalTime <<endl;

		ui32RandNo = randExpDist(dArrivalRate);	//Calculate inter-arrival time based on exponential distribution
		ui32ArrivalTime += ui32RandNo;		//Arrival time = Arrival time + inter-arrival time
	}

	fSample.close();
	cout << "Generated " << sFileName << " Successfully" <<endl;
	return sFileName;
}


//takes a parameter dLambda and returns a random number based on the exponential distribution of dLambda
uint32_t randExpDist(double dLambda){
	double dRand = (double) rand()/RAND_MAX;	//float from 0 to 1
	return  log(dRand) / -dLambda;	//random number based on exponential distribution of dLambda
}



//takes an unsigned int array and returns the maximum value
uint32_t findMax(uint32_t array[], uint32_t size) {
    uint32_t max = array[0];

    for (uint32_t i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];

    return max;
}

//takes an unsigned int array and returns the index of the minimum element
uint32_t indexOfMin(uint32_t array[], int size){
    int index = 0;

    for(int i = 1; i < size; i++)
        if(array[i] < array[index])
            index = i;

    return index;
}
