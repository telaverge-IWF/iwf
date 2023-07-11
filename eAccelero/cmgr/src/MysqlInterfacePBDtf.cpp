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


#include <CMAPICMgr.h>
#include <CMgrDbInterface.h>

using namespace std;


DbStatus_e mysql_cli_interface_PB::mysql_DictionaryConfig_Get_Config_Reqs(DynDictionaryRequest *pDynDictionaryConfig,DynDictionaryResponse *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    ::Dictionary localDictionary;

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);

    sql_DictionaryConfig_Create_Select_Query(&localDictionary,sStatement);
    if (mysql_exec_get_query(sStatement,&pRes) == DRE_DB_FAIL)
    {
        if(pRes != NULL)    
            delete pRes;

        PRINTF("%s:%d\n",__FUNCTION__,__LINE__);    
        return DRE_DB_FAIL;
    }

    mysql_DictionaryConfig_resultset_to_protoBuff(pRes,resp);
    delete pRes;

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    return DRE_DB_SUCCESS;

}

DbStatus_e mysql_cli_interface_PB::mysql_DictionaryConfig_resultset_to_protoBuff(sql::ResultSet *pRes,DynDictionaryResponse *resp)
{
    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    try
    {
        if(pRes->rowsCount() == 0)
        {
            return DRE_DB_SUCCESS;
        }


        while(pRes->next())
        {
            ::Dictionary *pDictionary = resp->add_dictionaries();
            pDictionary->set_dictionaryname(pRes->getString("DICTIONARY_NAME"));
            pDictionary->set_interfacename(pRes->getString("INTERFACE_NAME"));
            pDictionary->set_releasenum(pRes->getString("RELEASE_NUMBER"));
            pDictionary->set_dictionaryid(pRes->getInt("DICTIONARY_ID"));


        }   
    }
    catch (sql::SQLException &e)
    {
        cout << "#\t\t unix://path_to_mysql_socket.sock caused expected exception" << endl;
        cout << "#\t\t " << e.what() << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
        return DRE_DB_FAIL;
    }

    PRINTF("%s:%d \n",__FUNCTION__,__LINE__);
    return DRE_DB_SUCCESS;

}
