/*
 * stats.h
 *
 *      Author: Diaa Eldeen
 */

#ifndef STATS_H_
#define STATS_H_

#include <bits/stdc++.h>

#include "queueStruct.h"

using namespace std;


string getProbWaitAtMost(queueSystem_t* pQ, uint32_t ui32WaitTime);
string getProbWaitAtLeast(queueSystem_t* pQ, uint32_t ui32WaitTime);
string getProbQLenAtMost(queueSystem_t* pQ, uint32_t ui32QLen);
string getProbQLenAtLeast(queueSystem_t* pQ, uint32_t ui32QLen);

string getServerAll(queueSystem_t* pQ);
string getServerSvcRate(queueSystem_t* pQ, uint32_t ui32SvNo);
string getAvgServerSvc(queueSystem_t* pQ, uint32_t ui32SvNo);

string getServiceRate(queueSystem_t* pQ);
string getAvgService(queueSystem_t* pQ);
string getUtilizationAll(queueSystem_t* pQ);
string getUtilization(queueSystem_t* pQ, uint32_t ui32ServerNo);
string getMaxQLen(queueSystem_t* pQ);
string getMaxWait(queueSystem_t* pQ);
string getAvgWaiting(queueSystem_t* pQ);
string getArvlRate(queueSystem_t* pQ);
string getInterArvlTime(queueSystem_t* pQ);
string getTotalServiceT(queueSystem_t* pQ);
string getServiceDuration(queueSystem_t* pQ);
string getEntryDuration(queueSystem_t* pQ);
string convertTime(uint32_t ui32Seconds);
void printStats(queueSystem_t* pQueue);


#endif /* STATS_H_ */
