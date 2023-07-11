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
 ****************************************************************************/


#ifndef DCCA_API_H
#define DCCA_API_H

#include <iostream>

/**
 * Defines for timer indications for the application
 */
#define DCCA_TIMER_TX_TIME_OUT  0x77
#define DCCA_TIMER_TCC_TIME_OUT 0x88


/*.Interface: DiaMsgRouter
 *****************************************************************************
 *  Interface:
 *      DCCAApi  Class
 *
 *  Purpose:
 *      Implement the DCCA MML API and make them available to external interface
 *****************************************************************************/

class DCCAApi
{
public:
     /**
     * The purpose of this function is to print the DCCA module statistics
     */   
    static  void  PrintDccaStats(std::ostream&);
    
    /**
    * The purpose of this function is to clear the present statistics
    */
    static  void  ClearDccaStats();

    /**
    * The purpose of this function is to enable the DCCA module Trace
    */
    static  void  EnableDccaTrace();

    /**
    * The purpose of this function is to disable the DCCA module Trace
    */
    static  void  DisableDccaTrace();

    /**
    * The purpose of this function is to set the value of Tx Timer
    */ 
    static  void  SetTxTimer(unsigned int timerVal);
    /** 
    * The purpose of this function is to set the value of Tcc Timer
    */
    static  void  SetTccTimer(unsigned int timerVal);

    /**
    * The purpose of this function is to get the Tx Timer Value
    */
    static  unsigned int GetTxTimer();

    /**
    * The purpose of this function is to get the Tcc Timer Value
    */
    static  unsigned int GetTccTimer();

private:

};

#endif
