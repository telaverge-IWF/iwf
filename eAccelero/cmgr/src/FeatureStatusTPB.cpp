/*******************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/

/*
 * FILE:   FeatureStatusTPB.cpp
 * Author: Hemanth
 *
 * Created on Nov 30, 2014, 12:58 PM
 */


#include <CMgrDbInterface.h>

using namespace std;

void FeatureStatusTPBQuery::sql_FeatureStatus_Create_Check_Modifcation_Query(string featureName, char *pStatement)
{
	snprintf(pStatement,MAX_STATEMENT_SIZE,"select FEATURE_ID from FEATURE_STATUS_TB where FEATURE_NAME='%s'", featureName.c_str());
}

void FeatureStatusTPBQuery::sql_FeatureStatus_Create_Select_Query(string featureName, char *pStatement)
{
	char sWhereStatement[MAX_STATEMENT_SIZE]	= {0};
	snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from FEATURE_STATUS_TB ");
	snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

	DLOG_NONE(" > %s \n",__FUNCTION__);

    if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
    {
        snprintf(sWhereStatement + strlen(sWhereStatement),(MAX_STATEMENT_SIZE - strlen(sWhereStatement)),"FEATURE_NAME='%s' and ", featureName.c_str());
    }

    sWhereStatement[strlen(sWhereStatement) - 4] = '\0';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
    {
        snprintf(pStatement + strlen(pStatement),(MAX_STATEMENT_SIZE - strlen(pStatement))," %s ",sWhereStatement);
    }

	DLOG_NONE(" < %s \n",__FUNCTION__);
}

void FeatureStatusTPBQuery::sql_FeatureStatus_Create_Mod_Query(string featureName, bool enable, char *pStatement)
{
	DLOG_NONE(" > %s \n",__FUNCTION__);

	snprintf(pStatement,MAX_STATEMENT_SIZE,"update FEATURE_STATUS_TB set ");

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
    {
	    snprintf(pStatement + strlen(pStatement),(MAX_STATEMENT_SIZE - strlen(pStatement)),"IS_ENABLED=%d,",enable);
    }

	pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
    {
        snprintf(pStatement + strlen(pStatement),(MAX_STATEMENT_SIZE - strlen(pStatement)),"where FEATURE_NAME='%s'",featureName.c_str());
    }

	DLOG_NONE(" < %s \n",__FUNCTION__);
}
