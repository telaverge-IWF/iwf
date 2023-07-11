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
 *  ID: $Id: itu-ansi-tcap.c,v 1.1 2008/06/11 11:58:08 ssingh Exp $
 *
 * LOG: $Log: itu-ansi-tcap.c,v $
 * LOG: Revision 1.1  2008/06/11 11:58:08  ssingh
 * LOG: Reference Document:: ACC-CG-SDS-SS7-V1.0.02
 * LOG: D9010 and D9020::ANSI+ITU TCAP over ANSI/ITU SCCP
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-ansi-tcap.c,v 1.1 2008/06/11 11:58:08 ssingh Exp $"

#include <stdlib.h>

#include <its.h>
#include <its_object.h>
#include <its_ss7_trans.h>

#if defined (ANSI)

#undef CCITT
#undef ANSI
#define ANSI 1

#include <ansi/tcap.h>
#include <vframe.h>

/*
 * layer functions
 */
extern int ITCAP_Initialize_ANSI(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_ANSI(ITS_SS7_HANDLE);

extern int INTELLINET_SendComp_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt);
extern int INTELLINET_SendDlg_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_DLG *dlg);
extern int INTELLINET_AllocateDID_ANSI(ITS_SS7_HANDLE handle,
                                       ITS_CTXT *did);
extern int INTELLINET_FetchAddrs_ANSI(ITS_SS7_HANDLE handle,
                                      ITS_CTXT did,
                                      SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchQOS_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_ANSI(ITS_SS7_HANDLE handle,
                                  ITS_CTXT did, DLG_QOS *qos);

extern int INTELLINET_TCAP_Commit_ANSI(FILE* fp);

/*
 * undocumented
 */
ITSDLLAPI extern ITS_UINT ITS_SS7_Mask;

/*
 * stack record.
 */
ITSSS7DLLAPI SS7TRAN_Manager* ISS7_ANSI_Stack = NULL;

/*
 * class init.
 */
static int
ClassInit(ITS_Class objClass)
{
    /*
     * plug the superclass hole.
     */
    ITS_CLASS_SUPERCLASS(itsINTELLITCAP_ClassANSI) = itsTCAPSTACK_ClassANSI;

    /*
     * create the ATCAP stack instance
     */
    ISS7_ANSI_Stack = (SS7TRAN_Manager *)calloc(1, sizeof(SS7TRAN_Manager));
    if (ISS7_ANSI_Stack == NULL)
    {
        return (ITS_ENOMEM);
    }

    /*
     * initialize the relevent mechanisms.
     */
    TRANSPORT_MASK(ISS7_ANSI_Stack) = ITS_SS7_Mask;
    SS7TRAN_SUBORDINATE(ISS7_ANSI_Stack) =
        (SS7STACK_ClassRec *)itsINTELLITCAP_ClassANSI;

    /*
     * invoke the initialize method (note that we're calling
     * the constructor from it's own ClassInit).
     */
    SS7TRAN_HANDLE(ISS7_ANSI_Stack) =
        ITS_ConstructObject(itsINTELLITCAP_ClassANSI, ISS7_ANSI_Stack);

    if (SS7TRAN_HANDLE(ISS7_ANSI_Stack) == NULL)
    {
        free(ISS7_ANSI_Stack);
        ISS7_ANSI_Stack = NULL;

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
    if (ISS7_ANSI_Stack)
    {
        if (SS7TRAN_HANDLE(ISS7_ANSI_Stack))
        {
            ITS_DestructObject(SS7TRAN_HANDLE(ISS7_ANSI_Stack));
        }

        free(ISS7_ANSI_Stack);

        ISS7_ANSI_Stack = NULL;
    }
}

/*
 * the ANSI TCAP stack class record
 */
ITSSS7DLLAPI VENDOR_ClassRec itsINTELLITCAP_ClassRecANSI =
{
    /* core part */
    {
        NULL,                           /* no superclass in a DLL */
        sizeof(VENDOR_Instance),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        INTELLISS7_CLASS_NAME "ATCAP",   /* class name */
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
            NULL,                           /* initialize */
            NULL,                           /* terminate */
            NULL,                           /* no retrieve */
            NULL,                           /* send ANSI */
            NULL,                           /* no send CCITT */
            NULL,                           /* no send PRC */
            NULL,
            NULL                            /* commit */
        },
        /* ISUP */
        {
            NULL,                           /* initialize */
            NULL,                           /* terminate */
            NULL,                           /* getCIC */
            NULL,                           /* unreserveCIC */
            NULL,                           /* no retrieve */
            NULL,                           /* receive ANSI */
            NULL,                           /* no CCITT receive */
            NULL,                           /* send event */
            NULL,                           /* no CCITT send */
            NULL                            /* commit */
        },
        /* SCCP */
        {
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no getRef */
            NULL,                           /* no no retrieve */
            NULL,                           /* no send */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL                            /* no setCong */
        },
        /* TCAP */
        {
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
            NULL,                           /* no set congestion */
            INTELLINET_TCAP_Commit_ANSI     /* commit */
        }
    }
};

ITSSS7DLLAPI ITS_Class itsINTELLITCAP_ClassANSI =
    (ITS_Class)&itsINTELLITCAP_ClassRecANSI;

#endif

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
 * ID: $Id: itu-ansi-tcap.c,v 1.1 2008/06/11 11:58:08 ssingh Exp $
 *
 * LOG: $Log: itu-ansi-tcap.c,v $
 * LOG: Revision 1.1  2008/06/11 11:58:08  ssingh
 * LOG: Reference Document:: ACC-CG-SDS-SS7-V1.0.02
 * LOG: D9010 and D9020::ANSI+ITU TCAP over ANSI/ITU SCCP
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: itu-ansi-tcap.c,v 1.1 2008/06/11 11:58:08 ssingh Exp $"

#if defined (CCITT)

#undef ANSI
#undef CCITT
#define CCITT 1

#include <itu/tcap.h>
#include <vframe.h>

/*
 * layer functions
 */
extern int ITCAP_Initialize_CCITT(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_CCITT(ITS_SS7_HANDLE);


extern int INTELLINET_SendComp_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt);
extern int INTELLINET_SendDlg_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_DLG *dlg);
extern int INTELLINET_AllocateDID_CCITT(ITS_SS7_HANDLE handle,
                                        ITS_CTXT *did);
