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
 * LOG: $Log: dcca_stats.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.2  2006/11/14 10:17:17  hbhatnagar
 * LOG: shifted namespace to .cpp
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_stats.h,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $
 *
 ****************************************************************************/

#ifndef DCCA_STATS_H
#define DCCA_STATS_H

/**
 * Includes
 */
#include <its++.h>
#include <dia_stats.h>
#include <dcca_common.h>

/****************************************************************************
 *
 *  Interface: DCCAStats Class
 *      
 *  Purpose  : To implement DCCA statistics
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAStats : public DiaStats
{
public:
        /**
         * Singleton
         */
        static DCCAStats* GetDCCAStats();    
        /**
         * Destructor
         */
        ~DCCAStats();
        /**
         * To reset the statistics
         */
        void ResetAll();                
        /**
         * To print the statistics
         */
        void Print(std::ostream&) const;
        /**
         * To update the send statistics
         */
        void UpdateSendStats(DCCA_EVENT*);
        /**
         * To update the recv statistics
         */
        void UpdateRecvStats(DCCA_EVENT*);
        /**
         * Add to active session
         */
        void AddToActiveSession();
        /**
         * Remove from active session
         */
        void RemoveFromActiveSession();

private:
        /**
         * Constructor
         */
        DCCAStats();
        /**
         * Available counters
         */        
        ITS_UINT numCCRSent;
        ITS_UINT numCCASent;
        ITS_UINT numCCRRecv;
        ITS_UINT numCCARecv;
        ITS_UINT numActiveSessions;
};

#endif
