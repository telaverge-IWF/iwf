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
 * LOG: 
 * LOG:
 * LOG:
 *
 * ID: $Id: 
 *
 ****************************************************************************/

#ifndef DCCA_CONF_H
#define DCCA_CONF_H

/**
 * Includes
 */
#include <its++.h>
#include <dcca_trace.h>

/**
 * Defines
 */
#define DCCA_CONF_CCFH      0x11
#define DCCA_CONF_TX_TIMER  0x22
#define DCCA_CONF_TCC_TIMER 0x33
#define DCCA_CONF_RETAIN_SESSION 0x44

/****************************************************************************
 *
 *  Interface: DCCAConf Class
 *      
 *  Purpose  : To implement DCCA configuration
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAConf 
{
    public:
        /**
         * Singleton
         */
        static DCCAConf* GetDCCAConf();    
        /**
         * Destructor
         */
        ~DCCAConf();
        /**
         * To get conf
         */
        ITS_UINT GetConf(ITS_INT);
        /**
         * To set conf
         */
        void SetConf(ITS_INT, ITS_UINT);
        /**
         * To print the configuration
         */
        void Print(std::ostream&) const;

    private:
        /**
         * Constructor
         */
        DCCAConf();
        /**
         * Available conf
         */        
        ITS_UINT tx;
        ITS_UINT tcc;
        ITS_UINT ccfh;
        ITS_UINT retainSession;
};

#endif
