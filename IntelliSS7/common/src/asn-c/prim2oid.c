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
 * LOG: $Log: prim2oid.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:03  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:15  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:17  mmiers
 * LOG: Begin PR7.
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
 * LOG: Revision 3.2  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:39  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:33  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/02/26 15:41:08  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:36  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.8  1998/10/22 19:28:10  mmiers
 * LOG: Continue making PSAP threadsafe.
 * LOG:
 * LOG: Revision 1.7  1998/10/22 16:28:33  mmiers
 * LOG: Getting pepsy thread-safe.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:32  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:30:53  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:00  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:32:59  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * prim2oid.c - presentation element to object identifier
 */
#include <asn-c/AsnC.h>

#ident "$Id: prim2oid.c,v 9.1 2005/03/23 12:53:03 cvsadmin Exp $"

OID
prim2oid (PE pe)
{
    unsigned int i, *ip;
    PElementData dp, ep;
    OID	o = NULL;

    if (pe->pe_form != PE_FORM_PRIM ||
        (dp = pe->pe_prim) == NULL ||
        pe->pe_len == 0)
    {
        return (OID)pe_seterr (pe, PE_ERR_PRIM, NULL);
    }
    
    ep = dp + pe->pe_len;
    
    for (i = 1; dp < ep; i++)
    {
        /* another whacko OSI encoding... */
        if (*dp == 0x80)
        {
            return (OID)pe_seterr (pe, PE_ERR_OID, NULL);
        }
        
        while (*dp++ & 0x80)
        {
            if (dp > ep)
            {
                return (OID)pe_seterr (pe, PE_ERR_OID, NULL);
            }
        }
    }
    
    if ((o = (OID) malloc(sizeof(OIDentifier))) == NULL)
    {
        return (OID)pe_seterr (pe, PE_ERR_NMEM, NULL);
    }

    if ((ip = (unsigned int *) malloc ((i + 1) * sizeof *ip)) == NULL)
    {
        free(o);

        return (OID)pe_seterr (pe, PE_ERR_NMEM, NULL);
    }
    
    o->oid_elements = ip, o->oid_nelem = (int)i;
    
    for (dp = pe->pe_prim; dp < ep; )
    {
        i = 0;
        do
        {
            i <<= 7; 
            i |= *dp & 0x7f;
        }
        while (*dp++ & 0x80);
        
        if (ip != o->oid_elements)
        {
            *ip++ = i;
        }
        else
        {
            if (i < 40)
            {
                *ip++ = 0, *ip++ = i;
            }
            else
            {
                if (i < 80)
                {
                    *ip++ = 1, *ip++ = i - 40;
                }
                else
                {
                    *ip++ = 2, *ip++ = i - 80;
                }
            }
        }
    }
    
    return o;
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

