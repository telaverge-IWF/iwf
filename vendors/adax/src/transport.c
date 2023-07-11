/*********************************-*-C-*-************************************
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
 *
 *  ID: $Id: transport.c,v 9.4 2008/06/04 10:17:15 ssingh Exp $
 *
 * LOG: $Log: transport.c,v $
 * LOG: Revision 9.4  2008/06/04 10:17:15  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.3  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2.6.13  2008/03/28 15:56:37  skatta
 * LOG: fix for issue MTP2 traces are not disabled through OAM
 * LOG:
 * LOG: Revision 9.2.6.12  2007/09/17 07:10:34  ssingh
 * LOG: Fix provided for Issue ID:50 is propagated to Main Branch
 * LOG:
 * LOG: Revision 9.2.6.11  2006/12/23 10:07:00  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.2.6.10  2006/11/29 09:06:45  rdangi
 * LOG: Fix for Issue 4978 (ATM Service Option XML Parsing)
 * LOG:
 * LOG: Revision 9.2.6.9  2006/11/23 14:39:18  rdangi
 * LOG: Fix for Bug ID:4896-ATM Link Alignment Issue
 * LOG:
 * LOG: Revision 9.2.6.8  2006/11/20 15:15:57  rdangi
 * LOG: modified for the correct handling of vcid,vpi and vci
 * LOG:
 * LOG: Revision 9.2.6.7  2006/11/14 16:06:18  rdangi
 * LOG: Corrected the handling of attributes for VC_Info section during Parsing
 * LOG:
 * LOG: Revision 9.2.6.6  2006/10/27 16:17:56  rdangi
 * LOG: Initialize the numTimeslots with ZERO-magesh
 * LOG:
 * LOG: Revision 9.2.6.5  2006/05/17 14:55:43  lbana
 * LOG: Scrambling bit PBN Issue ID 3288
 * LOG:
 * LOG: Revision 9.2.6.4  2006/05/17 14:49:43  lbana
 * LOG: PBN Issue ID 3288:Made scrambling bit configurable
 * LOG:
 * LOG: Revision 9.2.6.3  2005/11/11 22:43:00  randresol
 * LOG: Add Sercice Option parameters for ATM
 * LOG:
 * LOG: Revision 9.2.6.2  2005/10/05 19:48:53  randresol
 * LOG: Remove some printf statements and fix default setup for "hardware"
 * LOG:
 * LOG: Revision 9.2.6.1  2005/09/12 04:36:42  randresol
 * LOG: Add implementation for ADAX ATMII Platform
 * LOG:
 * LOG: Revision 9.2  2005/05/06 10:06:23  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:54:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.1.6.2.6.4  2005/01/05 12:29:19  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.4.2.1.6.2.6.3  2005/01/05 10:29:10  snagesh
 * LOG: removed tabs
 * LOG:
 * LOG: Revision 7.4.2.1.6.2.6.2  2005/01/03 15:20:49  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.4.2.1.6.2.6.1  2004/12/16 14:56:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.4.2.1.6.2  2004/09/15 06:10:38  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.4.2.1.6.1  2004/07/09 07:06:46  dsatish
 * LOG: Merging activity for timeslot and 56kbps changes
 * LOG:
 * LOG: Revision 7.4.2.1  2003/05/07 11:36:31  ssingh
 * LOG: New ISUP function is added in vendor Class.
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.3  2002/12/04 04:21:30  randresol
 * LOG: Add PRC classes for Adax
 * LOG:
 * LOG: Revision 7.2  2002/11/09 20:42:42  randresol
 * LOG: fix parameter in read()
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/17 16:07:50  randresol
 * LOG: Bug in resource generation code
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.21  2002/02/26 21:17:35  mmiers
 * LOG: Debugging, cleanup.
 * LOG:
 * LOG: Revision 1.20  2002/02/01 22:12:37  mmiers
 * LOG: ISUP integration.
 * LOG:
 * LOG: Revision 1.19  2002/01/29 20:12:21  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.18  2002/01/10 16:50:07  mmiers
 * LOG: Switch to refcounting transports.
 * LOG:
 * LOG: Revision 1.17  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 1.16  2001/12/28 18:43:40  mmiers
 * LOG: A few mistakes to fix.
 * LOG:
 * LOG: Revision 1.15  2001/12/19 23:54:02  mmiers
 * LOG: Get ADAX vendor lib working.
 * LOG:
 * LOG: Revision 1.14  2001/12/19 21:01:14  mmiers
 * LOG: Don't pollute the namespace.
 * LOG:
 * LOG: Revision 1.13  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 1.12  2001/12/18 21:59:19  mmiers
 * LOG: Standardize on exports for vendors
 * LOG:
 * LOG: Revision 1.11  2001/12/18 21:34:51  mmiers
 * LOG: Interim version
 * LOG:
 * LOG: Revision 1.10  2001/12/18 21:23:37  mmiers
 * LOG: New format vendor
 * LOG:
 * LOG: Revision 1.9  2001/10/29 19:31:55  ngoel
 * LOG: Code SS7_PeekNextEvent
 * LOG:
 * LOG: Revision 1.8  2001/10/29 15:35:36  ngoel
 * LOG: bug fix link code configuration
 * LOG:
 * LOG: Revision 1.7  2001/10/27 03:40:50  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.6  2001/10/26 19:17:03  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.5  2001/10/25 21:43:39  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.4  2001/10/25 15:09:45  ngoel
 * LOG: add xml parser extension
 * LOG:
 * LOG: Revision 1.3  2001/10/24 15:30:15  ngoel
 * LOG: add Read INI
 * LOG:
 * LOG: Revision 1.2  2001/10/23 18:35:03  ngoel
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.1  2001/10/22 18:34:37  ngoel
 * LOG: first commit
 * LOG:
 *
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include <its.h>
#include <its_intern.h>
#include <its_mlist.h>
#include <its_ss7_trans.h>
#include <its_assertion.h>
#include <engine.h>
#include <mtp2_sn.h>

#include <sys/types.h>
#include <sys/poll.h>

#define ITS_INFINITE    -1

#define ADAX_INI_SECTION_NAME   "ADAX-TRACE"

/*
 * error reporting
 */
