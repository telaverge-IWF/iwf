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
 * LOG: $Log: dcca_context.h,v $
 * LOG: Revision 3.1.120.1  2014/11/17 05:03:39  jkchaitanya
 * LOG: changes for HA Bug Fixes
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.6  2007/01/23 07:46:56  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 * LOG: Revision 2.5  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.4  2006/11/14 10:12:42  hbhatnagar
 * LOG: shifted the namespace to .cpp
 * LOG:
 * LOG: Revision 2.3  2006/10/31 08:27:37  hbhatnagar
 * LOG: made changes to  ReleaseSession for BCGI
 * LOG:
 * LOG: Revision 2.2  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 13:03:40  nvijikumar
 * LOG: Bug Fix for ID: 4372 (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_context.h,v 3.1.120.1 2014/11/17 05:03:39 jkchaitanya Exp $
 *
 ****************************************************************************/

#ifndef DCCA_CONTEXT_H
#define DCCA_CONTEXT_H

/**
 * Includes
 */
#include <its++.h>
#include <dsm_ops.h>
#include <dcca_trace.h>
#include <dcca_stats.h>

/**
 * Defines
 */
#define DCCA_CONTEXT_TABLE_ID          0x50
#define DCCA_CONTEXT_TABLE_FT_GROUP_ID 0x00

#define DCCA_CONTEXT_ADD               0x00
#define DCCA_CONTEXT_FETCH             0x01
#define DCCA_CONTEXT_MODIFY            0x02
#define DCCA_CONTEXT_REMOVE            0x03
#define DCCA_CONTEXT_NONE              0x04
#define DCCA_CONTEXT_ERROR             0x05
#define DCCA_REMOVE_STACK_CONTEXT      0xF0

#define SESSION_ID_LENGTH              128


/**
 * DCCA context
 */
typedef struct _DCCA_CONTEXT
{    
    ITS_UINT    requestedaction;
    ITS_UINT    ccfh;
    ITS_UINT    mark;
    ITS_UINT    timer;
    ITS_UINT    state;
    ITS_UINT    session;
    ITS_UINT    requestType;
    ITS_UINT    statemachine;
    ITS_UINT    applicationid;
    ITS_UINT    clientId;
    ITS_SERIAL  timerkey;
    ITS_OCTET   sessionId[SESSION_ID_LENGTH]; /* The session Id String */
    bool        newlyReplicatedSession;
}
DCCA_CONTEXT;

/****************************************************************************
 *
 *  Interface: DCCAContext Class
 *      
 *  Purpose  : To maintain DCCA context
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAContext
{
public:
    /**
     * Constructor
     */
    DCCAContext();
    /**
     * Destructor
     */
    ~DCCAContext();
    /**
     * Method to set context
     */
    void SetContext(DCCA_CONTEXT*);
    /**
     * Method to get context
     */
    void GetContext(DCCA_CONTEXT*);

 private:
    /**
     * The DCCA_CONTEXT
     */
    DCCA_CONTEXT dccaContext;
};

/****************************************************************************
 *
 *  Interface: DCCAContextTable Class
 *      
 *  Purpose  : To maintain DCCA context
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCAContextTable
{      
public:
    /**
     * Constructor
     */
    DCCAContextTable();
    /**
     * Destructor
     */
    ~DCCAContextTable();
    /**
     * Method to access the DSM table
     */
    ITS_INT SubmitToCtx(ITS_INT, DCCA_CONTEXT*& ctx, ITS_OCTET* key, ITS_UINT len);

 private:
    /**
     * To update stat
     */
    DCCAStats *dccaStats;
    /**
     * Method to add an entry to DSM
     */
    ITS_INT Add(DCCA_CONTEXT*&, ITS_OCTET*, ITS_UINT);
    /**
     * Method to fetch an entry from DSM
     */
    ITS_INT Fetch(DCCA_CONTEXT*&, ITS_OCTET*, ITS_UINT);        
    /**
     * Method to modify an entry in DSM
     */
    ITS_INT Modify(DCCA_CONTEXT*&, ITS_OCTET*, ITS_UINT);
    /**
     * Method to remove an entry from DSM
     */
    ITS_INT Remove(ITS_OCTET*, ITS_UINT);
};

#endif
