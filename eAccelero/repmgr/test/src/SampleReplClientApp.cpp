/* ********************************--CPP-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/
/*Test stub which uses the replication client library*/


#include "ReplicationClient.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "Serialize.h"
#define SYNC_CONN_SIZE 3
#define ASYNC_POOL_SIZE 4
#define BUCKET_NAME "DiameterSession"
#define BUCKET_NAME1 "DiameterSession"
#define SESSION_DEST_REALM_MAX_SIZE 70
#define SESSION_ID_LEN 128
#define SIZE 100
#define IP "172.15.3.31"
#define CALL_ST_ID "A100023123-123123-123123-123"
#define KEY "172.15.3.31.A100023123-123123-123123-123\0"
#define KEY_LEN 100
#define NO_OF_THREADS 4
char realm[SESSION_DEST_REALM_MAX_SIZE]="abcdevfghijklmnopqrstuvwxyz123479abcdefghijklmnopqrstuvwxyz12347";
char sessionId[SESSION_ID_LEN]="abcd.efgh.ijkl.mnop.qrst.uvwx.yz.com.234234.qwer.asas.afva.tfas;eqwr.beqw.utbf.grwf.as;123.123123.com";

sessBindKey *sessbindingkey;
sessInfo *sessionInfo;


typedef std::map<std::string ,struct  SessionInfo> IPV4AndCalledStationIdMap;
typedef std::map<std::string ,struct  SessionInfo> IPV6AndCalledStationIdMap;
typedef std::map<std::string ,struct SessionBindingKey> SessionBindingMap;


char *sessionIdList[SIZE];
char *calledStList[SIZE];
int indx=strlen(sessionId)-1;
int len=strlen(sessionId);
int varIndx;

typedef struct threadInformation
{
    int start;
    int end;
    std::string bucketName;

}ThreadInfo;

void assignSessInfo_SessBind_Struct()
{
    sessbindingkey=  new sessBindKey[SIZE];
    sessionInfo= new sessInfo[SIZE];
    assert(sessbindingkey);

    int i=0;
    for(i=0; i< SIZE ; i++)
    {
	if(i%2)
	{
	    sessbindingkey[i].isIPv4Address=true;
	}
	else
	{
	    sessbindingkey[i].isIPv4Address=false;
	}

	switch(i%4)
	{
	    case 0: sessionInfo[i].gxSessionFlag=1;
		    sessionInfo[i].serverName="Serverone"; 
		    break;
	    case 1: sessionInfo[i].gxxSessionFlag=1;
		    sessionInfo[i].serverName="Servertwo"; 
		    break;
	    case 2: sessionInfo[i].rxSessionFlag=1;
		    sessionInfo[i].serverName="Serverthree"; 
	            break;
	    case 3: sessionInfo[i].s9SessionFlag=1;
		    sessionInfo[i].serverName="Serverfour"; 
		    break;	
	}

	sessionInfo[i].sessionTerminateTimerId=i;
	sessionInfo[i].counter=i;

    }


}


void free_list()
{
    int i=0;
    for(i=0;i<SIZE;i++)
    {
        free(sessionIdList[i]);
	free(calledStList[i]);
	
    }

}

//function to generate callstation id random
void generateCallStnId()
{
    int i=0;
    char temp[10]={'0'};
    for( i=0;i< SIZE; i++)
    {
	    calledStList[i]=(char*)malloc(KEY_LEN);
 	    sprintf(temp,"%d",i);
	    strcpy(calledStList[i],KEY);
	    strcat(calledStList[i],temp);
        printf("%d = %s\n",i,calledStList[i]);	

    }
}