int adax_errno = 0;
#ifdef DEBUG
int adax_debug = 1;
#else
int adax_debug = 0;
#endif

/* Global Variable */
 
ITS_BOOLEAN trace_construct_flag = ITS_FALSE;

extern TRACE_LevelInitializer MTP2_TraceMap[];

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      read the INI file.
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
 ****************************************************************************/
static int
ReadInstance_STANDALONE(ITS_SS7_HANDLE hand, int instance)
{
    ITS_SS7_CONTEXT *handle = (ITS_SS7_CONTEXT *)hand;
    char *env, buf[1024];
    FILE *f;

    sprintf(buf, "./ADAX.ini", env);
    if ((f = fopen(buf, "r")) == NULL)
    {
        if (adax_debug)
        {
            printf("Can't open config file for this instance.\n");
        }
        
        return 0;
    }

    if (adax_debug)
    {
        printf("Reading from config file: %s\n", buf);
    }

    while (fgets(buf, 256, f) != NULL)
    {
        char *tok;

        if (buf[0] == '#' || buf[0] == ';' || buf[0] == '\n')
        {
            continue;
        }

        if ((tok = strchr(buf, '=')) == NULL)
        {
            if (adax_debug)
            {
                printf("Malformed line in config file:\n%s\n\n", buf);
            }

            continue;
        }

        *tok = 0;
        tok++;

        if (strncmp(buf, "trunk", strlen("trunk")) == 0)
        {
            handle->trunk = atoi(tok);
        }
        else if (strncmp(buf, "TR_TYPE", strlen("TR_TYPE")) == 0)
        {
            handle->trunkType = atoi(tok);
        }
        else if (strncmp(buf, "baudRate", strlen("baudRate")) == 0)
        {
            handle->baudRate = atoi(tok);
        }
        else if (strncmp(buf, "timeSlots", strlen("timeSlots")) == 0)
        {
            handle->dataLink[0].timeslot = atoi(tok);
        }
        else if (strncmp(buf, "linkSet", strlen("linkSet")) == 0)
        {
            handle->linkSet = atoi(tok);
        }
        else
        {
            if (adax_debug)
            {
                printf("Invalid line in ini file: %s\n", buf);
            }
        }
    }

    if (adax_debug)
    {
        int i;

        printf("ITS read the following:\n");
        printf("  trunk: %d\n", handle->trunk);
        printf("  trunkType: %d\n", handle->trunkType);
        printf("  linkCodes:");
        for (i = 0; i < handle->numTimeslots; i++)
        {
            printf(" %d ", handle->dataLink[i].timeslot);
        }
        printf("\n");
        printf(" linkSet: %d\n", handle->linkSet);
    }

    return 1;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      read the resource database
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
 *  Revision History:
 *  -----------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 *
 *  ------------------------------------------------------------------------
 *  Magesh S 23/11/2006   Bug ID: 4896    Fix for ATM Link Alignment Failure
 ****************************************************************************/
static int
ReadInstance_INTEGRATED(ITS_SS7_HANDLE hand, ITS_USHORT instance)
{
    char buf[1024];
    char key[ITS_PATH_MAX], value[ITS_PATH_MAX];
    ITS_OCTET currentLinkCode;
    ITS_USHORT currentCircuit;
    ITS_UINT vcid[MAX_DATA_LINKS], vci[MAX_DATA_LINKS], vpi[MAX_DATA_LINKS];

    ITS_SS7_CONTEXT *handle = (ITS_SS7_CONTEXT *)hand;
    ITS_UINT i, j, idx;
    TRANSPORT_Control *tr = TRANSPORT_FindTransport(instance);

    /* Initialize vcid, vpi and vci */
    for(i = 0; i < MAX_DATA_LINKS; i++)
    {
      vcid[i] = -1;
      vpi[i] = -1;
      vci[i] = -1;
    }

    if (tr == NULL)
    {
        return 0;
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "hardware",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->hardware = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              ATM_SCRAMB_CELL_PAYLOAD_STR, buf, 1024) == ITS_SUCCESS)
    {
        handle->scrambType = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "trunk",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->trunk = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "TR_TYPE",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->trunkType = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "connectType",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->connectionType = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "baudRate",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->baudRate = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "globalServiceOptonsPresent",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptonsPresent = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "trafficClass",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.trafficClass = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "peekCellRate",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.peekCellRate = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "minimumSustainableCellRate",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.minimumSustainableCellRate = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "maxBurstSize",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.maxBurstSize = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "initialCellRate",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.initialCellRate = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "priority",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->globalServiceOptions.priority = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "linkSet",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->linkSet = atoi(buf);
    }
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "timeSlots",
                              buf, 1024) == ITS_SUCCESS)
    {
        char *tmp = buf, *ptr = buf;
        int i;

        /* Initialize the numTimeslots with ZERO */
        handle->numTimeslots = 0;

        for (i = 0; (tmp = strstr(tmp, ",")) != NULL && i < MAX_DATA_LINKS; i++)
        {
            *tmp = 0;
            handle->dataLink[i].timeslot = (ITS_OCTET)RESFILE_ParseNum(ptr);
            handle->numTimeslots++;
            tmp++;
            ptr = tmp;
        }
        if (i < MAX_DATA_LINKS)
        {
            handle->dataLink[i].timeslot = (ITS_OCTET)RESFILE_ParseNum(ptr);
            handle->numTimeslots++;
        }
    }


    idx = 0;

    RESFILE_Lock(tr->transport.res);
    RESFILE_Rewind(tr->transport.res, tr->transport.name);

    while (RESFILE_GetKeyName(tr->transport.res, tr->transport.name,
                              key, sizeof(key)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(tr->transport.res, tr->transport.name,
                               value, sizeof(value)) == ITS_SUCCESS)

   { 
       if (strcmp(value, "begin") == 0)
       {
           continue;
       }
       else if (strcmp(value, "end") == 0)
       {
           idx++;
           continue;
       }
       else if (strcmp(key, "vcId") == 0)
       {
           vcid[idx] = RESFILE_ParseNum(value);
           /* handle->dataLink[idx].atmInfo.vcId = RESFILE_ParseNum(value); */
       }
       else if (strcmp(key, "vpi") == 0)
       {
           vpi[idx] = RESFILE_ParseNum(value);
           /* handle->dataLink[idx].atmInfo.vpi = RESFILE_ParseNum(value); */
       }
       else if (strcmp(key, "vci") == 0)
       {
           vci[idx] = RESFILE_ParseNum(value);
           /* handle->dataLink[idx].atmInfo.vci = RESFILE_ParseNum(value); */
       }

    }

    RESFILE_Unlock(tr->transport.res);

    /* Fill the vcid, vpi and vci information properly in the handle 
       structure, this fix will maintain the consistency between timeslot, vcid, vpi
       and vci while filling the handle data structure */

    for(i = 0; i < MAX_DATA_LINKS; i++)
    {
      for(j = 0; j < MAX_DATA_LINKS; j++)
      {
        if(vcid[i] == handle->dataLink[j].timeslot)
        {
          handle->dataLink[j].atmInfo.vcId = vcid[i];
          handle->dataLink[j].atmInfo.vpi = vpi[i];
          handle->dataLink[j].atmInfo.vci = vci[i];
          break;  /* come out from the inner for loop */
        }
      }
    }

    /*
       significance of trace_construct_flag is to avoid the creation
       of MTP2 Trace everytime whenever first link in a linkset is created
       dynamically
    */
    if(trace_construct_flag == ITS_FALSE)
    {
        printf("\nMTP2:Inside TRACE_Construct...\n");
        if ((MTP2_ADAX_TraceData = TRACE_Constructor("ADAX-MTP2",
                                                     MTP2_TraceMap, 4)) == NULL)
        {
            return (ITS_ENOMEM);
        }
        trace_construct_flag = ITS_TRUE;

    /* Critical Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, ADAX_INI_SECTION_NAME,
                              MTP2_TRACE_CRITICAL_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_FALSE);
        }
    }

    /* Error Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, ADAX_INI_SECTION_NAME,
                              MTP2_TRACE_ERROR_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_ERROR_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_ERROR_STRING, ITS_FALSE);
        }
    }

    /* Warning Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, ADAX_INI_SECTION_NAME,
                              MTP2_TRACE_WARNING_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_WARNING_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_WARNING_STRING, ITS_FALSE);
        }
    }

    /* Debug Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, ADAX_INI_SECTION_NAME,
                              MTP2_TRACE_DEBUG_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        } 

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_DEBUG_STRING, ITS_FALSE);
        }
    }
    }

    RESFILE_Lock(tr->transport.res);
    RESFILE_Rewind(tr->transport.res, tr->transport.name);
    while (RESFILE_GetKeyName(tr->transport.res, tr->transport.name,
                              key,  1024) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(tr->transport.res, tr->transport.name,
                               value, 1024) == ITS_SUCCESS)
    {
        if (strcmp(key, LINK_CODE_STRING) == 0 )
        {
            currentLinkCode =  atoi(value);
            /*printf("$$$$ keyName = %s  value = %s $$$$\n", key, value);*/
        }
        if (strcmp(key, LINK_DATA_LINK_STRING) == 0)
        {
            currentCircuit = atoi(value);
            /*printf("$$$$ keyName = %s  value = %s timeslot = %d $$$$\n",
                    key, value, currentCircuit);*/
            for (j = 0; j < MAX_DATA_LINKS; j++)
            {
                if (handle->dataLink[j].timeslot == currentCircuit)
                {
                    handle->dataLink[j].linkCode = currentLinkCode;

                    /*printf("$$$$ i = %d , timeslot = %d , linkCode = %d $$$$\n ",
                            j, handle->dataLink[j].timeslot,
                            handle->dataLink[j].linkCode );*/

                    break;
                }
            }
            if (j == MAX_DATA_LINKS)
            {
                /*printf("$$$ ERROR: NO LinkCode - Circuit Matching $$$\n");*/
            }
        }


    }
    RESFILE_Unlock(tr->transport.res);


    /*if (adax_debug)*/
    {
        printf("ITS read the following:\n");
        printf("hardware: %d\n", handle->hardware);
        printf("trunk: %d\n", handle->trunk);
        printf("trunkType: %d\n", handle->trunkType);
        printf("connectType: %d\n", handle->connectionType);
        printf("baudRate: %d\n", handle->baudRate);
        printf("globalServiceOptonsPresent: %d\n", handle->globalServiceOptonsPresent);
        printf("trafficClass: %d\n", handle->globalServiceOptions.trafficClass);
        printf("peekCellRate: %d\n", handle->globalServiceOptions.peekCellRate);
        printf("minimumSustainableCellRate: %d\n", 
                  handle->globalServiceOptions.minimumSustainableCellRate);
        printf("maxBurstSize: %d\n", handle->globalServiceOptions.maxBurstSize);
        printf("initialCellRate: %d\n", handle->globalServiceOptions.initialCellRate);
        printf("priority: %d\n", handle->globalServiceOptions.priority);
        printf("linkSet: %d\n", handle->linkSet);
        printf("numTimeslots: %d\n", handle->numTimeslots);
        printf("LINK INFO:\n");
        for (i=0; i < handle->numTimeslots; i++)
        {
            printf(" Timeslot: %d \n", handle->dataLink[i].timeslot);
            printf(" vcId    : %d \n", handle->dataLink[i].atmInfo.vcId);
            printf(" vpi    : %d \n", handle->dataLink[i].atmInfo.vpi);
            printf(" vci    : %d \n", handle->dataLink[i].atmInfo.vci);
        }
        printf("\n");
    }

    TRANSPORT_UnfindTransport(tr);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the ADAX board.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - the context.
 *      ITS_EVENT - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
