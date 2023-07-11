/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: $Log: util.c,v $
 * LOG: Revision 9.1.176.1  2014/09/16 09:34:53  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.1.172.1  2014/09/15 07:20:41  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:04  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/06 21:05:16  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/10/28 18:46:53  mmiers
 * LOG: 64 bit build issues.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/16 02:04:42  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:02  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.2  2001/01/04 17:21:57  hdivoux
 * LOG: symbol collision
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:47  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:51  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/08/05 13:24:24  mmiers
 * LOG:
 * LOG:
 * LOG: Remove unused variable.
 * LOG:
 * LOG: Revision 1.8  1999/07/22 00:34:39  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.7  1999/06/01 17:15:09  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.6  1999/03/02 18:14:52  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.5  1999/02/26 04:09:51  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.4  1999/02/26 00:48:01  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.3  1998/11/19 02:40:53  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.2  1998/11/13 23:15:31  mmiers
 * LOG: Sanitize the NT build environment.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:17  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.11  1998/10/23 16:05:35  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.10  1998/10/23 00:19:19  mmiers
 * LOG: Working on pepsy.
 * LOG:
 * LOG: Revision 1.9  1998/10/22 19:28:06  mmiers
 * LOG: Continue making PSAP threadsafe.
 * LOG:
 * LOG: Revision 1.8  1998/10/22 00:47:41  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.7  1998/10/21 17:48:21  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

#if defined(__STDC__) || defined(WIN32) || defined(__cplusplus)
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */
#include "pepsy-driver.h"
#include <asn-c/AsnC.h>
#include "cmd_srch.h"

#ident "$Id: util.c,v 9.1.176.1 2014/09/16 09:34:53 jsarvesh Exp $"

#ifndef PEPYPARM
#define PEPYPARM        char *
#endif

#define pname(t) \
    ((t)->pe_typename ? *(t)->pe_typename : "???")

extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);
char *pr_petype (int type, char* nbuf);
void pr_entry(ptpe *p);
int same(ptpe *typ, ptpe *dflt, char *parm, modtyp *mod);

#if !defined(WIN32)
extern void exit();
#endif

#if defined(__STDC__) || defined(WIN32) || defined(__cplusplus)
extern void _asprintf (char *, char *, va_list);
#endif

static char   *pe_classlist[] =
{
    "UNIV",
    "APPL",
    "CONT",
    "PRIV"
};

static int	pe_maxclass = sizeof pe_classlist / sizeof pe_classlist[0];

