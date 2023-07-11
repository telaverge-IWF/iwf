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
 *  ID: $Id: prc.c,v 9.5 2008/07/18 05:44:02 ssingh Exp $
 *
 * LOG: $Log: prc.c,v $
 * LOG: Revision 9.5  2008/07/18 05:44:02  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.4  2008/06/17 08:28:13  ssingh
 * LOG: compilation error removal
 * LOG:
 * LOG: Revision 9.3  2008/06/17 06:39:07  nvijikumar
 * LOG: Updated for ITU over PRC support (split stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7030,D7070
 * LOG:
 * LOG: Revision 9.2  2007/02/01 13:25:20  yranade
 * LOG: 2nd round of merge
 * LOG:
 * LOG: Revision 9.1.10.1  2007/01/25 10:59:34  randresol
 * LOG: Modify PRC stack to allow it to run in parallel with ITU, TTC or ANSI stacks
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:53  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.6.1.6.1  2005/01/31 09:32:46  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.3.2.1.6.1  2004/09/15 05:46:44  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/05/07 09:33:33  ssingh
 * LOG: UnReserveCIC related changes done.
 * LOG:
 * LOG: Revision 7.3  2003/02/05 17:27:38  sjaddu
 * LOG: ReserveCic changes for ISUP.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/08/16 22:07:34  mmiers
 * LOG: Include the china variant
 * LOG:
 * LOG: Revision 6.6  2002/07/17 19:20:27  mmiers
 * LOG: Add missing NULLs
 * LOG:
 * LOG: Revision 6.5  2002/07/01 21:51:10  mmiers
 * LOG: Vframe changes to support ISUP.  Warning removal
 * LOG:
 * LOG: Revision 6.4  2002/06/28 16:34:35  hbalimid
 * LOG: Modified for ISUP vendor specific requirements.
 * LOG:
 * LOG: Revision 6.3  2002/05/29 22:43:47  mmiers
 * LOG: Signature change
 * LOG:
 * LOG: Revision 6.2  2002/05/07 15:44:05  wweng
 * LOG: Rename init/term functions for collision avoidance
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6  2002/02/13 21:19:15  mmiers
 * LOG: Finish up the ISUP integration.
 * LOG:
 * LOG: Revision 5.5  2002/02/01 21:57:12  mmiers
 * LOG: Missing include, corrections.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.3  2001/12/20 20:29:37  mmiers
 * LOG: Alignment
 * LOG:
 * LOG: Revision 5.2  2001/12/18 19:17:47  mmiers
 * LOG: Build on solaris
 * LOG:
 * LOG: Revision 5.1  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:43  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/08/02 21:27:27  dzhang
 * LOG: Renamed the class record type, forgot to correct vendors.
 * LOG:
 * LOG: Revision 2.2  2000/02/15 15:25:07  mmiers
 * LOG:
 * LOG: Add class part init.
 * LOG:
 * LOG: Revision 2.1  2000/02/02 15:54:20  mmiers
 * LOG:
 * LOG:
 * LOG: Modify stack startup to class initialize.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_object.h>
#include <its_ss7_trans.h>

#ident "$Id: prc.c,v 9.5 2008/07/18 05:44:02 ssingh Exp $"

#undef ANSI
#undef CCITT

#if defined(SPLIT_STACK) && defined(USE_PRC_SCCP)
#undef PRC
#undef TTC
#define PRC
#else
#define CCITT
#endif

#if !defined(SPLIT_STACK) && !defined(USE_ITU_SCCP)
#include <itu/tcap.h>
#endif
#include <itu/isup.h>
#if !defined(SPLIT_STACK) && !defined(USE_ANSI_SCCP)
#include <ansi/tcap.h>
#endif
#include <ansi/isup.h>

#include <vframe.h>

/*
 * layer functions
 */
extern int IMTP3_Initialize_PRC(ITS_SS7_HANDLE);
extern int IISUP_Initialize_PRC(ITS_SS7_HANDLE);
extern int ISCCP_Initialize_PRC(ITS_SS7_HANDLE);
extern int ITCAP_Initialize_ANSI(ITS_SS7_HANDLE);
extern int ITCAP_Initialize_CCITT(ITS_SS7_HANDLE);
extern int ITCAP_Initialize_PRC(ITS_SS7_HANDLE);
extern int IMTP3_Terminate_PRC(ITS_SS7_HANDLE);
extern int IISUP_Terminate_PRC(ITS_SS7_HANDLE);
extern int ISCCP_Terminate_PRC(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_ANSI(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_CCITT(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_PRC(ITS_SS7_HANDLE);

extern int INTELLINET_SendMTP3Event_PRC(ITS_SS7_HANDLE handl,
                                          ITS_OCTET type,
                                          MTP3_HEADER_PRC *mtp3,
                                          ITS_OCTET *buf, ITS_USHORT len);
extern int INTELLINET_ReserveCIC_PRC(ITS_SS7_HANDLE handle,
                                        ITS_OCTET sio,
                                        ITS_UINT opc, ITS_UINT dpc,
                                        ITS_USHORT cic,
                                        ITS_OCTET *status, ITS_CTXT *vcic);
extern int INTELLINET_UnReserveCIC_PRC(ITS_SS7_HANDLE handle,
                                        ITS_OCTET sio,
                                        ITS_UINT opc, ITS_UINT dpc,
                                        ITS_USHORT cic);
extern int INTELLINET_SendISUPEvent_PRC(ITS_HANDLE handle, ITS_OCTET type,
                                          ITS_HDR *hdr,
                                          ITS_ISUP_IE *ies, int ieCount,
                                          ISUP_MSG_DESC *desc);
extern int INTELLINET_ReceiveISUPEvent_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE *ies, int *ieCount,
                                             ISUP_MSG_DESC *desc);
extern int INTELLINET_SendSCCPEvent_PRC(ITS_HANDLE handle, ITS_OCTET type,
                                          ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount,
                                          SCCP_MSG_DESC* desc);
extern int INTELLINET_SendUOS_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SendUIS_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SetCongestion_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                          ITS_UINT pc, ITS_OCTET ssn,
                                          ITS_OCTET cong);
extern int INTELLINET_GetSCCPNextRef_PRC(ITS_SS7_HANDLE handle,
                                                ITS_CTXT *cref);
extern int INTELLINET_SendComp_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt);
extern int INTELLINET_SendComp_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt);
extern int INTELLINET_SendComp_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt);
extern int INTELLINET_SendDlg_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_DLG *dlg);
extern int INTELLINET_SendDlg_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_DLG *dlg);
extern int INTELLINET_SendDlg_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_DLG *dlg);
extern int INTELLINET_AllocateDID_ANSI(ITS_SS7_HANDLE handle,
                                       ITS_CTXT *did);