WaitForIndication(ITS_SS7_HANDLE handle,
                  int *indic_flag, int millisecs)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    struct pollfd pfd[MAX_DATA_LINKS + 1];
    int nfd, ret;
    char rbuf[2];
    ITS_UINT i;
 
    *indic_flag = 0;
    ret = ITS_ENOMSG;
    context->which = 0;
    memset(pfd, 0, MAX_DATA_LINKS + 1);

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP2) ==
        ITS_MTP2)
    {
        for (i = 0; i < context->numTimeslots; i++)
        {
            pfd[i].fd = context->fd[i];
            pfd[i].events = POLLIN;
            pfd[i].revents = 0;
        }

        if (context->hardware == ADAX_ATMII)
        {
           if (millisecs == ITS_INFINITE)
           {
               nfd = poll(pfd, context->numTimeslots, -1);
           }
           else
           {
               nfd = poll(pfd, context->numTimeslots, millisecs);
           }

           if (nfd <= 0)
           {
               return ITS_ENOMSG;
           }
        }
        else
        {
            pfd[context->numTimeslots].fd = context->pipefd[0];
            pfd[context->numTimeslots].events = POLLIN;
            pfd[context->numTimeslots].revents = 0;

            if (millisecs == ITS_INFINITE)
            {
                nfd = poll(pfd, context->numTimeslots + 1, -1);
            }
            else
            {
                nfd = poll(pfd, context->numTimeslots + 1, millisecs);
            }
    
            if (nfd <= 0)
            {
                return ITS_ENOMSG;
            }

            if (pfd[context->numTimeslots].revents != 0)
            {
                read(pfd[context->numTimeslots].fd, rbuf, 1);
    
                if (!MQUEUE_EmptyP(VENDOR_RCV_Q(context)))
                {
                    *indic_flag |= EVENT_FROM_MTP2;

                    ret = ITS_SUCCESS;
                }
            }
        }

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (pfd[i].revents == 0)
            {
                continue;
            }

            context->which |= 1 << i;

            *indic_flag |= EVENT_FROM_MTP2;

            ret = ITS_SUCCESS;
        }
    }

    return ret;
}

