/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: sip_transaction.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_transaction.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.11  2005/03/21 13:53:26  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.10.2.2  2005/02/07 14:12:25  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.10.2.1  2004/12/28 14:00:34  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.10  2004/06/28 07:33:13  sjaddu
 *  Bug fixes during load, SIP_Stackhandle is also added.
 *
 *  Revision 1.9  2004/05/16 08:47:46  sjaddu
 *  Added TCP support.
 *
 *  Revision 1.8  2004/04/21 06:45:04  sjaddu
 *  Fixed some bugs.
 *
 *  Revision 1.7  2004/04/16 04:54:55  akumar
 *  SIP attributes are configurable thru XML.
 *
 *  Revision 1.6  2004/04/15 12:16:16  sjaddu
 *  Added indications & state machine revamping.
 *
 *  Revision 1.5  2004/04/08 13:38:56  akumar
 *  Modified as per changes in SIP_MSG struct.
 *
 *  Revision 1.4  2004/04/05 07:47:25  sjaddu
 *  More testing, one complete call works fine.
 *
 *  Revision 1.3  2004/04/01 06:44:03  sjaddu
 *  Testing is in progress.
 *
 *  Revision 1.2  2004/03/30 11:51:42  sjaddu
 *  Commit after some unit testing is done.
 *
 *  Revision 1.1  2004/03/19 06:02:11  sjaddu
 *  Added first revsion for sip, work in progress.
 *
 ****************************************************************************/
#include <sip_intern.h>
#include <its_tq_trans.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <stdlib.h>
#include <its_transports.h>
#include <its_ss7_trans.h>

/* This is the transaction talbe */
static HASH_Table      __SIP_transactionTable = NULL;
static ITS_MUTEX       __SIP_hashGate;

static ITS_THREAD   *sipThread;
TQUEUETRAN_Manager *__SIP_RcvQueue;

