/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: mtp2.c,v 9.6 2008/07/18 05:55:13 ssingh Exp $
 *
 * LOG: $Log: mtp2.c,v $
 * LOG: Revision 9.6  2008/07/18 05:55:13  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.5  2008/06/04 10:17:15  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.3.6.33  2008/04/10 12:21:22  ssodhi
 * LOG: Improved Traces
 * LOG:
 * LOG: Revision 9.3.6.32  2008/03/28 15:56:23  skatta
 * LOG: fix for issue MTP2 traces are not disabled through OAM
 * LOG:
 * LOG: Revision 9.3.6.31  2008/03/19 12:22:52  ssodhi
 * LOG: Fix for issue 357 and added/improved MTP3 traces
 * LOG:
 * LOG: Revision 9.3.6.30  2008/02/27 15:35:12  nvijikumar
 * LOG: Fix for PBN Id: 540 Overload Control
 * LOG:
 * LOG: Revision 9.3.6.29  2008/01/30 15:30:57  ssodhi
 * LOG: Fix for issue #522
 * LOG:
 * LOG: Revision 9.3.6.28  2008/01/21 08:18:20  ssodhi
 * LOG: Fix to resolve hang issue
 * LOG:
 * LOG: Revision 9.3.6.27  2007/11/22 13:17:06  mshanmugam
 * LOG: Fix for issue id #220
 * LOG:
 * LOG: Revision 9.3.6.26  2007/11/16 11:42:47  mshanmugam
 * LOG: to avoid printf buffers building for every mesaging when DEBUG is OFF
 * LOG:
 * LOG: Revision 9.3.6.25  2007/07/20 12:59:53  raghavendrabk
 * LOG: Fix for 6111
 * LOG:
 * LOG: Revision 9.3.6.24  2007/05/11 10:03:34  raghavendrabk
 * LOG: MTP2_GetOm and MTP2_ResetOm APIs added for all the families
 * LOG:
 * LOG: Revision 9.3.6.23  2007/04/27 16:33:57  sbhaskaran
 * LOG: Handling of Internode links for all protocols
 * LOG:
 * LOG: Revision 9.3.6.22  2007/04/26 09:18:20  raghavendrabk
 * LOG: Resolved MML hanging issue with GetOm API
 * LOG:
 * LOG: Revision 9.3.6.21  2007/04/10 15:16:25  raghavendrabk
 * LOG: Check validation for MTP2_ADAX_TraceData
 * LOG:
 * LOG: Revision 9.3.6.20  2007/02/06 04:22:21  sbhaskaran
 * LOG: Merged the bug fix - NULL pointer check addition code - from the maintainance branch
 * LOG:
 * LOG: Revision 9.3.6.19  2007/01/22 15:10:41  gharipriya
 * LOG: Merged TTC Fixes from maintenance branch
 * LOG:
 * LOG: Revision 9.4  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.3.6.18  2006/12/23 10:07:00  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.3.6.17.4.3  2007/01/29 12:27:55  rdangi
 * LOG: Added check for NULL pointer to tc and context in performance data collection functions
 * LOG:
 * LOG: Revision 9.3.6.17.4.2  2007/01/06 14:26:17  gdalawai
 * LOG: Adjusted the length field while sending messages for TTC
 * LOG:
 * LOG: Revision 9.3.6.17.4.1  2007/01/01 06:36:01  ssingh
 * LOG: in support with J1 and 48/56kbps;TTC stack
 * LOG:
 * LOG: Revision 9.3.6.17  2006/11/30 07:29:08  rdangi
 * LOG: Stop MTP2 PM Data Collection for InterNode Links
 * LOG:
 * LOG: Revision 9.3.6.16  2006/11/28 14:55:10  rdangi
 * LOG: Modified the Prototype for MTP2_SetGeneralCfg
 * LOG:
 * LOG: Revision 9.3.6.15  2006/11/17 08:50:27  rdangi
 * LOG: Modified code to fix core dump
 * LOG:
 * LOG: Revision 9.3.6.14  2006/11/08 11:16:39  gharipriya
 * LOG: Fix for the Bug Id 4728. A buffer used in the RetrieveOne_HDCII function was
 * LOG: overflowing and it has been removed as a part of Bug fix.
 * LOG:
 * LOG: Revision 9.3.6.13  2006/11/07 13:25:15  gharipriya
 * LOG: Fix for the Bug ID 4373. The priority bit has to be discared when a message
 * LOG: is received and added when msg has to be sent for Broadband link alignment.
 * LOG:
 * LOG: Revision 9.3.6.12  2006/11/06 13:36:31  rdangi
 * LOG: Resolved Multiple opening of Ports
 * LOG:
 * LOG: Revision 9.3.6.11  2006/09/26 07:13:57  mshanmugam
 * LOG: Removed the Q752 Compilation flag
 * LOG:
 * LOG: Revision 9.3.6.10  2006/09/13 15:21:08  mshanmugam
 * LOG: extern c with cpp defined added
 * LOG:
 * LOG: Revision 9.3.6.9  2006/09/13 10:32:07  mshanmugam
 * LOG: The Get and Reset Om Functions made as extern C for Q752.
 * LOG:
 * LOG: Revision 9.3.6.8  2006/08/18 12:19:19  mshanmugam
 * LOG: Added new APIs for Q.752 Implementation.
 * LOG:
 * LOG: Revision 9.3.6.7  2006/05/17 14:55:43  lbana
 * LOG: Scrambling bit PBN Issue ID 3288
 * LOG:
 * LOG: Revision 9.3.6.6  2006/05/17 14:49:43  lbana
 * LOG: PBN Issue ID 3288:Made scrambling bit configurable
 * LOG:
 * LOG: Revision 9.3.6.5  2005/11/11 22:43:00  randresol
 * LOG: Add Sercice Option parameters for ATM
 * LOG:
 * LOG: Revision 9.3.6.4  2005/10/13 07:25:18  randresol
 * LOG: Add Debug Trace for Incoming and Outgoing data
 * LOG:
 * LOG: Revision 9.3.6.3  2005/09/28 23:36:03  randresol
 * LOG: Add SAAL pegs
 * LOG:
 * LOG: Revision 9.3.6.2  2005/09/16 02:43:51  randresol
 * LOG: Fix Problem with transmition of messages that are more then 64 bytes
 * LOG:
 * LOG: Revision 9.3.6.1  2005/09/12 04:36:42  randresol
 * LOG: Add implementation for ADAX ATMII Platform
 * LOG:
 * LOG: Revision 9.3  2005/05/06 10:06:23  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/07 07:27:30  snagesh
 * LOG: Modification for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:54:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.7  2005/02/07 05:09:18  snagesh
 * LOG: Fix for bug 1499
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.6  2005/02/03 08:51:44  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.5  2005/01/31 11:20:18  snagesh
 * LOG: MTP2 OSS APIs added
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.4  2005/01/05 12:29:19  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.3  2005/01/05 10:29:10  snagesh
 * LOG: removed tabs
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.2  2005/01/04 16:07:26  snagesh
 * LOG: commented get_gen_pegids MML
 * LOG:
 * LOG: Revision 7.2.2.2.8.3.14.1  2005/01/03 15:37:38  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.2.2.2.8.3  2004/07/09 07:04:02  dsatish
 * LOG: Merging activity of timeslot and 56kbps changes
 * LOG:
 * LOG: Revision 7.2.2.2.8.2  2004/03/18 13:30:35  kannanp
 * LOG: Review comments added.
 * LOG:
 * LOG: Revision 7.2.2.2.8.1  2004/03/17 12:52:46  kannanp
 * LOG: Added MTP2 Alarms.
 * LOG:
 * LOG: Revision 7.2.2.2  2003/03/28 17:17:12  randresol
 * LOG: Add linux HDCX support
 * LOG:
 * LOG: Revision 7.2.2.1  2003/02/18 02:30:40  randresol
 * LOG: Fix invalid messages
 * LOG:
 * LOG: Revision 7.2  2002/12/20 21:31:27  randresol
 * LOG: Fix bugs in BSNT and L3_L2_RETRIEVE_MSGS cases
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.21.2.2  2002/05/09 15:56:59  labuser
 * LOG: Remove conflict after merge.
 * LOG:
 * LOG: Revision 1.21.2.1  2002/05/01 13:25:56  ngoel
 * LOG: fix one extra byte while sending data
 * LOG:
 * LOG: Revision 1.21.4.1  2002/05/01 00:43:41  labuser
 * LOG: fixed the extra octed in send mtp2 data
 * LOG:
 * LOG: Revision 1.21  2002/02/26 21:17:35  mmiers
 * LOG: Debugging, cleanup.
 * LOG:
 * LOG: Revision 1.20  2002/01/29 20:12:21  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.19  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 1.18  2001/12/28 18:43:40  mmiers
 * LOG: A few mistakes to fix.
 * LOG:
 * LOG: Revision 1.17  2001/12/19 23:54:02  mmiers
 * LOG: Get ADAX vendor lib working.
 * LOG:
 * LOG: Revision 1.16  2001/12/19 21:01:14  mmiers
 * LOG: Don't pollute the namespace.
 * LOG:
 * LOG: Revision 1.15  2001/12/19 16:31:51  mmiers
 * LOG: Bug fixes, add archives
 * LOG:
 * LOG: Revision 1.14  2001/12/18 22:12:07  mmiers
 * LOG: Fix up to match vframe
 * LOG:
 * LOG: Revision 1.13  2001/12/18 21:59:19  mmiers
 * LOG: Standardize on exports for vendors
 * LOG:
 * LOG: Revision 1.12  2001/12/18 21:34:51  mmiers
 * LOG: Interim version
 * LOG:
 * LOG: Revision 1.11  2001/12/18 21:23:37  mmiers
 * LOG: New format vendor
 * LOG:
 * LOG: Revision 1.10  2001/10/29 19:52:38  ngoel
 * LOG: add out of service for SIOS event
 * LOG:
 * LOG: Revision 1.9  2001/10/29 17:41:25  ngoel
 * LOG: bug fix
 * LOG:
 * LOG: Revision 1.8  2001/10/29 15:59:03  ngoel
 * LOG: add messages for remote processor outage
 * LOG:
 * LOG: Revision 1.7  2001/10/26 19:15:56  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.6  2001/10/25 21:42:53  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.5  2001/10/24 21:32:11  ngoel
 * LOG: bug fix
 * LOG:
 * LOG: Revision 1.4  2001/10/24 15:29:29  ngoel
 * LOG: add error codes
 * LOG:
 * LOG: Revision 1.3  2001/10/23 18:31:51  ngoel
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.2  2001/10/22 21:09:56  ngoel
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.1  2001/10/22 18:33:51  ngoel
 * LOG: First commit
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_mlist.h>
#include <its_ss7_trans.h>
#include <its_intern.h>
#include <mtp2_cmn.h>
/* name collision */
#undef LINK_FAILED

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/poll.h>


#include <fcntl.h>
#include <stropts.h>
#include <hdc_user.h>
#include <atmii_user.h>
#include <qsaal.h>
#include <mtp2_user.h>
#include <mtp2_alarm.h>
#include <mtp2_pegs.h>

#if defined(linux)
#define HDC_FILE_NAME "/dev/hdcx"
#else
#define HDC_FILE_NAME "/dev/hdc"
#endif

#define ATMII_FILE_NAME  "/dev/atmii"

#define LSWAP(n) (((((ITS_UINT) (n) & 0xFF000000) >> 24) | \
                  (((ITS_UINT) (n) & 0x00FF0000) >> 8 ) | \
                  (((ITS_UINT) (n) & 0x0000FF00) << 8 ) | \
                  (((ITS_UINT) (n) & 0x000000FF) << 24) ))


static ITS_UINT pegs[PEG_ADAX_MTP2_NUM_GLOBAL_PEGS];
static PEGS_DECL_SUBSYS(ADAX_MTP2, pegs);
PEG_Manager *ADAX_MTP2_Pegs = &ADAX_MTP2_PEGS;

ITS_CHAR *mtp2GPegStr[] =
{
     "PEG_MTP2_GET_DATA_FAILED",
     "PEG_MTP2_SEND_DATA_FAILED",
     "PEG_MTP2_LOCAL_PROC_DOWN",
     "PEG_MTP2_LOCAL_PROC_UP",
     "PEG_MTP2_REMOTE_PROC_DOWN",
     "PEG_MTP2_REMOTE_PROC_UP",
     "PEG_MTP2_STAT_IND",
     "PEG_MTP2_SUERM_EXPIRY",
     "PEG_MTP2_INCORRECT_FIB_BSN",
     "PEG_MTP2_CONG_DETECTED",
     "PEG_MTP2_CONG_RECOVERED",
     "PEG_MTP2_MSU_TX",
     "PEG_MTP2_MSU_RX",
     "PEG_MTP2_T2_EXPIRED",
     "PEG_MTP2_T6_EXPIRED",
     "PEG_MTP2_T7_EXPIRED"
};

static TRACE_OutputInitializer fileCritTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    MTP2_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    MTP2_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