extern int INTELLINET_FetchAddrs_CCITT(ITS_SS7_HANDLE handle,
                                       ITS_CTXT did,
                                       SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_CCITT(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchQOS_CCITT(ITS_SS7_HANDLE handle,
                                     ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_CCITT(ITS_SS7_HANDLE handle,
                                   ITS_CTXT did, DLG_QOS *qos);


/*
 * undocumented
 */
ITSDLLAPI extern ITS_UINT ITS_SS7_Mask;

/*
 * stack record.
 */
ITSSS7DLLAPI SS7TRAN_Manager* ISS7_CCITT_Stack = NULL;

/*
 * class init.
 */
static int
ClassInit(ITS_Class objClass)
{
    /*
     * plug the superclass hole.
     */
    ITS_CLASS_SUPERCLASS(itsINTELLITCAP_ClassCCITT) = itsTCAPSTACK_ClassCCITT;
    /*
     * create the CCITT stack instance
     */
    ISS7_CCITT_Stack = (SS7TRAN_Manager *)calloc(1, sizeof(SS7TRAN_Manager));
    if (ISS7_CCITT_Stack == NULL)
    {
        return (ITS_ENOMEM);
    }

    /*
     * initialize the relevent mechanisms.
     */
    TRANSPORT_MASK(ISS7_CCITT_Stack) = ITS_SS7_Mask;
    SS7TRAN_SUBORDINATE(ISS7_CCITT_Stack) =
        (SS7STACK_ClassRec *)itsINTELLITCAP_ClassCCITT;

    /*
     * invoke the initialize method (note that we're calling
     * the constructor from it's own ClassInit).
     */
    SS7TRAN_HANDLE(ISS7_CCITT_Stack) =
        ITS_ConstructObject(itsINTELLITCAP_ClassCCITT, ISS7_CCITT_Stack);

    if (SS7TRAN_HANDLE(ISS7_CCITT_Stack) == NULL)
    {
        free(ISS7_CCITT_Stack);
        ISS7_CCITT_Stack = NULL;

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
    if (ISS7_CCITT_Stack)
    {
        if (SS7TRAN_HANDLE(ISS7_CCITT_Stack))
        {
            ITS_DestructObject(SS7TRAN_HANDLE(ISS7_CCITT_Stack));
        }

        free(ISS7_CCITT_Stack);

        ISS7_CCITT_Stack = NULL;
    }
}

/*
 * the ITCAP TCAP stack class record
 */
ITSSS7DLLAPI VENDOR_ClassRec itsINTELLITCAP_ClassRecCCITT =
{
    /* core part */
    {
        NULL,                           /* no superclass in a DLL */
        sizeof(VENDOR_Instance),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        INTELLISS7_CLASS_NAME "ITCAP",  /* class name */
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
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no retrieve */
            NULL,                           /* no send ANSI */
            NULL,                           /* no send CCITT */
            NULL                            /* no send PRC */
        },
        /* ISUP */
        {
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no getCIC */
            NULL,                           /* no unserveCIC */
            NULL,                           /* not retrieve */
            NULL,                           /* no receive ANSI */
            NULL,                           /* no receive */
            NULL,                           /* no send ANSI */
            NULL,                           /* no send event */
        },
        /* SCCP */
        {
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no getRef */
            NULL,                           /* no no retrieve */
            NULL,                           /* no send */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL                            /* no setCong */
        },
        /* TCAP */
        {
            ITCAP_Initialize_CCITT,         /* initialize */
            ITCAP_Terminate_CCITT,          /* terminate */
            INTELLINET_AllocateDID_CCITT,   /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_CCITT,      /* sendCmp */
            INTELLINET_SendDlg_CCITT,       /* sendDlg */
            INTELLINET_FetchAddrs_CCITT,    /* fetchAddrs */
            INTELLINET_SetAddrs_CCITT,      /* setAddrs */
            INTELLINET_FetchQOS_CCITT,      /* fetchQOS */
            INTELLINET_SetQOS_CCITT,        /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL                            /* no set congestion */
        }
    }
};

ITSSS7DLLAPI ITS_Class itsINTELLITCAP_ClassCCITT =
    (ITS_Class)&itsINTELLITCAP_ClassRecCCITT;

#endif
