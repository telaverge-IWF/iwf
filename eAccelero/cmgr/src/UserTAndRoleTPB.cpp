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


#include <CMgrDbInterface.h>

using namespace std;

void UserTAndRoleTPBQuery::sql_UserAndRole_Create_Select_Query(UserInfo *userConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select UserT.Username,UserT.Previlage,UserT.Password,ROLE_TB.ROLE from UserT inner join ROLE_TB on UserT.RoleID = ROLE_TB.ROLE_ID and ");

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    if(userConfigReq->has_username())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"UserT.Username='%s' and ",userConfigReq->username().c_str());
    }

    if(userConfigReq->has_usergroup())
    {
        ::Group *localGroup = userConfigReq->mutable_usergroup();
        if(localGroup->has_groupname())
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ROLE_TB.ROLE='%s' and ",localGroup->groupname().c_str());
    }

    pStatement[strlen(pStatement) - REMOVE_FOUR_CHARATERS] = '\0';

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

}


