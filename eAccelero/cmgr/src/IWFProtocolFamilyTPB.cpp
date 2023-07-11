/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#include <CMgrIwfDbInterface.h>

using namespace std;


void IWFProtocolFamilyTPBQuery::sql_ProtocolFamily_Create_Select_Query(IwfLocalHostConfig *IwfLocalHostConfigReq,char *pStatement)
{
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_PROTOCOL_FAMILY_TB"); 
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfLocalHostConfigReq->has_protocolid())
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE," IWF_PROTOCOL_FAMILY_ID = %d and ",IwfLocalHostConfigReq->has_protocolid());
    }

    sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

