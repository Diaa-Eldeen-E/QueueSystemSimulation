/*
 * UI.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: Diaa Eldeen
 */




#include "UI.h"


//main user interface
void userInterface(){


	queueSystem_t queueSystem;
	string sLine;

	cout << "All commands are NOT case sensitive" <<endl;

	while(1){

		cout << "\nChoose a command, [Real sample, Simulation, Probability, Exit] \n>>" ;

		getline(cin, sLine);

		transform( sLine.begin(), sLine.end(), sLine.begin(), ::toupper ); ;	//convert all to upper case

		if( sLine == "REAL SAMPLE" ){

			realSampleInit(&queueSystem);
			realSampleProcess(&queueSystem);
			printStats(&queueSystem);
		}
		else if( sLine == "SIMULATION" ){

			simulationUI(&queueSystem);
			simulateSystem(&queueSystem);
			printStats(&queueSystem);
		}
		else if( sLine == "PROBABILITY" ){

			if(queueSystem.vCustomers.size() > 1)	//if initialized
				probabilityUI(&queueSystem);

			else									//if non initialized -> error
				cout << "You can't calculate probability before real sample or simulation" <<endl;
		}

		else if (sLine == "EXIT"){
			exit(0);
		}

		else {
			cout << "Undefined command, try again" <<endl;
		}

		cin.sync();	//Ignore unread new line after cin >> anything
	}
}



//This functions initializes important values inside the queue structure
void queueInit(queueSystem_t* pQ){

	pQ->ui32LongestWait = 0;
	pQ->ui32MaxQLength = 0;
	pQ->ui64TotalWaitTime = 0;

	for(uint32_t i=0; i< pQ->vServers.size(); ++i){

		pQ->vServers[i].ui32ServedCustomers = 0;
		pQ->vServers[i].ui64TotalServiceTime = 0;
	}
}


//This function is a user interface to specify the simulation parameters
void simulationUI(queueSystem_t* pQ){

	uint32_t ui32NoOfCustomers, ui32NoOfServers, ui32Rate;

	//Take the number of customers from the user
	cout << "\nEnter the number of customers to be simulated: ";
	while(! getPositiveNum(ui32NoOfCustomers) )
		cout << "Try again: ";


	//Take the arrival rate of customers from the user
	cout << "\nEnter the arrival rate of customers (per hour): ";
	while(! getPositiveNum(ui32Rate) )
		cout << "Try again: ";


	//Take the number of servers from the user
	cout << "\nEnter the number of servers to be simulated: ";
	while(! getPositiveNum(ui32NoOfServers) )
		cout << "Try again: ";


	//Store the values
	pQ->vCustomers.resize(ui32NoOfCustomers);
	pQ->vServers.resize(ui32NoOfServers);
	pQ->dArrivalRate = (double) ui32Rate / 3600;	//converting it to customers per second


	//Take the service rate of each server from the user
	for(uint32_t i=0; i<pQ->vServers.size(); ++i){

		cout << "\nEnter the service rate of server No. " << i+1 << " (per hour): ";
		while(! getPositiveNum(ui32Rate) )
			cout << "Try again: ";


		pQ->vServers[i].dServiceRate = (double) ui32Rate / 3600;	//converting it to customers per second

		cout << "Server " << i+1 << " entered." <<"\n\n";
	}

	queueInit(pQ);
}


//initializes the real sample specific values
void realSampleInit(queueSystem_t* pQ){

	pQ->sFileName = "convertedRealSample.txt";	//The converted raw sample data file name

	pQ->vServers.resize(6);		//we have 6 servers in the sample
	pQ->vCustomers.resize(147);	//we have 147 customers

	pQ->vServers[0].ui32StartTime = 0;
	pQ->vServers[1].ui32StartTime = 0;
	pQ->vServers[2].ui32StartTime = 3000;	//he came late
	pQ->vServers[3].ui32StartTime = 0;
	pQ->vServers[4].ui32StartTime = 0;
	pQ->vServers[5].ui32StartTime = 7980;	//another shift

	queueInit(pQ);
}


//This function is a user interface to get any probability
void probabilityUI(queueSystem_t* pQ){

	string sLine = "";
	uint32_t ui32InputNum;

	while(1){

		cout << "\nChoose a command, [Q Length at most, Q length at least,\n";
		cout << 					"Wait time at most, Wait time at least, Back, Exit] \n>>" ;

		getline(cin, sLine);


		transform( sLine.begin(), sLine.end(), sLine.begin(), ::toupper ); ;	//convert all to upper case


		if( sLine == "Q LENGTH AT MOST" ){

			cout << "Enter the queue length (number of customers): ";

			while(! getPositiveNum(ui32InputNum) )
				cout << "Try again: ";

			cout << getProbQLenAtMost(pQ, ui32InputNum) <<endl;
		}
		else if( sLine == "Q LENGTH AT LEAST" ){

			cout << "Enter the queue length (number of customers): ";

			while(! getPositiveNum(ui32InputNum) )
				cout << "Try again: ";

			cout << getProbQLenAtLeast(pQ, ui32InputNum) <<endl;
		}
		else if( sLine == "WAIT TIME AT MOST" ){

			cout << "Enter the wait time (in seconds): ";

			while(! getPositiveNum(ui32InputNum) )
				cout << "Try again: ";

			cout << getProbWaitAtMost(pQ, ui32InputNum) <<endl;
		}

		else if( sLine == "WAIT TIME AT LEAST" ){

			cout << "Enter the wait time (in seconds): ";

			while(! getPositiveNum(ui32InputNum) )
				cout << "Try again: ";

			cout << getProbWaitAtLeast(pQ, ui32InputNum) <<endl;
		}

		else if (sLine == "EXIT"){
			exit(0);
		}
		else if (sLine == "BACK"){
			return;
		}

		else {
			cout << "Undefined command, try again" <<endl;
		}

		cin.sync();	//Ignore unread new line after cin >> anything
	}

}









//This functions is used to get a positive integer number from the user
//with all error checking
// @ui32Num  is where the number will be stored
// returns 1 in case of success and 0 if any error happened
bool getPositiveNum(uint32_t& ui32Num){
	string sEntry;
	cin >> sEntry;
	char* r;

	long liInputNum = strtol(sEntry.c_str(), &r, 10);

	//overflow check
	if(errno == ERANGE) {
		cout << "Error, entered number is too large " << endl;
		return 0;
	}
	//is number check
	else if (*r ) {
		cout << "Error, invalid number" <<endl;
		return 0;
	}
	//positive number check
	if (liInputNum <= 0) {
		cout << "Error, the number should be a positive integer" <<endl;
		return 0;
	}

	ui32Num = liInputNum;
	return 1;

}
