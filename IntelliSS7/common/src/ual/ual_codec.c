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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: ual_codec.c,v 9.6.54.1 2014/12/15 09:44:24 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_codec.c,v $
 *  LOG: Revision 9.6.54.1  2014/12/15 09:44:24  jkchaitanya
 *  LOG: changes for crash fix in mml command for asp state for bug 5392
 *  LOG:
 *  LOG: Revision 9.6  2008/06/29 15:15:52  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.5  2008/06/20 10:44:28  mshanmugam
 *  LOG: Accelero CGI Phase I: Added new alarms for Encode/Decode failure
 *  LOG:
 *  LOG: Revision 9.4  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.3.2.3  2007/05/23 10:31:31  pspl
 *  LOG: (PSPL, abhijeet) added VARIABLE_FIXED_LEN_CHECK to take care of multiple values
 *  LOG:                  fixed length fields (viz. affected_PC, RoutingContexts)
 *  LOG:
 *  LOG: Revision 9.3.2.2  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.3.2.1  2007/04/26 06:56:24  pspl
 *  LOG: PL, abhijeet)
 *  LOG: - added definitions for msg param validation functions
 *  LOG:   and corresponding data (UAL_CheckParamLength() and UAL_CheckParam())
 *  LOG: - Changed the decodeMSg() to use the param validation functions
 *  LOG:
 *  LOG: Revision 9.3  2005/12/08 03:36:17  clin
 *  LOG: fix bug #2482 and trace text.
 *  LOG:
 *  LOG: Revision 9.2  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:18  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.14.1.4.1  2004/12/15 13:11:16  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.1.14.1  2004/10/06 08:37:24  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
 *  LOG:
 *  LOG: Revision 6.1  2002/05/13 20:30:42  lbana
 *  LOG: uals in current starts from here...
 *  LOG:
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <its.h>

#include <its_ual.h>

#include <its_sockets.h>
#include <its_transports.h>
#include <its_trace.h>
#include <its_sctp_trans.h>

#include <ual_intern.h>


/*
This Array of structure is used to verify the Length of all the M3UA Parameters.
The array is made exactly like RFC 3332 Section: 3.2 Common/Specific Parameter List.
such that Values can be access directly by Parameter Id as INDEX.
*/
ParamLenCheckStruct paramLenCheck[]
               = {
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {MAX_LEN_CHECK,   PARAM_MAX_LENGTH},     /*UAL_PRM_INFO_STR*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {VARIABLE_FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_ROUT_CTX*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_DIAGNOSTIC*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_HEARTBEAT_DATA*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_TRAFFIC_MODE*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_ERROR_CODE*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_STATUS*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_ASP_ID*/
                  {VARIABLE_FIXED_LEN_CHECK, PARAM_FIXED_LENGTH}, /*UAL_PRM_AFFECTED_PC*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*Correlation ID*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_NET_APP*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*User/Cause*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*Congestion Indication*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*Concerned Destination*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_ROUTING_KEY*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_REG_RES*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_DREG_RES*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_LRK_ID*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*UAL_PRM_DPC*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_SI*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_OPC_LIST*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*UAL_PRM_CIC_RANGE*/
                  {BUFFER_OVERFLOW_CHECK, PARAM_NOT_USED}, /*Protocol DATA*/
                  {NOT_USED_CHECK,  PARAM_NOT_USED},
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH},   /*RM_REG_STATUS*/
                  {FIXED_LEN_CHECK, PARAM_FIXED_LENGTH}    /*UAL_PRM_DREG_STATUS*/
                 };
                                                                                   
/*
 * ASPUP 
 */
 
static ITS_USHORT    aspupOArgs[] =
{
    UAL_PRM_ASP_ID,  
    UAL_PRM_INFO_STR
};


UALDLLAPI 
UAL_MSG_DESC UAL_ASPUP_Desc =
{
    NULL, 0,
    aspupOArgs, sizeof(aspupOArgs) / sizeof(ITS_USHORT)
};


/*
 * UPACK 
 */
 
static ITS_USHORT    upackOArgs[] =
{
    UAL_PRM_INFO_STR
};


UALDLLAPI 
UAL_MSG_DESC UAL_UPACK_Desc =
{
    NULL, 0,
    upackOArgs, sizeof(upackOArgs) / sizeof(ITS_USHORT)
};


/*
 * ASPDN 
 */
 
static ITS_USHORT    aspdnOArgs[] =
{
    UAL_PRM_INFO_STR
};


UALDLLAPI 
UAL_MSG_DESC UAL_ASPDN_Desc =
{
    NULL, 0,
    aspdnOArgs, sizeof(aspdnOArgs) / sizeof(ITS_USHORT)
};


/*
 * DNACK 
 */
 
static ITS_USHORT    dnackOArgs[] =
{
   UAL_PRM_INFO_STR
};


UALDLLAPI 
UAL_MSG_DESC UAL_DNACK_Desc =
{
    NULL, 0,
    dnackOArgs, sizeof(dnackOArgs) / sizeof(ITS_USHORT)
};


/* 
 * HEARBEAT 
 */

static ITS_USHORT    beatOArgs[] =
{
   UAL_PRM_HEARTBEAT_DATA
};

UALDLLAPI 
UAL_MSG_DESC UAL_HEARTBEAT_Desc =
{
    NULL, 0,
    beatOArgs, sizeof(beatOArgs) / sizeof(ITS_USHORT)
};



/* 
 * HEARBEAT ACK
 */
static ITS_USHORT    beatackOArgs[] =
{
   UAL_PRM_HEARTBEAT_DATA
};

UALDLLAPI 
UAL_MSG_DESC UAL_HEARTBEAT_ACK_Desc =
{
    NULL, 0,
    beatackOArgs, sizeof(beatackOArgs) / sizeof(ITS_USHORT)
};



/*
 * ASPAC 
 */
static ITS_USHORT    aspacOArgs[] =
{
    UAL_PRM_TRAFFIC_MODE,
    UAL_PRM_ROUT_CTX,
    UAL_PRM_INFO_STR,
    SUA_PRM_DRN_LABEL,
    SUA_PRM_TID_LABEL
};

UALDLLAPI 
UAL_MSG_DESC UAL_ASPAC_Desc =
{
    NULL, 0,
    aspacOArgs, sizeof(aspacOArgs) / sizeof(ITS_USHORT)
};


/*
 * ASPAC_ACK 
 */
static ITS_USHORT    aspac_ackOArgs[] =
{
    UAL_PRM_TRAFFIC_MODE,
    UAL_PRM_ROUT_CTX,
    UAL_PRM_INFO_STR
};