//function to generate random sessionIds
void generateSessionIds()
{
    int i=0;
    char temp[10]={'0'};
    for(i=0;i<SIZE;i++)
    {  
        sessionIdList[i]=(char*)malloc(SESSION_ID_LEN);


        sprintf(temp,"%d",i);


        if(sessionId[i%strlen(sessionId)] == 'z')
        {  
            sessionId[i%strlen(sessionId)]='0';
        }
        else
        {
                sessionId[i%strlen(sessionId)]++;
                while(!isalnum(sessionId[i%strlen(sessionId)]))
                {  
                    sessionId[i%strlen(sessionId)]++;
                    if(sessionId[i%strlen(sessionId)] == 'z')
                    {  
                        sessionId[i%strlen(sessionId)]='0';
                    }
                }

        }
        memcpy(sessionIdList[i],sessionId,SESSION_ID_LEN);

        strcat(sessionIdList[i],temp);
        //printf("%s\n",sessionIdList[i]);
        //       
        //
   }      
}

//thread to insert the elements
void *deleteThread(void *ptr)
{
    ThreadInfo *threadInfo=(ThreadInfo*)ptr;
    int startVal=threadInfo->start;
    int end=threadInfo->end;
    std::string bucketName=threadInfo->bucketName;
    for( int i=startVal; i<=end; i++)
    {
        ReplicationClient::GetInstance()->ReplicateDeletedEntry(bucketName,std::string(calledStList[i]));
    }
 
}


