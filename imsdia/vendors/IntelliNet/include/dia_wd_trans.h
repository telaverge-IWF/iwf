/*********************************-*H*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 * LOG: $Log: dia_wd_trans.h,v $
 * LOG: Revision 3.2.68.2  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.2.68.1  2013/02/25 14:07:26  mallikarjun
 * LOG: Bug 623 changes DWR
 * LOG:
 * LOG: Revision 3.2  2008/08/25 05:52:12  ssaxena
 * LOG: 1. Failover / Failback indications to application
 * LOG: 2. Failback is XML configurable option
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.1.2.1  2007/12/14 11:19:27  hbhatnagar
 * LOG: Baselined the DeviceWatchDog Transport thread functionality removing the
 * LOG: DW Timer functionality.
 * LOG:
 * ID: $Id: dia_wd_trans.h,v 3.2.68.2 2013/04/07 03:54:21 cprem Exp $
 ****************************************************************************/
#ident "$Id: dia_wd_trans.h,v 3.2.68.2 2013/04/07 03:54:21 cprem Exp $"

#ifndef DIA_WD_TRANS_H
#define DIA_WD_TRANS_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_peer_table.h>

#define DEFAULT_DW_TIMER 6

/*.Interface: DiaWatchDogTransport
 *****************************************************************************
 *  Interface:
 *      DiaWatchDogTransport Class derived from DIAThread class.
 *
 *  Purpose:
 *      Implement the DeviceWatchDog Timer Functionality using thread.
 *****************************************************************************/
class DiaWatchDogTransport: public DIAThread
{
public:
    DiaWatchDogTransport(bool activate = true)
        :DIAThread(0, true, this)
    {
        m_bDeActivated = !activate ;
        _doExit = ITS_FALSE;
    }


    virtual ~DiaWatchDogTransport()
    {
    }

    void SetExit()
    {
        _doExit = ITS_TRUE;
    }

    ITS_USHORT GetInstance()
    {
        return _instance;
    }

    void Shutdown();

    void Execute(void *arg);

    int SendDWR(ITS_USHORT inst);
 
    static int InitiateFailover(ITS_USHORT inst);

    static int SendFailoverIndToApp(PEER_ENTRY *peer);

    void DeActivate()
    {
        m_bDeActivated = true;
    }
    void Activate()
    {
        m_bDeActivated = false;
    }

protected:
    ITS_USHORT   _instance;
    ITS_BOOLEAN  _doExit;
private:

    bool m_bDeActivated;
};

#endif