UALDLLAPI 
UAL_MSG_DESC UAL_ASPAC_ACK_Desc =
{
    NULL, 0,
    aspac_ackOArgs, sizeof(aspac_ackOArgs) / sizeof(ITS_USHORT)
};


/*
 * ASPIA 
 */
static ITS_USHORT    aspiaOArgs[] =
{
   UAL_PRM_ROUT_CTX,
   UAL_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_ASPIA_Desc =
{
    NULL, 0,
    aspiaOArgs, sizeof(aspiaOArgs) / sizeof(ITS_USHORT)
};


/*
 * ASPIA_ACK 
 */

static ITS_USHORT    aspia_ackOArgs[] =
{
   UAL_PRM_TRAFFIC_MODE,
   UAL_PRM_ROUT_CTX,
   UAL_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_ASPIA_ACK_Desc =
{
    NULL, 0,
    aspia_ackOArgs, sizeof(aspia_ackOArgs) / sizeof(ITS_USHORT)
};

/*
 * NTFY 
 */
static ITS_USHORT    ntfyMArgs[] =
{
    UAL_PRM_STATUS
};

static ITS_USHORT    ntfyOArgs[] =
{
    UAL_PRM_ASP_ID,
    UAL_PRM_ROUT_CTX,
    UAL_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_NTFY_Desc =
{
    ntfyMArgs, sizeof(ntfyMArgs) / sizeof(ITS_USHORT),
    ntfyOArgs, sizeof(ntfyOArgs) / sizeof(ITS_USHORT)
};


/*
 * ERR 
 */
static ITS_USHORT    errMArgs[] =
{
    UAL_PRM_ERROR_CODE
};

static ITS_USHORT    errOArgs[] =
{
    UAL_PRM_DIAGNOSTIC,
    UAL_PRM_ROUT_CTX,
    UAL_PRM_NET_APP,
    UAL_PRM_AFFECTED_PC
};

UALDLLAPI 
UAL_MSG_DESC UAL_ERR_Desc =
{
    errMArgs, sizeof(errMArgs) / sizeof(ITS_USHORT),
    errOArgs, sizeof(errOArgs) / sizeof(ITS_USHORT)
};


/*
 * Dynamic registration messages
 */
UALDLLAPI 
extern UAL_MSG_DESC UAL_DREGRES_Desc;

/* 
 * REGREQ
 */
static ITS_USHORT    regreqMArgs[] = 
{
    UAL_PRM_ROUTING_KEY
};

UALDLLAPI 
UAL_MSG_DESC UAL_REGREQ_Desc = 
{
    regreqMArgs, sizeof(regreqMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};


static ITS_USHORT    suaregreqMArgs[] = 
{
    SUA_PRM_RKEY
};

static ITS_USHORT    suaregreqOArgs[] = 
{
    SUA_PRM_ASP_CAPAB
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_REGREQ_Desc = 
{
    suaregreqMArgs, sizeof(suaregreqMArgs) / sizeof(ITS_USHORT),
    suaregreqOArgs, sizeof(suaregreqOArgs) / sizeof(ITS_USHORT),
};


/*
 * REGRSP
 */
static ITS_USHORT    regrspMArgs[] =
{
    UAL_PRM_REG_RES
};

UALDLLAPI 
UAL_MSG_DESC UAL_REGRSP_Desc =
{
    regrspMArgs, sizeof(regrspMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};

static ITS_USHORT    suaregrspMArgs[] =
{
    SUA_PRM_REG_RES
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_REGRSP_Desc =
{
    suaregrspMArgs, sizeof(suaregrspMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};


/*
 * DEREGREQ
 */
static ITS_USHORT   dregreqMArgs[] =
{
    UAL_PRM_ROUT_CTX
};

UALDLLAPI 
UAL_MSG_DESC UAL_DREGREQ_Desc =
{
    dregreqMArgs, sizeof(dregreqMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};

/*
 * DREGRSP
 */
static ITS_USHORT   dregrspMArgs[] =
{
    UAL_PRM_DREG_RES
};

UALDLLAPI 
UAL_MSG_DESC UAL_DREGRSP_Desc =
{
    dregrspMArgs, sizeof(dregrspMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};


/*
 * SS7 signaling network management messages
 */

/*
 *** DUNA ***
 * This message corresponds to the SCCP: SSP
 */
static ITS_USHORT    suadunaMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    suadunaOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_DUNA_Desc =
{
    suadunaMArgs, sizeof(suadunaMArgs) / sizeof(ITS_USHORT),
    suadunaOArgs, sizeof(suadunaOArgs) / sizeof(ITS_USHORT)
};


/*
 *** DAVA ***
 * This message corresponds to the SCCP: SSA
 */
static ITS_USHORT    suadavaMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    suadavaOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_DAVA_Desc =
{
    suadavaMArgs, sizeof(suadavaMArgs) / sizeof(ITS_USHORT),
    suadavaOArgs, sizeof(suadavaOArgs) / sizeof(ITS_USHORT)
};


/*
 *** DAUD ***
 * This message corresponds to the SCCP: SST
 */
static ITS_USHORT    suadaudMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    suadaudOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_DAUD_Desc =
{
    suadaudMArgs, sizeof(suadaudMArgs) / sizeof(ITS_USHORT),
    suadaudOArgs, sizeof(suadaudOArgs) / sizeof(ITS_USHORT)
};



/*
 *** SCON ***
 */

static ITS_USHORT    suasconMArgs[] =
{
    SUA_PRM_CONG_LEVEL,
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    suasconOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};

UALDLLAPI 
UAL_MSG_DESC UAL_SUA_SCON_Desc =
{
    suasconMArgs, sizeof(suasconMArgs) / sizeof(ITS_USHORT),
    suasconOArgs, sizeof(suasconOArgs) / sizeof(ITS_USHORT)
};



int
UAL_GetPadding(int size)
{
    if ((size % 4) == 0)
    {
        return 0;
    }
    else
    {
        return 4 - (size % 4);
    }
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that prints aUAL IE element.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      IE - pointer to theUAL_IE to be displayed.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
UAL_PrintUAL_IES(ITS_UAL_IE *IE)
{
    if (IE != NULL)
    {
        int i;

        printf("------------UAL_IE Begin ------------\n");
        printf("Prarmeter Type: 0x%04x \n", IE->param_id);
        printf("Parameter len : 0x%04x \n", IE->param_length);

        for (i = 0; i < IE->param_length; i++)
        {
            printf("0x%02x ", *((unsigned char *)&(IE->param_data) + i));
        }
        printf("\n------------UAL_IE End ------------\n");
    }
    else
    {
        printf("IE * is NULL \n");
    }

    return;
}




/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that find aUAL IE element.
 *     
 *  Input Parameters:
 *      ies - pointer to th first element of an array of ITS_UAL_IE
 *      ieCount - Number of ies in the array
 *      paramId - ie Id of the searched IE
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to the IE if found, else NULL
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_UAL_IE*
UAL_FindUALIE(ITS_UAL_IE *ies, int ieCount, ITS_USHORT paramId)
{
    int i;
    
    for (i=0; i < ieCount; i++)
    {
        if (ies[i].param_id == paramId)
        {
            return &ies[i];
        }
    }

    return NULL;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change the common message header from host
 *      to network format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
UAL_HComHdrToN(UAL_MSG_HDR *msgHdr)
{
    msgHdr->msgLen = SOCK_HToNL(msgHdr->msgLen);

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to convert the common message header from
 *      network to host format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
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
 *
 ******************************************************************************/
void
UAL_NComHdrToH(UAL_MSG_HDR *msgHdr)
{

    msgHdr->msgLen = SOCK_NToHL(msgHdr->msgLen);

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_UAL_IE array to the network 
 *      format
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 *
 ******************************************************************************/
void
UAL_HUALIESToN(ITS_UAL_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case UAL_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_HToNL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case UAL_PRM_TRAFFIC_MODE:

            ies[i].param_data.trafMode.tm = 
                           SOCK_HToNL(ies[i].param_data.trafMode.tm);

            break;           

        case UAL_PRM_ERROR_CODE:

            ies[i].param_data.errCode.eCode = 
                              SOCK_HToNL(ies[i].param_data.errCode.eCode);

            break;           

        case UAL_PRM_STATUS:

            ies[i].param_data.statusType.id = 
                              SOCK_HToNS(ies[i].param_data.statusType.id);

            ies[i].param_data.statusType.type = 
                              SOCK_HToNS(ies[i].param_data.statusType.type);

            break;

        case UAL_PRM_REG_STATUS:

            ies[i].param_data.regStat.regStat = 
                            SOCK_HToNL(ies[i].param_data.regStat.regStat);

            break;

        case UAL_PRM_DREG_STATUS:

            ies[i].param_data.deregStat.deregStat = 
                            SOCK_HToNL(ies[i].param_data.deregStat.deregStat);

            break;

        case UAL_PRM_LRK_ID:

            ies[i].param_data.localRkId.localRKid = 
                            SOCK_HToNL(ies[i].param_data.localRkId.localRKid);
            
            break;


        case UAL_PRM_ASP_ID:

            ies[i].param_data.aspId.aspId = 
                              SOCK_HToNL(ies[i].param_data.aspId.aspId);

            break;
        }
    }

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_UAL_IE array to the HOST 
 *      format.
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 *
 ******************************************************************************/
void
UAL_NUALIESToH(ITS_UAL_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case UAL_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_NToHL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case UAL_PRM_TRAFFIC_MODE:

            ies[i].param_data.trafMode.tm = 
                           SOCK_NToHL(ies[i].param_data.trafMode.tm);

            break;           

        case UAL_PRM_ERROR_CODE:

            ies[i].param_data.errCode.eCode = 
                              SOCK_NToHL(ies[i].param_data.errCode.eCode);

            break;           

        case UAL_PRM_STATUS:

            ies[i].param_data.statusType.id = 
                              SOCK_NToHS(ies[i].param_data.statusType.id);

            ies[i].param_data.statusType.type = 
                              SOCK_NToHS(ies[i].param_data.statusType.type);

            break;

        case UAL_PRM_REG_STATUS:

            ies[i].param_data.regStat.regStat = 
                            SOCK_NToHL(ies[i].param_data.regStat.regStat);

            break;

        case UAL_PRM_DREG_STATUS:

            ies[i].param_data.deregStat.deregStat = 
                            SOCK_NToHL(ies[i].param_data.deregStat.deregStat);

            break;

        case UAL_PRM_LRK_ID:

            ies[i].param_data.localRkId.localRKid = 
                            SOCK_NToHL(ies[i].param_data.localRkId.localRKid);
            
            break;


        case UAL_PRM_ASP_ID:

            ies[i].param_data.aspId.aspId = 
                              SOCK_NToHL(ies[i].param_data.aspId.aspId);

            break;
        
        }
    }

    return;
}




/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to encode aUAL message from a given array of
 *     UAL IES.
 *     
 *  Input Parameters:
 *      ies - pointer to the first element of IES array (common msg header).
 *      ieCount - number of IES in the array.
 *      desc - pointer toUAL message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      event - pointer to ITS_EVENT containing the builtUAL message.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_EncodeMsg(ITS_UAL_IE *ies, int ieCount,ITS_EVENT *event,
              UAL_MSG_DESC* desc)
{
    int i, j, offset, evoffset;
    ITS_UAL_IE* ieRef[ITS_MAX_UAL_IES];
    ITS_USHORT *margs = desc->mParam;
    int nmargs = desc->nmParam;
    ITS_USHORT *oargs = desc->oParam;
    int noargs = desc->noParam;
    ITS_USHORT len = 0, padding = 0;
    ITS_BOOLEAN sawOpt = ITS_FALSE;

    assert(event != NULL);

    /* sanity */
    if (ieCount > ITS_MAX_UAL_IES)
    {
        UAL_Alarm(4053,  __FILE__, __LINE__, NULL);

        return (ITS_EOVERFLOW);
    }
     

     /* change the params to network format */
    UAL_HUALIESToN(ies, ieCount);

    /* 
     * The first step is to use a temporary array of IES* to
     * store ptrs to the message parameters in the following order
     * - the common header
     * - the madatory parameters
     * - the optional parameters if any
     * In the meanwhile we can check if all mandatory parameters are 
     * present for sanity purposes
     */

    /*
     * The first IE int the array should be the common message header
     * this is common to all UAL messages
     */
    if(ies[0].param_id !=UAL_PRM_MSG_HDR)
    {
        UAL_Alarm(4053,  __FILE__, __LINE__, NULL);

        return (ITS_EINVALIDARGS);
    }

    ieRef[0] = ies;

    /* start at one, 0 is the common msg header */
    offset = 1;

    /* find the mandatory parameters */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 1; j < ieCount; j++) /* we can start at 1, 0 is message header */
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            UAL_Alarm(4053,  __FILE__, __LINE__, NULL);

            return (ITS_EMISSMAND);
        }
    }
    
    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                sawOpt = ITS_TRUE;
                break;
            }
        }
        /* if missing, that's ok */
    } 

    /* skip extras */
    while (offset <= ieCount)   /* we use <= because of the common 
                                   message header offset starts at 1 */
    {
        ieRef[offset] = NULL;
        offset++;
    }

    evoffset = sizeof(UAL_MSG_HDR);

    /* copy in the mandatories */
    for (i = 1; i <= nmargs; i++)
    {
        /* cpy param id */
        ieRef[i]->param_id = SOCK_HToNS(ieRef[i]->param_id);

        memcpy(&event->data[evoffset], &ieRef[i]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i]->param_length;
        padding =UAL_GetPadding(len);
        ieRef[i]->param_length = SOCK_HToNS((ITS_USHORT)(len + 4));

        memcpy(&event->data[evoffset], &ieRef[i]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;

        memset(&event->data[evoffset], 0, (len + padding)); 
        memcpy(&event->data[evoffset], &ieRef[i]->param_data, len);
  
        evoffset += (len + padding);
    }

    /* copy in the optionals */

    for (i = 1; i <= noargs; i++)
    {
        if (ieRef[i + nmargs] == NULL )
        {
            break;
        }

        /* cpy param id */
        ieRef[i + nmargs]->param_id = SOCK_HToNS(ieRef[i+nmargs]->param_id);


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i+nmargs]->param_length;
        padding =UAL_GetPadding(len);
        ieRef[i + nmargs]->param_length = 
                                 SOCK_HToNS((ITS_USHORT)(len + 4));


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;


        memset(&event->data[evoffset], 0, (len + padding));
        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_data, len);
            
        evoffset += (len + padding);
    }

    /* set final length */
    event->len = evoffset;

    /* take care of the message length */
    ieRef[0]->param_data.msgHeader.msgLen = SOCK_HToNL(event->len);

    /* copy in the message header with updated message pointers */
    memcpy(&event->data[0], &ieRef[0]->param_data, sizeof(UAL_MSG_HDR));

    /* WHAT ABOUT THE EVENT SOURCE -> left to the user to fill in */

    return (ITS_SUCCESS);

}

UALDLLAPI ITS_BOOLEAN
UAL_CheckParamLength(ITS_INT paramId,ITS_INT paramLen)
{
    ITS_BOOLEAN retVal = ITS_TRUE;
    ITS_INT checkType,checkVal;
    ITS_INT paramIndex = paramId;

    /*if parameter is not common parameter */
    if(paramIndex > LAST_COMMON_PARAM_IDX)
    {  
        /*
         * Subtracting the difrence between Common params and Specific Params 
         * so that we can directly map parameter id to INDEX in array.
         */
        paramIndex -= COM_SPEC_PARAM_INDEX_DIFF;

        if(paramIndex > ( sizeof(paramLenCheck) / (sizeof(ITS_INT) + sizeof(ParamLenCheckTypes)) ))
        {
            return ITS_FALSE;
        }
    }
       
    checkType = paramLenCheck[paramIndex].checkType;
    checkVal =  paramLenCheck[paramIndex].checkVal;
    
    switch(checkType)
    {
        case FIXED_LEN_CHECK:
        {
            if(paramLen!=checkVal)
            {
                retVal = ITS_FALSE;
            }
            break;
        }
        case VARIABLE_FIXED_LEN_CHECK:
        {
            if(paramLen%checkVal)
            {
                retVal = ITS_FALSE;
            }
            break;
        }
        case MAX_LEN_CHECK:
        {
            if(paramLen > checkVal ||  paramLen < 0)
            {
                retVal = ITS_FALSE;
            }
            break;
        }
        case BUFFER_OVERFLOW_CHECK:
        {    
            /*
	     * Note(PSPL): Note sure what do for these params, 
	     * so skipping it for the time being
	     */
            break;
        }
        case NOT_USED_CHECK:
        default:
        {
            retVal = ITS_FALSE;
        }
    }
    return retVal;
}



ITS_INT
UAL_CheckParam(ITS_USHORT param_id, UAL_MSG_DESC *desc)
{
    ITS_INT i=0;

    /*check for Mandatory Parameter*/
    for(i=0; i < desc->nmParam; i++)
    {
        if(desc->mParam[i] == param_id)
        {
            return MANDATORY_PARAMETER;
        }
    }
    /*check for Optional Parameter*/
    for(i=0; i < desc->noParam; i++)
    {
        if(desc->oParam[i] == param_id)
        {
            return OPTIONAL_PARAMETER;
        }
    }

    /*If Parameter id not matches to Mandatory and Optional*/
    return PARAMETER_NOT_FOUND;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to decode aUAL message to an array ofUAL IES.
 *     
 *  Input Parameters:
 *      ev - pointer to ITS_EVENT containing theUAL message to be decoded.
 *      desc - pointer to the message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      ies - pointer to the array of IES where the message is decoded.
 *      ieCount - number of decode IES in the array.
 *
 *  Return Value:
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *      This function is used internally that is not directly by the user.
 *
 *  See Also:
 *     UAL_EncodeMsg().
 *
 ******************************************************************************/
int
UAL_DecodeMsg(ITS_UAL_IE *ies, int *ieCount, ITS_EVENT *ev,
             UAL_MSG_DESC *desc)
{
    ITS_USHORT msgLen = ev->len;
    int evOffset = 0;
    ITS_UAL_IE *ieRef = ies;

    /* to check madetory and optional parameters */
    ITS_INT mParamCount=0,oParamCount=0;
    ITS_INT retVal = 0;

    *ieCount = 0;
   
    /* take care of the common msg header */
    ies[0].param_id =UAL_PRM_MSG_HDR;
    ies[0].param_length = sizeof(UAL_MSG_HDR);
    
    memcpy(&ies[0].param_data.msgHeader, &ev->data[evOffset],
           sizeof(UAL_MSG_HDR));
    UAL_NComHdrToH(&ies[0].param_data.msgHeader);

    (*ieCount)++;
    ies++;
    evOffset += sizeof(UAL_MSG_HDR);
    
    /* Getting all Parametrs from event buffer */ 
    while (evOffset < msgLen)
    {
        ies[0].param_id = ev->data[evOffset] << 8 |
                          ev->data[evOffset + 1];
        evOffset += 2;

        /* Check if parameter is valid for this message type and Update check list */
        retVal = UAL_CheckParam(ies[0].param_id,desc);
        if(retVal == MANDATORY_PARAMETER)
        {
            mParamCount++; 
        }
        else 
        if(retVal == OPTIONAL_PARAMETER)
        {
	    oParamCount++;
        }
	else
        {
            UAL_ERROR(("Unexpected Parameter=%0x:  Message dropped\n",(ies[0].param_id)));
            UAL_Alarm(4054,  __FILE__, __LINE__, NULL);
            return (UAL_ERR_UNEXP_PARAM);
        }

        ies[0].param_length = (ev->data[evOffset] << 8 |
                               ev->data[evOffset + 1]) -4 ;
        evOffset += 2;

        /*check for valid Parameter length*/
        if(UAL_CheckParamLength(ies[0].param_id,ies[0].param_length) == ITS_FALSE)
        {
            UAL_ERROR(("Invalid Parameter Length for ParamID=%0x: : Message dropped\n",ies[0].param_id));
            return (UAL_ERR_PARM_FIELD_ERR);
        }
         
        if ((ies[0].param_length < msgLen) && (evOffset < ev->len))
        {
            memcpy(&ies[0].param_data, &ev->data[evOffset],
            ies[0].param_length);
            evOffset += ies[0].param_length + UAL_GetPadding(ies[0].param_length);

            (*ieCount)++;
 
            if (*ieCount > ITS_MAX_UAL_IES)
            {
                UAL_Alarm(4054,  __FILE__, __LINE__, NULL);
                return (ITS_EOVERFLOW);
            }

            ies++;
        }  
        else
        {
            UAL_Alarm(4054,  __FILE__, __LINE__, NULL);
	    return (ITS_EOVERFLOW);
        } 
    }

    if(mParamCount > desc->nmParam)
    {
        /* lets move ahead with unharming extra param, with a warning */
        UAL_WARNING(("One or more mandatory parameter(s) repeated!!"));
    }
    /* check for all the Mandatory Parameters are present */
    else if(mParamCount != desc->nmParam)
    {
        UAL_ERROR(("Mandatory parameter missing: Message dropped\n"));
        UAL_Alarm(4054,  __FILE__, __LINE__, NULL);
        return (UAL_ERR_MISSING_PARAM);   
    }


    /* put the params in the host format */
    UAL_NUALIESToH(ieRef, *ieCount);
    return (ITS_SUCCESS);
}

int
UAL_GetPointCodeValue(UAL_PC pointCode)
{
    ITS_UINT ret = 0;

    /* Find out ITU or other point code */
#if defined (CCITT)
        ret = UAL_GET_PC_VALUE_CCITT(pointCode); 
#elif defined (ANSI)
        ret = UAL_GET_PC_VALUE_ANSI(pointCode);
#elif defined (PRC)
        ret = UAL_GET_PC_VALUE_PRC(pointCode);
#elif defined (TTC)
        ret = UAL_GET_PC_VALUE_TTC(pointCode);
#endif   
    return ret;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_RoutingKeyToRKContext(RK_Context *ctxt, ITS_OCTET *rkData, int dataLen)
{
    int ret = ITS_SUCCESS, offset = 0;
    ITS_UAL_IE ie;
    ITS_USHORT param_id, param_length = 0;
    ITS_BOOLEAN hasDPC, hasOPC, hasSIO, hasCIC, hasTM;

    hasOPC = hasDPC = hasSIO = hasCIC = hasTM = ITS_FALSE;

    ITS_C_ASSERT((ctxt != NULL) && (rkData != NULL));

    /* now decode an populate rinfo */

    while (offset < dataLen)
    {
        param_id = rkData[offset] << 8 | 
                   rkData[offset + 1];
        offset += 2;

        param_length = (rkData[offset] << 8 | 
                        rkData[offset + 1]) - 4;
        offset += 2;
        
        memcpy(&ie.param_data, &rkData[offset], 
               param_length);

        offset += param_length + UAL_GetPadding(param_length);
            
        switch (param_id)
        {
        case UAL_PRM_DPC:

            ctxt->asInfo.dpc = UAL_GetPointCodeValue(ie.param_data.dpc);

            hasDPC = ITS_TRUE;
                
            break;

        case UAL_PRM_LRK_ID:

            ctxt->rCtxt = SOCK_NToHL(ie.param_data.localRkId.localRKid);

            break;

        case UAL_PRM_NET_APP:

            /* TODO */
            ctxt->na.na = ie.param_data.siList.siList[0];

            break;

        case UAL_PRM_SI:

            ctxt->asInfo.criteria.sio = ie.param_data.siList.siList[0];

            hasSIO = ITS_TRUE;

            break;

        case UAL_PRM_OPC_LIST:

            ctxt->asInfo.criteria.opc = 
                        UAL_GetPointCodeValue(ie.param_data.opcList.opcList[0]);

            hasOPC = ITS_TRUE;

            break;

        case UAL_PRM_CIC_RANGE:

            ctxt->asInfo.criteria.opc = 
                    UAL_GetPointCodeValue(ie.param_data.cicList.cicList[0].opc);

            ctxt->asInfo.criteria.range.begin = 
                             SOCK_NToHS(ie.param_data.cicList.cicList[0].loCIC);

            ctxt->asInfo.criteria.range.end = 
                             SOCK_NToHS(ie.param_data.cicList.cicList[0].hiCIC);

            hasCIC = ITS_TRUE;
            hasOPC = ITS_TRUE;

            break;

        case UAL_PRM_TRAFFIC_MODE:

            ctxt->trafficMode = SOCK_NToHL(ie.param_data.trafMode.tm);

            if(!UAL_CheckTMValid(ctxt->trafficMode))
            {
                UAL_ERROR(("Invalid TrafficMode %d \n", ctxt->trafficMode));

                return ITS_EMISSMAND;
            }

            hasTM = ITS_TRUE;

            break;

        default:

            UAL_ERROR(("UAL_DecodeRoutingKey: Unknown param \n"));

            break;
        }
    } 
  
    if (!hasTM)
    {
        UAL_ERROR(("Invalid TrafficMode %d \n", ctxt->trafficMode));

        return ITS_EMISSMAND;
    }

    /* Now figure out the route style */
    if (hasDPC && (!hasOPC) && (!hasSIO) && (!hasCIC))
    {
        ctxt->asInfo.style = ROUTE_DPC_NI;
    }
    else if (hasDPC && hasOPC && (!hasSIO) && (!hasCIC))
    {
        ctxt->asInfo.style = ROUTE_DPC_OPC_NI;
    }
    else if (hasDPC && (!hasOPC) && hasSIO && (!hasCIC))
    {
        ctxt->asInfo.style = ROUTE_DPC_SIO;
    }
    else if (hasDPC && hasOPC && hasSIO && hasCIC)
    {
        ctxt->asInfo.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
    }
    else if (hasDPC && hasSIO && hasOPC)
    {
        ctxt->asInfo.style = ROUTE_DPC_OPC_SIO;
    }
    else
    {
        UAL_ERROR(("Invalid Route Style !!! \n"));

        return ITS_EMISSMAND;
    }

    /* TODO think about this more for other type of routes */
    /* FIXME: May need to get NA  to determine FAMILY */
    ctxt->asInfo.family = FAMILY_ITU;

    return ret;
}


int
UAL_SUA_DecodeAddress(ITS_OCTET *suaAddr, int len, ITS_OCTET *routIndic, 
                  ITS_OCTET *addrIndic, ITS_UINT *pc, ITS_OCTET *ssn, 
                  SUA_GT *gt, int *gtLen)
{
    int ret = ITS_SUCCESS;
    int  offset = 0;
    ITS_USHORT paramId, paramLen;

    *routIndic = suaAddr[1];
    *addrIndic = suaAddr[3];

    offset = 4;

    while (offset < (len - 4))
    {
        paramId = suaAddr[offset] << 8 | 
                  suaAddr[offset + 1];
         
        offset += 2;

        paramLen = (suaAddr[offset] << 8 | 
                    suaAddr[offset + 1]) - 4;

        offset += 2;

        if (paramId == SUA_SPRM_PC)
        {
            SUA_PC suaPC;

            memcpy(&suaPC, &suaAddr[offset], paramLen);

            *pc = SUA_PC_GET_VALUE(suaPC);
        }
        else if (paramId == SUA_SPRM_SSN)
        {
            int localSSN = 0;

            memcpy(&localSSN, &suaAddr[offset], paramLen);

            *ssn = (ITS_OCTET)SOCK_NToHL(localSSN);
        }
        else if (paramId == SUA_SPRM_GT)
        {
            memcpy(gt, &suaAddr[offset], paramLen);

            *gtLen = paramLen;
        }

        offset += paramLen + UAL_GetPadding(paramLen); 

    }
    
    return (ret);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_SuaRoutingKeyToRKContext(RK_Context *ctxt, ITS_OCTET *rkData, int dataLen)
{
    ITS_SUA_IE ies[5];
    ITS_OCTET ieCount = 0;
    ITS_UINT rkid;
    int ret;
    ITS_UINT pc;
    ITS_OCTET ssn;
    ITS_OCTET routIndic, addrIndic;
    SUA_GT     gt;
    int        gtLen, i;
    ITS_BOOLEAN opcPres = ITS_FALSE;

   ret = UAL_DecodeSuaRoutingKey(rkData, dataLen, &rkid, ies, &ieCount);
   
   if (ret != ITS_SUCCESS)
   {
        UAL_ERROR(("UAL_SuaRoutingKeyToRKContex: error  RK Decode"
                         "indentifier, code: %d \n", ret));
        return ret;
   }

    ctxt->rCtxt = rkid;

    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SUA_PRM_LOCAL_RKID :

            break;

            case SUA_PRM_SRC_ADDR :

            ret = UAL_SUA_DecodeAddress(ies[i].param_data.dstAddrs.routIndic, 
                                    ies[i].param_length,
                                    &routIndic, &addrIndic, &pc, &ssn, &gt,
                                    &gtLen);
            if ( ret != ITS_SUCCESS)
            {
                 UAL_ERROR(("UAL_SuaRoutingKeyToRKContex: DstAddr"
                             " decode failed"));
                 return !ITS_SUCCESS;
            }

            if (addrIndic == SUA_CPA_HAS_PC_MASK)
            {
                ctxt->asInfo.criteria.opc = pc;
                opcPres = ITS_TRUE;
            }

            break;

            case SUA_PRM_DST_ADDR :

            ret = UAL_SUA_DecodeAddress(ies[i].param_data.dstAddrs.routIndic, 
                                    ies[i].param_length,
                                    &routIndic, &addrIndic, &pc, &ssn, &gt,
                                    &gtLen);

            if ( ret != ITS_SUCCESS)
            {
                 UAL_ERROR(("UAL_SuaRoutingKeyToRKContex: DstAddr"
                             " decode failed"));
                 return !ITS_SUCCESS;
            }

            if ( ((addrIndic & SUA_CPA_HAS_SSN_MASK) == SUA_CPA_HAS_SSN_MASK) &&
                 ((addrIndic & SUA_CPA_HAS_PC_MASK) == SUA_CPA_HAS_PC_MASK) )
            {

                ctxt->asInfo.dpc = pc;
                ctxt->asInfo.criteria.ssn = ssn;
                ctxt->asInfo.criteria.sio = MTP3_SIO_SCCP;
                ctxt->asInfo.style = ROUTE_DPC_SIO_SSN;

            }
            else if (addrIndic == SUA_CPA_HAS_SSN_MASK)
            {

                ctxt->asInfo.criteria.ssn = ssn;
                /* TO DO  might have to send error message*/

            }
            else if (addrIndic == SUA_CPA_HAS_PC_MASK)
            {
                ctxt->asInfo.dpc = pc;
                ctxt->asInfo.style = ROUTE_DPC_SIO;
                ctxt->asInfo.criteria.sio = MTP3_SIO_SCCP;
            }

            break;

            case  SUA_PRM_ADDR_RANG:

            /*TODO */

            break;

            case SUA_PRM_NET_APP :

            /*TODO */

            break;

            case SUA_PRM_ASP_CAPAB :

                memcpy(&ctxt->aspCapab, &ies[i].param_data.capab, 
                       ies[i].param_length);

            break;

            case SUA_PRM_TRAFFIC_MODE :

                ctxt->trafficMode = ies[i].param_data.trafMd.tm;

            break;

            default :

                UAL_ERROR(("UAL_SuaRoutingKeyToRKContex: error  Invalid"
                                 "IE in routing key"));
                return !ITS_SUCCESS;
        }
        
    }

    return ret;
}


int
UAL_RoutingKeyGetLRKID(ITS_OCTET *rkData, int dataLen)
{
    int offset = 0;
    ITS_USHORT param_id = 0, param_length = 0;
    int lrkid = 0;

    ITS_C_ASSERT(rkData != NULL);

    while (offset < dataLen)
    {
        param_id = rkData[offset] << 8 | 
                   rkData[offset + 1];
        offset += 2;

        param_length = (rkData[offset] << 8 | 
                        rkData[offset + 1]) - 4;
        offset += 2;
        
        if (param_id == UAL_PRM_LRK_ID)
        {
            memcpy(&lrkid, rkData, sizeof(ITS_UINT));

            return  SOCK_NToHL(lrkid);
        }
        else
        {
            offset += param_length + UAL_GetPadding(param_length);
        }
    }            

    return lrkid;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_EncodeRoutingKey(UAL_AS_DEF *as, ITS_UAL_IE *ie, ITS_UINT *localRctxt)
{
    int ret = ITS_SUCCESS, ieCount = 0, i = 0;
    ITS_UAL_IE localIEs[ITS_MAX_UAL_IES];
    ITS_UINT localRKId = 0, offset = 0, padding = 0;

    ITS_C_ASSERT((as != NULL) && (ie != NULL));
   
    /* 1) get local RK id and populate IES */
    ret = UAL_AllocateLocalRKId(&localRKId);  /* TODO Race Condition !!! think !!! */
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_EncodeRoutingKey: error allocating local RK "
                         "indentifier, code: %d \n", ret));
        *localRctxt = 0;

        return ret;
    }
    else
    {
        *localRctxt = localRKId;

        localIEs[ieCount].param_id = UAL_PRM_LRK_ID;
        localIEs[ieCount].param_length = sizeof(UAL_LOCAL_RK_ID);
        localRKId = SOCK_HToNL(localRKId);
        localIEs[ieCount].param_data.localRkId.localRKid = localRKId;
        
        ieCount++;
    }

    /* DPC */

    localIEs[ieCount].param_id = UAL_PRM_DPC;
    localIEs[ieCount].param_length = sizeof(UAL_PC);
    memcpy(&localIEs[ieCount].param_data.dpc, &as->dpc, sizeof(UAL_PC));
    
    ieCount++;

    /* traffic Mode mandatory */
    if (as->tm != 0)
    {
        localIEs[ieCount].param_id = UAL_PRM_TRAFFIC_MODE;
        localIEs[ieCount].param_length = sizeof(UAL_TRAFFIC_MODE);
        as->tm = SOCK_HToNL(as->tm);
        localIEs[ieCount].param_data.trafMode.tm = as->tm;
     
        ieCount++;
    }
    else
    {
        UAL_ERROR(("UAL_EncodeRoutingKey: missing Traffic Mode %n"));

        return ITS_EMISSMAND;
    }

    /* Network Apperance */
    if (as->na != 0)
    {
        localIEs[ieCount].param_id = UAL_PRM_NET_APP;
        localIEs[ieCount].param_length = sizeof(UAL_NET_APP);
        as->na = SOCK_HToNL(as->na);
        localIEs[ieCount].param_data.netApp.na = as->na;


        ieCount++;
    }

    /* OPC List */
    if (as->numOPC != 0)
    {
        localIEs[ieCount].param_id = UAL_PRM_OPC_LIST;
        localIEs[ieCount].param_length = (as->numOPC * sizeof(UAL_PC));
        memcpy(&localIEs[ieCount].param_data.opcList.opcList, as->opc.opcList,
               sizeof(localIEs[ieCount].param_length));

        ieCount++;
    }

    /* SIO */
    if (as->numSI != 0)
    {
        localIEs[ieCount].param_id = UAL_PRM_SI;
        localIEs[ieCount].param_length = as->numSI;
        memcpy(&localIEs[ieCount].param_data.siList.siList, as->si.siList,
               localIEs[ieCount].param_length);

        ieCount++;
    }

    /* CIC Range */
    if (as->numCICRange != 0)
    {
        localIEs[ieCount].param_id = UAL_PRM_CIC_RANGE;

        for (i = 0; i < as->numCICRange; i++)
        {
        
            as->cicRange.cicList[i].hiCIC = 
                                     SOCK_HToNS(as->cicRange.cicList[i].hiCIC);
            as->cicRange.cicList[i].loCIC = 
                                     SOCK_HToNS(as->cicRange.cicList[i].loCIC);

            memcpy(&localIEs[ieCount].param_data.cicList.cicList[offset],
                   &as->cicRange, sizeof(UAL_CIC_RANGE));

        }

        ieCount++;
    }

    /* 2) Encode the RK into ie */
    ie->param_id = UAL_PRM_ROUTING_KEY;

    offset = 0;

    for (i = 0; i < ieCount; i++)
    {
        int len;

        /* cpy param id */
        localIEs[i].param_id = SOCK_HToNS(localIEs[i].param_id);

        memcpy(&ie->param_data.rkData.RKData[offset], &localIEs[i].param_id, 
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = localIEs[i].param_length;

        padding = UAL_GetPadding(len);

        localIEs[i].param_length = SOCK_HToNS((ITS_USHORT)(len + 4));

        memcpy(&ie->param_data.rkData.RKData[offset], &localIEs[i].param_length, 
               sizeof(ITS_USHORT));

        offset += 2;

        memset(&ie->param_data.rkData.RKData[offset], 0, (len + padding)); 
        memcpy(&ie->param_data.rkData.RKData[offset], &localIEs[i].param_data,
               len);
  
        offset += (len + padding);
    }
  
    ie->param_length = offset;

    return ret;

}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_EncodeSuaRoutingKey(UAL_AS_DEF *as, ITS_UAL_IE *ie, ITS_UINT *localRctxt)
{
    int addrLen; 
    int offset = 0;
    int padding = 0;
    ITS_USHORT len;
    ITS_USHORT param_id;
    ITS_UINT rkid = 0;
    SUA_ADDRS *srcAddr = as->srcAddr;
    SUA_ADDRS *dstAddr = as->destAddr;
    UAL_RK *rkey = &(ie->param_data.rkData);
    int ret;

    ITS_C_ASSERT((as != NULL) && (ie != NULL));
   
    ret = UAL_AllocateLocalRKId(&rkid);

    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_EncodeSuaRoutingKey: error allocating local RK "
                         "indentifier, code: %d \n", ret));
        *localRctxt = 0;

        return ret;
    }
    else
    {
        *localRctxt = rkid;
    }

    param_id = SUA_PRM_LOCAL_RKID;

    param_id = SOCK_HToNS(param_id);

    memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
    offset += 2;

    /* cpy param len */
    len = 8; 

    len = SOCK_HToNS(len);

    memcpy(&rkey->RKData[offset], &len,
           sizeof(ITS_USHORT));

    offset += 2;
       

    rkid = SOCK_HToNL(rkid);
    memcpy(&rkey->RKData[offset], &rkid,
           sizeof(ITS_UINT));
    offset += 4;

    if (as->tm != 0)
    {
        param_id = SUA_PRM_TRAFFIC_MODE;

        param_id = SOCK_HToNS(param_id);

        memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = 8; 

        len = SOCK_HToNS(len);

        memcpy(&rkey->RKData[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;
       
        as->tm = SOCK_HToNL(as->tm);

        memcpy(&rkey->RKData[offset], &as->tm,
               sizeof(ITS_UINT));
        offset += 4;

    }

    if (as->na != 0)
    {
        param_id = SUA_PRM_NET_APP;

        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = 8; 

        len = SOCK_HToNS(len);

        memcpy(&rkey->RKData[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;
       
        as->na = SOCK_HToNL(as->na);

        memcpy(&rkey->RKData[offset], &as->na,
               sizeof(ITS_UINT));
        offset += 4;

    }

    if (as->aspCapab != 0)
    {
        param_id = SUA_PRM_ASP_CAPAB ;

        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = 8; 

        len = SOCK_HToNS(len);

        memcpy(&rkey->RKData[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;
       
        memcpy(&rkey->RKData[offset], as->aspCapab,
               sizeof(ITS_UINT));
        offset += 4;

    }

    if ( srcAddr != NULL)
    {
        param_id = SUA_PRM_SRC_ADDR;
        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = srcAddr->len + 4; 

        padding = UAL_GetPadding(len);
        len = SOCK_HToNS(len + 4);

        memcpy(&rkey->RKData[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;

        addrLen =  srcAddr->len + 4;

        padding = UAL_GetPadding(addrLen);

        memset(&rkey->RKData[offset], 0, (addrLen + padding));
            
        memcpy(&rkey->RKData[offset], 
               srcAddr->routIndic, 2);
    
        memcpy(&rkey->RKData[offset + 2], 
               srcAddr->addrIndic, 2);

        memcpy(&rkey->RKData[offset + 4], 
               srcAddr->addrData, 
               srcAddr->len);

        offset += (addrLen + padding);           
    }

    if ( dstAddr != NULL)
    {
        param_id = SUA_PRM_DST_ADDR;
        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->RKData[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = dstAddr->len + 4; 

        padding = UAL_GetPadding(len);
        len = SOCK_HToNS(len + 4);

        memcpy(&rkey->RKData[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;

        addrLen =  dstAddr->len + 4;

        padding = UAL_GetPadding(addrLen);

        memset(&rkey->RKData[offset], 0, (addrLen + padding));
            
        memcpy(&rkey->RKData[offset], 
               dstAddr->routIndic, 2);
    
        memcpy(&rkey->RKData[offset + 2], 
               dstAddr->addrIndic, 2);

        memcpy(&rkey->RKData[offset + 4], 
               dstAddr->addrData, 
               dstAddr->len);

        offset += (addrLen + padding);           
    }

    ie->param_id = SUA_PRM_RKEY;
    ie->param_length = offset;

    return ITS_SUCCESS;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_DecodeSuaRoutingKey(ITS_OCTET *rkey, ITS_USHORT rKeyLen,ITS_UINT *rkid,
                        ITS_SUA_IE *ies, ITS_OCTET *ieCount)
{
    int ret = ITS_SUCCESS;
    int  offset = 0;
    ITS_USHORT paramId, paramLen;


    /*memcpy(rkid, &rkey[offset], sizeof(ITS_UINT));

    *rkid = SOCK_NToHL(*rkid);

    offset += 4;*/

    while (offset < (rKeyLen - 4))
    {
        paramId = rkey[offset] << 8 | 
                  rkey[offset + 1];
         
        offset += 2;

        paramLen = (rkey[offset] << 8 | 
                    rkey[offset + 1]) - 4;

        offset += 2;

        switch(paramId)
        {
            case SUA_PRM_LOCAL_RKID :

                memcpy(rkid, &rkey[offset], sizeof(ITS_UINT));

                *rkid = SOCK_NToHL(*rkid);

            break;

            case SUA_PRM_ASP_CAPAB :

                memcpy(&ies[0].param_data.capab, &rkey[offset], 
                       paramLen);

            break;

            case SUA_PRM_TRAFFIC_MODE :

                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            case SUA_PRM_SRC_ADDR :

                memcpy(ies[0].param_data.srcAddrs.routIndic, 
                       &rkey[offset], 2);

                memcpy(ies[0].param_data.srcAddrs.addrIndic, 
                       &rkey[offset + 2], 2);

                memcpy(ies[0].param_data.srcAddrs.addrData,
                       &rkey[offset + 4], paramLen - 4);
            break;

            case SUA_PRM_DST_ADDR :

                memcpy(ies[0].param_data.dstAddrs.routIndic, 
                       &rkey[offset], 2);

                memcpy(ies[0].param_data.dstAddrs.addrIndic, 
                       &rkey[offset + 2], 2);

                memcpy(ies[0].param_data.dstAddrs.addrData,
                       &rkey[offset + 4], paramLen - 4);
            break;

            case SUA_PRM_NET_APP :

                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            case SUA_PRM_ADDR_RANG :

                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            default :

               return !ITS_SUCCESS;
            break;
        }

        offset += paramLen + UAL_GetPadding(paramLen); 

        ies[0].param_id = paramId;

        ies[0].param_length = paramLen;
        
        (*ieCount)++;
    
        if (*ieCount > ITS_MAX_SUA_IES)
        {
            return (ITS_EOVERFLOW);
        }

        ies++;

    }
    
    return (ret);
}




/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int 
UAL_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, ITS_UINT *rkList, 
                         int size)
{
    int ret = ITS_SUCCESS, i;
    ITS_USHORT offset = 0;
    
    if (rkList == NULL)
    {
        *len = 0;
    }
    else
    {
        ITS_UINT var = 0;

        for (i = 0; i<size; i++)
        {
            var = SOCK_HToNL(rkList[i]);
            memcpy(&data[offset], &var, sizeof(ITS_UINT));
            offset += sizeof(ITS_UINT);      
        }

        *len = offset;

    }
    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, ITS_UINT *rkList,
                         int *size)
{
    int ret = ITS_SUCCESS;
    int num = len / sizeof(ITS_UINT);

    *size = 0;

    if (!(len % sizeof(ITS_UINT)) && (num < UAL_MAX_RCTXT_LEN))
    {
        int i;

        for (i = 0; i < num; i++)
        {
            memcpy(&rkList[i], data, sizeof(ITS_UINT));
            rkList[i] = SOCK_NToHL(rkList[i]);
            data += sizeof(ITS_UINT);
            (*size)++;
            printf("rkList[%d] = %d, size = %d",i,rkList[i],size); 
        }
    }
    else
    {
        UAL_Alarm(4055,  __FILE__, __LINE__, NULL);
        return -1;
    }

    return ret;
}

ITS_BOOLEAN
UAL_CheckTMValid(ITS_UINT tm)
{
   return ((tm == UAL_OVERRIDE_MODE) || (tm == UAL_LOADSHARE_MODE));
}






