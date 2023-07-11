/*********************************-*-HPP-*-**********************************
*                                                                          *
*             Copyright 2006 IntelliNet Technologies, Inc.                 *
*                            All Rights Reserved.                          *
*             Manufactured in the United States of America.                *
*       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
*                                                                          *
*   This product and related documentation is protected by copyright and   *
*   distributed under licenses restricting its use, copying, distribution  *
*   and decompilation.  No part of this product or related documentation   *
*   may be reproduced in any form by any means without prior written       *
*   authorization of IntelliNet Technologies and its licensors, if any.    *
*                                                                          *
*   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
*   government is subject to restrictions as set forth in subparagraph     *
*   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
*   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
*                                                                          *
*****************************************************************************/


#if !defined DIA_INCOMING_EVENT_Q_H_
#define DIA_INCOMING_EVENT_Q_H_

#include <map>
#include <queue>


#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>

class IncomingMsgQ
{
public:
    
  static IncomingMsgQ *GetIncomingMsgQ();


  ITS_INT InsertMsgEvent(ITS_UINT& aIndex,bool& aMsgExist,ITS_EVENT* aEvent);
  ITS_INT GetMsgEvent(ITS_UINT& aIndex,bool& aMsgExist,ITS_EVENT** aEvent);
  ITS_INT RemoveMsgEventEntry(ITS_UINT& aIndex);

   
	IncomingMsgQ();
    ~IncomingMsgQ(); 

private:

	void Lock() const;
    void Unlock() const;

	
    typedef std::queue<ITS_EVENT*> EventQ;
    typedef std::map<ITS_UINT, EventQ*> IndexToEventMap;
    IndexToEventMap m_InComingMsgMap;

    static its::ITS_Mutex maplock;
    static its::ITS_Mutex instanceguard;
    static IncomingMsgQ* m_IncomingMsgQueue;
};

#define INCOMING_MESSAGEQ   IncomingMsgQ::GetIncomingMsgQ()



#endif