/*
 * a helper for the parser extension
 */
typedef struct _XMLData
{
    struct _XMLData *next;
    ITS_SS7_CONTEXT ctxt;
    char            *sectionName;
}
XML_ParseData;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Start parsing ADAX information in XML files.
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
 *  Revision History:
 *  -----------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 *
 *  ------------------------------------------------------------------------
 *  Magesh S 29/11/2006   Bug ID: 4978    Fix for ATM Service Option XML 
 *                                        Parsing
 ****************************************************************************/
VSS7DLLAPI void
ADAX_ParseStart(ENGINE_ParserExtension ext,
               const char *el, const char **attr)
{
    XML_ParseData *pd;

    /* NOTE: this can't handle nested XML */
    ITS_SS7_CONTEXT *ctxt;

    /* NOTE: this can't handle nested XML */
    /* NOTE: But it needs to handle multiple instances */

    if (strcmp(el, ENGINE_PE_ELEMENT_NAME(ext)) == 0)
    {
        pd = calloc(1, sizeof(XML_ParseData));
        ITS_C_ASSERT(pd != NULL);

        pd->next = ENGINE_PE_USER_DATA(ext);
        ENGINE_PE_USER_DATA(ext) = pd;

        ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

        ctxt->globalServiceOptonsPresent = 0;
        
        while (*attr)
        {
            if (strcmp(*attr, "sectionName") == 0)
            {
                attr++;

                pd->sectionName = strdup(*attr);
                ITS_C_ASSERT(pd->sectionName != NULL);

                attr++;
            }



            if (strcmp(*attr, "trunk") == 0)
            {
                attr++;

                ctxt->trunk = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if (strcmp(*attr, "hardware") == 0)
            {
                attr++;

                if (strcmp(*attr, "HDCII") == 0)
                {
                    ctxt->hardware = ADAX_HDCII;
                }
                else if (strcmp(*attr, "ATMII") == 0)
                {
                    ctxt->hardware = ADAX_ATMII;
                }
                else
                {
                    if (adax_debug)
                    {
                        printf("======>>>>> ADAX ERROR: hardware  must be "  
                        " HDCII or ATMII... setting ADAX_HDCII as default \n");
                    }
                    ctxt->hardware = ADAX_HDCII;
                }

                attr++;
            }
            else if (strcmp(*attr, "TR_TYPE") == 0)
            {
                attr++;
                if (strcmp(*attr, "T1") == 0)
                {
                    ctxt->trunkType = ADAX_T1;
                }
                else if (strcmp(*attr, "E1") == 0)
                {
                    ctxt->trunkType = ADAX_E1;
                }
                else if (strcmp(*attr, "J1") == 0)
                {
                    ctxt->trunkType = ADAX_J1;
                }
                else if (strcmp(*attr, "OC3") == 0)
                {
                    ctxt->trunkType = ADAX_OC3;
                }
                else
                {
                    if (adax_debug)
                    {
                        printf("======>>>>> ADAX ERROR: TR_TYPE must be "
                               "E1 or T1 or OC3... setting E1 as Default\n");
                    }
                    ctxt->trunkType = ADAX_E1;
                }


                /*ctxt->trunkType = RESFILE_ParseNum(*attr);*/

                attr++;
            }
            else if (strcmp(*attr, "connectType") == 0)
            {
                attr++;

                if (strcmp(*attr, "AAL5") == 0)
                {
                    ctxt->connectionType = ATMII_AAL5;
                }
                else if (strcmp(*attr, "HDLC") == 0)
                {
                    ctxt->connectionType = ATMII_HDLC;
                }
                else if (strcmp(*attr, "AAL2") == 0)
                {
                    ctxt->connectionType = ATMII_AAL2;
                }
                else if (strcmp(*attr, "AAL0") == 0)
                {
                    ctxt->connectionType = ATMII_AAL0;
                }
                else
                {
                    if (adax_debug)
                    {
                        printf("======>>>>> ADAX ERROR: connectType  must be "  
                        "AAL5, HDLC, AAL2 or AAL0... setting AAL5 as default \n");
                    }
                    ctxt->connectionType = ATMII_AAL5;
                }

                attr++;
            }
            else if (strcmp(*attr, "baudRate") == 0)
            {
                attr++;

                ctxt->baudRate = RESFILE_ParseNum(*attr);

                if ( (ctxt->baudRate != BAUD_RATE_64) &&
                     (ctxt->baudRate != BAUD_RATE_56) && 
                     (ctxt->baudRate != BAUD_RATE_48) )
                {
                   
                   if (adax_debug) 
                   {
                        printf("===>> ADAX ERROR: Invalid Baud Rate... " 
                               "using 64kbps\n");
                   }
                    /* used default baud rate */
                    ctxt->baudRate = BAUD_RATE_64;
                }
                attr++;
            }
            else if (strcmp(*attr, "linkSet") == 0)
            {
                attr++;

                ctxt->linkSet = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if (strcmp(*attr, "timeSlots") == 0)
            {
                char buf[ITS_PATH_MAX];
                char *tmp = buf, *ptr = buf;
                int i;

                attr++;

                strncpy(buf, *attr, ITS_PATH_MAX);

                for (i = 0; (tmp = strstr(tmp, ",")) != NULL && i < MAX_DATA_LINKS; i++)
                {
                    *tmp = 0;
                    ctxt->dataLink[i].timeslot = (ITS_OCTET)RESFILE_ParseNum(ptr);
                    ctxt->numTimeslots++;
                    tmp++;
                    ptr = tmp;
                }
                if (i < MAX_DATA_LINKS)
                {
                    ctxt->dataLink[i].timeslot = (ITS_OCTET)RESFILE_ParseNum(ptr);
                    ctxt->numTimeslots++;
                }

                attr++;
            }
            else if (strcmp(*attr, ATM_SCRAMB_CELL_PAYLOAD_STR) == 0)
            {
                attr++;
                if (strcmp(*attr, ATM_SCRAMBLE_ENABLE_STR) == 0)
                {
                    ctxt->scrambType = ATM_CELL_PAYLOAD;
                }
                attr++;
            }
            else if ((strcmp(*attr, ATM_SCRAMB_DS3_STR) == 0) ||
                     (strcmp(*attr, ATM_SCRAM_E3_STR) == 0))
            {
                printf("Unsupported ScrambleType.\n");
                attr += 2;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, "Service_Options") == 0)
    {
       
        ITS_C_ASSERT(ENGINE_PE_USER_DATA(ext) != NULL);

        pd = ENGINE_PE_USER_DATA(ext);
        ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

        ctxt->globalServiceOptonsPresent = 1;

        while (*attr)
        {
            if (strcmp(*attr, "trafficClass") == 0)
            {
                attr++;

                if (strcmp(*attr, "CBR") == 0)
                {
                    ctxt->globalServiceOptions.trafficClass = ATMII_CBR;
                }
                else if (strcmp(*attr, "VBR") == 0)
                {
                    ctxt->globalServiceOptions.trafficClass = ATMII_VBR;
                }
                else if (strcmp(*attr, "ABR") == 0)
                {
                    ctxt->globalServiceOptions.trafficClass = ATMII_ABR;
                }
                else
                {

                    ctxt->globalServiceOptions.trafficClass = ATMII_INVALID;
                    printf("Invalid Traffic Class... "
                           "CBR, VBR, ABR are the valid one \n");
                }

               printf("serviceOption.trafficClass: %d\n", ctxt->globalServiceOptions.trafficClass);

                attr++;
            }
            if (strcmp(*attr, "peekCellRate") == 0)
            {
                attr++;

               ctxt->globalServiceOptions.peekCellRate = RESFILE_ParseNum(*attr);

               printf("serviceOption.peekCellRate: %d\n", ctxt->globalServiceOptions.peekCellRate);
                attr++;
            }
            if (strcmp(*attr, "minimumSustainableCellRate") == 0)
            {
                attr++;

                ctxt->globalServiceOptions.minimumSustainableCellRate = RESFILE_ParseNum(*attr);
               printf("serviceOption.minimumSustainableCellRate: %d\n", ctxt->globalServiceOptions.minimumSustainableCellRate);

                attr++;
            }
            if (strcmp(*attr, "maxBurstSize") == 0)
            {
                attr++;

                ctxt->globalServiceOptions.maxBurstSize = RESFILE_ParseNum(*attr);
               printf("serviceOption.maxBurstSize: %d\n", ctxt->globalServiceOptions.maxBurstSize);

                attr++;
            }
            if (strcmp(*attr, "initialCellRate") == 0)
            {
                attr++;

               ctxt->globalServiceOptions.initialCellRate = RESFILE_ParseNum(*attr);

               printf("serviceOption.initialCellRate: %d\n", ctxt->globalServiceOptions.initialCellRate);
                attr++;
            }
            if (strcmp(*attr, "priority") == 0)
            {
                attr++;

                ctxt->globalServiceOptions.priority = RESFILE_ParseNum(*attr);
                printf("serviceOption.priority: %d\n", ctxt->globalServiceOptions.priority);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }


    }
    else if (strcmp(el, "VC_Info") == 0)
    {
        int i, idx, vcId;

        ITS_C_ASSERT(ENGINE_PE_USER_DATA(ext) != NULL);

        pd = ENGINE_PE_USER_DATA(ext);
        ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

        while(*attr)
        {
            if(strcmp(*attr, "vcId") == 0)
            {
                attr++;

                vcId = RESFILE_ParseNum(*attr);

                for (i = 0; i < ctxt->numTimeslots; i++)
                {
                    if (ctxt->dataLink[i].timeslot == vcId)
                    {
                        idx = i;
                        break;
                    }
                }
 
                ctxt->dataLink[idx].atmInfo.vcId = vcId;

                attr++;
            }

            if(strcmp(*attr, "vpi") == 0)
            {
                attr++;

                ctxt->dataLink[idx].atmInfo.vpi = RESFILE_ParseNum(*attr);

                attr++;
            }
            if(strcmp(*attr, "vci") == 0)
            {
                attr++;

                ctxt->dataLink[idx].atmInfo.vci = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }

        }


    }

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Term parsing ADAX information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
ADAX_ParseEnd(ENGINE_ParserExtension ext, const char *el)
{
    /* don't care */
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert ADAX information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
ADAX_ConvertParserData(RESFILE_Manager *appRes,
                      ENGINE_ParserExtension ext)
{
    int ret, i;
    char tmp[ITS_PATH_MAX];
    XML_ParseData *pd = (XML_ParseData *)ENGINE_PE_USER_DATA(ext);

    ITS_SS7_CONTEXT *ctxt;

    while (pd != NULL)
    {
        ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

        /* convert the extension data to resources */

        sprintf(tmp, "%d", ctxt->hardware);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "hardware", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);


        sprintf(tmp, "%d", ctxt->trunk);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "trunk", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->trunkType);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "TR_TYPE", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->connectionType);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "connectType", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
         
        sprintf(tmp, "%d", ctxt->baudRate );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "baudRate", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptonsPresent);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "globalServiceOptonsPresent", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.trafficClass );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "trafficClass", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.peekCellRate );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "peekCellRate", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.minimumSustainableCellRate );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "minimumSustainableCellRate", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.maxBurstSize );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "maxBurstSize", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.initialCellRate );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "initialCellRate", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->globalServiceOptions.priority );
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "priority", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->linkSet);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "linkSet", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->scrambType);

        if (ctxt->scrambType == ATM_CELL_PAYLOAD)
        {
            ret = RESFILE_AddKeyValue(appRes, pd->sectionName, 
                                      ATM_SCRAMB_CELL_PAYLOAD_STR, tmp);
        }
        else if (ctxt->scrambType != ATM_SCRAMB_NONE)
        {
            printf("Unsupported Scrambling type\n");
        } 

        tmp[0] = 0;
        for (i = 0; i < ctxt->numTimeslots; i++)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%d,", ctxt->dataLink[i].timeslot);
            strcat(tmp, buf);
        }
        if (ctxt->numTimeslots)
        {
            tmp[strlen(tmp)-1] = 0;
        }
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "timeSlots", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        for(i = 0; i < ctxt->numTimeslots; i++ )
        {
            char buf[ITS_PATH_MAX];

            ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                      "VC_Info", "begin");

            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /*vcId*/
            sprintf(buf, "%d", ctxt->dataLink[i].atmInfo.vcId);
            ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                      "vcId", buf);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /*vpi*/
            sprintf(buf, "%d", ctxt->dataLink[i].atmInfo.vpi);
            ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                      "vpi", buf);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
             
            /*vci*/
            sprintf(buf, "%d", ctxt->dataLink[i].atmInfo.vci);
            ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                      "vci", buf);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                      "VC_Info", "end");


        } 

        pd = pd->next;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Diff ADAX information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