int
#if !defined(__STDC__) && !defined( WIN32 ) && !defined(__cplusplus)
pepsylose (va_alist)
va_dcl
{
    modtyp  *module;
    char    *cp;
    PE      pe;
    ptpe    *p, *p1;
    va_list ap;
    char    buffer[BUFSIZ];
    char localBuf[BUFSIZ];

    va_start (ap);

    module = va_arg (ap, modtyp *);
    p = va_arg (ap, ptpe *);
    pe = va_arg (ap, PE);
#else
pepsylose(modtyp *module, ptpe *p, PE pe, ...)
{
    ptpe    *p1;
    char    buffer[BUFSIZ];
    va_list ap;
    char *cp;
    char localBuf[BUFSIZ];
    char tmpBuf[30];

    va_start(ap, pe);
#endif

    _asprintf (buffer, NULL, ap);
    sprintf (localBuf, "%s: module %s",
                    buffer, module ? module->md_name : "<none>");
    if (p)
    {
        for (p1 = p; p1->pe_type != PE_END; p1++)
        {
            continue;
        }
        cp = localBuf + strlen (localBuf);
        sprintf (cp, "encoding %s expecting %s,class=%s/id=%d",
                        pname(p1),
                        pr_petype (p->pe_type, tmpBuf),
                        pe_classlist[p->pe_flags & FL_CLASS],
                        p->pe_tag);
    }

    if (pe && ((int)pe->pe_class) < pe_maxclass)
    {
        cp = localBuf + strlen (localBuf);
        sprintf (cp, " found %s/%d", pe_classlist[pe->pe_class],
                        pe->pe_id);
    }

    va_end (ap);
    return NOTOK;
}

int
#if !defined( __STDC__ ) && !defined( WIN32 ) && !defined(__cplusplus)
ppepsylose (va_alist)
    va_dcl
{
    modtyp  *module;
    ptpe    *p;
    PE      pe;
    char    *cp;
    va_list ap;
    char    buffer[BUFSIZ];
    char localBuf[BUFSIZ];

    va_start (ap);

    module = va_arg (ap, modtyp *);
    p = va_arg (ap, ptpe *);
    pe = va_arg (ap, PE);
#else
ppepsylose (modtyp *module, ptpe *p, PE pe, ...)
{
    va_list ap;
    char    buffer[BUFSIZ];
    char    *cp;
    char    localBuf[BUFSIZ];
    char    tmpBuf[32];

    va_start(ap, pe);
#endif

    _asprintf (buffer, NULL, ap);
    sprintf (localBuf, "%s: module %s",
                    buffer, module ? module->md_name : "<none>");
    if (p)
    {
        cp = localBuf + strlen (localBuf);
        sprintf (cp, " %s/class=%s/id=%d",
                        pr_petype (p->pe_type, tmpBuf),
                        pe_classlist[p->pe_flags & FL_CLASS],
                        p->pe_tag);
        if (p->pe_typename)
        {
            sprintf (cp, "(%s)", *p->pe_typename);
        }
    }
    
    if (pe && ((int)pe->pe_class) < pe_maxclass)
    {
        cp = localBuf + strlen (localBuf);
        sprintf (cp, " got %s/%d", pe_classlist[pe->pe_class],
                        pe->pe_id);
    }

    va_end (ap);
    return NOTOK;
}

/*
 * Useful little routines
 */
/*
 * print out the message and if the arguement is greater than 0
 * terminate
 */
void
ferr(int n, char *mesg)
{
    printf(mesg);
    if (n > 0)
    {
        exit(n);
    }
}
/*
 * print out the message and number and if the arguement is greater
 * than 0 terminate
 */
void
ferrd(int n, char *mesg, int d)
/* char   *mesg;
int     d; */
{
    printf(mesg, d);
    if (n > 0)
    {
        exit(n);
    }
}

/*
 * 0 = Encoding table, 1 = Decoding table, 2 = Printing table
 */
#define TYP_ENC         0
#define TYP_DEC         1
#define TYP_PRINT       2
#define TYP_LAST        2

void
dmp_tpe(char *s, ptpe *p, modtyp *mod)
{
    int     typ, i, j;
    ptpe   **par, **prev;
    char   *name = NULL;

    printf("%s: (%s)", s, mod->md_name);
    /*
     * Calculate what table it is in - we assume they are in order of
     * increasing address
     */

    par = NULL;
    for (typ = 0; typ <= TYP_LAST; typ++)
    {
        switch (typ)
        {
        case TYP_ENC:
            if (mod->md_etab != NULL && mod->md_etab[0] < p)
            {
                par = mod->md_etab;
                name = "Encoding:";
            }
            break;

        case TYP_DEC:
            if (mod->md_dtab != NULL && mod->md_dtab[0] < p)
            {
                par = mod->md_dtab;
                name = "Decoding:";
            }
            break;

        case TYP_PRINT:
            if (mod->md_ptab != NULL && mod->md_ptab[0] < (ptpe *) p)
            {
                par = (ptpe **) mod->md_ptab;
                name = "Printing:";
            }
            break;

        default:
            pepsylose (mod, p, NULL, "dmp_tpe:typ = %d internal error\n",
                typ);
            return;
        }
    }

    if (par == NULL)
    {
        printf("can't find entry %p\n", p);
        return;
    }

    prev = par;
    for (i = mod->md_nentries; i > 0; i--)
    {
        if (*par > p)
        {
            break;
        }
        par++;
    }

    if (par == prev)
    {
        pepsylose (mod, p, NULL,
            "dmp_tpe:par == prev == %p internal error\n", par);
    }

    par--;
    j = p - *par;

    printf("%s type %d + %d ", name, (int)(par - prev), j);
    pr_entry(p);
}

#define NENTRY(x)       ((sizeof (x)/sizeof (x[0])))
/*
 * Print out a ptpe entry
 */

static CMD_TABLE pepsy_type_tbl[] =
{
    {   "PE_START",     PE_START       },
    {   "PE_END",       PE_END         },
    {   "XOBJECT",      XOBJECT        },
    {   "UCODE",        UCODE          },
    {   "MEMALLOC",     MEMALLOC       },
    {   "SCTRL",        SCTRL          },
    {   "CH_ACT",       CH_ACT         },
    {   "OPTL",         OPTL           },
    {   "BOPTIONAL",    BOPTIONAL      },
    {   "FREE_ONLY",    FREE_ONLY      },
    {   "TYPE_DATA",    TYPE_DATA      },
    {   "ANY",          ANY            },
    {   "INTEGER",      INTEGER        },
    {   "BOOLEAN",      BOOLEAN        },
    {   "OBJECT",       OBJECT         },
    {   "BITSTRING",    BITSTRING      },
    {   "OCTETSTRING",  OCTETSTRING    },
    {   "SET_START",    SET_START      },
    {   "SEQ_START",    SEQ_START      },
    {   "SEQOF_START",  SEQOF_START    },
    {   "SETOF_START",  SETOF_START    },
    {   "CHOICE_START", CHOICE_START   },
    {   "REALTYPE",     REALTYPE       },
    {   "ASN_NULL",     ASN_NULL       },
    {   "ASN_OID",      ASN_OID        },
    {   "ETAG",         ETAG           },
    {   "IMP_OBJ",      IMP_OBJ        },
    {   "EXTOBJ",       EXTOBJ         },
    {   "EXTMOD",       EXTMOD         },
    {   "OBJID",        OBJID          },
    {   "DFLT_F",       DFLT_F         },
    {   "DFLT_B",       DFLT_B         },
    {   "T_STRING",     T_STRING       },
    {   "OCTET_PTR",    OCTET_PTR      },
    {   "OCTET_LEN",    OCTET_LEN      },
    {   "BITSTR_PTR",   BITSTR_PTR     },
    {   "BITSTR_LEN",   BITSTR_LEN     },
    {   "STYPE_DATA",   STYPE_DATA     },
    {   "STYPE_DATA",   STYPE_DATA     },
    {   "SBITSTRING",   SBITSTRING     },
    {   "SOBJID",       SOBJID         },
    {   "SREALTYPE",    SREALTYPE      },
    {   "SANY",         SANY           },
    {   "SEXTOBJ",      SEXTOBJ        },
    {   "SOBJECT",      SOBJECT        },
    {   "SOCTETSTRING", SOCTETSTRING   },
    {   "SEXTERNAL",    SEXTERNAL      },
    {   "SSEQ_START",   SSEQ_START     },
    {   "SSET_START",   SSET_START     },
    {   "SSEQOF_START", SSEQOF_START   },
    {   "SSETOF_START", SSETOF_START   },
    {   "SCHOICE_START",SCHOICE_START  },
    {   NULL,           -10            }
};

char *
pr_petype (int type, char* nbuf)
{
    char *p;

    if ((p = rcmd_srch (type, pepsy_type_tbl)) == NULL)
    {
            sprintf (p = nbuf, "%d", type);
    }

    return p;
}

void
pr_entry(ptpe *p)
{
    char tmpBuf[32];

    printf ("%s, ", pr_petype (p->pe_type, tmpBuf));
    printf("%ld, %d, %d}\n", p->pe_ucode, (int)p->pe_tag, p->pe_flags);
}


/*
 * null function for what evr purposes
 */
void
f_null()
{
}

/*
 * compare a given number of bits pointed to by the two character
 * pointers return 0 if they are the same non zero otherwise
 */
int
bitscmp(char *p1, char *p2, int len)
{
    int i;
    unsigned int mask;

    if (len >= 8 && memcmp(p1, p2, len / 8))
    {
        return (1);
    }

    if (len % 8 == 0)
    {
        return (0);
    }

    /* Check those last few bits */
    i = len / 8;
    mask = (0xff00 >> len % 8) & 0xff;
    if ((p1[i] & mask) != (p2[i] & mask))
    {
        return (1);
    }

    return (0);
}

#define MIN(a, b)       (a < b ? a : b)
/*
 * compare an octet string and a qb and return 0 if they are the same
 * and non zero otherwise
 */
int
ostrcmp(char *p, int len, struct qbuf *qb)
{
    struct qbuf *qp;

    if (len < 0 || qb == NULL || p == NULL)
        return (1);
    qp = qb;
    do
    {
        if (qp->qb_data != NULL)
        {
            if (qp->qb_len < 0)
            {
                ferrd(1, "ostrcmp:qb_len %d < 0", qp->qb_len);
            }

            if (qp->qb_len > len)
            {
                return (1);
            }

            if (memcmp(qp->qb_data, p, qp->qb_len))
            {
                return (1);
            }

            if ((len -= qp->qb_len) == 0)
            {
                return (0);
            }

            p += qp->qb_len;
        }
        qp = qp->qb_forw;
    }
    while (qp != qb);

    return (len);
}

/*
 * Is data present for the optional item? 1 for yes 0 for no
 */
int
hasdata(PEPYPARM parm, ptpe *p, modtyp *mod, int *popt, int *optcnt)
{
    switch (p->pe_type)
    {
    case INTEGER:
    case REALTYPE:
    case BOOLEAN:
    case ASN_NULL:
        if (DEFAULT(p))
        {
            /* Default's don't have bit map */
            if ((p[1].pe_type == DFLT_B && same(p, p + 1, parm, mod)) ||
                (p[-1].pe_type == DFLT_F && same(p, p - 1, parm, mod)))
            {
                goto next;
            }
            break;
        }

        if (!TESTBIT(*popt, (*optcnt)++))
        {
            goto next;          /* Missing so skip */
        }
        break;

    case ETAG:
        if (!hasdata(parm, p + 1, mod, popt, optcnt))
        {
            goto next;
        }
        break;

    case IMP_OBJ:
        if ((p[1].pe_type == SOBJECT && parm == NULL) ||
            *((char **) (parm + p[1].pe_ucode)) == NULL)
        {
            goto next;
        }
        break;

    default:
        if (*((char **) (parm + p->pe_ucode)) == NULL)
        {
            goto next;
        }
        break;
    }

    return (1);

next:
    return (0);
}

/*
 * determine if the default value is the same as the value in the
 * structure and if so return greater than zero (meaning don't encode this
 * item). On error return NOTOK
 */
int 
same(ptpe *typ, ptpe *dflt, char *parm, modtyp *mod)
{
    int     val;
    int len;
    char   *p1;
    PE      pe = NULL;
    struct qbuf *qb;

    switch (typ->pe_type)
    {
    case INTEGER:
        val = IVAL(mod, dflt) == *(integer *) (parm + typ->pe_ucode);
        break;

#ifdef  PEPSY_REALS
    case REALTYPE:
        val = RVAL(mod, dflt) == *(double *) (parm + typ->pe_ucode);
        break;
#endif

    case BOOLEAN:
        val = IVAL(mod, dflt) == *(char *) (parm + typ->pe_ucode);
        break;

    case ASN_NULL:
        val = 1;                /* Only one value */
        break;

    case SBITSTRING:
        if ((pe = (PE) parm) == NULL)
        {
            val = 1;
            break;
        }
        goto bstring;

    case BITSTRING:
        if ((pe = *(PE *) (parm + typ->pe_ucode)) == NULL)
        {
            val = 1;
            break;
        }
bstring:
        if ((p1 = bitstr2strb(pe, &val)) == NULL)
        {
            pepsylose (mod, typ, pe, "same:bad bitstring\n");
            return (NOTOK);
            /* Should really abort encoding here but how can we comunicate this
             * to the routine that calls us?
             */
        }
bstring2:
        if (val != IVAL(mod, dflt) || bitscmp(PVAL(mod, dflt), p1, val))
        {
            val = 0;
        }
        else
        {
            val = 1;
        }
        if (typ->pe_type != BITSTR_PTR)
        {
            free(p1);
        }
        break;

    case BITSTR_PTR:
        if (typ[1].pe_type != BITSTR_LEN)
        {
            return pepsylose (mod, typ, pe, "same:missing BITSTR_LEN\n");
        }
        if ((p1 = *(char **) (parm + typ->pe_ucode)) == NULL)
        {
            val = 1;
            break;
        }
        val = *(int *) (parm + (typ + 1)->pe_ucode);
        goto bstring2;

    case SOCTETSTRING:
        if ((qb = (struct qbuf *) parm) == NULL)
        {
            val = 1;
            break;
        }
        goto ostring;

    case OCTETSTRING:
        if ((qb = *(struct qbuf **) (parm + typ->pe_ucode)) == NULL)
        {
            val = 1;
            break;
        }
ostring:
        if (ostrcmp(PVAL(mod, dflt), (int ) IVAL(mod, dflt), qb))
        {
            val = 0;
        }
        else
        {
            val = 1;
        }
        break;

    case OCTET_PTR:
        if (typ[1].pe_type != OCTET_LEN)
        {
            return pepsylose (mod, typ, pe, "same:missing OCTET_LEN\n");
        }
        if ((p1 = *(char **) (parm + typ->pe_ucode)) == NULL)
        {
            val = 1;
            break;
        }
        len = *(int *) (parm + (typ + 1)->pe_ucode);
        goto o1string;

    case T_STRING:
        if ((p1 = *(char **) (parm + typ->pe_ucode)) == NULL)
        {
            val = 1;
            break;
        }
        len = (int)strlen(p1);
o1string:
        if (len != IVAL(mod, dflt))
        {
            val = 0;
            break;
        }
        if (memcmp(PVAL(mod, dflt), p1, len))
        {
            val = 0;
        }
        else
        {
            val = 1;
        }
        break;

    case OBJECT:
        if (*(char **) (parm + typ->pe_ucode) == NULL)
        {
            val = 1;            /* to conform with pepy's way of
                                 * doing default */
            break;
        }
        val = same(mod->md_etab[typ->pe_tag] + 1, dflt,
                   *(char **) (parm + typ->pe_ucode), mod);
        break;

    case SOBJECT:
        if ((char *) parm == NULL)
        {
            val = 1;            /* to conform with pepy's way of
                                 * doing default */
            break;
        }
        val = same(mod->md_etab[typ->pe_tag] + 1, dflt, parm, mod);
        break;

    case IMP_OBJ:
        typ++;                  /* fall through */

    case ANY:
    case SANY:
    case SEXTOBJ:
    case EXTOBJ:
    case OBJID:
    case SOBJID:
    case SEQ_START:
    case SET_START:
    case -1:                    /* Just use the pepy method of null
                                 * pointers */
        /*
         * This is the posy/pepy hack way of doing things at the
         * moment
         */
        val = *(char **) (parm + typ->pe_ucode) == NULL;
        break;

    default:
        pepsylose (mod, typ, NULL, "same: %d not implemented\n",
            typ->pe_type);
        return (NOTOK);
    }

    return (val);
}

/*
 * Calculate the next tpe entry in the sequence. Count a sequence as
 * one element
 */
ptpe    *
next_tpe(ptpe *p)
{
    int     level;



    level = 0;
    if (p->pe_type == PE_END)
    {
        pepsylose (NULL, p, NULL,
            "next_tpe:internal error: unexpected PE_END found");
        return (p);
    }

    do
    {
again:
        switch (p->pe_type)
        {
        case SSEQ_START:
        case SSEQOF_START:
        case SSET_START:
        case SSETOF_START:
        case SCHOICE_START:
        case SEQ_START:
        case SEQOF_START:
        case SET_START:
        case SETOF_START:
        case CHOICE_START:
            level++;
            break;

        case UCODE:
        case MEMALLOC:
        case SCTRL:
        case CH_ACT:
        case INTEGER:
        case REALTYPE:
        case BOOLEAN:
        case SANY:
        case ANY:
        case ASN_NULL:
        case OBJECT:
        case SOBJECT:
        case BITSTRING:
        case BITSTR_LEN:
        case SBITSTRING:
        case OCTETSTRING:
        case T_STRING:
        case OCTET_LEN:
        case SOCTETSTRING:
        case OBJID:
        case SOBJID:
        case OPTL:
        case EXTMOD:
        case DFLT_B:
            break;

        case IMP_OBJ:
        case ETAG:
        case EXTOBJ:
        case SEXTOBJ:
        case DFLT_F:
        case OCTET_PTR:
        case BITSTR_PTR:
        case BOPTIONAL:
        case FREE_ONLY:
            p++;
            goto again;

        case PE_END:
            level--;
            break;

        default:
            ferrd(1, "next_tpe: unknown type %d\n", p->pe_type);
        }

        p++;
    }
    while (level > 0 || p->pe_type == DFLT_B);

    return (p);
}

/*
 * Is there a match at for this tag and class pair. Return 1 if yes 0
 * if no We will search through contained objects and through choices
 */
int 
ismatch(ptpe *p, modtyp *mod, unsigned int cl, unsigned int tag)
{
    while (!ISDTYPE(p) && p->pe_type != PE_END)
    {
        p++;
    }
    if (p->pe_type == PE_END)
    {
        return(1);
    }

    switch (p->pe_type)
    {
    case SOBJECT:
    case OBJECT:
        /* Needs to be changed for optional and default */
        return (ismatch(p = mod->md_dtab[p->pe_tag] + 1, mod, cl, tag));

    case SEXTOBJ:
    case EXTOBJ:
        if (p[1].pe_type != EXTMOD)
        {
            dmp_tpe("ismatch: missing EXTMOD", p, mod);
            ferr(1, "ismatch:internal error\n");
        }
        return (ismatch(EXT2MOD(mod, (p + 1))->md_dtab[p->pe_tag] + 1,
                        EXT2MOD(mod, (p + 1)), cl, tag));

    case CHOICE_START:
    case SCHOICE_START:
        for (p++; p->pe_type != PE_END; p = next_tpe (p))
        {
            if (!ISDTYPE(p))
            {
                continue;
            }
            if (ismatch(p, mod, cl, tag))
            {
                return (1);
            }
        }
        return (0);

    case SANY:
        return (1);

    case ANY:
        if (STAG(p) == -1)
        {
            return (1);
        }
        /* else fall through - not sure if this is needed */

    default:
        return (tag == TAG(p) && cl == CLASS(p));
    }
}

/*
 * find the data entry that goes with this DFLT_F entry
 * bascially skip over any ETAGS that (an arbitary number but almost always 1)
 */
ptpe    *
fdflt_f(ptpe *p)
{
    if (p->pe_type != DFLT_F)
        ferr(1, "fdlt_f:Internal Error missing DFLT_F\n");
    
    for (p++; p->pe_type != PE_END; p++)
    {
        if (p->pe_type != ETAG)
        {
            return (p);
        }
    }
    ferr(1, "fdlt_f:Internal Error PE_END found\n");
    
    /*NOTREACHED*/
    return NULL;
}

/*
 * find the DFLT_B entry
 */
ptpe    *
fdflt_b(ptpe *p)
{
    for (p++; p->pe_type != PE_END; p++)
    {
        if (p->pe_type == DFLT_B)
        {
                return (p);
        }
    }

    ferr(1, "fdflt_b:Internal Error PE_END found\n");
    
    /*NOTREACHED*/
    return NULL;
}

/****************************************************************************
 *
 * The ISODE is openly available but is NOT in the public domain.  You
 * are allowed and encouraged to take this software and build commercial
 * products.  However, as a condition of use, you are required to ``hold
 * harmless'' all contributors.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that this notice and the reference to this notice appearing in each
 * software module be retained unaltered, and that the name of any
 * contributors shall not be used in advertising or publicity pertaining
 * to distribution of the software without specific written prior permission.
 * No contributor makes any representations about the suitability of this
 * software for any purpose.  It is provided ``as is'' without express or
 * implied warranty.
 * 
 *      ALL CONTRIBUTORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 *      SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 *      AND FITNESS FOR THE PARTICULAR PURPOSE, TITLE, AND NON-INFRINGEMENT.
 *
 *      IN NO EVENT SHALL ANY CONTRIBUTOR BE LIABLE FOR ANY SPECIAL,
 *      INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT, OR
 *      OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE
 *      USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ***************************************************************************/

