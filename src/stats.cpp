/*
 * stats.cpp
 *
 *      Author: Diaa Eldeen
 */



#include "stats.h"



//------------------------------------------------------------------//
//*********************   Probability section *********************//
//-----------------------------------------------------------------//

//Calculates the probability that a customer waits at most ui32WaitTime
string getProbWaitAtMost(queueSystem_t* pQ, uint32_t ui32WaitTime){

	uint32_t ui32Counter =0;
	for(uint32_t i=0; i<pQ->vCustomers.size(); ++i){

		if( pQ->vCustomers[i].ui32WaitTime <= ui32WaitTime )  //the -1 because the customer is counted in the Q length
			ui32Counter++;
	}
	return   to_string( (double)ui32Counter / pQ->vCustomers.size() );
}


//Calculates the probability that a customer waits at least ui32WaitTime
string getProbWaitAtLeast(queueSystem_t* pQ, uint32_t ui32WaitTime){

	uint32_t ui32Counter =0;
	for(uint32_t i=0; i<pQ->vCustomers.size(); ++i){

		if( pQ->vCustomers[i].ui32WaitTime >= ui32WaitTime )  //the -1 because the customer is counted in the Q length
			ui32Counter++;
	}
	return   to_string( (double)ui32Counter / pQ->vCustomers.size() );
}


//Calculates the probability that a customer finds a queue length that is at most ui32QLen
string getProbQLenAtMost(queueSystem_t* pQ, uint32_t ui32QLen){

	uint32_t ui32Counter =0;
	for(uint32_t i=0; i<pQ->vCustomers.size(); ++i){

		if( (pQ->vCustomers[i].ui32QLength -1) <= ui32QLen )  //the -1 because the customer is counted in the Q length
			ui32Counter++;
	}
	return   to_string( (double)ui32Counter / pQ->vCustomers.size() );
}


//Calculates the probability that a customer finds a queue length that is at least ui32QLen
string getProbQLenAtLeast(queueSystem_t* pQ, uint32_t ui32QLen){

	uint32_t ui32Counter =0;
	for(uint32_t i=0; i<pQ->vCustomers.size(); ++i){

		if( (pQ->vCustomers[i].ui32QLength -1) >= ui32QLen )  //the -1 because the customer is counted in the Q length
			ui32Counter++;
	}

	return   to_string( (double)ui32Counter / pQ->vCustomers.size() );
}



//-------------------------------------------------------------------------//
//*********************   Servers statistics section *********************//
//------------------------------------------------------------------------//

//this function returns all servers statistics
string getServerAll(queueSystem_t* pQ){
	stringstream ss;

	for(uint8_t i =0; i<pQ->vServers.size(); ++i){
		ss << "Server" + to_string(i+1) + ":  ";
		ss << "Utilization: " << getUtilization(pQ, i);
		ss << ",\t Average service time: " << getAvgServerSvc(pQ, i);
		ss << ", " << getServerSvcRate(pQ, i);

		ss << endl;
	}
	return ss.str();
}


//returns the utilization percentages of all servers
string getUtilizationAll(queueSystem_t* pQ){

	string sOut ="";
	for(uint8_t i =0; i<pQ->vServers.size(); ++i){
		sOut += "Server" + to_string(i+1) + ":  ";
		sOut += getUtilization(pQ, i);
		sOut += "\n";
	}
	return sOut;
}


//returns the utilization percentage of a certain server
string getUtilization(queueSystem_t* pQ, uint32_t ui32SvNo){

	if(ui32SvNo <= pQ->vServers.size()){
		uint32_t ui32ServerPeriod = pQ->vServers[ui32SvNo].ui32EndTime - pQ->vServers[ui32SvNo].ui32StartTime;
		return (to_string( (double) pQ->vServers[ui32SvNo].ui64TotalServiceTime / ui32ServerPeriod * 100 )  + " %");

	}
	else{
		//error
		return "Server Number doesn't exist";
	}

}


//get service rate for a server
string getServerSvcRate(queueSystem_t* pQ, uint32_t ui32SvNo){

	//Server 's served customers / server 's total service time
	return to_string( (uint32_t) ((float) pQ->vServers[ui32SvNo].ui32ServedCustomers / pQ->vServers[ui32SvNo].ui64TotalServiceTime  * 3600 ) ) \
			+ " customers per hour";
}

//average service time for server
string getAvgServerSvc(queueSystem_t* pQ, uint32_t ui32SvNo){

	// server 's total service time / Server 's served customers
	return convertTime( pQ->vServers[ui32SvNo].ui64TotalServiceTime / pQ->vServers[ui32SvNo].ui32ServedCustomers );
}




//---------------------------------------------------------------------------//
//*********************   Customers statistics section *********************//
//--------------------------------------------------------------------------//

//get service rate for customers
string getServiceRate(queueSystem_t* pQ){

	// Number of customers / total service time of all customers
	return to_string( (uint32_t)( (float) pQ->vCustomers.size() / pQ->ui64LastCustomerExit * 3600 ) ) \
					+ " customers per hour";
}

//average service time for customers
string getAvgService(queueSystem_t* pQ){

	uint64_t ui64Sum =0;
	for(uint8_t i =0; i<pQ->vServers.size(); ++i){
		ui64Sum += pQ->vServers[i].ui64TotalServiceTime ;

	}

	// total service time of all customers / Number of customers
	return convertTime( ui64Sum / pQ->vCustomers.size() );
}


