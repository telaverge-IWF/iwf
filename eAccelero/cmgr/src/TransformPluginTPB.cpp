/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

void TransformPluginTPBQuery::sql_PluginConfig_Create_Check_Modifcation_Query(TransformPluginConfig *pTransformPluginConfig, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select PLUGIN_ID from TRANSFORM_PLUGIN_TB where PLUGIN_NAME = '%s'",pTransformPluginConfig->pluginname().c_str());

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}


void TransformPluginTPBQuery::sql_PluginConfig_Create_Mod_Query(TransformPluginConfig *pTransformPluginConfig, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update TRANSFORM_PLUGIN_TB set ");

    if(pTransformPluginConfig->has_ispluginenabled())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"IS_ENABLED=%d,",pTransformPluginConfig->ispluginenabled());
    }

    if(pTransformPluginConfig->has_pluginconfigfile())
    {
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"CONFIG_FILE='%s',",pTransformPluginConfig->pluginconfigfile().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';

    if(strlen(pStatement) < MAX_STATEMENT_SIZE)
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement),"where PLUGIN_NAME='%s'",pTransformPluginConfig->pluginname().c_str());

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

#if 0
void TransformPluginTPBQuery::sql_PluginConfig_Create_Select_Query(DictionaryConfig *pDictionaryConfig, char *pStatement)
{
    DLOG_NONE(" > %s:%d \n",__FUNCTION__,__LINE__);

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  TRANSFORM_PLUGIN_TB");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pTransformPluginConfig->has_dictionaryid1())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID1=%d and ",pTransformPluginConfig->dictionaryid1());
    }

    if(pTransformPluginConfig->has_dictionaryid2())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID2=%d and ",pTransformPluginConfig->dictionaryid2());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s:%d \n",__FUNCTION__,__LINE__);
}
#endif
void TransformPluginTPBQuery::sql_PluginConfig_Create_Select_Query(TransformPluginConfig *pTransformPluginConfig, char *pStatement)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  TRANSFORM_PLUGIN_TB");

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(pTransformPluginConfig->has_pluginname())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"PLUGIN_NAME='%s' and ",pTransformPluginConfig->pluginname().c_str());
    }

    if(pTransformPluginConfig->has_dictionaryid1())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID1=%d and ",pTransformPluginConfig->dictionaryid1());
    }

    if(pTransformPluginConfig->has_dictionaryid2())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"DICTIONARY_ID2=%d and ",pTransformPluginConfig->dictionaryid2());
    }

    if(pTransformPluginConfig->has_ispluginenabled())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"IS_ENABLED=%d and ",pTransformPluginConfig->ispluginenabled());
    }

    if(pTransformPluginConfig->has_pluginconfigfile())
    {
        iFlag = 1;
        if(strlen(sWhereStatement) < MAX_STATEMENT_SIZE)
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE - strlen(sWhereStatement),"CONFIG_FILE='%s' and ",pTransformPluginConfig->pluginconfigfile().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        if(strlen(pStatement) < MAX_STATEMENT_SIZE)
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE - strlen(pStatement)," %s ",sWhereStatement);
    }
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}
