
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
 *  ID: $Id: ual_sua_snm.c,v 9.1 2005/03/23 12:53:49 cvsadmin Exp $
 *
 *  LOG: $Log: ual_sua_snm.c,v $
 *  LOG: Revision 9.1  2005/03/23 12:53:49  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:20  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.30.1  2004/12/15 13:15:37  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2  2002/11/14 21:32:28  omayor
 *  LOG: Warning removal
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.4  2002/06/12 19:20:17  lbana
 *  LOG: Put in changes after Henry's comments.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/17 20:22:06  lbana
 *  LOG: More testing on current.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
 *  LOG:
 *  LOG: Revision 6.1  2002/05/13 20:30:42  lbana
 *  LOG: uals in current starts from here...
 *  LOG:
 *  LOG: Revision 1.1.2.7  2002/04/16 18:50:36  ngoel
 *  LOG: change sua msg type when sending response to DAUD
 *  LOG:
 *  LOG: Revision 1.1.2.6  2002/03/26 23:42:16  omayor
 *  LOG: A couple of SUA symbols remained. Initialize timer array.
 *  LOG:
 *  LOG: Revision 1.1.2.5  2002/03/25 17:51:12  ngoel
 *  LOG: commit sua management callback
 *  LOG:
 *  LOG: Revision 1.1.2.4  2002/03/25 17:13:26  ngoel
 *  LOG: add ual desc for snm messages
 *  LOG:
 *  LOG: Revision 1.1.2.3  2002/03/15 00:13:10  omayor
 *  LOG: Removed variant dependencies plus a few warning on linux.
 *  LOG:
 *  LOG: Revision 1.1.2.2  2002/03/14 20:04:53  ngoel
 *  LOG: After initial test with sua
 *  LOG:
 *
 ****************************************************************************/

#include <its_ual.h>
#include <its_tq_trans.h>
#include <its_sctp_trans.h>

