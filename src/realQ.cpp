/*
 * realQ.cpp
 *
 *      Author: Diaa Eldeen
 */




#include "realQ.h"



//Creates a file for each server containing timing information of served customers
//and calculates essential statistics
void realSampleProcess(queueSystem_t* pQ){

	systemInit(pQ);

	//Variables
	queue <uint32_t> q;	//this contains customers that are currently being served or waiting
	string sLine;
	uint32_t ui32LineNum, ui32ArrivalTime, ui32StartTime, ui32EndTime, svrIdx, ui32ServiceTime, ui32WaitTime, ui32Qlength;



	getline(pQ->fRawData, sLine);		//Ignore the title line

	while(getline(pQ->fRawData, sLine)){

		//read a line and parse it using string stream
		stringstream ssParse(sLine);
		ssParse >> ui32LineNum >> ui32ArrivalTime >> ui32StartTime >> ui32EndTime >> svrIdx;

		svrIdx--;	//convert from counting number to index  (server index)
		ui32ServiceTime = ui32EndTime - ui32StartTime;
		ui32WaitTime = ui32StartTime - ui32ArrivalTime;

		q.push(ui32EndTime);	//add the current customer to the queue

		//if the first customers in the queue finished their service remove them from the queue
		while((!q.empty()) &&  (ui32ArrivalTime > q.front()) )
			q.pop();

		ui32Qlength = q.size();

		pQ->vServers[svrIdx].ui32ServedCustomers++;

		//Printing data to the file
		pQ->vServers[svrIdx].fFile << left;	//Align left
		pQ->vServers[svrIdx].fFile << setw(12) << pQ->vServers[svrIdx].ui32ServedCustomers ;	//print line number
		pQ->vServers[svrIdx].fFile << setw(13) << ui32ArrivalTime ;		//print out arrival time
		pQ->vServers[svrIdx].fFile << setw(11) << ui32StartTime ;		//print out start time
		pQ->vServers[svrIdx].fFile << setw(9)  << ui32EndTime ; 	  	//print out end time
		pQ->vServers[svrIdx].fFile << setw(13) << ui32ServiceTime ; 	//print out service time
		pQ->vServers[svrIdx].fFile << setw(10) << ui32WaitTime ;		//print out wait time
		pQ->vServers[svrIdx].fFile << setw(9)  << ui32Qlength <<endl;	//print out Queue length


		//updating stats
		pQ->vCustomers[ui32LineNum-1].ui32WaitTime = ui32WaitTime;
		pQ->vCustomers[ui32LineNum-1].ui32QLength = ui32Qlength;
		pQ->vServers[svrIdx].ui64TotalServiceTime += ui32ServiceTime;
		pQ->ui64TotalWaitTime += ui32WaitTime;

		if(pQ->ui32LongestWait < ui32WaitTime)	//Record the longest wait
			pQ->ui32LongestWait = ui32WaitTime;

		if(pQ->ui32MaxQLength < ui32Qlength)	//Record the longest queue length
			pQ->ui32MaxQLength = ui32Qlength;

	}

	//updating final stats
	pQ->ui64LastCustomerEntry = ui32ArrivalTime;
	pQ->ui64LastCustomerExit = ui32EndTime;

	systemExit(pQ);
}



//This function opens the sample file for read and creates the servers files
void systemInit(queueSystem_t* pQ){

	pQ ->fRawData.open(pQ->sFileName, ios::in);

	//check that the file has opened correctly
	if(!pQ ->fRawData.is_open()){
		cerr << "Error opening the file " << pQ ->sFileName << endl;
		exit(1);
	}

	for(uint32_t i=0; i<pQ->vServers.size(); ++i){

		//open a file for writing and reading for each server
		pQ->vServers[i].sFileName = "Server" + to_string(i+1) + ".txt";	//Server name depends on the server no.

		pQ->vServers[i].fFile.open(pQ->vServers[i].sFileName, ios::out );   //create the file if it isn't created
		pQ->vServers[i].fFile.close();
		pQ->vServers[i].fFile.open(pQ->vServers[i].sFileName, ios::out | ios::in);
		//reopened the file because the file must be created first before opening it for read and write

		//title line
		pQ->vServers[i].fFile << "CustomerNo  ArrivalTime  StartTime  EndTime  ServiceTime  WaitTime  QLength"<<endl;
	}

}



