/******************************-*-CPP-*-**********************************
 *                                                                       *
 *          Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                         All Rights Reserved.                          *
 *          Manufactured in the United States of America.                *
 *    1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                       *
 *This product and related documentation is protected by copyright and   *
 *distributed under licenses restricting its use, copying, distribution  *
 *and decompilation.  No part of this product or related documentation   *
 *may be reproduced in any form by any means without prior written       *
 *authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                       *
 *RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *government is subject to restrictions as set forth in subparagraph     *
 *(c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                       *
 *************************************************************************
 */

#include <iomanip>

#include <stdlib.h>
#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>
#include <dia_incoming_msg_q.h>
#include <dia_utils.h>

#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_cmn.h>
#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif


ITS_Mutex IncomingMsgQ::instanceguard(0);
ITS_Mutex IncomingMsgQ::maplock(0);


IncomingMsgQ* IncomingMsgQ::m_IncomingMsgQueue = NULL;


IncomingMsgQ::IncomingMsgQ()
{}

IncomingMsgQ::~IncomingMsgQ()
{
}

IncomingMsgQ*
IncomingMsgQ::GetIncomingMsgQ()
{
 
    if (m_IncomingMsgQueue == NULL)
    {
        const_cast<ITS_Mutex&>(instanceguard).Acquire();

        m_IncomingMsgQueue = new IncomingMsgQ;

        const_cast<ITS_Mutex&>(instanceguard).Release();
    }
    
    return m_IncomingMsgQueue;
}

void
IncomingMsgQ::Lock() const
{
    int res = const_cast<ITS_Mutex&>(maplock).Acquire();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

void
IncomingMsgQ::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(maplock).Release();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}


  ITS_INT IncomingMsgQ::InsertMsgEvent(ITS_UINT& aIndex,bool& aMsgExist,ITS_EVENT* aEvent)
  	{
		DT_DBG(("ENTER InsertMsgEvent"));
		EventQ *lQueue=NULL;
		ITS_INT retVal=ITS_SUCCESS;
		Lock();
			
		std::map<ITS_UINT, EventQ*>::iterator mapIter;
		mapIter=m_InComingMsgMap.find(aIndex);
		if(mapIter != m_InComingMsgMap.end())
		{
			lQueue=(*mapIter).second;
			lQueue->push(aEvent);
			aMsgExist=true;
		    DT_DBG(("Found the entry for Sess-Index = %d , Session-Entry PedingMsg = %d ",aIndex,aMsgExist));
		}
		else
		{
	        DT_DBG(("Creating new entry for Sess-Index = %d",aIndex));
			lQueue = new EventQ();
			std::pair<std::map<ITS_UINT,EventQ*>::iterator,bool> ret;
   
			ret = m_InComingMsgMap.insert(std::pair<ITS_UINT,EventQ*>(aIndex,lQueue));
			if (ret.second== true)
			{
				lQueue->push(aEvent);
				aMsgExist=true;
				DT_DBG(("Insert entry Success , Session-Entry PedingMsg = %d ",aMsgExist));
			}
			else
			{
				retVal= (!ITS_SUCCESS);
				aMsgExist=false;
				delete lQueue; 
				DT_WRN(("Failed to Create Queue Entry for Sess-Index = %d",aIndex));
			}

		}
		Unlock();
		DT_DBG(("LEAVE InsertMsgEvent  and RetVal = %d",retVal));
		return retVal;
	}
  ITS_INT IncomingMsgQ::GetMsgEvent(ITS_UINT& aIndex,bool& aMsgExist,ITS_EVENT** aEvent)
  	{
		DT_DBG(("ENTER GetMsgEvent"));
		EventQ *lQueue=NULL;
		ITS_INT retVal=ITS_SUCCESS;
		Lock();
		std::map<ITS_UINT, EventQ*>::iterator mapIter;
		mapIter=m_InComingMsgMap.find(aIndex);
		if( (mapIter != m_InComingMsgMap.end()) && ( NULL != (*mapIter).second))
		{
			lQueue=(*mapIter).second;
			if(lQueue->empty())
			{
				aMsgExist=false;
				DT_DBG(("MsgEvent Queue is Empty"));
			}
			else
			{
				*aEvent = (ITS_EVENT*)lQueue->front();
				lQueue->pop();
				aMsgExist=(!lQueue->empty());
			}
			
		    DT_DBG(("Found MsgEvent Queue for Ses-Index = %d - Session-Entry PedingMsg = %d , queue-Empty = %d",aIndex,aMsgExist,lQueue->empty()));
		}
		else
		{
			retVal= (!ITS_SUCCESS);
			aMsgExist=false;
			DT_WRN(("No MsgEvent Queue Found for Ses-Index = %d - Session-Entry PedingMsg = %d",aIndex,aMsgExist));
		}
		Unlock();
		DT_DBG(("LEAVE GetMsgEvent RetVal = %d ",retVal));
		return retVal;
	}

  ITS_INT IncomingMsgQ::RemoveMsgEventEntry(ITS_UINT& aIndex)
  {
	  DT_DBG(("ENTER RemoveMsgEventEntry"));
	  EventQ *lQueue=NULL;
	  ITS_INT retVal=ITS_SUCCESS;
	  Lock();
	  std::map<ITS_UINT, EventQ*>::iterator mapIter;
	  mapIter=m_InComingMsgMap.find(aIndex);
	  if( (mapIter != m_InComingMsgMap.end()) && ( NULL != (*mapIter).second ))
	  {
			DT_DBG(("Found the Entry to be Removed for Sess-Indx = %d",aIndex));
			lQueue=(*mapIter).second;
			while(!lQueue->empty())
		        {
				ITS_EVENT* aEvent = (ITS_EVENT*)lQueue->front();
                                ITS_EVENT_TERM(aEvent);
				lQueue->pop();
				delete aEvent;
				aEvent=NULL;
			}
			delete lQueue;
			lQueue=NULL;
			m_InComingMsgMap.erase(mapIter);

		}
		else
		{
			retVal=(!ITS_SUCCESS);
			DT_WRN(("No MsgEvent Queue Found for Sess-Index = %d",aIndex));
		}
	   Unlock();
	   DT_DBG(("LEAVE RemoveMsgEventEntry  RetVal = %d",retVal));
	   return retVal;

  }