string getMaxQLen(queueSystem_t* pQ){
	return  to_string( pQ->ui32MaxQLength );
}


string getMaxWait(queueSystem_t* pQ){
	return convertTime( pQ->ui32LongestWait );
}


string getAvgWaiting(queueSystem_t* pQ){
	return convertTime( pQ->ui64TotalWaitTime / pQ->vCustomers.size() );
}


string getArvlRate(queueSystem_t* pQ){
	return  to_string( (uint32_t) ( (float) pQ->vCustomers.size() / pQ->ui64LastCustomerEntry  * 3600) ) \
			+ " customers per hour" ;
}

string getInterArvlTime(queueSystem_t* pQ){
	return convertTime( pQ->ui64LastCustomerEntry / pQ->vCustomers.size() ) ;
}


//returns the total service time of all customers
string getTotalServiceT(queueSystem_t* pQ){
	uint64_t ui64Sum =0;

	for(uint8_t i =0; i<pQ->vServers.size(); ++i){
		ui64Sum += pQ->vServers[i].ui64TotalServiceTime ;
	}

	return convertTime( ui64Sum );
}


//The duration in which servers were serving the customers
//This includes the time to service the remaining queue after closing the system entry
string getServiceDuration(queueSystem_t* pQ){
	return convertTime( pQ->ui64LastCustomerExit ) ;
}


//The duration in which the system was open (for customers to enter)
string getEntryDuration(queueSystem_t* pQ){
	return convertTime( pQ->ui64LastCustomerEntry ) ;
}


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

//this function takes time in seconds and returns a formated time in hours or minutes or seconds
string convertTime(uint32_t ui32Seconds){

	stringstream ss;

	if(ui32Seconds > 60 && ui32Seconds < 3600){		//minutes and seconds

		float fMins = (float) ui32Seconds / 60;
		uint32_t ui32Mins = fMins;
		ss << ui32Mins << " Minutes ";

		uint32_t ui32FracSecs = ui32Seconds - ui32Mins * 60;	//convert minute fraction to seconds
		if(ui32FracSecs)
			ss << "and " << ui32FracSecs << " seconds";
	}
	else if(ui32Seconds > 3600){					//hours and minutes

		float fHours = (float) ui32Seconds / 3600;
		uint32_t ui32Hours = fHours;
		ss << (uint32_t) fHours << " Hours ";

		uint32_t ui32Mins = ( (float) fHours -  ui32Hours)* 60;	//convert hour fraction to minutes
		if(ui32Mins)
			ss <<  "and " << ui32Mins << " minutes";
	}
	else {											//just seconds
		ss << ui32Seconds << " Seconds";
	}

	return ss.str();
}


//print all statistics
void printStats(queueSystem_t* pQ){

    fstream fStatsFile;
    fStatsFile.open("stats.txt", ios::out);

    fStatsFile << "Queue statistics report\n\n " <<endl;

    fStatsFile << "Total number of customers: " << pQ->vCustomers.size() <<endl;
    fStatsFile << "Total number of servers: " << pQ->vServers.size() <<endl;
    fStatsFile << "Open time duration: " << getEntryDuration(pQ) <<endl;
    fStatsFile << "Serving time duration: " << getServiceDuration(pQ) <<endl;
    fStatsFile << "Total service time: " << getTotalServiceT(pQ) <<endl;

    fStatsFile << "\nAverage inter-arrival time: " << getInterArvlTime(pQ) ;
    fStatsFile << ", "<< getArvlRate(pQ) <<endl;

    fStatsFile << "Average service time: \t\t" << getAvgService(pQ) ;
    fStatsFile << ", "<< getServiceRate(pQ) <<endl;

    fStatsFile << "\nAverage waiting time: " << getAvgWaiting(pQ) <<endl;

    fStatsFile << "Longest waiting time: " << getMaxWait(pQ) <<endl;
    fStatsFile << "\nLongest Queue length: " << getMaxQLen(pQ) <<endl;

    fStatsFile << "\nServers related statistics: " <<endl;
    fStatsFile << getServerAll(pQ) <<endl;




    fStatsFile << "probability that a customers enters and doesn't wait : ";
    fStatsFile <<  getProbQLenAtMost( pQ, pQ->vServers.size() -1) << "\n\n";

    fStatsFile << "probability that a customers enters and waits for at most one customer : ";
    fStatsFile <<  getProbQLenAtMost( pQ, (pQ->vServers.size() *2) -1) <<endl;
    fStatsFile << "(i.e. one customer or no wait) \n" <<endl;


    fStatsFile << "probability that a customers enters and waits for at least one customer : ";
    fStatsFile << getProbQLenAtLeast( pQ, pQ->vServers.size() ) <<endl;
    fStatsFile << "(i.e. one customer or more) \n" <<endl;



    fStatsFile << "probability that a customers enters and waits for at least 60 seconds : ";
    fStatsFile << getProbWaitAtLeast( pQ, 60 ) <<endl;
    fStatsFile << "(i.e. 60 seconds or more) \n" <<endl;


    fStatsFile << "probability that a customers enters and waits for at most 60 seconds : ";
    fStatsFile <<  getProbWaitAtMost( pQ, 60 ) <<endl;
    fStatsFile << "(i.e. 60 seconds or less) \n" <<endl;



    fStatsFile.close();

    cout << "\nStatistics are calculated successfully in stats.txt " <<endl;
}