#include "ual_intern.h"

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
 *      ITS_SUCCESS - 
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_HandleSuaSNMClassMsg(ITS_EVENT *ev, ITS_USHORT msgType, ASP_Entry *aspEntry)
{
    ITS_UINT apc = 0;
    ITS_UINT assn = 0;
    ITS_USHORT paramId, paramLen;
    int evOffset = 0;
    ITS_OCTET asmi = 0x00;
    ITS_BOOLEAN isAllowed = ITS_FALSE;
    ITS_SUA_IE suaIes[ITS_MAX_SUA_IES];
    int ieCount = 0;
    int ret;

    /* skip the common message header */
    evOffset += sizeof(SUA_MSG_HDR);

    switch (msgType)
    {
        case SUA_MSG_DAUD:

        if (UAL_SUA_DAUD_Desc.nmParam != 0)   /* It can be possible */
        {
            int i;
       
            for (i = 0; i < UAL_SUA_DAUD_Desc.nmParam; i++)
            {
                paramId = ev->data[evOffset] << 8 |
                          ev->data[evOffset + 1];
                evOffset += 2;

                paramLen = (ev->data[evOffset] << 8 | 
                            ev->data[evOffset + 1]) - 4;
                evOffset += 2;
            
                switch (paramId)
                {
                case SUA_SPRM_SSN:
                {
                    SUA_SSN ssn;
                    memcpy(&ssn, &ev->data[evOffset], sizeof(SUA_SSN));

                    assn = ssn.ssn;

                    break;
                }
                case SUA_PRM_AFFECTED_PC:
                {
                    SUA_AFFECTED_DEST pc;

                    memcpy(&pc, &ev->data[evOffset], sizeof(SUA_AFFECTED_DEST));

                    apc = SUA_PC_GET_VALUE(pc);
                
                    break;
                }

                default :
                    UAL_ERROR(("Unknown parameter in DAUD \n"));
                    return ITS_EINVALIDARGS;

                }
                     
                evOffset += paramLen + UAL_GetPadding(paramLen);
    
            }  
        }
        else
        {
            return SUA_EBADMSG;
        }

        /* optional parameters */
        if (UAL_SUA_DAUD_Desc.noParam != 0)   /* It can be possible */
        {
            while (evOffset < ev->len)
            {
                paramId = ev->data[evOffset] << 8 |
                      ev->data[evOffset + 1];
                evOffset += 2;

                paramLen = (ev->data[evOffset] << 8 | 
                            ev->data[evOffset + 1]) - 4;
                evOffset += 2;
            
               switch (paramId)
                {
                case SUA_PRM_SMI:
                {
                    SUA_SMI smi;
                    memcpy(&smi, &ev->data[evOffset], sizeof(SUA_SMI));

                    asmi = (ITS_OCTET)smi.smi;

                    break;
                }
                case SUA_SPRM_SSN:
                {
                    SUA_SSN ssn;
                    memcpy(&ssn, &ev->data[evOffset], sizeof(SUA_SSN));

                    assn = ssn.ssn;

                    break;
                }

                default :
                    UAL_ERROR(("Unknown parameter in DAUD \n"));
                    return ITS_EINVALIDARGS;
                break;

                }
                     
                evOffset += paramLen + UAL_GetPadding(paramLen);
    
            }  
        }

        memset((char*)&suaIes[ieCount].param_data.msgHeader, 0, 
              sizeof(SUA_MSG_HDR));
        suaIes[ieCount].param_id = SUA_PRM_MSG_HDR;
        suaIes[ieCount].param_length = sizeof(SUA_MSG_HDR);
        suaIes[ieCount].param_data.msgHeader.version = SUA_PROT_VER1;

        ieCount++;

        suaIes[ieCount].param_id = SUA_PRM_SMI;
        suaIes[ieCount].param_length = sizeof(SUA_SMI);
        suaIes[ieCount].param_data.smi.smi = asmi;

        ieCount++;

        suaIes[ieCount].param_id = SUA_SPRM_SSN;
        suaIes[ieCount].param_length = sizeof(SUA_SSN);
        suaIes[ieCount].param_data.ssn.ssn = assn;

         ieCount++;

        suaIes[ieCount].param_id = SUA_PRM_AFFECTED_PC;
        suaIes[ieCount].param_length = sizeof(SUA_PC);

        SUA_PC_SET_VALUE(suaIes[ieCount].param_data.pc, apc);

        ieCount++;

        /*
         * TODO: Ask Narendar to change the funcion name.
         * Commented out this line
         */

#if 0
        if (ROUTE_GetRouteStatus(apc, assn, &isAllowed) != ITS_SUCCESS)
        {
             UAL_ERROR((" GetRouteStatus Failed \n"));

             suaIes[0].param_data.msgHeader.msgClass = SUA_CL_SSNM_MSG;
             suaIes[0].param_data.msgHeader.msgType = SUA_MSG_DUNA;

             ev->data[3] = SUA_MSG_DUNA;
             SUA_EncodeMsg(suaIes, ieCount, ev, &UAL_SUA_DUNA_Desc);

             ev->src = UAL_MANAGER_INSTANCE;

            ret = TRANSPORT_PutEvent(aspEntry->trId, ev);

             return (ret);
        }
#endif

        if (isAllowed)
        {
            suaIes[0].param_data.msgHeader.msgClass = SUA_CL_SSNM_MSG;
            suaIes[0].param_data.msgHeader.msgType = SUA_MSG_DAVA;

             ev->data[3] = SUA_MSG_DAVA;
            /*SUA_EncodeMsg(suaIes, ieCount, ev, &UAL_SUA_DAVA_Desc);*/

            ev->src = UAL_MANAGER_INSTANCE;

            ret = TRANSPORT_PutEvent(aspEntry->trId, ev);
        }
        else
        {
            suaIes[0].param_data.msgHeader.msgClass = SUA_CL_SSNM_MSG;
            suaIes[0].param_data.msgHeader.msgType = SUA_MSG_DUNA;

            /*SUA_EncodeMsg(suaIes, ieCount, ev, &UAL_SUA_DUNA_Desc);*/

             ev->data[3] = SUA_MSG_DUNA;
            ev->src = UAL_MANAGER_INSTANCE;

            ret = TRANSPORT_PutEvent(aspEntry->trId, ev);
        }

        break;

        default :
            UAL_ERROR((" Received  SNM message other than DAUD"
                             " at SG \n"));
            return ITS_EINVALIDARGS;
        break;
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
 *      ITS_SUCCESS - 
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
UAL_SCCPMgmtCallback(ITS_POINTER object, ITS_POINTER userData, 
                     ITS_POINTER callData)
{
#if 0
    ITS_EVENT   *evt;
    ITS_SCCP_IE ies[ITS_MAX_SCCP_IES];
    SCCP_SCMG   scmgData;
    int         ret = ITS_SUCCESS, i = 0;
    ITS_SUA_IE ie[ITS_MAX_SUA_IES];
    int ieCount = 0;
    UAL_MSG_DESC *desc;
    ITS_OCTET msgType;
    ITS_UINT realPC;

    evt = (ITS_EVENT *)callData;

    UAL_DEBUG(("UAL_SCCPMgmtCallback received message\n"));

    ret = SCCP_Decode(ies, &ieCount, evt, &SCCP_UDT_Desc_CCITT);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("SCMG CallBack: SCCP_Decode failed code %d.\n", 
                         ret));
    }

    /* find the DATA ie to get the SCMG message type */
    while ((ies[i].param_id != SCCP_PRM_DATA) && (i < ieCount))
    {
        i++;
    }

    /* we are interested with UIS and UOS only */
    if (ies[i].param_id == SCCP_PRM_DATA)
    {
        memcpy(&scmgData, &ies[i].param_data.userData, sizeof(SCCP_SCMG));
        
        switch(scmgData.type)
        {
            case SCCP_SCMG_SS_ALLOWED :
                msgType = SUA_MSG_DAVA;
                desc = &UAL_SUA_DAVA_Desc;
                break;
             case SCCP_SCMG_SS_PROHIBIT :
                 msgType = SUA_MSG_DUNA;
                 desc = &UAL_SUA_DUNA_Desc;
                 break;
             case SCCP_SCMG_SS_STATUS_TEST :
                
                return;
             default :
                return;
                 break;
        }

        memset((char*)&ie[ieCount].param_data.msgHeader, 0, 
               sizeof(SUA_MSG_HDR));
        ie[ieCount].param_id = SUA_PRM_MSG_HDR;
        ie[ieCount].param_length = sizeof(SUA_MSG_HDR);
        ie[ieCount].param_data.msgHeader.version = SUA_PROT_VER1;
        ie[ieCount].param_data.msgHeader.msgClass = SUA_CL_SSNM_MSG;
         ie[ieCount].param_data.msgHeader.msgType = msgType;

        ieCount++;

        ie[ieCount].param_id = SUA_PRM_SMI;
        ie[ieCount].param_length = sizeof(SUA_SMI);
        ie[ieCount].param_data.smi.smi = scmgData.multiplicity;

        (ieCount)++;

        ie[ieCount].param_id = SUA_SPRM_SSN;
        ie[ieCount].param_length = sizeof(SUA_SSN);
        ie[ieCount].param_data.ssn.ssn = scmgData.ssn;

        ieCount++;

        ie[ieCount].param_id = SUA_PRM_AFFECTED_PC;
        ie[ieCount].param_length = sizeof(SUA_PC);

         realPC = MTP3_PC_GET_VALUE(scmgData.pointCode);

        SUA_PC_SET_VALUE(ie[ieCount].param_data.pc, realPC);

        ieCount++;

    }
    else
    {
        UAL_ERROR(("SCMG CallBack: Received a non SCMG message.\n"));  
    }

    /*ret = SUA_EncodeMsg(ie, ieCount, evt, desc);*/
   
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("SUA_Encode failed \n"));
        return;
    }

    ret = UAL_BroadCastMsg(evt, UAL_ASP_ACTIVE, ITS_FALSE);
    if (ret != ITS_SUCCESS)
    {
         UAL_ERROR(("UAL_LMHandleRKMMsg: Error Broadcasting SNMM\n"));
    }
#endif

    return;
}

