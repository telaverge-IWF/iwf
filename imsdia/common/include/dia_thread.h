/*********************************-*-C-*-************************************
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
 * ID: $Id: dia_thread.h,v 3.3 2008/09/05 07:16:23 vnarang Exp $
 *
 * LOG: $Log: dia_thread.h,v $
 * LOG: Revision 3.3  2008/09/05 07:16:23  vnarang
 * LOG: Arguments Order for Thread is changed
 * LOG:
 * LOG: Revision 3.2  2008/08/29 13:04:36  vnarang
 * LOG: Added a new constructor to create DETACHED threads
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2008/03/27 11:50:34  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.1.10.1  2008/01/06 10:04:21  avinashks
 * LOG: Changes made to provide fix for issue no.19 raised by Dhiranand during
 * LOG: the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.1  2006/10/05 11:53:11  yranade
 * LOG: ITS-Diameter specific updates. Removed cyclic dependency, move DiaThread
 * LOG: interface into it's own file.
 * LOG:
 ****************************************************************************/
#ident "$Id: dia_thread.h,v 3.3 2008/09/05 07:16:23 vnarang Exp $"

#ifndef DIA_THREAD_H
#define DIA_THREAD_H

#include <its++.h>
#include <its_thread.h>

/** DIAThread 
 *****************************************************************************
 *  Interface:
 *      DIAThread 
 *      
 *  Purpose:
 *      Provides an interface for application developers to
 *      design a multi-threaded application.
 *****************************************************************************/
class DIAThread:public its::Thread
{
public:
    /***********************************************************************/
    /** Purpose:
    *       Create a dia application specific thread
    *       
    *  Input Parameters:
    *       stackSize - size of thread stack
    *       running - worker name
    *       arg - function arguments
    *       
    ************************************************************************/
    DIAThread(int stackSize, bool running, void *arg)
        : its::Thread(stackSize, (ITS_THREAD_FUNC)CallFunc,
                 running ? ITS_TRUE : ITS_FALSE)
    {
        thread->thread.threadArg = arg;
    }
   

    /***********************************************************************/
    /** Purpose:
    *       Create a dia application specific thread on the basis of thread
    *       Type specified
    *       
    *  Input Parameters:
    *       stackSize - size of thread stack
    *       running - worker name
    *       arg - function arguments
    *       thrType - DETACHED or JOINABLE
    *       
    ************************************************************************/
    DIAThread(int stackSize, bool running, void *arg,THREAD_TYPE thrType)
        : its::Thread(stackSize, (ITS_THREAD_FUNC)CallFunc,thrType,
                 running ? ITS_TRUE : ITS_FALSE)
    {
        thread->thread.threadArg = arg;
    }
 
    /***********************************************************************/
    /** Purpose:
    *       Start a dia application specific thread    
    *           
    ************************************************************************/
    /**
     * Fix for issue No. 19 raised by Dhirananda.
     * Start returns value instead of void. 
    */
    int Start()
    {
        return Enter(this);
    }
    
    /***********************************************************************/
    /** Purpose:
    *       Destruct a dia application specific thread
    *           
    ************************************************************************/
    virtual ~DIAThread()
    {
    }
    /***********************************************************************/
    /** Purpose:
     *      Thread function
     *
     *  Notes:
     *      Specializations of this base class need to implement
     *      this method.  Specializations should include any data
     *      (or context) they need for this method in the instance
     *      data.
     *
     ************************************************************************/

    /* user needs to supply */
    virtual void Execute(void *arg){}

private:
   
    /***********************************************************************/
    /*  Purpose:
     *       Provide C/C++ linkage
     *
     *  Notes:
     *      Refer Execute()
     *
     ************************************************************************/
    static THREAD_RET_TYPE
    CallFunc(void *arg)
    {
        DIAThread *thr = (DIAThread *)arg;

        thr->Execute(thr->thread->thread.threadArg);

        THREAD_NORMAL_EXIT;
    }

};

#endif