TRACE_LevelInitializer MTP2_TraceMap[] =
{
    {MTP2_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {MTP2_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {MTP2_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {MTP2_DEBUG_STRING,    ITS_TRUE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* MTP2_ADAX_TraceData = NULL;

mtp2OmBuffer omBuf;

/* Function Prototype */
#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */
void MTP2_ResetOm_CCITT();
void MTP2_GetOm_CCITT(mtp2Om *);
int MTP2_SetGeneralCfg(MTP2GeneralCfg* cfg);
void MTP2_ResetOm_TTC();
void MTP2_GetOm_TTC(mtp2Om *);
void MTP2_ResetOm_PRC();
void MTP2_GetOm_PRC(mtp2Om *);
void MTP2_ResetOm_ANSI();
void MTP2_GetOm_ANSI(mtp2Om *);
#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

void MTP2_ResetOm_MML_CCITT();
void MTP2_GetOm_MML_CCITT(DBC_Server *);
void MTP2LinkOmDataInitialize(mtp2_stat_table *);

static MTP2GeneralCfg* MTP2_GetGeneralCfg();
//static int MTP2_SetGeneralCfg(MTP2GeneralCfg* cfg);
static void DumpGeneralPegs(DBC_Server *dbc);
static void DumpGeneralPegIds(DBC_Server *dbc);
static void DumpLinkPegs(DBC_Server *dbc, ITS_OCTET linkSet,
                         ITS_OCTET linkCode, mtp2_stat_param_t *linkPegs);

static int atmii_create_aal5_setvc_opts(atmii_setvc_opts_t *opts,
                                 unsigned int vc,
                                 unsigned int traffic_class,
                                 unsigned int PCR,
                                 unsigned int MCR_SCR,
                                 unsigned int MBS,
                                 unsigned int ICR,
                                 unsigned short RDF,
                                 unsigned short RIF,
                                 unsigned short CDF,
                                 unsigned short priority,
                                 unsigned int maxframe,
                                 unsigned int buff_class);


extern int errno;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the ADAX interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
InitializeMTP2_HDCII(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    struct strioctl strioctl;
    ITS_UINT param[2];
    ITS_UINT module = MODULE_MTP2;
    int ret;
    init_block_t iblock;
    ITS_UINT i = 0;

    errno = 0;

    if(context->pipefd[0] == 0 && context->pipefd[1] == 0)
    {
      ret = pipe(context->pipefd);

      if (ret == ADAX_FAILED)
      {
          MTP2_CRITICAL(("ADAX Initialize failed. Pipe open failed for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[i].linkCode));
          MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);
  
          return ITS_EINVALIDARGS;
      }
    }

    for (i = 0; i < context->numTimeslots; i++)
    {
        if(context->fd[i] > 0)
        {
          continue;
        }

        context->fd[i] = open(HDC_FILE_NAME, O_RDWR | O_NDELAY);

        if (context->fd[i] == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. Device open failed "
                            "for linkSet %d linkCode %d\n",
                            context->linkSet, context->dataLink[i].linkCode));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_ENOTFOUND;
        }
        
        strioctl.ic_cmd = AIOCSETPORT;
        strioctl.ic_dp = (ITS_CHAR *)&(context->trunk);
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. AIOCSETPORT failed "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet, context->dataLink[i].linkCode, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        strioctl.ic_cmd = AIOCSETTTS;
        if(context->trunkType == ADAX_E1)
        {
            param[0] = (1 << ( context->dataLink[i].timeslot));
            strioctl.ic_dp = (ITS_CHAR *)&(param);
            strioctl.ic_len = sizeof(ITS_UINT);
        }
        else if (context->trunkType == ADAX_T1)
        {
            param[0] = (1 << ( context->dataLink[i].timeslot));
            if (context->baudRate == BAUD_RATE_64)
            {
                param[1] = ADAX_64Kbps;
            }
            else if (context->baudRate == BAUD_RATE_56)
            {
                param[1] = ADAX_56Kbps;
            }
            else
            {
                MTP2_CRITICAL(("ADAX Initialize failed. Invalid Baud Rate %d "
                               "for linkSet %d linkCode %d\n",
                               context->baudRate, context->linkSet, context->dataLink[i].linkCode));
                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }


            strioctl.ic_dp = (ITS_CHAR *)&(param);
            strioctl.ic_len = sizeof(param);
        }
        else if (context->trunkType == ADAX_J1)
        {
            param[0] = (1 << ( context->dataLink[i].timeslot));
            if (context->baudRate == BAUD_RATE_64)
            {
                param[1] = ADAX_64Kbps;
            }
            else if (context->baudRate == BAUD_RATE_56)
            {
                param[1] = ADAX_56Kbps;
            }
            else
            {
                MTP2_CRITICAL(("ADAX Initialize failed. Invalid Baud Rate %d "
                               "for linkSet %d linkCode %d\n",
                               context->baudRate, context->linkSet, context->dataLink[i].linkCode));
                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }

            strioctl.ic_dp = (ITS_CHAR *)&(param);
            strioctl.ic_len = sizeof(param);
        }

        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. AIOCSETTTS failed "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet, context->dataLink[i].linkCode, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        strioctl.ic_cmd = SAIOPSHMOD;
        strioctl.ic_dp = (ITS_CHAR *)&(module);
        strioctl.ic_len = sizeof(module);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            if (errno == EEXIST || errno == 0)
            {
                strioctl.ic_cmd = SAIOPOPMOD;
                strioctl.ic_dp = NULL;
                strioctl.ic_len = 0;
                strioctl.ic_timout = -1;

                ret = ioctl(context->fd[i], I_STR, &strioctl);
                if (ret == ADAX_FAILED)
                {
                    MTP2_CRITICAL(("ADAX Initialize failed. Pop Module failed "
                                   "for linkSet %d linkCode %d. error = %d\n",
                                   context->linkSet, context->dataLink[i].linkCode, errno));
                    MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                    return ITS_EINVALIDARGS;
                }

                strioctl.ic_cmd = SAIOPSHMOD;
                strioctl.ic_dp = (ITS_CHAR *)&(module);
                strioctl.ic_len = sizeof(module);
                strioctl.ic_timout = -1;

                ret = ioctl(context->fd[i], I_STR, &strioctl);

                if (ret == ADAX_FAILED)
                {
                    MTP2_CRITICAL(("ADAX Initialize failed. Push Module failed "
                                   "for linkSet %d linkCode %d. error = %d\n",
                                   context->linkSet, context->dataLink[i].linkCode, errno));
                    MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                    return ITS_EINVALIDARGS;
                }
            }
            else
            {
                MTP2_CRITICAL(("ADAX Initialize failed. Push Module failed "
                               "for linkSet %d linkCode %d. error = %d\n",
                               context->linkSet, context->dataLink[i].linkCode, errno));
                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }
        }

        strioctl.ic_cmd = AIOCTRANS;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. AIOTRANS failed "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet, context->dataLink[i].linkCode, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        strioctl.ic_cmd = MTP2GETIB;
        strioctl.ic_dp = (ITS_CHAR *)&(iblock);
        strioctl.ic_len = sizeof(init_block_t);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. MTP2GETIB failed "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet, context->dataLink[i].linkCode, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        iblock.timer_val[IB_TIMER_T4e] = 100;

        strioctl.ic_cmd = MTP2SETIB;
        strioctl.ic_dp = (ITS_CHAR *)&(iblock);
        strioctl.ic_len = sizeof(init_block_t);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. MTP2SETIB failed "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet, context->dataLink[i].linkCode, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }
    }
    
    MTP2_DEBUG(("ADAX Initialized\n"));
    MTP2_Alarm_ADAX(12000, __FILE__, __LINE__,NULL);
    
    DBC_AddDoCommand(ADAX_MTP2_Console);

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the ADAX interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
InitializeMTP2_ATMII(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;  
    struct strioctl strioctl;
    SSCF_PARAM sscf_param;
    ITS_UINT vc, vpi, vci, setport;
    atmii_setvc_opts_t opts;
    int i, ret;

    for (i = 0; i < context->numTimeslots; i++)
    {
        if(context->fd[i] > 0)
        {
          continue;
        }

        context->fd[i] = open(ATMII_FILE_NAME, O_RDWR | O_NDELAY);
        
        if (context->fd[i] < 0)
        {
            MTP2_CRITICAL(("ADAX ATMII Initialize failed. Device open failed "
                            "for linkSet %d linkCode %d\n",
                            context->linkSet, context->dataLink[i].linkCode));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_ENOTFOUND;
        }

        /*********** Setting the trunk port ************/

        if (context->trunkType == ADAX_OC3)
        {
            if (context->trunk < 0 || context->trunk > 1)
            {
                MTP2_CRITICAL(("ERROR: Board Type is ATMII-OC3, " 
                               "Trunk must be 0 or 1"));
                return ITS_EINVALIDARGS;
            }
        }
        else if ( (context->trunkType == ADAX_T1 ) || 
                  (context->trunkType == ADAX_E1 ) ||
                  (context->trunkType == ADAX_J1 ) )
        {
            if (context->trunk < 0 || context->trunk > 3)
            {
                MTP2_CRITICAL(("ERROR: Board Type is ATMII-ET1, " 
                               "Trunk must be 0 or 3"));
                return ITS_EINVALIDARGS;
            }
 
        }
      
        if (context->connectionType == ATMII_AAL5)
        { 
            setport = context->trunk | AAL5_PORT_REQ;
        }
        else if (context->connectionType == ATMII_HDLC)
        {
            setport = context->trunk | HDLC_PORT_REQ;
        }
        else if (context->connectionType == ATMII_AAL2)
        {
            setport = context->trunk | AAL2_PORT_REQ;
        }
        else 
        {
            MTP2_CRITICAL(("Connection Type not supported\n"));
        }

        strioctl.ic_cmd = AIOCSETPORT;
        strioctl.ic_dp = (ITS_CHAR *)&setport;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);
        if (ret < 0)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. AIOCSETPORT failed "
                           "for Trunk port: %d  errno=%d\n",
                           context->trunk, errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        if (context->trunkType == ADAX_OC3)
        {
            ITS_UINT scramb = 0; /* To see difference of behavior with ADAX
                                  * in one OC3 card we need to enable and disable it.
                                  * could not depend on default settings
                                  */

            /* Set Scrambling */
            if (context->scrambType == ATM_CELL_PAYLOAD)
            {
                scramb = 1;
            }

            strioctl.ic_cmd    = AIOCSETSCRAMB;
            strioctl.ic_dp     = (char *) &scramb;
            strioctl.ic_len    = sizeof(scramb);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[i], I_STR, &strioctl);

            if (ret < 0)
            {
                MTP2_CRITICAL(("InitializeMTP2_ATMII: FAILED to set CELL_PAYLOAD"
                               " scrambling. error = %d", errno));

                return ITS_EINVALIDARGS;
            }
            else
            {
                MTP2_CRITICAL(("InitializeMTP2_ATMII: CELL_PAYLOAD is Set to = %d\n",
                               scramb));
            }
        }

        if (context->connectionType == ATMII_AAL5)
        {

            /************* Set VPI/VCI ************/

            vpi = context->dataLink[i].atmInfo.vpi;
            vci = context->dataLink[i].atmInfo.vci;
        
            vc = ((vpi << 20) | (vci << 4));

            vc = LSWAP(vc);

            if (context->globalServiceOptonsPresent)
            {

                ret = atmii_create_aal5_setvc_opts
                         (&opts, 
                          vc, 
                          context->globalServiceOptions.trafficClass,
                          context->globalServiceOptions.peekCellRate,
                          context->globalServiceOptions.minimumSustainableCellRate,
                          context->globalServiceOptions.maxBurstSize,
                          context->globalServiceOptions.initialCellRate,
                          0, /* RDF not supported for CBR and VCR */
                          0, /* RIF  not supported for CBR and VCR */
                          0, /* CDF  not supported for CBR and VCR */
                          context->globalServiceOptions.priority,
                          MAX_AAL5_FRAME,
                          context->globalServiceOptions.bufferClass);
 
                if (ret != 0)
                {
                    MTP2_CRITICAL(("ADAX Initialize:Setting Service Options Failed "
                                   "vc: %d  ret=%d\n",
                                   vc, ret));
                    MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                    return ITS_EINVALIDARGS;
                }

                strioctl.ic_dp = (ITS_CHAR *) &opts;
                strioctl.ic_len = sizeof(atmii_setvc_opts_t);
            }
            else
            {
                strioctl.ic_cmd = AIOCSETVC;
                strioctl.ic_dp = (ITS_CHAR *)&vc;
                strioctl.ic_len = sizeof(ITS_UINT);
                strioctl.ic_timout = -1;
            }

            strioctl.ic_cmd = AIOCSETVC;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[i], I_STR, &strioctl);
            MTP2_DEBUG(("Setting CV:%d   ret=%d\n", vc, ret));

            if (ret < 0)
            {
                MTP2_CRITICAL(("ADAX Initialize failed. Set VC Failed "
                               "vc: %d  errno=%d\n",
                               vc, errno));
                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }

        }
        else if (context->connectionType == ATMII_HDLC)
        {
            atmii_setts_opts_t opts;
            

            /* we don't want inverted data */
            opts.data_inv = 0;

            opts.ds0set = (1 << (context->dataLink[i].timeslot));
            if (context->baudRate == BAUD_RATE_64)
            {
                opts.fill_mask = ADAX_64Kbps;
            }
            else if (context->baudRate == BAUD_RATE_56)
            {
                opts.fill_mask = ADAX_56Kbps;
            }
            else
            {
                MTP2_CRITICAL(("ADAX Initialize failed. Invalid Baud Rate %d "
                               "for linkSet %d linkCode %d\n",
                               context->baudRate, context->linkSet, 
                               context->dataLink[i].linkCode));
                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }


            strioctl.ic_cmd = AIOCSETTTS;
            strioctl.ic_dp = (ITS_CHAR *)&opts;
            strioctl.ic_len = sizeof(opts);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[i], I_STR, &strioctl);

            if (ret == ADAX_FAILED)
            {
                MTP2_CRITICAL(("ADAX Initialize failed. AIOCSETTTS failed "
                               "for linkSet %d linkCode %d. error = %d\n",
                               context->linkSet, 
                               context->dataLink[i].linkCode, errno));

                MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

                return ITS_EINVALIDARGS;
            }

        }

        /************ Load SSOP Module *************/
        ret = ioctl(context->fd[i], I_PUSH, "a_sscop");
        if (ret < 0)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. Fail to load SSCF Module "
                           "errno=%d\n", errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

        /************ Load SSCF  Module *************/
        ret = ioctl(context->fd[i], I_PUSH, "a_sscf");
        if (ret < 0)
        {
            MTP2_CRITICAL(("ADAX Initialize failed. Fail to load SSCF Module "
                           "errno=%d\n", errno));
            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }

       /* Setting timers */

        strioctl.ic_cmd = LIO_GNPARAM;
        strioctl.ic_dp = (ITS_CHAR *)&sscf_param;
        strioctl.ic_len = sizeof(sscf_param);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize: Fail to retreive SSCF Parameters  "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet,
                           context->dataLink[i].linkCode, errno));

            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }


/*
        sscf_param.t1 = 3000;
        sscf_param.t2 = 20000;
*/
        strioctl.ic_cmd = LIO_NPARAM;
        strioctl.ic_dp = (ITS_CHAR *)&sscf_param;
        strioctl.ic_len = sizeof(sscf_param);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[i], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_CRITICAL(("ADAX Initialize: Fail to set T1, T2, T3 Timers  "
                           "for linkSet %d linkCode %d. error = %d\n",
                           context->linkSet,
                           context->dataLink[i].linkCode, errno));

            MTP2_Alarm_ADAX(12001, __FILE__, __LINE__,NULL);

            return ITS_EINVALIDARGS;
        }



    }

    DBC_AddDoCommand(ADAX_MTP2_Console);

    return ITS_SUCCESS; 
 
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the ADAX interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
int
ADAXInitializeMTP2(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;  

    /* Initialize the OM Buffer variables */
    omBuf.activeOm = 0x00;
    omBuf.inactiveOm = 0x01;

    if (context->hardware == ADAX_ATMII)
    {
        MTP2_WARNING(("ADAX Initialize: Initializing ATMII board\n"));
        return InitializeMTP2_ATMII(handl);
    }
    else
    {
        MTP2_WARNING(("ADAX Initialize: Initializing HDCII board\n"));
        return InitializeMTP2_HDCII(handl);
    }

    /* NOTREACHED */
    /* return ITS_SUCCESS; */
}
  
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
int
ADAXTermMTP2(ITS_SS7_HANDLE handle)
{
    ITS_UINT i;
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;

    for (i = 0; i < context->numTimeslots; i++)
    {
        close(context->fd[i]);
    }
    
    TRACE_Destructor(MTP2_ADAX_TraceData);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
RetrieveOne_HDCII(ITS_SS7_HANDLE handl, ITS_UINT nfd)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    ITS_EVENT ev;
    int flags = 0;
    struct strbuf ctlstr, datastr;
    int ret;
    unsigned int *pi;
    ITS_UINT msg, state, event;
    ITS_CHAR ctlbuf[MAX_CTL_BUF];
    ITS_CHAR databuf[MAX_MTP2_FRAME];

    ctlstr.maxlen = sizeof(ctlbuf);
    ctlstr.buf = (ITS_CHAR *)ctlbuf;
    ctlstr.len = 0;

    datastr.maxlen = sizeof(databuf);

    datastr.buf = (ITS_CHAR *)databuf;

    datastr.len = 0;

    errno = 0;
    msg = 0;


    ret = getmsg(context->fd[nfd], &ctlstr, &datastr, &flags);

    if (ret < 0)
    {
        if (errno == EAGAIN)
        {
            MTP2_ERROR(("No Data available for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12002, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);

            return ITS_ENOMSG;
        }
        else
        {
            MTP2_ERROR(("Read error for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12002, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);

            return (ITS_ENOTFOUND);
        }
    }

    if (ctlstr.len > 0 && ctlstr.len <= MAX_CTL_BUF)
    {
        pi = (ITS_UINT *)(ctlstr.buf);

        msg = *pi++;

        state = *pi++;

        event = *pi++;
    }
    else if (datastr.len  > 0 && datastr.len <= MAX_MTP2_FRAME)
    {
        MTP2_DEBUG(("MTP2:::: Link %d: linkSet %d Data received\n",
                    context->dataLink[nfd].linkCode, context->linkSet));
        PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX);    

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       datastr.len + 3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_DATA;
        ev.data[1] = context->linkSet;
        ev.data[2] = context->dataLink[nfd].linkCode;

        memcpy(&ev.data[3], datastr.buf, datastr.len);

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }
    else
    {
        return (ITS_ENOMSG);
    }

    switch (msg)
    {
    case MTP2_PHASE_IND:
        context->mtp2State = state;

        switch (state)
        {
        case OUT_OF_SERVICE:
            MTP2_DEBUG(("Phase Ind Out Of Service received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case INITIAL_ALIGNMENT:
            MTP2_DEBUG(("Phase Ind Initial Alignment received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case ALIGNED_NOT_READY:
            MTP2_DEBUG(("Phase Ind Aligned Not Ready received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case PROVING:
            MTP2_DEBUG(("Phase Ind Proving received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case ALIGNED_READY:
            MTP2_DEBUG(("Phase Ind Aligned Ready received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case IN_SERVICE:
            MTP2_DEBUG(("Phase Ind In Service received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_IN_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        default:
            MTP2_DEBUG(("Phase Ind received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;
        }
        break;

    case MTP2_PPRIM_IND:
        context->mtp2Status = state;

        switch (event)
        {
        case T1_EXPIRY:
            MTP2_WARNING(("T1 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12022, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T1_EXPIRED);    

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T2_EXPIRY:
            MTP2_WARNING(("T2 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12003, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T2_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T3_EXPIRY:
            MTP2_WARNING(("T3 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12023, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T3_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T6_EXPIRY:
            MTP2_WARNING(("T6 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T6_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T7_EXPIRY:
            MTP2_WARNING(("T7 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12004, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T7_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case START_LINK_FROM_MTP3:
            MTP2_DEBUG(("Start Link from MTP3 "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case STOP_LINK_FROM_MTP3:
            MTP2_DEBUG(("Stop Link from MTP3 "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIOS_FROM_NETWORK:
            MTP2_WARNING(("SIOS received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIO_FROM_NETWORK:
            MTP2_WARNING(("SIO received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                             "ls=%x:link=%x",
                           context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;


        case SIN_FROM_NETWORK:
            MTP2_WARNING(("SIN received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;

        case SIE_FROM_NETWORK:
            MTP2_WARNING(("SIE received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;


        case LINK_FAILED:
            MTP2_WARNING(("Link Failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SUERM_EXPIRY:
            MTP2_WARNING(("SUERM Expiry "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12016, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY);

            return ITS_ENOMSG;

        case INCORRECT_FIB_BSN:
            MTP2_WARNING(("Incorrect FIB BSN "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12014, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN);

            return ITS_ENOMSG;

        case CURRENT_PROVING_ATTEMPT_FAILURE:
            MTP2_WARNING(("Current proving attempt failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12024, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);

            return ITS_ENOMSG;

        case ALL_PROVING_ATTEMPT_FAILURE:
            MTP2_WARNING(("All proving attempts failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12025, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);

            return ITS_ENOMSG;

        case PROCESSOR_OUTAGE_FROM_MTP3:
            MTP2_WARNING(("Local Processor Down "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12006, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN);    

            return ITS_ENOMSG;

        case SIPO_FROM_NETWORK:
            MTP2_WARNING(("Remote Processor Down "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12007, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_OUT;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));


        case LPO_RECOVERY:
            MTP2_DEBUG(("Local Processor Up "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12008, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP);

            return ITS_ENOMSG;

        case RPO_RECOVERY:
            MTP2_DEBUG(("Remote Processor Up "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12009, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_REC;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case LOCAL_CONG:
            MTP2_WARNING(("Local congestion "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12017, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_DETECTED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ONSET;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIB_FROM_NETWORK:
            MTP2_DEBUG(("Remote congestion "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12026, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_DETECTED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ONSET;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case LCONG_RECOVERY:
            MTP2_DEBUG(("Local congestion recovery "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12018, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ABATES;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case RCONG_RECOVERY:
            MTP2_DEBUG(("Remote congestion recovery "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12027, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_RECOVERED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ABATES;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case FISU_FROM_NETWORK:
            return ITS_ENOMSG;

        case MSU_FROM_NETWORK:
            MTP2_DEBUG(("MTP2:::: Link %d: linkSet %d Data received\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            if (datastr.len < 0 || datastr.len > MAX_MTP2_FRAME)
            {
                return ITS_ENOMSG;
            }

            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           datastr.len + 3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_DATA;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            memcpy(&ev.data[3], datastr.buf, datastr.len);

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));


        default:
            MTP2_ERROR(("Unknown Event received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            return ITS_ENOMSG;
        }
    
    default:
        MTP2_ERROR(("Illegal MTP2 Ind received "
                    "for linkSet %d linkCode %d\n",
                    context->linkSet, context->dataLink[nfd].linkCode));

        return ITS_ENOMSG;
    }

    /* NOTREACHED */
    /* return (ITS_SUCCESS); */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya  07-11-2006  Bug ID:4373     Broadband link Alignment. The 
 *                                          priority bit has to be discarded.
 ****************************************************************************/
static int
RetrieveOne_ATMII(ITS_SS7_HANDLE handl, ITS_UINT nfd)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    ITS_EVENT ev;
    int flags = 0;
    struct strbuf ctlstr, datastr;
    int ret;
    ITS_UINT msg, state, event;
    ITS_CHAR ctlbuf[MAX_CTL_BUF];
    ITS_CHAR databuf[MAX_AAL5_FRAME];
    char buf[3*MAX_AAL5_FRAME];
    char printBuf[3*MAX_AAL5_FRAME];
    int i;

    ctlstr.maxlen = sizeof(ctlbuf);
    ctlstr.buf = (ITS_CHAR *)ctlbuf;
    ctlstr.len = 0;

    datastr.maxlen = sizeof(databuf);

    datastr.buf = (ITS_CHAR *)databuf;

    datastr.len = 0;

    errno = 0;
    msg = 0;


    ret = getmsg(context->fd[nfd], &ctlstr, &datastr, &flags);


    if (ret < 0)
    {
        if (errno == EAGAIN)
        {
            MTP2_ERROR(("No Data available for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12002, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);

            return ITS_ENOMSG;
        }
        else
        {
            MTP2_ERROR(("Read error for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12002, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);

            return (ITS_ENOTFOUND);
        }
    }

    if (ctlstr.len > 0 && ctlstr.len <= MAX_CTL_BUF)
    {
#if 0
        pi = (ITS_UINT *)(ctlstr.buf);

        msg = *pi++;

        state = *pi++;

        event = *pi++;
#endif
        struct sscf_ind_t *sscf_msg;
        msg = state = event = 0;

        sscf_msg = (struct sscf_ind_t *) ctlstr.buf;

        msg =  sscf_msg->sscf_ind;
        event = sscf_msg->ind_type;
        state  = sscf_msg->opt_param;

    }
    else if (datastr.len  > 0 && datastr.len <= MAX_AAL5_FRAME)
    {

        MTP2_DEBUG(("MTP2:::: Link %d: linkSet %d Data received\n",
                    context->dataLink[nfd].linkCode, context->linkSet));
        PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX);    

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       datastr.len + 3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_DATA;
        ev.data[1] = context->linkSet;
        ev.data[2] = context->dataLink[nfd].linkCode;

#if defined(TTC)
{
        /*Discard the first byte of the Routing label which 
        is the priority bit.*/ 
        memcpy(&ev.data[3], &datastr.buf[1], (datastr.len - 1));
}
#else
{
        memcpy(&ev.data[3], datastr.buf, datastr.len);
}
#endif
        if(TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG))
        {
            memset(buf, 0, 3*MAX_AAL5_FRAME);
            memset(printBuf, 0, 3*MAX_AAL5_FRAME);
            sprintf(printBuf,"DATA:: MTP3 <-------  MTP2 [linkSet %d linkCode %d]\n",
		    context->linkSet,context->dataLink[nfd].linkCode);

            for (i = 0 ; i < datastr.len; i++)
            {
                sprintf(buf, "%02x ", (ITS_OCTET) datastr.buf[i]);
                strcat(printBuf, buf);
                if (i && (i % 23 == 0))
                {
                    strcat(printBuf, "\n");
                }
            }

            MTP2_DEBUG(("%s\n", printBuf));
        }

        //return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        return  TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
    }
    else
    {
        return (ITS_ENOMSG);
    }

    switch (msg)
    {
    case SSCF_CTL_MSG_IND:

        switch (event)
        {
        case AAL_IN_SERVICE_IND:

            MTP2_WARNING(("*** MTP2:: AAL_IN_SERVICE_IND Received ls:%2u ln:%3u *** \n",
                          context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_IN_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            //return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	        return  TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

        case AAL_OUT_OF_SERVICE_IND:

  	        if (state == ANS)
	        {
		        MTP2_WARNING(("*** MTP2:: AAL_OUT_OF_SERVICE_IND Received. ls:%2u ln:%3u. Reason=%d (%s) ***\n",
			       context->linkSet, context->dataLink[nfd].linkCode, 
			       state, AAL_OUT_OF_SERVICE_REASON_STR(state)));
	        }
	        else
	        {
		        MTP2_CRITICAL(("*** MTP2:: AAL_OUT_OF_SERVICE_IND Received. ls:%2u ln:%3u. Reason=%d (%s) ***\n",
			       context->linkSet, context->dataLink[nfd].linkCode, 
			       state, AAL_OUT_OF_SERVICE_REASON_STR(state)));

	    } 	

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            //return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	        return  TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

        case AAL_PROVING_IND:
            MTP2_DEBUG((" MTP2:: AAL_PROVING_IND Received\n"));
            break;

        case AAL_STOP_PROVING_IND:
            MTP2_DEBUG((" MTP2:: AAL_STOP_PROVING_IND Received\n"));
            break;

        case AAL_CONGEST_IND:
            MTP2_DEBUG((" MTP2:: AAL_CONGEST_IND Received\n"));
            break;

        case AAL_CONGEST_CEASED_IND:
            MTP2_DEBUG((" MTP2:: AAL_CONGEST_CEASED_IND Received\n"));
            break;

        case AAL_RETRIEVAL_COMP_IND:
            MTP2_DEBUG((" MTP2:: AAL_RETRIEVAL_COMP_IND Received\n"));
            break;

        case AAL_RETRIEVED_MSGS_IND:
            MTP2_DEBUG((" MTP2:: AAL_RETRIEVED_MSGS_IND Received\n"));
            break;

        case AAL_BSNT_CONF:
            MTP2_DEBUG((" MTP2:: AAL_BSNT_CONF Received\n"));
            break;

        case AAL_BSNT_NOT_RETR_CONF:
            MTP2_DEBUG((" MTP2:: AAL_BSNT_NOT_RETR_CONF Received\n"));
            break;

        case AAL_PROVING_UNS:
            MTP2_DEBUG((" MTP2:: AAL_PROVING_UNS Received\n"));
            break;

        default:
            MTP2_ERROR(("Illegal AAL5 event received "
                    "for linkSet %d linkCode %d\n",
                    context->linkSet, context->dataLink[nfd].linkCode));
       }

    break;

    default:
        MTP2_ERROR(("Illegal SSCF Ind received "
                    "for linkSet %d linkCode %d\n",
                    context->linkSet, context->dataLink[nfd].linkCode));

#if 0
    case MTP2_PHASE_IND:
        context->mtp2State = state;

        switch (state)
        {
        case OUT_OF_SERVICE:
            MTP2_DEBUG(("Phase Ind Out Of Service received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case INITIAL_ALIGNMENT:
            MTP2_DEBUG(("Phase Ind Initial Alignment received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case ALIGNED_NOT_READY:
            MTP2_DEBUG(("Phase Ind Aligned Not Ready received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case PROVING:
            MTP2_DEBUG(("Phase Ind Proving received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case ALIGNED_READY:
            MTP2_DEBUG(("Phase Ind Aligned Ready received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case IN_SERVICE:
            MTP2_DEBUG(("Phase Ind In Service received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_IN_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        default:
            MTP2_DEBUG(("Phase Ind received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;
        }
        break;

    case MTP2_PPRIM_IND:
        context->mtp2Status = state;

        switch (event)
        {
        case T1_EXPIRY:
            MTP2_WARNING(("T1 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12022, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T1_EXPIRED);    

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T2_EXPIRY:
            MTP2_WARNING(("T2 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12003, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T2_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T3_EXPIRY:
            MTP2_WARNING(("T3 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12023, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T3_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T6_EXPIRY:
            MTP2_WARNING(("T6 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T6_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case T7_EXPIRY:
            MTP2_WARNING(("T7 expiry received "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12004, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_T7_EXPIRED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case START_LINK_FROM_MTP3:
            MTP2_DEBUG(("Start Link from MTP3 "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return ITS_ENOMSG;

        case STOP_LINK_FROM_MTP3:
            MTP2_DEBUG(("Stop Link from MTP3 "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIOS_FROM_NETWORK:
            MTP2_WARNING(("SIOS received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIO_FROM_NETWORK:
            MTP2_WARNING(("SIO received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                             "ls=%x:link=%x",
                           context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;


        case SIN_FROM_NETWORK:
            MTP2_WARNING(("SIN received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;

        case SIE_FROM_NETWORK:
            MTP2_WARNING(("SIE received from network "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12005, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);

            return ITS_ENOMSG;


        case LINK_FAILED:
            MTP2_WARNING(("Link Failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_OUT_OF_SERVICE;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SUERM_EXPIRY:
            MTP2_WARNING(("SUERM Expiry "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12016, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY);

            return ITS_ENOMSG;

        case INCORRECT_FIB_BSN:
            MTP2_WARNING(("Incorrect FIB BSN "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12014, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN);

            return ITS_ENOMSG;

        case CURRENT_PROVING_ATTEMPT_FAILURE:
            MTP2_WARNING(("Current proving attempt failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12024, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);

            return ITS_ENOMSG;

        case ALL_PROVING_ATTEMPT_FAILURE:
            MTP2_WARNING(("All proving attempts failed "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12025, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);

            return ITS_ENOMSG;

        case PROCESSOR_OUTAGE_FROM_MTP3:
            MTP2_WARNING(("Local Processor Down "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12006, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN);    

            return ITS_ENOMSG;

        case SIPO_FROM_NETWORK:
            MTP2_WARNING(("Remote Processor Down "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12007, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_OUT;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));


        case LPO_RECOVERY:
            MTP2_DEBUG(("Local Processor Up "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12008, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP);

            return ITS_ENOMSG;

        case RPO_RECOVERY:
            MTP2_DEBUG(("Remote Processor Up "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12009, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_REC;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case LOCAL_CONG:
            MTP2_WARNING(("Local congestion "
                          "for linkSet %d linkCode %d\n",
                          context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12017, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_DETECTED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ONSET;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case SIB_FROM_NETWORK:
            MTP2_DEBUG(("Remote congestion "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12026, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_DETECTED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ONSET;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case LCONG_RECOVERY:
            MTP2_DEBUG(("Local congestion recovery "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12018, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ABATES;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case RCONG_RECOVERY:
            MTP2_DEBUG(("Remote congestion recovery "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            MTP2_Alarm_ADAX(12027, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,context->dataLink[nfd].linkCode);
            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_RECOVERED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ABATES;

            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case FISU_FROM_NETWORK:
            return ITS_ENOMSG;

        case MSU_FROM_NETWORK:
            MTP2_DEBUG(("MTP2:::: Link %d: linkSet %d Data received\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            if (datastr.len < 0 || datastr.len > MAX_AAL5_FRAME)
            {
                return ITS_ENOMSG;
            }

            PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           datastr.len + 3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_DATA;
            ev.data[1] = context->linkSet;
            ev.data[2] = context->dataLink[nfd].linkCode;

            memcpy(&ev.data[3], datastr.buf, datastr.len);

            if(TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG))
            {
                memset(buf, 0, 3*MAX_AAL5_FRAME);
                memset(printBuf, 0, 3*MAX_AAL5_FRAME);
                sprintf(printBuf,"DATA:: MTP2 -----> MTP3\n");

                for (i = 0 ; i < datastr.len; i++)
                {
                    sprintf(buf, "%02x ", (ITS_OCTET) datastr.buf[i]);
                    strcat(printBuf, buf);
                    if (i && (i % 23 == 0))
                    {
                        strcat(printBuf, "\n");
                    }
                }

                MTP2_DEBUG(("%s\n", printBuf));
            }
           
            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));


        default:
            MTP2_ERROR(("Unknown Event received "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));

            return ITS_ENOMSG;
        }
    default:
        MTP2_ERROR(("Illegal MTP2 Ind received "
                    "for linkSet %d linkCode %d\n",
                    context->linkSet, context->dataLink[nfd].linkCode));

        return ITS_ENOMSG;
#endif
    }

    /* NOTREACHED */
    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
int
ADAXRetrieveMTP2Message(ITS_SS7_HANDLE handl)
{
    ITS_UINT i;
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    int ret;

    ret = ITS_ENOMSG;
    for (i = 0; i < context->numTimeslots; i++)
    {
        if (context->which & (1 << i))
        {
            if (context->hardware == ADAX_ATMII)
            {
                ret = RetrieveOne_ATMII(handl, i);
            }
            else
            { 
                ret = RetrieveOne_HDCII(handl, i);
            }
        }
    }
    context->which = 0;

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Added handling of LPO/LPR 
 *                       ID::D0010               events from MTP3 for LPO
 *                                               feature
 *
 ****************************************************************************/
static int
SendMTP2Event_HDCII(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    ITS_EVENT ev;
    ITS_OCTET linkSet;
    ITS_OCTET linkCode;
    short ret;
    struct strioctl strioctl;
    struct strbuf datastr;
    ITS_UINT buff[MAX_MTP2_FRAME/sizeof(ITS_UINT)];
    struct pollfd pfd;
    ITS_UINT *pi;
    ITS_UINT nmsgs;
    ITS_UINT fsnc;
    ITS_UINT kbuff[MAX_MTP2_FRAME/sizeof(ITS_UINT)];
    ITS_CHAR wbuf[2];
    int      nfd = -1;
    ITS_UINT i;

    ev.data = data;
    ev.len = dlen;

    linkSet = L2_LINK_SET(&ev);
    linkCode = L2_LINK_CODE(&ev);

    for(i = 0; i < context->numTimeslots; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            nfd = i;
            break;
        }
    }

    if (nfd == -1 )
    {
        MTP2_ERROR(("LinkCode %d not configured\n", linkCode));
        return (ITS_ENOTFOUND);
    }

    switch (L2_MSG_TYPE(&ev))
    {
    case L3_L2_START:
        MTP2_DEBUG(("MTP2:::: START for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2START;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send START failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12010, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }
    
        MTP2_Alarm_ADAX(12012, __FILE__, __LINE__,
                        "ls=%x:link=%x",
                        context->linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_STOP:
        MTP2_DEBUG(("MTP2:::: STOP for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2STOP;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send STOP failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12011, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }

        MTP2_Alarm_ADAX(12013, __FILE__, __LINE__,
                        "ls=%x:link=%x",
        context->linkSet,linkCode);

        return (ITS_SUCCESS);
        
    case L3_L2_RESUME:
        MTP2_DEBUG(("MTP2:::: STOP for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2CONTINUE;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send RESUME failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
        MTP2_DEBUG(("MTP2:::: CLEAR BUFFERS for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2FLUSH;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send CLEAR BUFFERS failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12019, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY:
        MTP2_DEBUG(("MTP2:::: EMERGENCY for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2EMRGNCY;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send EMERGENCY failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12020, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY_CEASE:
        MTP2_DEBUG(("MTP2:::: EMERGENCY CEASE for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2EMRGEND;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send EMERGENCY CEASE failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_DATA:
        memcpy(buff, L2_LINK_DATA(&ev) + 1,
               dlen - 4 * sizeof(ITS_OCTET));

        datastr.maxlen = dlen - 4 * sizeof(ITS_OCTET);
        datastr.len = dlen - 4 * sizeof(ITS_OCTET);
        datastr.buf = (char *)buff;

        if (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG))
        {
            printf("==========> SendMTP2Event_HDCII: len: %d\n", datastr.len);

            for (ret = 0; ret < datastr.len; ret++) 
            {
                printf("%02x ", datastr.buf[ret]);
            }
            printf("\n");
        }
 
        pfd.fd = context->fd[nfd];
        pfd.events = POLLOUT;
        
        ret = putmsg(context->fd[nfd], NULL, &datastr, 0);

        MTP2_DEBUG(("SendMTP2Event_HDCII: putEvent: ret %d\n", ret));

        if (ret != 0)
        {
            static int throttled = 0, aborted = 0;

            if (errno == EAGAIN)
            {
                throttled++;

                if (throttled && !(throttled % 50))
                {
                    MTP2_ERROR(("MTP2 putmsg failed "
                                "for linkSet %d linkCode %d. "
                                "Throttled %d times\n", throttled));
                }

                pfd.revents = 0;
                while (pfd.revents == 0)
                {
                    poll(&pfd, 1, 1000*5);
                }
                ret = putmsg(context->fd[nfd], NULL, &datastr, 0);
                if(ret != 0)
                {
                    aborted++;

                    if (aborted && !(aborted % 50))
                    {
                        MTP2_ERROR(("MTP2 putmsg failed "
                                    "for linkSet %d linkCode %d. "
                                    "Aborted %d times\n", throttled));
                    }

                    MTP2_ERROR(("MTP2 putmsg failed "
                                "for linkSet %d linkCode %d. error = %d\n",
                                context->linkSet, context->dataLink[nfd].linkCode, errno));
                    MTP2_Alarm_ADAX(12021, __FILE__, __LINE__,
                                    "ls=%x:link=%x",
                                    context->linkSet,linkCode);
                    PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);

                    return (ITS_ENOTFOUND);
                }
            }
            else
            {
                MTP2_ERROR(("For linkSet %d linkCode %d. MTP2 put msg Failed errno=%d\n",
                            context->linkSet, context->dataLink[nfd].linkCode, errno));

                return (ITS_ENOTFOUND);
            }
        }
        PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_TX);

        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_BSNT:
        MTP2_DEBUG(("MTP2:::: RETRIEVE BSNT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        if( context->mtp2Status == INSERVICE)
        {
            MTP2_ERROR(("Cannot RETRIEVE BSNT "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return (ITS_ENOTFOUND);
        }

        strioctl.ic_cmd = MTP2RBSNT;
        strioctl.ic_dp = (ITS_CHAR *)kbuff;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send RETRIEVE BSNT failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
        else
        {
            pi = (ITS_UINT *)kbuff;

            MTP2_ERROR(("Send RETRIEVE BSNT failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET) + sizeof(ITS_UINT));

            ev.data[0] = L2_L3_BSNT;
            ev.data[1] = context->linkSet;
            ev.data[2] = linkCode;
            memcpy(&ev.data[3], pi, sizeof(ITS_UINT));

            ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
            
            if ( ret != ITS_SUCCESS)
            {
                 return ret;
            }

            /* unblock the poll */
            write(context->pipefd[1], wbuf, 1);

            return ITS_SUCCESS;
        }
        
    case L3_L2_RETRIEVE_MSGS:
        memcpy(&fsnc, L2_LINK_DATA(&ev), sizeof(ITS_UINT));

        MTP2_DEBUG(("MTP2:::: RETRIEVE MSGS for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        if ( context->mtp2Status == INSERVICE)
        {
            MTP2_ERROR(("RETRIEVE MSGS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }

        strioctl.ic_cmd = MTP2FSNC;
        strioctl.ic_dp = (ITS_CHAR *)&fsnc;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send RETRIEVE MSGS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));    
            MTP2_Alarm_ADAX(12015, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }

        strioctl.ic_cmd = MTP2GETTS;
        strioctl.ic_dp = (ITS_CHAR *)kbuff;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 GETTS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
        else
        {
            nmsgs = *(ITS_UINT *)kbuff;

            MTP2_DEBUG(("Number of Messages Retrieved is %d "
                        "for linkSet %d linkCode %d\n",
                        nmsgs, context->linkSet, context->dataLink[nfd].linkCode));
        }

        while (ret == 0 && nmsgs--)
        {
       
            strioctl.ic_cmd = MTP2GETTQ;
            strioctl.ic_dp = (ITS_CHAR *)kbuff;
            strioctl.ic_len = MAX_MTP2_FRAME;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);


            if (ret == ADAX_FAILED)
            {
                MTP2_ERROR(("MTP2 GETTQ failed "
                            "for linkSet %d linkCode %d. error = %d\n",
                            context->linkSet, context->dataLink[nfd].linkCode, errno));

                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_EVENT_INIT(&ev, ITS_MTP2_SRC, 
                                strioctl.ic_len + 3 * sizeof(ITS_OCTET));

                ev.data[0] = L2_L3_RETRIEVED_MSG;
                ev.data[1] = context->linkSet;
                ev.data[2] = linkCode;

                memcpy(&ev.data[3], kbuff, strioctl.ic_len); ;

                ret =  MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

                if (ret != ITS_SUCCESS)
                {
                    return ret;
                }
            }
            
        }

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
        ev.data[1] = context->linkSet;
        ev.data[2] = linkCode;

        ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
            
        if ( ret != ITS_SUCCESS)
        {
             return ret;
        }

        write(context->pipefd[1], wbuf, 1);

        return ITS_SUCCESS;
        
    case L3_L2_CONNECT:
        MTP2_DEBUG(("MTP2:::: CONNECT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        return (ITS_SUCCESS);
        
    case L3_L2_DISCONNECT:
        MTP2_DEBUG(("MTP2:::: DISCONNECT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2STOP;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 DISCONNECT failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        

    case L3_L2_LOCAL_PROCESSOR_OUT:
        MTP2_DEBUG(("MTP2:::: LPO for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2LPO;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 LPO failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }

        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_REC:
        MTP2_DEBUG(("MTP2:::: LPR for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = MTP2LPR;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 LPO failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);

    default:
        break;
    }

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya  07-11-2006  Bug ID:4373     Broadband link Alignment. The
 *                                          priority bit has to be added.
 *
 *  S Magesh    22-11-2007  Bug ID:220      When Link Deactivation is performed
 *                                          L2_L3_BSNT request is received by
 *                                          MTP3 Layer after some delay.  To
 *                                          avoid this as a temporary fix, instead
 *                                          of putting the message in the VENDOR
 *                                          Queue, the message is directly put
 *                                          into the Intellinet MTP3 Queue.
 ****************************************************************************/
static int
SendMTP2Event_ATMII(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    ITS_EVENT ev;
    ITS_OCTET linkSet;
    ITS_OCTET linkCode;
    short ret;
    struct strioctl strioctl;
    struct strbuf datastr;
    ITS_OCTET buff[MAX_AAL5_FRAME];
    struct pollfd pfd;
    ITS_UINT *pi;
    ITS_UINT nmsgs;
    ITS_UINT fsnc;
    ITS_OCTET kbuff[MAX_AAL5_FRAME];
    ITS_CHAR wbuf[2];
    int      nfd = -1;
    ITS_UINT i;
    char buf[3*MAX_AAL5_FRAME];
    char printBuf[3*MAX_AAL5_FRAME];

#define MULTIPLICATION_FACTOR  10
    ITS_UINT pollCallCount = 0;
    ITS_UINT pollCallCountBurst = MULTIPLICATION_FACTOR;

    ev.data = data;
    ev.len = dlen;

    linkSet = L2_LINK_SET(&ev);
    linkCode = L2_LINK_CODE(&ev);

    for(i = 0; i < context->numTimeslots; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            nfd = i;
            break;
        }
    }

    if (nfd == -1 )
    {
        MTP2_ERROR(("LinkCode %d not configured\n", linkCode));
        return (ITS_ENOTFOUND);
    }

    switch (L2_MSG_TYPE(&ev))
    {
    case L3_L2_START:
        MTP2_DEBUG(("MTP2:::: START for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_START;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send START failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12010, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }
    
        MTP2_Alarm_ADAX(12012, __FILE__, __LINE__,
                        "ls=%x:link=%x",
                        context->linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_STOP:
        MTP2_DEBUG(("MTP2:::: STOP for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_STOP;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send STOP failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12011, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }

        MTP2_Alarm_ADAX(12013, __FILE__, __LINE__,
                        "ls=%x:link=%x",
        context->linkSet,linkCode);

        return (ITS_SUCCESS);
        
    case L3_L2_RESUME:
        MTP2_DEBUG(("MTP2:::: CONTINUE for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));
    
        return (ITS_SUCCESS);
        
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
        MTP2_DEBUG(("MTP2:::: CLEAR BUFFERS for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY:
        MTP2_DEBUG(("MTP2:::: EMERGENCY for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_EMERGENCY;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);


        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send EMERGENCY failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            MTP2_Alarm_ADAX(12020, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY_CEASE:
        MTP2_DEBUG(("MTP2:::: EMERGENCY CEASE for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_EM_CEASES;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send EMERGENCY CEASE failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);
        
    case L3_L2_DATA:
#if defined(TTC)
{
        /* Adding the priority bit as the first byte of the routing label */ 
        buff[0] = 0x00;

        memcpy(&buff[1], L2_LINK_DATA(&ev) + 1,
               dlen - 4 * sizeof(ITS_OCTET));
               dlen++;
}
#else
{
        memcpy(buff, L2_LINK_DATA(&ev) + 1,
               dlen - 4 * sizeof(ITS_OCTET));
}
#endif
        datastr.maxlen = dlen - 4 * sizeof(ITS_OCTET);
        datastr.len = dlen - 4 * sizeof(ITS_OCTET);
        datastr.buf = (char *)buff;

        pfd.fd = context->fd[nfd];
        pfd.events = POLLOUT;
       
        if(TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG))
        {
            memset(buf, 0, 3*MAX_AAL5_FRAME);
            memset(printBuf, 0, 3*MAX_AAL5_FRAME);
            sprintf(printBuf,"DATA:: MTP3 -----> MTP2 [linkSet %d linkCode %d]\n",
		    context->linkSet, context->dataLink[nfd].linkCode);

            for (i = 0 ; i < datastr.len; i++)
            {
                sprintf(buf, "%02x ", (ITS_OCTET) datastr.buf[i]);
                strcat(printBuf, buf);
                if (i && (i % 23 == 0))
                {
                    strcat(printBuf, "\n");
                }
            }

            MTP2_DEBUG(("%s\n", printBuf));
        }

        ret = putmsg(context->fd[nfd], NULL, &datastr, 0);

        if (ret != 0)
        {
            static int throttled = 0, aborted = 0;

            if (errno == EAGAIN)
            {
                throttled++;

                if (throttled && !(throttled % 50))
                {
                    MTP2_ERROR(("MTP2 putmsg failed for linkSet %d linkCode %d. "
                                "Throttled %d times\n", 
				    context->linkSet, context->dataLink[nfd].linkCode,
				    throttled));
                }

                pfd.revents = 0;

                while (pfd.revents == 0)
                {
                    poll(&pfd, 1, 1000*5);
		            pollCallCount++;
		            if (((pollCallCount % pollCallCountBurst ) == 0))
		            {
			            MTP2_WARNING(("MTP2 poll called (linkSet %d linkCode %d)  %d times\n", 
				            context->linkSet, context->dataLink[nfd].linkCode,
				            pollCallCount));
                        if (pollCallCountBurst > (pollCallCountBurst*MULTIPLICATION_FACTOR))
                        {
                            pollCallCountBurst = pollCallCountBurst*MULTIPLICATION_FACTOR;
                        }
		            }
                }
                ret = putmsg(context->fd[nfd], NULL, &datastr, 0);
                if(ret != 0)
                {
                    aborted++;

                    if (aborted && !(aborted % 50))
                    {
                        MTP2_ERROR(("MTP2 putmsg failed for linkSet %d linkCode %d. "
                                    "Aborted %d times\n", 
				        context->linkSet, context->dataLink[nfd].linkCode,
				        throttled));
                    }

                    MTP2_ERROR(("MTP2 putmsg failed "
                                "for linkSet %d linkCode %d. error = %d\n",
                                context->linkSet, context->dataLink[nfd].linkCode, errno));
                    MTP2_Alarm_ADAX(12021, __FILE__, __LINE__,
                                    "ls=%x:link=%x",
                                    context->linkSet,linkCode);
                    PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);

                    return (ITS_ENOTFOUND);
                }
            }
            else
            {
                MTP2_ERROR(("For linkSet %d linkCode %d. MTP2 put msg Failed errno=%d\n",
                            context->linkSet, context->dataLink[nfd].linkCode, errno));

                return (ITS_ENOTFOUND);
            }
        }
        PEG_IncrPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_TX);

        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_BSNT:
        MTP2_DEBUG(("MTP2:::: RETRIEVE BSNT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        if( context->mtp2Status == INSERVICE)
        {
            MTP2_ERROR(("Cannot RETRIEVE BSNT "
                        "for linkSet %d linkCode %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode));
            return (ITS_ENOTFOUND);
        }

        strioctl.ic_cmd = LIO_BSNT;
        strioctl.ic_dp = (ITS_CHAR *)kbuff;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send RETRIEVE BSNT failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
        else
        {
            pi = (ITS_UINT *)kbuff;

            MTP2_DEBUG(("Send RETRIEVE BSNT success "
                        "for linkSet %d linkCode %d. bsnt =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, *pi));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET) + sizeof(ITS_UINT));

            ev.data[0] = L2_L3_BSNT;
            ev.data[1] = context->linkSet;
            ev.data[2] = linkCode;
            memcpy(&ev.data[3], pi, sizeof(ITS_UINT));

            ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
            //ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
            
            if ( ret != ITS_SUCCESS)
            {
                 return ret;
            }

            /* unblock the poll */
            write(context->pipefd[1], wbuf, 1);

            return ITS_SUCCESS;
        }
        
    case L3_L2_RETRIEVE_MSGS:
        memcpy(&fsnc, L2_LINK_DATA(&ev), sizeof(ITS_UINT));

        MTP2_WARNING(("MTP2:::: RETRIEVE MSGS for linkSet %d linkCode %d "
                      "  nfd %d fscn %d\n", 
                      context->linkSet, linkCode, nfd, fsnc));

        if ( context->mtp2Status == INSERVICE)
        {
            MTP2_ERROR(("RETRIEVE MSGS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }

        SSCOP_GETTN cnt;

        strioctl.ic_cmd = LIO_GETTN;
        strioctl.ic_dp = (ITS_CHAR *)&cnt;
        strioctl.ic_len = sizeof(SSCOP_GETTN);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 GETTS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));
            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));
    
            ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
            ev.data[1] = context->linkSet;
            ev.data[2] = linkCode;

            //ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	        ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
            
            if ( ret != ITS_SUCCESS)
            {
                 return ret;
            }


            return (ITS_ENOTFOUND);
        }
        else
        {
            nmsgs = *(ITS_UINT *)kbuff;

            MTP2_DEBUG(("Number of Messages Retrieved is %d "
                        "for linkSet %d linkCode %d\n",
                        nmsgs, context->linkSet, context->dataLink[nfd].linkCode));

        }


        strioctl.ic_cmd = LIO_FSNC;
        strioctl.ic_dp = (ITS_CHAR *)&fsnc;
        strioctl.ic_len = sizeof(ITS_UINT);
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("Send RETRIEVE MSGS failed "
                        "for linkSet %d linkCode %d. error =%d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));    
            MTP2_Alarm_ADAX(12015, __FILE__, __LINE__,
                            "ls=%x:link=%x",
                            context->linkSet,linkCode);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));
    
            ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
            ev.data[1] = context->linkSet;
            ev.data[2] = linkCode;

            //ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	        ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
            
            if ( ret != ITS_SUCCESS)
            {
                 return ret;
            }


            return (ITS_ENOTFOUND);
        }

        while (ret == 0 && nmsgs--)
        {
       
            strioctl.ic_cmd = LIO_GETTQ;
            strioctl.ic_dp = (ITS_CHAR *)kbuff;
            strioctl.ic_len = MAX_MTP2_FRAME;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);


            if (ret == ADAX_FAILED)
            {
                MTP2_ERROR(("MTP2 GETTQ failed "
                            "for linkSet %d linkCode %d. error = %d\n",
                            context->linkSet, context->dataLink[nfd].linkCode, errno));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));
    
            ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
            ev.data[1] = context->linkSet;
            ev.data[2] = linkCode;

            //ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	        ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
            
            if ( ret != ITS_SUCCESS)
            {
                 return ret;
            }


                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_EVENT_INIT(&ev, ITS_MTP2_SRC, 
                                strioctl.ic_len + 3 * sizeof(ITS_OCTET));

                ev.data[0] = L2_L3_RETRIEVED_MSG;
                ev.data[1] = context->linkSet;
                ev.data[2] = linkCode;

                memcpy(&ev.data[3], kbuff, strioctl.ic_len); ;

                //ret =  MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
		        ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

                if (ret != ITS_SUCCESS)
                {
		            MTP2_ERROR(("MTP2 MQUEUE_Enqueue failed "
				            "for linkSet %d linkCode %d.\n",
				            context->linkSet, linkCode));
                    return ret;
                }
            }
            
        }

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
        ev.data[1] = context->linkSet;
        ev.data[2] = linkCode;

        //ret = MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
	    ret = TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
            
        if ( ret != ITS_SUCCESS)
        {
	        MTP2_ERROR(("MTP2 MQUEUE_Enqueue (RETRIEVAL_COMPLETE event) failed "
			"for linkSet %d linkCode %d.\n",
			context->linkSet, linkCode));
             return ret;
        }
	     
	    MTP2_DEBUG(("MTP2 Message Retrieval Successful "
		    "for linkSet %d linkCode %d.\n",
		    context->linkSet, linkCode));

        write(context->pipefd[1], wbuf, 1);

        return ITS_SUCCESS;
        
    case L3_L2_CONNECT:
        MTP2_DEBUG(("MTP2:::: CONNECT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_EMERGENCY;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 CONNECT  failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }

        return (ITS_SUCCESS);
        
        
    case L3_L2_DISCONNECT:
        MTP2_DEBUG(("MTP2:::: DISCONNECT for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));
#if 0
        strioctl.ic_cmd = LIO_STOP;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 DISCONNECT failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
#endif
    
        return (ITS_SUCCESS);
        

    case L3_L2_LOCAL_PROCESSOR_OUT:
        MTP2_DEBUG(("MTP2:::: LPO for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_SET_LPO;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 LPO failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }

        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_REC:
        MTP2_DEBUG(("MTP2:::: LPR for linkSet %d linkCode %d nfd %d\n",
                    context->linkSet, linkCode, nfd));

        strioctl.ic_cmd = LIO_CLEAR_LPO;
        strioctl.ic_dp = NULL;
        strioctl.ic_len = 0;
        strioctl.ic_timout = -1;

        ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        if (ret == ADAX_FAILED)
        {
            MTP2_ERROR(("MTP2 LPO failed "
                        "for linkSet %d linkCode %d. error = %d\n",
                        context->linkSet, context->dataLink[nfd].linkCode, errno));

            return (ITS_ENOTFOUND);
        }
    
        return (ITS_SUCCESS);

    default:
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *
 ****************************************************************************/
int
ADAXSendMTP2Event(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;

    if (context->hardware == ADAX_ATMII)
    {
        return SendMTP2Event_ATMII(handle, data, dlen);
    }
    else
    {
        return SendMTP2Event_HDCII(handle, data, dlen);
    }

    /* NOTREACHED */
    /* return ITS_SUCCESS; */
}
 
/*
 ****************************************************************************
 *  Purpose:
 *      Processes the MML command received by the DBC Server
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *      const char*     cmdLine
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
void
ADAX_MTP2_Console(DBC_Server *dbc, const char *cmdLine)
{
    int ret;
    char buf[ITS_PATH_MAX];

    if (DBC_Cmd(dbc, "m2_get_gen_cfg", "MTP2 Get General Config", "<>", "<>"))
    {
        MTP2GeneralCfg *cfg = 0;
        ITS_UINT almLevel;

        cfg =  MTP2_GetGeneralCfg();
        sprintf(buf, "\n********** MTP2 General Config **********\n");
        DBC_AppendText(dbc, buf);

        almLevel = cfg->alarmLevel;

        switch(almLevel)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "\n    Alarm Level:  CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "\n    Alarm Level:  MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "\n    Alarm Level:  MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "\n    Alarm Level:  INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "\n    Alarm Level:  OFF\n");
            break;

            default :
                sprintf(buf, "\n    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);
        strcpy(buf, "\n    MTP2 Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
            if (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL))
            {
                strcpy(buf, "        Critical  = ");
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Critical  = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR))
            {
                strcpy(buf, "        Error     = ");
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Error     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING))
            {
                strcpy(buf, "        Warning   = ");
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Warning   = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG))
            {
                strcpy(buf, "        Debug     = ");
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Debug     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            strcpy(buf, "        Critical  = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Error     = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Warning   = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Debug     = null\n");
            DBC_AppendText(dbc, buf);
        }
        sprintf(buf, "\n********** End of MTP2 General Config **********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_set_gen_cfg", "MTP2 Set General Config",
                     "<alarm level> <Trace Type> <traceOutput> <On/Off>",""))
    {
        MTP2GeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_set_gen_cfg <alarmlevel> <tracetype>"
                         " <trOutput> <On/Off>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL ||
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") ||
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") ||
                 strstr(alarmLevel, "info"))
           {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") ||
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "\nInvalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, MTP2_CRITICAL_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, MTP2_ERROR_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, MTP2_WARNING_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, MTP2_DEBUG_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, MTP2_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, MTP2_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, MTP2_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MTP2_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "\n********** MTP2 General Config Set **********\n");
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_get_gen_peg", "Get MTP2 General Pegs", "<Pegid>", "<>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_OCTET pegId;
        ITS_UINT value;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf,  "\n********** Invalid Command Arguments **********\n"
                           "Usage: m2_get_gen_peg [<Peg Id> or <All/all>]\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        if(strncmp(pgName, "All", 3) == 0 ||
           strncmp(pgName, "all", 3) == 0 ||
           atoi(pgName) == ALL_MTP2_PEGS)
        {
           MTP2_GetOm_MML_CCITT(dbc);
           DumpGeneralPegs(dbc);
           return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n********** Unrecognized Peg **********\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pegId = atoi(pgName);

        if (pegId >= PEG_ADAX_MTP2_NUM_GLOBAL_PEGS)
        {
            sprintf(buf, "\n********** Invalid Peg Type **********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n   %s \n", mtp2GPegStr[pegId]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(ADAX_MTP2_Pegs, pegId);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "m2_get_gen_pegids", "Get all MTP2 General Peg Ids", "<>", "<>"))
    {
        DumpGeneralPegIds(dbc);
    }
#endif

    else if (DBC_Cmd(dbc, "m2_clr_gen_peg", "Clear MTP2 General Pegs", "<Pegid>", "<>"))
    {
           char pegType[ITS_PATH_MAX];
        ITS_OCTET pegId;

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_clr_gen_peg [<Peg Id> or <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0 ||
           atoi(pegType) == ALL_MTP2_PEGS)
        {
           MTP2_ResetOm_MML_CCITT();

           for (pegId = 0; pegId < PEG_ADAX_MTP2_NUM_GLOBAL_PEGS; pegId++)
           {
               PEG_ClearPeg(ADAX_MTP2_Pegs, pegId);
           }

           sprintf(buf, "\n** Cleared all MTP2 general pegs **\n");
           DBC_AppendText(dbc, buf);
           return;
        }
        else
        {
           if(!isdigit((int)pegType[0]))
           {
              sprintf(buf, "\n********** Unrecognized Peg **********\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        if (atoi(pegType) >= PEG_ADAX_MTP2_NUM_GLOBAL_PEGS)
        {
             sprintf(buf, "\n** MTP2 general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
        }

        PEG_ClearPeg(ADAX_MTP2_Pegs, atoi(pegType));

        sprintf(buf, "\n********** Cleared MTP2 general peg id %d **********\n", atoi(pegType));
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_get_all_link_pegs", "Get MTP2 Link Pegs", "<linkset> <linkcode>", "<>"))
    {
        ITS_INT linkSet, linkCode;
        ITS_OCTET i;
        ITS_INT nfd = -1;
        struct strioctl strioctl;
        SSCOP_STATS sstats;
        SSCF_LMFAULTS sfaults;
        SS7_LinkPtr ln;
        TRANSPORT_Control *tc;
        SS7TRAN_Manager *ss7;
        ITS_SS7_CONTEXT *context;
        VENDOR_Instance *inst;
        mtp2_stat_param_t linkPegs;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_get_all_link_pegs <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n*** Link %d on link set %d is not configured ***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        tc = TRANSPORT_FindTransport(ln->id);

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
            {
                nfd = i;
                break;
            }
        }
        
        if (nfd == -1)
        {
            sprintf(buf, "\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */
            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        } 
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        } 

        if (ret == ADAX_FAILED)
        {
            sprintf(buf, "\n** Error while getting link pegs **\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            if (context->hardware == ADAX_ATMII)
            {
                memset(&linkPegs, 0, sizeof(linkPegs));    
                linkPegs.num_msu_rx            = sstats.sdu_icount;
                linkPegs.num_sif_sio_octet_rx  = sstats.sdu_ibytes;
                linkPegs.num_msu_tx            = sstats.sdu_ocount;
                linkPegs.num_sif_sio_octet_tx  = sstats.sdu_obytes;
                linkPegs.num_msu_rtx           = sstats.retrans_count;
                linkPegs.num_octet_rtx         = sstats.retrans_bytes;

                linkPegs.sl_failure_all_reason  = sfaults.sl_fail_all;
                linkPegs.sl_failure_t2t3_expiry = sfaults.sl_fail_no_resp;
                linkPegs.sl_failure_suerm       = sfaults.sl_fail_err_rate;
                linkPegs.sl_cong_too_long       = sfaults.sl_fail_cong;
                linkPegs.sl_prov_algn_failed    = sfaults.sl_fail_align;
                linkPegs.num_su_error         = sfaults.sl_error_v;
            }

            DumpLinkPegs(dbc, linkSet, linkCode, &linkPegs);
        }
    }
    else if (DBC_Cmd(dbc, "m2_clr_all_link_pegs", "Clear MTP2 Link Pegs", "<linkset> <linkcode>", "<>"))
    {
        ITS_INT linkSet, linkCode;
        ITS_OCTET i;
        ITS_INT nfd = -1;
        struct strioctl strioctl;
        SSCOP_STATS sstats;
        SSCF_LMFAULTS sfaults;
        SS7_LinkPtr ln;
        TRANSPORT_Control *tc;
        SS7TRAN_Manager *ss7;
        ITS_SS7_CONTEXT *context;
        VENDOR_Instance *inst;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_clr_all_link_pegs <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n*** Link %d on link set %d is not configured ***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        tc = TRANSPORT_FindTransport(ln->id);

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            sprintf(buf, "\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }
       
        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        } 
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

        }

        if (ret == ADAX_FAILED)
        {
            sprintf(buf, "\n** Error while clearing link pegs **\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            sprintf(buf, "\n********** Cleared MTP2 link pegs for  **********\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n    Linkset:%d  Linkcode:%d \n", linkCode, linkSet);
            DBC_AppendText(dbc, buf);
        }
    }
}

/*
 ****************************************************************************
 *  Purpose:
 *      Gets the MTP2 Alarms and Trace levels
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      MTP2GeneralCfg*     cfg
 ****************************************************************************/
MTP2GeneralCfg*
MTP2_GetGeneralCfg()
{
       MTP2GeneralCfg *cfg;

    cfg = calloc(1, sizeof(MTP2GeneralCfg));
    if (cfg == NULL)
    {
        return (NULL);
    }
    cfg->traceOn = (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 0) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 1) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 2))) ||
                   (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 0) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 1) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 2))) ||
                   (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 0) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 1) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 2))) ||
                   (TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 0) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 1) ||
                     TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 2)));

    cfg->alarmLevel = MTP2_AlarmLevel;

    return (cfg);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Sets the MTP2 Alarms and Trace levels
 *
 *  Input Parameters:
 *      MTP2GeneralCfg*     cfg
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
int
MTP2_SetGeneralCfg(MTP2GeneralCfg* cfg)
{
    if(MTP2_ADAX_TraceData == NULL)
    {
      return !ITS_SUCCESS;
    }

    MTP2_AlarmLevel = cfg->alarmLevel;

    if (strstr(cfg->traceType, "all") != NULL)
    {
        if (cfg->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      MTP2_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       cfg->traceOutput, ITS_FALSE);
        }
    }
    else
    {
       if (cfg->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       cfg->traceType,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      cfg->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       cfg->traceType,
                                       cfg->traceOutput, ITS_FALSE);
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData,
                                      cfg->traceType, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 General Pegs
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 ****************************************************************************/
static void
DumpGeneralPegs(DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "\n********** Printing Global Pegs **********\n");
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_GET_DATA_FAILED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SEND_DATA_FAILED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_DOWN),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_UP),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_DOWN),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_UP),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_STAT_IND),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SUERM_EXPIRY),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_INCORRECT_FIB_BSN),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_DETECTED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_RECOVERED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_TX),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_TX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_RX),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T2_EXPIRED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T2_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T6_EXPIRED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T6_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T7_EXPIRED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T7_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T1_EXPIRED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T1_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T3_EXPIRED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T3_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_CONG_DETECTED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%30s:              value %d\n",
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_CONG_RECOVERED),
                    PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 General Peg Ids
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
static void
DumpGeneralPegIds(DBC_Server *dbc)
{
        char buf[32000];

    memset(buf , 0, 32000);

    sprintf(buf, "\n********** Printing Global Peg Ids **********\n");
    DBC_AppendText(dbc, buf);

    /* Print the pegs and their assciated Id's */
    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_GET_DATA_FAILED),
                PEG_MTP2_GET_DATA_FAILED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SEND_DATA_FAILED),
                PEG_MTP2_SEND_DATA_FAILED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_DOWN),
                PEG_MTP2_LOCAL_PROC_DOWN,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_UP),
                PEG_MTP2_LOCAL_PROC_UP,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_DOWN),
                PEG_MTP2_REMOTE_PROC_DOWN,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_UP),
                PEG_MTP2_REMOTE_PROC_UP,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_STAT_IND),
                PEG_MTP2_STAT_IND,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SUERM_EXPIRY),
                PEG_MTP2_SUERM_EXPIRY,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY));

    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_INCORRECT_FIB_BSN),
                PEG_MTP2_INCORRECT_FIB_BSN,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_DETECTED),
                PEG_MTP2_CONG_DETECTED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_RECOVERED),
                PEG_MTP2_CONG_RECOVERED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_TX),
                PEG_MTP2_MSU_TX,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_TX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_RX),
                PEG_MTP2_MSU_RX,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T2_EXPIRED),
                PEG_MTP2_T2_EXPIRED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T2_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T6_EXPIRED),
                PEG_MTP2_T6_EXPIRED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T6_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T7_EXPIRED),
                PEG_MTP2_T7_EXPIRED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T7_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T1_EXPIRED),
                PEG_MTP2_T1_EXPIRED,
               PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T1_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T3_EXPIRED),
                PEG_MTP2_T3_EXPIRED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T3_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_CONG_DETECTED),
                PEG_MTP2_REMOTE_CONG_DETECTED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n",
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_CONG_RECOVERED),
                PEG_MTP2_REMOTE_CONG_RECOVERED,
                PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 Link Pegs
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 ****************************************************************************/
static void
DumpLinkPegs(DBC_Server *dbc, ITS_OCTET linkSet,
             ITS_OCTET linkCode, mtp2_stat_param_t *linkPegs)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "\n********** Printing Link Pegs for **********\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n    Linkset:%d  Linkcode:%d \n", linkSet, linkCode);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_FAIL_ALL_REASON),
                    linkPegs->sl_failure_all_reason);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SUERM_EXPIRY),
                    linkPegs->sl_failure_suerm);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_INCORRECT_FIB_BSN),
                    linkPegs->sl_failure_abnormal_fib_bsnr);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_T6_EXPIRED),
                    linkPegs->sl_cong_too_long);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_T7_EXPIRED),
                    linkPegs->sl_failure_t7_expiry);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_PROV_ALIGN_FAILED),
                    linkPegs->sl_prov_algn_failed);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_ERR_SU),
                    linkPegs->num_su_error);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_NEG_ACK),
                    linkPegs->num_neg_ack);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_MSU_TX),
                    linkPegs->num_msu_tx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_MSU_RX),
                    linkPegs->num_msu_rx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIF_SIO_OCTET_TX),
                    linkPegs->num_sif_sio_octet_tx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIF_SIO_OCTET_RX),
                    linkPegs->num_sif_sio_octet_rx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_OCTET_RTX),
                    linkPegs->num_octet_rtx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_MSU_RTX),
                    linkPegs->num_msu_rtx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_T2_T3_EXPIRED),
                    linkPegs->sl_failure_t2t3_expiry);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIB_TX),
                    linkPegs->num_sib_tx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %d\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIB_RX),
                    linkPegs->num_sib_rx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}


/****************************************************************************
 *  Purpose:
 *      Gets the MTP2 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralCfg*    genCfg
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetGeneralCfg(MTP2_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)MTP2_AlarmLevel;

    genCfg->debugTrace = TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG);
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING);
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR);
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL);
    if (genCfg->criticalTrace)
    {
       genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP2 General config
 *
 *  Input Parameters:
 *      MTP2_GeneralCfg*    genCfg
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_SetGeneralCfg(MTP2_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    MTP2_AlarmLevel = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_DEBUG_STRING,  ITS_TRUE);

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_DEBUG_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_WARNING_STRING,  ITS_TRUE);

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_WARNING_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_ERROR_STRING,  ITS_TRUE);

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_ERROR_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_CRITICAL_STRING,  ITS_TRUE);

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }

        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_ADAX_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_ADAX_TraceData, MTP2_CRITICAL_STRING,  ITS_FALSE);
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the MTP2 General pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralPegs*   genPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetGeneralPegs(MTP2_GeneralPegs* genPegs)
{
    if (genPegs == NULL)
        return ITS_ENOMEM;

    genPegs->getDataFailed      = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);
    genPegs->sendDataFailed     = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);
    genPegs->localProcDown      = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN);
    genPegs->localProcUp        = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP);
    genPegs->remoteProcDown     = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN);
    genPegs->remoteProcUp       = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP);
    genPegs->statInd            = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_STAT_IND);
    genPegs->suermExpiry        = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY);
    genPegs->incorrectFibBsn    = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN);
    genPegs->congDetected       = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_DETECTED);
    genPegs->congRecovered      = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED);
    genPegs->msuTx              = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_TX);
    genPegs->msuRx              = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_MSU_RX);
    genPegs->t2Expired          = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T2_EXPIRED);
    genPegs->t6Expired          = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T6_EXPIRED);
    genPegs->t7Expired          = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T7_EXPIRED);
    genPegs->t1Expired          = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T1_EXPIRED);
    genPegs->t3Expired          = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_T3_EXPIRED);
    genPegs->remoteCongDetected = PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_DETECTED);
    genPegs->remoteCongRecovered= PEG_GetPeg(ADAX_MTP2_Pegs, PEG_MTP2_REMOTE_CONG_RECOVERED);

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the specified or all MTP2 General pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralPegs*   genPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_ClearGeneralPeg(ITS_UINT pegId)
{
    if (pegId == MTP2_ALL_PEGS)
    {
        PEG_ClearBlock(ADAX_MTP2_Pegs);
    }
    else
    {
        if (pegId >= PEG_ADAX_MTP2_NUM_GLOBAL_PEGS)
        {
            MTP2_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(ADAX_MTP2_Pegs, pegId);
        }
    }

    MTP2_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the MTP2 Link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      MTP2_LinkPegs*  linkPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetLinkPegs(ITS_OCTET linkSet, ITS_OCTET linkCode, MTP2_LinkPegs* linkPegs)
{
    int ret;
    ITS_OCTET i;
    ITS_INT nfd = -1;
    struct strioctl strioctl;
    SSCOP_STATS sstats;
    SSCF_LMFAULTS sfaults;
    SS7_LinkPtr ln;
    TRANSPORT_Control *tc;
    SS7TRAN_Manager *ss7;
    ITS_SS7_CONTEXT *context;
    VENDOR_Instance *inst;
    mtp2_stat_param_t lnPegs;

    if (linkPegs == NULL)
        return ITS_ENOMEM;

    if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
    {
        MTP2_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    tc = TRANSPORT_FindTransport(ln->id);
    if (tc == NULL)
    {
        MTP2_ERROR(("Transport %d not found\n", ln->id));
        return ITS_ENOTFOUND;
    }

    ss7 = (SS7TRAN_Manager *)tc;
    inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
    context = (ITS_SS7_CONTEXT *)inst;

    for (i = 0; i < context->numTimeslots; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            nfd = i;
            break;
        }
    }
        
    if (nfd == -1)
    {
        MTP2_ERROR(("Invalid linkset/linkcode\n"));
        return ITS_ENOTFOUND;
    }

    if (context->hardware == ADAX_ATMII)
    { 
            ITS_UINT clear = 0; /* don't clear stats */
            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

    } 
    else
    {
        strioctl.ic_cmd = MTP2COUNTS;
        strioctl.ic_dp = (ITS_CHAR *)&lnPegs;
        strioctl.ic_len = sizeof(lnPegs);
        strioctl.ic_timout = -1;
    }

    ret = ioctl(context->fd[nfd], I_STR, &strioctl);
    if (ret == ADAX_FAILED)
    {
        MTP2_ERROR(("Adax command failed\n", ln->id));
        return ITS_ESENDFAIL;
    }
    else
    {
        if (context->hardware == ADAX_ATMII)
        {
            linkPegs->linkFailure       = sfaults.sl_fail_all;
            linkPegs->suermExpiry       = sfaults.sl_fail_err_rate;
            linkPegs->incorrectFibBsn   = 0 ;
            linkPegs->t6Expired         = sfaults.sl_fail_cong;
            linkPegs->t7Expired         = 0;
            linkPegs->provingFailed     = sfaults.sl_fail_align;
            linkPegs->errSU             = sfaults.sl_error_v;
            linkPegs->negAck            = 0;
            linkPegs->msuTx             = sstats.sdu_ocount;
            linkPegs->msuRx             = sstats.sdu_icount;
            linkPegs->sifSioOctetRx     = sstats.sdu_ibytes; 
            linkPegs->sifSioOctetTx     = sstats.sdu_obytes;
            linkPegs->octetRtx          = sstats.retrans_count;
            linkPegs->msuRtx            = sstats.retrans_bytes;
            linkPegs->t2t3Expired       = sfaults.sl_fail_no_resp;
            linkPegs->sibTx             = 0;
            linkPegs->sibRx             = 0;

        }
        else
        {
            linkPegs->linkFailure       = lnPegs.sl_failure_all_reason;
            linkPegs->suermExpiry       = lnPegs.sl_failure_suerm;
            linkPegs->incorrectFibBsn   = lnPegs.sl_failure_abnormal_fib_bsnr;
            linkPegs->t6Expired         = lnPegs.sl_cong_too_long;
            linkPegs->t7Expired         = lnPegs.sl_failure_t7_expiry;
            linkPegs->provingFailed     = lnPegs.sl_prov_algn_failed;
            linkPegs->errSU             = lnPegs.num_su_error;
            linkPegs->negAck            = lnPegs.num_neg_ack;
            linkPegs->msuTx             = lnPegs.num_msu_tx;
            linkPegs->msuRx             = lnPegs.num_msu_rx;
            linkPegs->sifSioOctetRx     = lnPegs.num_sif_sio_octet_tx;
            linkPegs->sifSioOctetTx     = lnPegs.num_sif_sio_octet_rx;
            linkPegs->octetRtx          = lnPegs.num_octet_rtx;
            linkPegs->msuRtx            = lnPegs.num_msu_rtx;
            linkPegs->t2t3Expired       = lnPegs.sl_failure_t2t3_expiry;
            linkPegs->sibTx             = lnPegs.num_sib_tx;
            linkPegs->sibRx             = lnPegs.num_sib_rx;
        }

        return ITS_SUCCESS;
    }
}

/****************************************************************************
 *  Purpose:
 *      Clears all the MTP2 Link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_ClearLinkPegs(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_OCTET i;
    ITS_INT nfd = -1;
    struct strioctl strioctl;
    SS7_LinkPtr ln;
    TRANSPORT_Control *tc;
    SS7TRAN_Manager *ss7;
    ITS_SS7_CONTEXT *context;
    VENDOR_Instance *inst;
    int ret;

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP2_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    tc = TRANSPORT_FindTransport(ln->id);
    if (tc == NULL)
    {
        MTP2_ERROR(("Transport %d not found\n", ln->id));
        return ITS_ENOTFOUND;
    }

    ss7 = (SS7TRAN_Manager *)tc;
    inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
    context = (ITS_SS7_CONTEXT *)inst;

    for (i = 0; i < context->numTimeslots; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            nfd = i;
            break;
        }
    }

    if (nfd == -1)
    {
        MTP2_ERROR(("Invalid linkset/linkcode\n"));
        return ITS_ENOTFOUND;
    }

    strioctl.ic_cmd = MTP2ZERO;
    strioctl.ic_dp = NULL;
    strioctl.ic_len = 0;
    strioctl.ic_timout = -1;

    ret = ioctl(context->fd[nfd], I_STR, &strioctl);
    if (ret == ADAX_FAILED)
    {
        MTP2_ERROR(("Adax command failed\n", ln->id));
        return ITS_ESENDFAIL;
    }
    else
    {
        MTP2_DEBUG(("Pegs cleared for linkset %d linkcode %d\n", linkSet, linkCode));
        return ITS_SUCCESS;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the configuration in the XML file.
 *
 *  Input Parameters:
 *      FILE* fp - File Pointer to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 * Mani        05-05-2005  BugId:1793
 *
 *  See Also:
 ****************************************************************************/


int 
ADAXCommit(FILE* fp)
{
    fprintf(fp, "\t\t<ADAX-MTP2>\n");
    
    if (MTP2_ADAX_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<VendorTrace>\n");
        if (TRACE_IsLevelOn(MTP2_ADAX_TraceData,
            MTP2_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_ADAX_TraceData,
            MTP2_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_ADAX_TraceData,
            MTP2_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_ADAX_TraceData,
            MTP2_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_ADAX_TraceData,
                MTP2_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</VendorTrace>\n");
    }
    
    fprintf(fp, "\t\t</ADAX-MTP2>\n\n");

    return ITS_SUCCESS;
}

/* rtn: cells_to_atmf_rate
 * inputs:
 *          cellrate: rate in cells per second.
 * returns:
 *          16-bit Floating ATM Forum Rate Format
 */
unsigned short cells_to_atmf_rate(unsigned int cellrate)
{
unsigned int i, arate, e, m;

        i = 1;
        e = 0x1F;  /* 0x1F is NZ bit of exponent - 1 */
        if (!cellrate)
                return(0);
        do
                {
                i <<= 1;
                e += 1;
                }
        while (i <= cellrate);

        i >>= 1; /* Get exponent part value */
        m = (512 * (cellrate - i))/i;
        arate = (e << 9) + m;
        arate = arate & 0xffff;

        return(arate);
}

/* rtn: atmii_create_aal5_setvc_opts
 * Inputs:
 *
 * atmii_setvc_opts_t *opts,  -- Pointer to atmii_setvc_opts_t to fill out.
 * unsigned int vc,           -- VPI/VCI in little endian format
 * unsigned int traffic_class,-- one of ATMF traffic class defines above.
 * unsigned int PCR,          -- Peak Cell Rate (1/PCR,ABR,VBR) in cells/sec
 * unsigned int MCR_SCR,      -- Minimum Cell Rate (ABR)/
 *                            -- Sustainable Cell Rate (VBR) in cells/sec
 * unsigned int MBS,          -- Max Burst Size (VBR) in cells
 * unsigned int ICR,          -- Initial Cell Rate (ABR) in cells/sec
 * unsigned short RDF,        -- Rate Decrease Factor (ABR),-LOG2 power of 2
 * unsigned short RIF,        -- Rate Increase Factor (ABR),-LOG2 power of 2
 * unsigned short CDF,        -- Cutoff Decrease Factor (ABR), 1+ -LOG2
 * unsigned short priority,   -- Relative Tx Priority of this VC, 0 is highest
 *                               3 is the lowest.
 * unsigned int maxframe,     -- Maximum frame size acceptable for
 *                               receive PDUs, usually MAX_AAL5_FRAME
 * unsigned int buff_class    -- receive buffer class, 0 to 3
 *
 * Returns:
 *   >0  Error.  Value indicates error type
 *   0   Success.
 */
static int atmii_create_aal5_setvc_opts(atmii_setvc_opts_t *opts,
                                 unsigned int vc,
                                 unsigned int traffic_class,
                                 unsigned int PCR,
                                 unsigned int MCR_SCR,
                                 unsigned int MBS,
                                 unsigned int ICR,
                                 unsigned short RDF,
                                 unsigned short RIF,
                                 unsigned short CDF,
                                 unsigned short priority,
                                 unsigned int maxframe,
                                 unsigned int buff_class)
{
aal5_opts_t *aal5p;

        /* Zero the structure initially */
        memset(opts, 0, sizeof(atmii_setvc_opts_t));

        /* No checking is done of the VPI/VCI.
         * It should be specified in Little Endian format.
         */
        opts->vpi_vci = vc;
        opts->reserved = 0;

        aal5p = &opts->cfg.aal5cfg;

        /* Check the VC Priority */
        if (priority > 3)
                return(1);

        /* Check Traffic Class type */
        if (traffic_class >= ATMF_AAL50_BAD)
                return(2);

        /* Check Maximum Frame Size */
        if ( (maxframe == 0) || (maxframe > MAX_AAL5_FRAME) )
                return(3);

        aal5p->maxSDU_aal_pri_traf = (maxframe << 16) |
                                     (priority << 8) |
                                     (traffic_class << 4);

        /* Check Buffer Class */
        if ( buff_class > 3 )
                return(4);

        aal5p->buffer_class = buff_class;

        /* AAL5 supports 1/PCI, VBR or ABR type connections */

        /* If 1/PCR we only care about the PCR,
         * if VBR we only care about the PCR, SCR, and MBS,
         * for ABR connections we care about everything
         */

        /* The minimum rate is 62.5 cells per second,
         * Max is 353208 cells per second (OC-3), 4528 (E1), or 3622 (T1) */
        if ( (PCR < 63) || (PCR > 353208) )
                return(5);
        aal5p->pcr = cells_to_atmf_rate(PCR);

        /* If this is a 1/PCR connection, everything else is 0,
         * so just return */
        if (traffic_class == ATMF_AAL50_1PCR)
                return(0);

        /* Check VBR parameters */

        /* The minimum rate is 62.5 cells per second,
         * Max is 353208 cells per second (OC-3), 4528 (E1), or 3622 (T1) */
        if ( (MCR_SCR < 63) || (MCR_SCR > 353208) )
                return(6);

        aal5p->mcr_scr = cells_to_atmf_rate(MCR_SCR);

        /* Check Max Burst Size, Max 255 Min 1, specified in cells */
        if ( ((traffic_class == ATMF_AAL50_VBR) && (MBS == 0)) || (MBS > 255) )
                return(7);

        aal5p->mbs = MBS;

        /* We're done if VBR... */
        if (traffic_class == ATMF_AAL50_VBR)
                return(0);

        /* Check ABR parameters */

        /* The minimum rate is 62.5 cells per second,
         * Max is 353208 cells per second (OC-3), 4528 (E1), or 3622 (T1) */
        if ( (ICR < 63) || (ICR > 353208) )
                return(8);

        aal5p->icr = cells_to_atmf_rate(ICR);

        /* Max is 15 == 1/32,768, min is 0 == 1 */
        if (RDF > 15)
                return(9);
        /* Max is 15 == 1/32,768, min is 0 == 1 */
        if (RIF > 15)
                return(10);
        /* Max is 7 == 1/64 min is 0 == no CDF */
        if (CDF > 7)
                return(11);

        aal5p->rdf_rif_cdf = (RDF << 8) | (RIF << 4) | (CDF);

        return(0);
}



/****************************************************************************
 *  Purpose:
 *      This API is invoked by the MTP3 SubDAP, whenever the OM Duration
 *      timer is started. 
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void 
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0030 - D0100       
 *                                D0260 - D0300
 *
 ****************************************************************************/
#if defined(CCITT)
void MTP2_ResetOm_CCITT()
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear Active MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize (&mtp2LinkOmImage[omBuf.activeOm]);
 
  /* Loop through all the configured Links in the system and
     clear the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_ITU)
      {
         continue;
      }
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);
        
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
              MTP2_DEBUG(("MTP2 PM-Reset not possible for Internode Link %d Linkset %d\n", 
		      linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;
        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
      }
    }
  }
}
#endif

#if defined (TTC)
void MTP2_ResetOm_TTC()
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear Active MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize (&mtp2LinkOmImage[omBuf.activeOm]);
 
  /* Loop through all the configured Links in the system and
     clear the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_JAPAN)
      {
         continue;
      }
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);
        
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Reset not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;
        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
      }
    }
  }
}
#endif

#if defined (PRC)
void MTP2_ResetOm_PRC()
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear Active MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize (&mtp2LinkOmImage[omBuf.activeOm]);
 
  /* Loop through all the configured Links in the system and
     clear the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_CHINA)
      {
         continue;
      }
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);
        
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Reset not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;
        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
      }
    }
  }
}
#endif

#if defined (ANSI)
void MTP2_ResetOm_ANSI()
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear Active MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize (&mtp2LinkOmImage[omBuf.activeOm]);
 
  /* Loop through all the configured Links in the system and
     clear the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_ANSI)
      {
         continue;
      }  
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);
        
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Reset not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;
        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
      }
    }
  }
}
#endif

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the MTP3 SubDAP, whenever the OM Duration
 *      timer expires. 
 *
 *  Input Parameters:
 *      OAM Statistics Structure 
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0030 - D0100
 *                                D0260 - D0300
 *
 ****************************************************************************/
#if defined (CCITT)
void MTP2_GetOm_CCITT(mtp2Om *OmMtp2Data)
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear the OAM Statistics structure before filling it */
  memset(OmMtp2Data, 0, sizeof(mtp2Om));

  OmMtp2Data->family = FAMILY_ITU;
  /* Clear the Inactive MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize(&mtp2LinkOmImage[omBuf.inactiveOm]);

  /* Toggle ACTIVE/INACTIVE MTP2 Link Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Loop through all the configured Links in the system and
     collect the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j < ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if(ls->family != FAMILY_ITU)
      {
         continue;
      }
  
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        nfd = -1;
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        /* Since MTP2 related information is not maintained for Internode Links,
           we should not perform the OM Collection for the Internode Links */
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Get not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            continue;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
        else
        {
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkset = linkset;
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkcode = linkcode;

          if (context->hardware == ADAX_ATMII)
          {
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx            = sstats.sdu_icount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx  = sstats.sdu_ibytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx            = sstats.sdu_ocount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx  = sstats.sdu_obytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx         = sstats.retrans_bytes;

              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason  = sfaults.sl_fail_all;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm       = sfaults.sl_fail_err_rate;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long       = sfaults.sl_fail_cong;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed    = sfaults.sl_fail_align;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error           = sfaults.sl_error_v;
          }
          else
          {
              memcpy(&mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], &linkPegs, sizeof(mtp2_stat_param_t));
          }

          /* Copy the content from the Inactive Buffer to the OAM Buffer */
          memcpy(&OmMtp2Data->hdr[OmMtp2Data->count], 
               &mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode], sizeof(mtp2_ls_ln));
          memcpy(&OmMtp2Data->stats[OmMtp2Data->count], 
               &mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], sizeof(mtp2_stat_param_t));
          OmMtp2Data->count++; 
        }
      }
    }
  }
}
#endif



#if defined (TTC)
void MTP2_GetOm_TTC(mtp2Om *OmMtp2Data)
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear the OAM Statistics structure before filling it */
  memset(OmMtp2Data, 0, sizeof(mtp2Om));
  OmMtp2Data->family = FAMILY_JAPAN;
  /* Clear the Inactive MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize(&mtp2LinkOmImage[omBuf.inactiveOm]);

  /* Toggle ACTIVE/INACTIVE MTP2 Link Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Loop through all the configured Links in the system and
     collect the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_JAPAN)
      {
          continue;
      }
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        nfd = -1;
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        /* Since MTP2 related information is not maintained for Internode Links,
           we should not perform the OM Collection for the Internode Links */
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Get not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            continue;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
        else
        {
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkset = linkset;
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkcode = linkcode;

          if (context->hardware == ADAX_ATMII)
          {
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx            = sstats.sdu_icount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx  = sstats.sdu_ibytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx            = sstats.sdu_ocount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx  = sstats.sdu_obytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx         = sstats.retrans_bytes;

              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason  = sfaults.sl_fail_all;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm       = sfaults.sl_fail_err_rate;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long       = sfaults.sl_fail_cong;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed    = sfaults.sl_fail_align;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error           = sfaults.sl_error_v;
          }
          else
          {
              memcpy(&mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], &linkPegs, sizeof(mtp2_stat_param_t));
          }

          /* Copy the content from the Inactive Buffer to the OAM Buffer */
          memcpy(&OmMtp2Data->hdr[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode], sizeof(mtp2_ls_ln));
          memcpy(&OmMtp2Data->stats[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], sizeof(mtp2_stat_param_t));
          OmMtp2Data->count++; 
        }
      }
    }
  }
}
#endif
 
#if defined(PRC)
void MTP2_GetOm_PRC(mtp2Om *OmMtp2Data)
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear the OAM Statistics structure before filling it */
  memset(OmMtp2Data, 0, sizeof(mtp2Om));
  OmMtp2Data->family = FAMILY_CHINA; 
  /* Clear the Inactive MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize(&mtp2LinkOmImage[omBuf.inactiveOm]);

  /* Toggle ACTIVE/INACTIVE MTP2 Link Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Loop through all the configured Links in the system and
     collect the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_CHINA)
      {
          continue;
      }

      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        nfd = -1;
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        /* Since MTP2 related information is not maintained for Internode Links,
           we should not perform the OM Collection for the Internode Links */
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Get not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            continue;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
        else
        {
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkset = linkset;
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkcode = linkcode;

          if (context->hardware == ADAX_ATMII)
          {
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx            = sstats.sdu_icount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx  = sstats.sdu_ibytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx            = sstats.sdu_ocount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx  = sstats.sdu_obytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx         = sstats.retrans_bytes;

              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason  = sfaults.sl_fail_all;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm       = sfaults.sl_fail_err_rate;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long       = sfaults.sl_fail_cong;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed    = sfaults.sl_fail_align;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error           = sfaults.sl_error_v;
          }
          else
          {
              memcpy(&mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], &linkPegs, sizeof(mtp2_stat_param_t));
          }

          /* Copy the content from the Inactive Buffer to the OAM Buffer */
          memcpy(&OmMtp2Data->hdr[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode], sizeof(mtp2_ls_ln));
          memcpy(&OmMtp2Data->stats[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], sizeof(mtp2_stat_param_t));
          OmMtp2Data->count++; 
        }
      }
    }
  }
}
#endif

#if defined (ANSI)
void MTP2_GetOm_ANSI(mtp2Om *OmMtp2Data)
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear the OAM Statistics structure before filling it */
  memset(OmMtp2Data, 0, sizeof(mtp2Om));

  OmMtp2Data->family = FAMILY_ANSI;
  /* Clear the Inactive MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize(&mtp2LinkOmImage[omBuf.inactiveOm]);

  /* Toggle ACTIVE/INACTIVE MTP2 Link Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Loop through all the configured Links in the system and
     collect the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      if (ls->family != FAMILY_ANSI)
      {
          continue;
      }
 
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        nfd = -1;
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        /* Since MTP2 related information is not maintained for Internode Links,
           we should not perform the OM Collection for the Internode Links */
        if(NULL == tc) continue;

        if((strcmp(tc->transport.name, "MTP3 InterNode ITU") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode TTC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode PRC") == 0) ||
           (strcmp(tc->transport.name, "MTP3 InterNode ANSI") == 0))
        {
          MTP2_DEBUG(("MTP2 PM-Get not possible for Internode Link %d Linkset %d\n", linkcode, linkset));
          continue;
        }

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        if(NULL == context) continue;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            continue;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
        else
        {
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkset = linkset;
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkcode = linkcode;

          if (context->hardware == ADAX_ATMII)
          {
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx            = sstats.sdu_icount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx  = sstats.sdu_ibytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx            = sstats.sdu_ocount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx  = sstats.sdu_obytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx         = sstats.retrans_bytes;

              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason  = sfaults.sl_fail_all;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm       = sfaults.sl_fail_err_rate;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long       = sfaults.sl_fail_cong;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed    = sfaults.sl_fail_align;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error           = sfaults.sl_error_v;
          }
          else
          {
              memcpy(&mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], &linkPegs, sizeof(mtp2_stat_param_t));
          }

          /* Copy the content from the Inactive Buffer to the OAM Buffer */
          memcpy(&OmMtp2Data->hdr[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode], sizeof(mtp2_ls_ln));
          memcpy(&OmMtp2Data->stats[OmMtp2Data->count], 
              &mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], sizeof(mtp2_stat_param_t));
          OmMtp2Data->count++; 
        }
      }
    }
  }
}
#endif

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the mi_clr_gen_peg MML Command. 
 *
 *                 !!! WARNING WARNING WARNING !!! 
 *   This function should not be invoked, when the OAM
 *   duration timer is running.  If this function is called
 *   when the OAM duration timer is running, there will be
 *   inconsistent MTP2 OM values.
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0030 - D0100
 *                                D0260 - D0300
 *
 ****************************************************************************/
void MTP2_ResetOm_MML_CCITT()
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;

  /* Clear Active MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize (&mtp2LinkOmImage[omBuf.activeOm]);

  /* Loop through all the configured Links in the system and
     clear the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j <= ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 1; /*clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2ZERO;
            strioctl.ic_dp = NULL;
            strioctl.ic_len = 0;
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
      }
    }
  }
}

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the m2_get_gen_peg MML command.
 *
 *                 !!! WARNING WARNING WARNING !!!
 *   This function should not be invoked, when the OAM
 *   duration timer is running.  If this function is called
 *   when the OAM duration timer is running, there will be
 *   inconsistent MTP2 OM values.
 * 
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0030 - D0100
 *                                D0260 - D0300
 *
 ****************************************************************************/
void MTP2_GetOm_MML_CCITT(DBC_Server *dbc)
{
  struct strioctl strioctl;
  SSCOP_STATS sstats;
  SSCF_LMFAULTS sfaults;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  TRANSPORT_Control *tc;
  SS7TRAN_Manager *ss7;
  ITS_SS7_CONTEXT *context;
  VENDOR_Instance *inst;
  mtp2_stat_param_t linkPegs;
  int ret;
  ITS_OCTET linkset, linkcode, i, j, k;
  ITS_INT nfd = -1;
  char buffer[200];

  /* Clear the Inactive MTP2 Link OM Buffer */
  MTP2LinkOmDataInitialize(&mtp2LinkOmImage[omBuf.inactiveOm]);

  /* Toggle ACTIVE/INACTIVE MTP2 Link Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Print the contents properly in the Debug Console */

  sprintf(buffer, "\n          ****** Q752 MTP2 Measurements ******\n");
  DBC_AppendText(dbc, buffer);

  sprintf(buffer, "    ------------------------------------------------\n");
  DBC_AppendText(dbc, buffer);

  /* Loop through all the configured Links in the system and
     collect the MTP Level 2 OMs from the ADAX Card */

  for(j = 1; j < ITS_SS7_DEFAULT_LINK_SET; j++)
  {
    if((ls = LINKSET_FindLinkSetNoLock(j)) != NULL)
    {
      linkset = ls->linkSet;

      for(k = 0; k < ls->numLinks; k++)
      {
        ln = ls->links[k];

        linkcode = ln->linkCode;

        tc = TRANSPORT_FindTransport(ln->id);

        ss7 = (SS7TRAN_Manager *)tc;
        inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
        context = (ITS_SS7_CONTEXT *)inst;

        for (i = 0; i < context->numTimeslots; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkcode)
            {
                nfd = i;
                break;
            }
        }

        if (nfd == -1)
        {
            MTP2_ERROR(("\n*** Invalid Linkset %d Linkcode %d ***\n",
                           linkset, linkcode));
            return;
        }

        if (context->hardware == ADAX_ATMII)
        {
            ITS_UINT clear = 0; /* don't clear stats */

            *(ITS_UINT *) &sstats = clear;
            strioctl.ic_cmd = LIO_STAT;
            strioctl.ic_dp = (ITS_CHAR *)&sstats;
            strioctl.ic_len = sizeof(sstats);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);

            *(ITS_UINT *) &sfaults = clear;
            strioctl.ic_cmd = LIO_GLMFAULTS;
            strioctl.ic_dp = (ITS_CHAR *)&sfaults;
            strioctl.ic_len = sizeof(sfaults);
            strioctl.ic_timout = -1;
            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }
        else
        {
            strioctl.ic_cmd = MTP2COUNTS;
            strioctl.ic_dp = (ITS_CHAR *)&linkPegs;
            strioctl.ic_len = sizeof(linkPegs);
            strioctl.ic_timout = -1;

            ret = ioctl(context->fd[nfd], I_STR, &strioctl);
        }

        if (ret == ADAX_FAILED)
        {
            return;
        }
        else
        {
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkset = linkset;
          mtp2LinkOmImage[omBuf.inactiveOm].mtp2Hdr[linkset][linkcode].linkcode = linkcode;

          if (context->hardware == ADAX_ATMII)
          {
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx            = sstats.sdu_icount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx  = sstats.sdu_ibytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx            = sstats.sdu_ocount;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx  = sstats.sdu_obytes;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx         = sstats.retrans_bytes;

              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason  = sfaults.sl_fail_all;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm       = sfaults.sl_fail_err_rate;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long       = sfaults.sl_fail_cong;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed    = sfaults.sl_fail_align;
              mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error           = sfaults.sl_error_v;
          }
          else
          {
              memcpy(&mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode], &linkPegs, sizeof(mtp2_stat_param_t));
          }

          sprintf(buffer, "\n Link Set                        : %d", linkset);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Code                       : %d", linkcode);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - All Reason       : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_all_reason);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - Abnormal FIB/BSN : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_abnormal_fib_bsnr);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - T7 Expiry        : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_t7_expiry);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - Congestion       : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_cong_too_long);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - SUERM            : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_failure_suerm);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Link Failure - Proving/Alignment: %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].sl_prov_algn_failed);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n SU Error Count                  : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_su_error);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Negative Acknowledgement        : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_neg_ack);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n Octets Retransmit Count         : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_octet_rtx);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n SIF/SIO Octets Tx Count         : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_tx);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n SIF/SIO Octets Rx Count         : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_sif_sio_octet_rx);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n MSU Transmit Count              : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_tx);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n MSU Receive Count               : %d", mtp2LinkOmImage[omBuf.inactiveOm].statData[linkset][linkcode].num_msu_rx);
          DBC_AppendText(dbc, buffer);

          sprintf(buffer, "\n");
          DBC_AppendText(dbc, buffer);
        }
      }
    }
  }
}

/****************************************************************************
 *  Purpose:
 *      This function clears the MTP2 OM Buffer.
 *
 *  Input Parameters:
 *      MTP2 Statistics structure  
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0030 - D0100
 *                                D0260 - D0300
 *
 ****************************************************************************/

void MTP2LinkOmDataInitialize(mtp2_stat_table *mtp2_om_data_ptr)
{
  memset (mtp2_om_data_ptr, 0, sizeof(mtp2_stat_table));
}