static THREAD_RET_TYPE SIPThreadEntry(void *arg);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function Inits the transaction layer
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SIP_TransactionLayerInit()
{
    int numThreads = 1;
    int i =0;
    
    /* Create task que */
    if ((__SIP_RcvQueue = TQUEUETRAN_CreateTransport("ITS-SIP",
                                                      ITS_SIP_SRC,
                                                      ITS_APP_PROTOCOL_1)) == NULL)
    {
        return (ITS_ENOTRANSPORT);
    }

    /* Create Transaction table */
    SIP_InitTransactionTables();

    /* Dispatch a thread */
    for (i = 0; i < numThreads; i++)
    {
        if ((sipThread = (ITS_THREAD *)ITS_Calloc(numThreads,
                                               sizeof(ITS_THREAD))) == NULL)
        {
            SIP_ERROR(("SIP_TransactionLayerInit:: faled to init thread \n"));

            TQUEUETRAN_DeleteTransport(__SIP_RcvQueue);

            return (ITS_ENOMEM);
        }

        if (THREAD_CreateThread(&sipThread[i], 0, SIPThreadEntry,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            TQUEUETRAN_DeleteTransport(__SIP_RcvQueue);
            ITS_Free(sipThread);
            return ITS_EBADTHREAD;

        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is sip thread entry function to transaction layer
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static THREAD_RET_TYPE SIPThreadEntry(void *arg)
{
    ITS_EVENT sipEvent;
    ITS_BOOLEAN cont = ITS_TRUE;

    SIP_DEBUG(("SIPThreadEntry:: Enter \n"));

    while (cont)
    {
        SIP_DEBUG(("SIPThreadEntry:: Get Next Event Call \n\n"));

        sipEvent.data = 0;

        TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__SIP_RcvQueue))
                                                        (__SIP_RcvQueue,
                                                        &sipEvent);
        switch(sipEvent.src)
        {
        case ITS_SIP_TRANSPORT_SRC:
            SIP_DEBUG(("Received event from network \n"));
            SIP_HandleMsg(&sipEvent, ITS_SIP_TRANSPORT_SRC);
            break;

        case ITS_SIP_SRC:
            SIP_DEBUG(("Received event from its self, Terminate \n"));
            SIP_TermTransactionTables();
            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            SIP_DEBUG(("Received event from TIMER \n"));
            SIP_HandleTimeOut(&sipEvent);
            break;

        default :
            SIP_DEBUG(("Received event from application \n"));
            SIP_HandleMsg(&sipEvent, ITS_SIP_APP_SRC);
        }

    }
    THREAD_NORMAL_EXIT;    
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This creates hash table for transactions
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SIP_InitTransactionTables()
{
    int ret;
   
    if ((__SIP_transactionTable = HASH_CreateTable()) == NULL)
    {
        SIP_ERROR(("SIP_InitTransactionTables: Create failed\n"));

        return (ITS_ENOMEM);
    }

    if ((ret = MUTEX_CreateMutex(&__SIP_hashGate, 0)) != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_InitTransactionTables: mutex create failed\n"));

        HASH_DeleteTable(__SIP_transactionTable);

        return (ret);
    }

    /* Init ICT map table*/
    SIP_ICTLoadFsm();

    /* Init IST map table*/
    SIP_ISTLoadFsm();

    /* Init NICT map table*/
    SIP_NICTLoadFsm();

    /* Init NIST map table*/
    SIP_NISTLoadFsm();

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function deletes the hash table and hash mutex.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SIP_TermTransactionTables()
{

    HASH_DeleteTable(__SIP_transactionTable);

    MUTEX_DeleteMutex(&__SIP_hashGate);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      We need a decent little hash that's pretty good at eliminating
 *      duplicates. Lets take it from ISUP it used to work there well
 *
 *  Input Parameters:
 *      key - key data
 *      klen - key length
 *
 *  Return Value:
 *      hash value
 *
 *  Notes:
 *      if they use a lot of one byte keys they deserve the side effects.
 ****************************************************************************/
static ITS_INT
LocalHash(ITS_OCTET *key, ITS_UINT klen)
{
    ITS_INT ret = 131;
    ITS_UINT i;

    for (i = 0; i < klen; i++)
    {
        if (key[i])
        {
            ret *= (key[i] << 3) | 1;
        }
        else
        {
            ret *= ret;
        }
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates new transaction key from msg
 *
 *  Input Parameters:
 *      msg*  -  SIP_MSG pointer
 *
 *  Input/Output Parameters:
 *      key*  -   ptr to SIP_TRANSACTION_KEY
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Return the ITS_SUCCESS or ERROR code
 *
 *  Notes:
 *      No memory is allocated by this function
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SIP_TransactionKeyFromMsg(SIP_MSG *msg,
                          SIP_TRANSACTION_KEY *key)
{
    if (msg == NULL || key == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    strcpy(key->callId.number, msg->callId.number);
    strcpy(key->callId.host, msg->callId.host);

    key->cSeq.number = msg->cseq.number;
    strcpy(key->cSeq.method, msg->cseq.method);

    /*TBD*/
    /*key->viaUri = strdup(msg->topVia);*/

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the transaction entry func
 *
 *  Input Parameters:
 *          type  -  of type SIP_TRANSACTION_TYPE
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *          return Transaction entry function, or NULL
 *  Notes:
 *  See Also:
 ****************************************************************************/
SIP_TransactionEntryFunc
SIP_GetTransactionEntryFunc(SIP_TRANSACTION_TYPE type)
{
    SIP_DEBUG(("SIP_GetTransactionEntryFunc:: Entry \n"));
    switch (type)
    {
    case SIP_ICT:
        return SIP_ICTEntry;
    case SIP_IST:
        return SIP_ISTEntry;
    case SIP_NICT:
        return SIP_NICTEntry;
    case SIP_NIST:
        return SIP_NISTEntry;
    default:
        SIP_ERROR(("SIP_GetTransactionEntryFunc:: No match for tr type\n"));
        return NULL;
    }
} 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns transaction type 
 *
 *  Input Parameters:
 *      msg*  -  SIP_MSG pointer
 *
 *  Input/Output Parameters:
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *          Transaction type
 *  Notes:
 *  See Also:
 ****************************************************************************/
SIP_TRANSACTION_TYPE
SIP_GetTransactionType(SIP_MSG *msg, ITS_USHORT src)
{
    SIP_DEBUG(("SIP_GetTransactionType:: Getting the tr type\n"));
    switch(msg->msgId)
    {
    case SIP_MSG_REGISTER:
    case SIP_MSG_BYE:
    case SIP_MSG_OPTIONS:
        if (src != ITS_SIP_TRANSPORT_SRC)
        {
            SIP_DEBUG(("SIP_GetTransactionType::  SIP_NICT\n"));
            return  SIP_NICT;
        }
        else
        {   
            SIP_DEBUG(("SIP_GetTransactionType::  SIP_NIST\n"));
            return SIP_NIST;
        }
    case SIP_MSG_INVITE:
    case SIP_MSG_PRACK:
        if (src != ITS_SIP_TRANSPORT_SRC)
        {
            SIP_DEBUG(("SIP_GetTransactionType::  SIP_ICT\n"));
            return  SIP_ICT;
        }
        else
        {
            SIP_DEBUG(("SIP_GetTransactionType::  SIP_IST\n"));
            return SIP_IST;
        }
    }
    SIP_ERROR(("Invalid msg Id = %d \n", msg->msgId));
    return SIP_ICT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function inits the transaction contxet
 *
 *  Input Parameters:
 *      msg*  -  SIP_MSG pointer
 *
 *  Input/Output Parameters:
 *      returnCode*  -   ptr to ITS_INT
 *                       Return the ITS_SUCCESS or ERROR code
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      ctxt *  -  memory is allocated this function
 *  See Also:
 ****************************************************************************/
static int
SIP_InitTransactionCtxt(SIP_MSG *msg, SIP_TRANSACTION_CTXT **ctxt)
{
    if (msg == NULL || ctxt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    *ctxt = ITS_Malloc(sizeof(SIP_TRANSACTION_CTXT));

    strcpy((*ctxt)->callId.number, msg->callId.number);
    strcpy((*ctxt)->callId.host, msg->callId.host);

    strcpy((*ctxt)->cSeq.method, msg->cseq.method);
    (*ctxt)->cSeq.number =  msg->cseq.number;

    /*TDB for other headers */

    (*ctxt)->locked = ITS_TRUE;

    (*ctxt)->lockTime = TIMERS_Time();

    (*ctxt)->purge = ITS_FALSE;

    (*ctxt)->msgBuf = NULL;

    (*ctxt)->sipMsg = NULL;
    
    (*ctxt)->lastRes = 0; 

    (*ctxt)->tId  = 0;  /* do we require this */

    (*ctxt)->fsmState = SIP_IDLE;
       
    (*ctxt)->isReliableResp = ITS_FALSE;

    (*ctxt)->timerKey = 0; 

    (*ctxt)->reTranstimer = SIP_configInfo.T1; 
    
    /* These are deault, override out side */
    (*ctxt)->port = SIP_DEFAULT_SOCK_PORT; 

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function copies headers from msg to the transaction contxet
 *
 *  Input Parameters:
 *      msg*  -  SIP_MSG pointer
 *
 *  Input/Output Parameters:
 *      returnCode*  -   ptr to ITS_INT
 *                       Return the ITS_SUCCESS or ERROR code
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      Deletes old header and copies the new ones 
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SIP_CopyHeadersToCtxt(SIP_MSG *msg, SIP_TRANSACTION_CTXT *ctxt)
{
    if (msg == NULL || ctxt == NULL)
    {
        return ITS_EINVALIDARGS;
    }
    
    /*Fill the header*/
    strcpy(ctxt->callId.number, msg->callId.number);
    strcpy(ctxt->callId.host, msg->callId.host);

    strcpy(ctxt->cSeq.method, msg->cseq.method);
    ctxt->cSeq.number =  msg->cseq.number;

    /* More header later TBD*/

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function compares the keys
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *                       Return the ITS_TRUE or FALSE
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
SIP_CompareCallId(SIP_CALLID_HDR * rcallId, SIP_CALLID_HDR * lcallId )
{
    if (strcmp(rcallId->number, lcallId->number) == 0 &&
        strcmp(rcallId->host,   lcallId->host)  == 0)
    {
        return ITS_TRUE;
    }
    else
    {
        SIP_DEBUG(("SIP_CompareCallId::Failed number %s host = %s \n",
                    lcallId->number, lcallId->host));
        return ITS_FALSE;
    } 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function compares the keys
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *                       Return the ITS_TRUE or FALSE
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
SIP_CompareCseq(SIP_CSEQ_HDR * rCseq, SIP_CSEQ_HDR * lCseq )
{
    if (rCseq->number == lCseq->number)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    } 
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates new transaction in tr table
 *
 *  Input Parameters:
 *      msg*  -  SIP_MSG pointer
 *
 *  Input/Output Parameters:
 *      returnCode*  -   ptr to ITS_INT
 *                       Return the ITS_SUCCESS or ERROR code
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      Incase of success This method will lock the row the return pointer
 *      caller should call release after this call
 *      ctxt *  -  memory is allocated this function
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SIP_TRANSACTION_CTXT *
SIP_CreateTransactionCtxt(SIP_MSG *msg, ITS_INT *returnCode)
                          
{
    SIP_TRANSACTION_CTXT *dummy;
    SIP_TRANSACTION_CTXT *tmp;
    SIP_TRANSACTION_CTXT *ctxt;
    int hash =0 , ret = 0;
    *returnCode = ITS_SUCCESS;
    
    if (msg == NULL || returnCode == NULL) 
    {
        SIP_ERROR(("SIP_CreateTransactionCtxt:: Failed \n"));
        if (returnCode)
            *returnCode = ITS_EINVALIDARGS;
        return NULL;
    }

    if (MUTEX_AcquireMutex(&__SIP_hashGate) != ITS_SUCCESS)
    {
        *returnCode = ITS_EBADMUTEX;
        return NULL;
    }

    hash = LocalHash((ITS_OCTET *)msg->callId.number,
                                  strlen(msg->callId.number));

    ret = HASH_FindEntry(__SIP_transactionTable, SIP_TRANSACTION_RID,
                         hash, (ITS_POINTER*) &dummy);
    if (ret == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            /* compare callId, cSeq, and top via TBD */
            if (SIP_CompareCallId(&tmp->callId, &msg->callId) &&
                SIP_CompareCseq(&tmp->cSeq, &msg->cseq) ) 
            {
                SIP_ERROR(("SIP_CreateTransactionCtxt:: Failed to create "
                           "transaction ctxt , collision already exists \n"));
                *returnCode = ITS_EINUSE;

                MUTEX_ReleaseMutex(&__SIP_hashGate);
                return NULL;
            }
        }
    }

    if (SIP_InitTransactionCtxt(msg, &ctxt) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__SIP_hashGate);
        *returnCode = ITS_ENOMEM;
        return NULL;
    }

    /* If at all this is a collision */
    ctxt->next = dummy;

    if (HASH_AddEntry(__SIP_transactionTable, SIP_TRANSACTION_RID,
                        hash, (ITS_POINTER) ctxt) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__SIP_hashGate);
        ITS_Free(ctxt);
        *returnCode = ITS_ENOMEM;
        return NULL;
    }

    SIP_DEBUG(("SIP_CreateTransactionCtxt:: Success \n"));

    MUTEX_ReleaseMutex(&__SIP_hashGate);
    return ctxt;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Finds the transaction ctxt.
 *      This method will lock the row the return pointer
 *      caller should release after this call
 *
 *  Input Parameters:
 *      brachId*  -  Branch Id from top via field
 *      method   -  method type upcode
 *
 *  Input/Output Parameters:
 *      SIP_TRANSACTION_CTXT**  -  ptr to SIP_TRANSACTION_CTXT
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Return the ITS_SUCCESS or ERROR code
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI SIP_TRANSACTION_CTXT *
SIP_FindTransactionCtxt(SIP_TRANSACTION_KEY *key,
                        ITS_INT *returnCode)
{
    int ret = 0;
    SIP_TRANSACTION_CTXT *dummy;
    SIP_TRANSACTION_CTXT *tmp;
    int hash = 0;

    if (key == NULL || returnCode == NULL)
    {
        SIP_ERROR(("SIP_FindTransactionCtxt:: Failed \n"));
        if (returnCode)
        {
            *returnCode = ITS_EINVALIDARGS;
        }
        return NULL;
    }

    if (MUTEX_AcquireMutex(&__SIP_hashGate) != ITS_SUCCESS)
    {
        SIP_ERROR((": Couldn't acquire mutex.\n"));
        *returnCode = ITS_EBADMUTEX;
        return NULL;
    }

    /*Get the hash key from call Id */
    hash = LocalHash((ITS_OCTET *)key->callId.number,
                                  strlen(key->callId.number));

    ret = HASH_FindEntry(__SIP_transactionTable, SIP_TRANSACTION_RID,
                         hash, (ITS_POINTER*) &dummy);
    if (ret != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__SIP_hashGate);
        *returnCode = ITS_ENOTFOUND;
        return NULL;
    }
    else
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (SIP_CompareCallId(&tmp->callId, &key->callId) && 
                SIP_CompareCseq(&tmp->cSeq, &key->cSeq) )
            {
                SIP_DEBUG(("SIP_FindTransactionCtxt:: Found the entry \n"));
                break;
            }
        }

        if (tmp == NULL)
        {
            SIP_DEBUG(("Could not the match with the header \n"));
            *returnCode = ITS_ENOTFOUND;
            return NULL;
        }
    }

    if (tmp->locked)
    {
        *returnCode = ITS_EINUSE;
        MUTEX_ReleaseMutex(&__SIP_hashGate);
        SIP_DEBUG(("SIP_FindTransactionCtxt:: Entry In Use "));
        return NULL;
    }

    tmp->lockTime = TIMERS_Time();
    tmp->locked = ITS_TRUE;
    *returnCode = ITS_SUCCESS;
    MUTEX_ReleaseMutex(&__SIP_hashGate);

    return tmp;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function releases the transaction row lock
 *      This call should  follow after  FindTransactionCtxt()
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS incase of success or error code
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SIP_CommitTransactionCtxt(SIP_TRANSACTION_CTXT *ctxt)
{
    if (ctxt == NULL)
    {
        return ITS_EINVALIDARGS;
    }    

    if (MUTEX_AcquireMutex(&__SIP_hashGate) != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_CommitTransactionCtxt:: Couldn't acquire mutex.\n"));
        return ITS_EBADMUTEX;
    }

    if (ctxt->locked)
    {
        ctxt->locked = ITS_FALSE;
        ctxt->lockTime = 0;
    }
    else
    {
        SIP_ERROR(("SIP_CommitTransactionCtxt:: We  have problem here"
                   " caller attmpted to commit ctxt, without lock \n"));
        MUTEX_ReleaseMutex(&__SIP_hashGate);   
        return ITS_EROWNOTLOCKED;
    }
    
    MUTEX_ReleaseMutex(&__SIP_hashGate);   

    SIP_DEBUG(("SIP_CommitTransactionCtxt:: Commiting the row \n"));

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function frees the memory for transaction ctxt
 *
 *  Input Parameters:
 *      ctxt - ptr of type SIP_TRANSACTION_CTXT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SIP_FreeTransactionCtxt(SIP_TRANSACTION_CTXT *ctxt)
{
    if (ctxt->msgBuf != NULL)
        ITS_Free(ctxt->msgBuf);

    if (ctxt->sipMsg != NULL)
       SIP_MsgFree(ctxt->sipMsg);

    ITS_Free(ctxt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function delete the transaction ctxt from tr table
 *
 *  Input Parameters:
 *      ctxt  - ptr to SIP_TRANSACTION_CTXT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      This call frees the memory for ctxt, caller MUST not attempt
 *      to use ctxt after this call.
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SIP_DeleteTransactionCtxt(SIP_TRANSACTION_CTXT *ctxt)
{
    int hash = 0;
    int ret = 0;
    SIP_TRANSACTION_CTXT *tmp1 = NULL;
    SIP_TRANSACTION_CTXT *tmp  = NULL;
    SIP_TRANSACTION_CTXT *dummy  = NULL;

    if (ctxt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    if (MUTEX_AcquireMutex(&__SIP_hashGate) != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_DeleteTransactionCtxt:: Couldn't acquire mutex.\n"));
        return ITS_EBADMUTEX;
    }

    if (!ctxt->locked)
    {
        SIP_ERROR(("SIP_DeleteTransactionCtxt:: Row not locked \n"));
        MUTEX_ReleaseMutex(&__SIP_hashGate);
        return ITS_EROWNOTLOCKED;
    }

    /*Get the hash key from call Id */
    hash = LocalHash((ITS_OCTET *)ctxt->callId.number,
                                  strlen(ctxt->callId.number));

    ret = HASH_FindEntry(__SIP_transactionTable, SIP_TRANSACTION_RID,
                         hash, (ITS_POINTER*) &dummy);
    if (ret == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (tmp  == ctxt)
            {
                if (tmp1 == NULL)
                {
                    dummy = tmp->next;
                    SIP_FreeTransactionCtxt(tmp);
                    break;
                }
                tmp1->next = tmp->next;
                SIP_FreeTransactionCtxt(tmp);
                break;
            }
            else
            {
                tmp1 = tmp;
            }
        }
    }

    /*
     * delete entry
     */
    if (dummy == NULL)
    {
        ret = HASH_DeleteEntry(__SIP_transactionTable,
                               SIP_TRANSACTION_RID, hash);
        SIP_DEBUG(("SIP_DeleteTransactionCtxt:: Deleting Entry\n"));
    }
    else
    {
        ret = HASH_AddEntry(__SIP_transactionTable, SIP_TRANSACTION_RID,
                            hash, (ITS_POINTER)dummy);
        SIP_DEBUG(("SIP_DeleteTransactionCtxt:: Deleting tr Entry\n"));
    }


    MUTEX_ReleaseMutex(&__SIP_hashGate);

    SIP_DEBUG(("SIP_DeleteTransactionCtxt:: Exit \n"));

    return ret;
}