extern int INTELLINET_AllocateDID_CCITT(ITS_SS7_HANDLE handle,
                                       ITS_CTXT *did);
extern int INTELLINET_AllocateDID_PRC(ITS_SS7_HANDLE handle,
                                        ITS_CTXT *did);
extern int INTELLINET_FetchAddrs_ANSI(ITS_SS7_HANDLE handle,
                                      ITS_CTXT did,
                                      SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchAddrs_CCITT(ITS_SS7_HANDLE handle,
                                      ITS_CTXT did,
                                      SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchAddrs_PRC(ITS_SS7_HANDLE handle,
                                       ITS_CTXT did,
                                       SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_CCITT(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_PRC(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchQOS_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_FetchQOS_CCITT(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_FetchQOS_PRC(ITS_SS7_HANDLE handle,
                                     ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_ANSI(ITS_SS7_HANDLE handle,
                                  ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_CCITT(ITS_SS7_HANDLE handle,
                                  ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_PRC(ITS_SS7_HANDLE handle,
                                   ITS_CTXT did, DLG_QOS *qos);

/*
 * Commit Methods
 */
extern int INTELLINET_MTP3_Commit_PRC(FILE* fp);
extern int INTELLINET_SCCP_Commit_PRC(FILE* fp);
extern int INTELLINET_TCAP_Commit_PRC(FILE* fp);
extern int INTELLINET_ISUP_Commit_PRC(FILE* fp, int pos,
                                       int opc, int dpc, int sio);
extern int INTELLINET_TCAP_Commit_ANSI(FILE* fp);
extern int INTELLINET_TCAP_Commit_CCITT(FILE* fp);

/*
 * undocumented
 */
ITSDLLAPI extern ITS_UINT ITS_SS7_Mask;

/*
 * stack record.
 */
ITSSS7DLLAPI SS7TRAN_Manager* ISS7_PRC_Stack = NULL;

/*
 * class init.
 */
static int
ClassInit(ITS_Class objClass)
{
    /*
     * plug the superclass hole.
     */
    ITS_CLASS_SUPERCLASS(itsINTELLISS7_ClassPRC) = itsSS7STACK_ClassPRC;

    /*
     * create the PRC stack instance
     */
    ISS7_PRC_Stack = (SS7TRAN_Manager *)calloc(1, sizeof(SS7TRAN_Manager));
    if (ISS7_PRC_Stack == NULL)
    {
        return (ITS_ENOMEM);
    }

    /*
     * initialize the relevent mechanisms.
     */
    TRANSPORT_MASK(ISS7_PRC_Stack) = ITS_SS7_Mask;
    SS7TRAN_SUBORDINATE(ISS7_PRC_Stack) =
        (SS7STACK_ClassRec *)itsINTELLISS7_ClassPRC;

    /*
     * invoke the initialize method (note that we're calling
     * the constructor from it's own ClassInit).
     */
    SS7TRAN_HANDLE(ISS7_PRC_Stack) =
        ITS_ConstructObject(itsINTELLISS7_ClassPRC, ISS7_PRC_Stack);

    if (SS7TRAN_HANDLE(ISS7_PRC_Stack) == NULL)
    {
        free(ISS7_PRC_Stack);
        ISS7_PRC_Stack = NULL;

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*
 * class destroy
 */
static void
ClassDest(ITS_Class objClass)
{
    if (ISS7_PRC_Stack)
    {
        if (SS7TRAN_HANDLE(ISS7_PRC_Stack))
        {
            ITS_DestructObject(SS7TRAN_HANDLE(ISS7_PRC_Stack));
        }

        free(ISS7_PRC_Stack);

        ISS7_PRC_Stack = NULL;
    }
}

/*
 * the PRC stack class record
 */
ITSSS7DLLAPI VENDOR_ClassRec itsINTELLISS7_ClassRecPRC =
{
    /* core part */
    {
        NULL,                           /* no superclass in a DLL */
        sizeof(VENDOR_Instance),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        INTELLISS7_CLASS_NAME "PRC",    /* class name */
        ClassInit,                      /* class init */
        ClassDest,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* stack part */
    {
        NULL,                           /* get next */
        NULL,                           /* peek next */
        NULL                            /* put */
    },
    /* vendor part */
    {
        NULL,                               /* no load resources */
        NULL,                               /* no await indication */
        /* MTP2 */
        {
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no retrieve */
            NULL                            /* no send */
        },
        /* MTP3 */
        {
            IMTP3_Initialize_PRC,         /* initialize */
            IMTP3_Terminate_PRC,          /* terminate */
            NULL,                         /* no retrieve */
            NULL,                         /* no send ANSI */
            NULL,                         /* no send CCITT */
            INTELLINET_SendMTP3Event_PRC, /* send PRC */
            NULL,                         /* no send TTC */
            INTELLINET_MTP3_Commit_PRC
        },
        /* ISUP */
        {
            NULL, /*IISUP_Initialize_PRC,*/         /* initialize */
            NULL,/*IISUP_Terminate_PRC,*/          /* terminate */
            NULL, /*INTELLINET_ReserveCIC_PRC,*/   /* getCIC */
            NULL, /*INTELLINET_UnReserveCIC_PRC,*/    /* unserveCIC */
            NULL,                           /* no retrieve ANSI */
            NULL,                           /* no receive ANSI */
            NULL, /*INTELLINET_ReceiveISUPEvent_PRC,*/ /* retrieve */
            NULL,                           /* no send ANSI */
            NULL, /*INTELLINET_SendISUPEvent_PRC,*/ /* send event */
            NULL /*INTELLINET_ISUP_Commit_PRC*/
        },
        /* SCCP */
        {
            ISCCP_Initialize_PRC,         /* initialize */
            ISCCP_Terminate_PRC,          /* terminate */
            INTELLINET_GetSCCPNextRef_PRC,/* getRef */
            NULL,                           /* no retrieve */
            INTELLINET_SendSCCPEvent_PRC, /* send */
            INTELLINET_SendUOS_PRC,       /* UOS */
            INTELLINET_SendUIS_PRC,       /* UIS */
            INTELLINET_SetCongestion_PRC,  /* setCong */
            INTELLINET_SCCP_Commit_PRC
        },
        /* TCAP */
        {
#if defined(SPLIT_STACK) && defined(USE_ANSI_TCAP)
            ITCAP_Initialize_ANSI,          /* initialize */
            ITCAP_Terminate_ANSI,           /* terminate */
            INTELLINET_AllocateDID_ANSI,    /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_ANSI,       /* sendCmp */
            INTELLINET_SendDlg_ANSI,        /* sendDlg */
            INTELLINET_FetchAddrs_ANSI,     /* fetchAddrs */
            INTELLINET_SetAddrs_ANSI,       /* setAddrs */
            INTELLINET_FetchQOS_ANSI,       /* fetchQOS */
            INTELLINET_SetQOS_ANSI,         /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL,                            /* no set congestion */
            INTELLINET_TCAP_Commit_ANSI
#elif defined(SPLIT_STACK) && defined (USE_ITU_TCAP)
            ITCAP_Initialize_CCITT,          /* initialize */
            ITCAP_Terminate_CCITT,           /* terminate */
            INTELLINET_AllocateDID_CCITT,    /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_CCITT,       /* sendCmp */
            INTELLINET_SendDlg_CCITT,        /* sendDlg */
            INTELLINET_FetchAddrs_CCITT,     /* fetchAddrs */
            INTELLINET_SetAddrs_CCITT,       /* setAddrs */
            INTELLINET_FetchQOS_CCITT,       /* fetchQOS */
            INTELLINET_SetQOS_CCITT,         /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL,                            /* no set congestion */
            INTELLINET_TCAP_Commit_CCITT
#else
            ITCAP_Initialize_PRC,         /* initialize */
            ITCAP_Terminate_PRC,          /* terminate */
            INTELLINET_AllocateDID_PRC,   /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_PRC,      /* sendCmp */
            INTELLINET_SendDlg_PRC,       /* sendDlg */
            INTELLINET_FetchAddrs_PRC,    /* fetchAddrs */
            INTELLINET_SetAddrs_PRC,      /* setAddrs */
            INTELLINET_FetchQOS_PRC,      /* fetchQOS */
            INTELLINET_SetQOS_PRC,        /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL,                            /* no set congestion */
            INTELLINET_TCAP_Commit_PRC
#endif
        }
    }
};

ITSSS7DLLAPI ITS_Class itsINTELLISS7_ClassPRC =
    (ITS_Class)&itsINTELLISS7_ClassRecPRC;