//updates final stats and closes opened files
void systemExit(queueSystem_t* pQ){

	//loop to close all the opened files
	for(uint32_t i=0; i<pQ->vServers.size(); ++i){

		pQ->vServers[i].ui32EndTime = 11688;	//The time at which i stopped sampling
		pQ->vServers[i].fFile.close();
	}
	pQ ->fRawData.close();

	cout << "\nCreated servers successfully" <<endl;
}





//The code below is not used in the program.
//It was used only one time to convert the collected sample file
//So, it's not recommended to read it

//this function is performed to convert the raw data i collected from the pharmacy
//to more easier format for processing and to remove invalid entries
//this function is very specific to the data i collected and cannot be used for any other sample
string covertCustomersData(string sFileName){

	fstream fRawFile;
	fRawFile.open(sFileName, ios::in);

	if(!fRawFile.is_open()){
		cerr << "Error opening the file " << sFileName << endl;
		exit(1);
	}

	fstream fCustomersFile;
	fCustomersFile.open("converted" + sFileName, ios::out);

	string sLine, sLineNum, sArrivalTime, sStartTime, sEndTime, sZeroTime;
	uint32_t ui32ZeroTime, ui32ServerNo;

	getline(fRawFile, sLine);		//Ignore the titles line
	fCustomersFile << "CustomerNo  ArrivalTime  StartTime  EndTime  ServerNo"<<endl;

	uint32_t i=0, ui32NoOfServedCustomers =0;
	while(getline(fRawFile, sLine)){

		++i;
		//Parse the current line
		stringstream ss(sLine);
		ss >> sLineNum >> sArrivalTime >> sStartTime;

		if(ss.rdbuf()->in_avail() == 0)		//if the rest of line is missing
			continue;	 	//skip this line

		ss >> sEndTime;	// end time

		if(ss.rdbuf()->in_avail() == 0)		//if the rest of line is missing
			continue;		// skip this line

		if(i == 1){
			sZeroTime = sArrivalTime;
			ui32ZeroTime = to_secs(sZeroTime);
		}

		//I took 10 mins break at customer 131, so i'm subtracting 10 mins from the time after customer 131
		if( i == 131)
			ui32ZeroTime += to_secs("00:10:00") ; //add 10 mins to zero time


		ss >> ui32ServerNo;
		ui32NoOfServedCustomers++;


		fCustomersFile << left;	//Align left
		fCustomersFile << setw(12) << ui32NoOfServedCustomers ;	//the line number
		fCustomersFile << setw(13) << to_secs(sArrivalTime) - ui32ZeroTime ; //arrival time in secs
		fCustomersFile << setw(11) << to_secs(sStartTime) - ui32ZeroTime ;	//start time in secs
		fCustomersFile << setw(9) << to_secs(sEndTime) - ui32ZeroTime ;		//end time in secs
		fCustomersFile << setw(10) << ui32ServerNo <<endl;
	}

	fRawFile.close();
	fCustomersFile.close();

	cout << "Converted customers data successfully" <<endl;
	return ("converted" + sFileName) ;
}



//function takes a string time format (00:10:15) as an input and returns the time as
// an unsigned integer seconds format (615)
uint32_t to_secs(string sTime){

	uint32_t ui32Hours, ui32Mins, ui32Secs;
	char cTextDelimiter;
	string sTemp = sTime;

	stringstream ss(sTemp);
	ss >> ui32Hours >> cTextDelimiter >> ui32Mins >> cTextDelimiter >> ui32Secs;

	 return ui32Hours * 3600 + ui32Mins * 60 + ui32Secs ;
}
