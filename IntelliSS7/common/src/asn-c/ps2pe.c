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
 * LOG: $Log: ps2pe.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:04  cvsadmin
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
 * LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
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
 * LOG: Revision 3.1  2000/08/16 00:04:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:40  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:36  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/02/26 15:41:08  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:47:59  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:44  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:45  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.8  1998/10/22 20:29:26  mmiers
 * LOG: Finish reentrancy fixes, round one.
 * LOG:
 * LOG: Revision 1.7  1998/10/21 17:48:34  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 04:30:56  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 02:41:03  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.4  1998/10/20 23:33:01  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * ps2pe.c - presentation stream to presentation element
 */

#include <asn-c/AsnC.h>

#ident "$Id: ps2pe.c,v 9.1 2005/03/23 12:53:04 cvsadmin Exp $"

int  ps_read_id (PS ps, int top, PElementClass* classp,
                 PElementForm* form, PElementID *id);
int  ps_read_len (PS ps, PElementLen *len);
int  ps_read_cons (PS ps, PE *pe, PElementLen len);

PE
ps2pe_aux (PS ps, int top, int all)
{
    PElementLen len;
    PElementClass   classp;
    PElementForm    form;
    PElementID	    id;
    PE	    pe;
    PE	    rpe = NULL;	/* for lint */
    
    if (top && ps_prime (ps, 0) == NOTOK)
    {
        return NULL;
    }
    
    if (ps_read_id (ps, top, &classp, &form, &id) == NOTOK)
    {
        return NULL;
    }
    
    if ((pe = pe_alloc (classp, form, id)) == NULL)
    {
        return (PE)ps_seterr (ps, PS_ERR_NMEM, NULL);
    }
    
    if (ps_read_len (ps, &pe->pe_len) == NOTOK)
    {
        goto you_lose;
    }
    
    if (all == 0)
    {
        return pe;
    }
    
    len = pe->pe_len;
    switch (pe->pe_form)
    {
    case PE_FORM_PRIM: 
        if (len == PE_LEN_INDF)
        {
            rpe = ps_seterr (ps, PS_ERR_INDF, rpe);
            goto you_lose;
        }
        
        if (len > 0)
        {
            if (ps->ps_inline)
            {	/* "ultra-efficiency"... */
                if (ps->ps_base == NULL || ps->ps_cnt < len)
                {
                    rpe = ps_seterr (ps, PS_ERR_EOF, rpe);
                    
                    goto you_lose;
                }
                
                pe->pe_inline = 1;
                pe->pe_prim = (PElementData) ps->ps_ptr;
                ps->ps_ptr += len, ps->ps_cnt -= len;
                ps->ps_byteno += len;
            }
            else
            {
                if ((pe->pe_prim = PEDalloc (len)) == NULL)
                {
                    pe = ps_seterr (ps, PS_ERR_NMEM, rpe);
                    
                    goto you_lose;
                }
                if (ps_read (ps, pe->pe_prim, len) == NOTOK)
                {
                    goto you_lose;
                }
            }
        }
        break;
        
    case PE_FORM_CONS: 
        if (len != 0 && ps_read_cons (ps, &pe->pe_cons, len) == NOTOK)
        {
            goto you_lose;
        }
        break;
    }
    
    if (top && ps_prime (ps, -1) == NOTOK)
    {
        goto you_lose;
    }
    
    return pe;
    
you_lose:
    pe_free (pe);
    
    return NULL;
}

#define pe_id_overshift \
    (PE_ID_MASK << (PE_ID_BITS - PE_ID_SHIFT))

int
ps_read_id (PS ps, int top, PElementClass* classp,
            PElementForm* form, PElementID *id)
{
    byte    c, d;
    PElementID j;
    
    if (ps_read (ps, &c, 1) == NOTOK)
    {
        if (top && ps->ps_errno == PS_ERR_EOF)
        {
            ps->ps_errno = PS_ERR_NONE;
        }
        
        return NOTOK;
    }
    
    *classp = (PElementClass)(((int)(c & PE_CLASS_MASK)) >> PE_CLASS_SHIFT);
    *form = (PElementForm)(((int)(c & PE_FORM_MASK)) >> PE_FORM_SHIFT);
    j = (c & PE_CODE_MASK);
    
    if (j == PE_ID_XTND)
    {
        for (j = 0;; j <<= PE_ID_SHIFT)
        {
            if (ps_read (ps, &d, 1) == NOTOK)
            {
                if (ps->ps_errno == PS_ERR_EOF)
                {
                    ps->ps_errno = PS_ERR_EOFID;
                }
                
                return NOTOK;
            }
            
            j |= d & PE_ID_MASK;
            if (!(d & PE_ID_MORE))
            {
                break;
            }
            if (j & pe_id_overshift)
            {
                return ps_seterr (ps, PS_ERR_OVERID, NOTOK);
            }
        }
    }
    *id = j;
    
    return OK;
}

int
ps_read_len (PS ps, PElementLen *len)
{
     int    i;
     PElementLen j;
    byte    c;

    if (ps_read (ps, &c, 1) == NOTOK)
    {
	return NOTOK;
    }

    if ((i = c) & PE_LEN_XTND)
    {
	if ((i &= PE_LEN_MASK) > sizeof (PElementLen))
        {
	    return ps_seterr (ps, PS_ERR_OVERLEN, NOTOK);
        }

	if (i)
        {
	    for (j = 0; i-- > 0;)
            {
		if (ps_read (ps, &c, 1) == NOTOK)
                {
		    if (ps->ps_errno == PS_ERR_EOF)
                    {
			ps->ps_errno = PS_ERR_EOFLEN;
                    }
		    return NOTOK;
		}

		j = (j << 8) | (c & 0xff);
	    }
	    *len = j;
	}
	else
        {
	    *len = PE_LEN_INDF;
        }
    }
    else
    {
	*len = i;
    }

    return OK;
}

int
ps_read_cons (PS ps, PE *pe, PElementLen len)
{
    int    cc;
    PE	    p, q;
    
    cc = ps->ps_byteno + len;
    
    if ((p = ps2pe_aux (ps, 0, 1)) == NULL)
    {
no_cons:
    return NOTOK;
    }
    *pe = p;
    
    if (len == PE_LEN_INDF)
    {
        if (p->pe_class == PE_CLASS_UNIV && p->pe_id == PE_UNIV_EOC)
        {
            pe_free (p);
            *pe = NULL;
            
            return OK;
        }
        
        for (q = p; (p = ps2pe_aux (ps, 0, 1)) != NULL; q = q->pe_next = p)
        {
            if (p->pe_class == PE_CLASS_UNIV && p->pe_id == PE_UNIV_EOC)
            {
                pe_free (p);
                
                return OK;
            }
        }
        
        goto no_cons;
    }
    
    for (q = p;; q = q->pe_next = p)
    {
        if (cc < ps->ps_byteno)
        {
            return ps_seterr (ps, PS_ERR_LEN, NOTOK);
        }
        
        if (cc == ps->ps_byteno)
        {
            return OK;
        }
        if ((p = ps2pe_aux (ps, 0, 1)) == NULL)
        {
            goto no_cons;
        }
    }
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