ADAX_Diff(RESFILE_Manager *appRes,
         ENGINE_ParserExtension ext1,
         ENGINE_ParserExtension ext2)
{
    /* don't care */
}

#if defined(ANSI)

static int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsADAX_ClassANSI) = itsSS7STACK_ClassANSI;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsADAX_ClassRecANSI =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        ADAX_CLASS_NAME_ANSI,       /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
            ADAXInitializeMTP2,
            ADAXTermMTP2,
            ADAXRetrieveMTP2Message,
            ADAXSendMTP2Event,
            ADAXCommit
        },
        /* MTP3 */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* ISUP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* SCCP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* TCAP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        }
    }
};

VSS7DLLAPI ITS_Class itsADAX_ClassANSI = (ITS_Class)&itsADAX_ClassRecANSI;

#elif defined(CCITT)

static int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsADAX_ClassCCITT) = itsSS7STACK_ClassCCITT;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsADAX_ClassRecCCITT =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        ADAX_CLASS_NAME_CCITT,      /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
            ADAXInitializeMTP2,
            ADAXTermMTP2,
            ADAXRetrieveMTP2Message,
            ADAXSendMTP2Event,
            ADAXCommit
        },
        /* MTP3 */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* ISUP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* SCCP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* TCAP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        }
    }
};