using namespace eAccelero;
int main(int argc , char *argv[])
{
    char serialBuff[256];
    char deSerialBuff[256];
    Serialize serializeObj;
    Serialize deSerializeObj;
    if(argc <= 7)
    {
	printf("Usage: <port> <username> <password> <bucket1> <bucket2> [ <operation> <start> <end> <RepeatCount>]....:\n");
	return 0;
    }

    generateSessionIds();
    generateCallStnId();
    assignSessInfo_SessBind_Struct();       

    std::vector<ReplicaBean> replicas;
    /*Populate the connection details*/
    CouchbaseConnectorBean connDetails;
    connDetails.serverAddress="localhost";
    connDetails.serverPort=atoi(argv[1]);
    connDetails.userName=argv[2];
    connDetails.password=argv[3];


    /*Populate the bucket details*/
    ReplicaBean bean(argv[4],4000,1000);
    replicas.push_back(bean);
    bean.replicaName=argv[5];;
    bean.replicaSize=4000;
    bean.replicaTTL=1000;
    replicas.push_back(bean);


    /*Initialize logger*/
    Logger m_logger("replication");
    // m_logger.SetLogChannel(&(DREController::Instance().GetSyslogChannel()));
    m_logger.SetLevel(Logger::EACC_LOG_DEBUG);         
 
    /*Initialize ReplicationClient library*/
    if( ReplicationClient::Initialize(SYNC_CONN_SIZE,
				 ASYNC_POOL_SIZE,
				 connDetails,
				 replicas,
				m_logger) != SUCCESS)
    {
	printf("ReplicationClient Initialization failure!\n");
	return 0;
    }
    int y;

    std::vector<std::string> outData;





    int test=10;
    std::string testkey="testKey";
    char buffer[10]={'\0'};
    
    sessInfo sessDataRead;
    sessBindKey  bindDataRead;   

    int dat=0;
    int end=0;
    int repeatCount=1;
    uint32_t output;

    ReplicationClient *replCl=ReplicationClient::GetInstance();

    replCl->GetBulkReplicatedEntries("IwfSessionEntries",1,10000,outData);

    scanf("%d",&y);
    for( int j=5;j<argc;j++)
    {
        switch(atoi(argv[j]))
 	{

	case 1:
	test=1;
        printf("INSERTING %s to %s\n",argv[j+1],argv[j+2]);
	end=atoi(argv[j+2]);
	repeatCount=atoi(argv[j+3]);
	for( int k=0; k < repeatCount ; k++)
	{
	    sleep(1);
	    printf("INSERT iteration %d\n",k+1);
            for( int i=atoi(argv[j+1]) ;i< end ;i++)
            {
		//serialize 
		serializeObj.serialize(ERLBF_SESS_INFO,serialBuff,&sessionInfo[i]);
                replCl->ReplicateNewEntry(argv[4],std::string(calledStList[i]),serialBuff,strlen(serialBuff)+1);
	//        replCl->ReplicateNewEntry(argv[5],std::string(sessionIdList[i]),(void*)&sessbindingkey[i],sizeof(SessionBindingKey));
	    }
	}
	j++;
	j++;
	j++;
        break;
    
        //scanf("%d",&y);
	case 2:
	test=2;
 	printf("UPDATING %s to %s\n",argv[j+1],argv[j+2]);
	end=atoi(argv[j+2]);
	repeatCount=atoi(argv[j+3]);
	for( int k=0 ; k <repeatCount; k++)
	{
	    sleep(1);
	    printf("UPDATE iteration %d\n",k+1);
            for( int i=atoi(argv[j+1]) ;i< end ;i++)
            {
		/**Serialize the entry*/

	        sessionInfo[i].serverName="UPDATED";
		serializeObj.serialize(ERLBF_SESS_INFO,serialBuff,&sessionInfo[i]);
                replCl->ReplicateUpdatedEntry(argv[4],std::string(calledStList[i]),serialBuff,strlen(serialBuff)+1);
	       // replCl->ReplicateUpdatedEntry(argv[5],std::string(sessionIdList[i]),(void*)&sessbindingkey[i],sizeof(SessionBindingKey));
            }
	}
	j++;
	j++;
	j++;
       	break;

	case 3:
	printf("READING %s to %s\n",argv[j+1],argv[j+2]);
	end=atoi(argv[j+2]);
	repeatCount=atoi(argv[j+3]);
	for( int k=0; k< repeatCount; k++)
	{
	    sleep(1);
	    printf("READ iteration %d\n",k+1);
            for( int i=atoi(argv[j+1]) ;i< end ;i++)
            {
		
	        if(replCl->GetReplicatedEntry(argv[4],std::string(calledStList[i]),deSerialBuff,&output) == SUCCESS)
	        { 
		   /*deserialize the entry*/
		    deSerializeObj.deserialize(ERLBF_SESS_INFO,&sessDataRead,(void*)deSerialBuff); 
	            printf("%d: sessDataReadSessId=%s sessCounter=%d len=%d\n",i,sessDataRead.serverName.c_str(),sessDataRead.counter,output);
	        }
                else
	        {
	            printf("ERROR in getting the value for %d\n",i);
	        }

	   	/* if(replCl->GetReplicatedEntry(argv[5],std::string(sessionIdList[i]),&bindDataRead,&output) == SUCCESS)
	    	{
	    	    printf("%d: bindDataReadServerName=%s len=%d\n",i,bindDataRead.key.c_str(),output);
	    	}
	    	else
	    	 {
	    	    printf("ERROR in getting the value for %d\n",i);
	    	}
      		*/
            }
	}
	j++;
	j++;
	j++;
       	break;

	case 4:
	printf("DELETING %s to %s\n",argv[j+1],argv[j+2]);
	end=atoi(argv[j+2]);
	repeatCount=atoi(argv[j+3]);
	for(int k=0; k< repeatCount ; k++)
	{
        ThreadInfo info[NO_OF_THREADS];
        pthread_t threads[NO_OF_THREADS];
        sleep(1);
	    printf("DELETE iteration %d\n",k+1);
        int start=atoi(argv[j+1]);


        for(int i=0;i<NO_OF_THREADS;i++)
        {
            info[i].start=i*((end-start)/NO_OF_THREADS);
            info[i].end=info[i].start+((end-start)/NO_OF_THREADS) -1;
            info[i].bucketName=argv[4];
            pthread_create(&threads[i],NULL,deleteThread,(void*)&info[i]);
            sleep(1);

        }
        for(int i=0;i<NO_OF_THREADS;i++)
        {

            pthread_join(threads[i],NULL);
        }

        //replCl->ReplicateDeletedEntry(argv[4],std::string(calledStList[i]));
        //    replCl->ReplicateDeletedEntry(argv[5],std::string(sessionIdList[i]));

	}
	
	j++;
	j++;
	j++;
        break;	

        }
    }
//    printf("Terminating connections!\n");
//    replCl->Terminate();

//*/
    while(1);

}