VSS7DLLAPI ITS_Class itsADAX_ClassCCITT = (ITS_Class)&itsADAX_ClassRecCCITT;

#elif defined(PRC)

static int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsADAX_ClassPRC) = itsSS7STACK_ClassPRC;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsADAX_ClassRecPRC =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        ADAX_CLASS_NAME_PRC,        /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
            ADAXInitializeMTP2,
            ADAXTermMTP2,
            ADAXRetrieveMTP2Message,
            ADAXSendMTP2Event,
            ADAXCommit
        },
        /* MTP3 */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* ISUP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* SCCP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* TCAP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        }
    }
};

VSS7DLLAPI ITS_Class itsADAX_ClassPRC = (ITS_Class)&itsADAX_ClassRecPRC;

#elif defined(TTC)

static int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsADAX_ClassTTC) = itsSS7STACK_ClassTTC;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsADAX_ClassRecTTC =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        ADAX_CLASS_NAME_TTC,        /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
            ADAXInitializeMTP2,
            ADAXTermMTP2,
            ADAXRetrieveMTP2Message,
            ADAXSendMTP2Event,
            ADAXCommit
        },
        /* MTP3 */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* ISUP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* SCCP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        },
        /* TCAP */
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        }
    }
};

VSS7DLLAPI ITS_Class itsADAX_ClassTTC = (ITS_Class)&itsADAX_ClassRecTTC;

#endif

#if defined(STANDALONE)
#if defined(ANSI)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsADAX_ClassRecANSI;
#elif defined(CCITT)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsADAX_ClassRecCCITT;
#elif defined(PRC)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsADAX_ClassRecPRC;
#elif defined(TTC)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsADAX_ClassRecTTC;
#endif
#endif
