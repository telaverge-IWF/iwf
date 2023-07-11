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
extern std::map<int,std::string> iwfErrorMap;


CMgrIwfDbInterface::CMgrIwfDbInterface(string sHostName,string sUserName,string sPassword,string sDataBase,ConfigManager *pConfigManager,ConfigManagerAlarms *pConfigManagerAlarms):
    m_dbHandle(sHostName,sUserName,sPassword,sDataBase,pConfigManagerAlarms)
{
    m_ConfigManager = pConfigManager;
    m_ConfigManagerAlarms = pConfigManagerAlarms;
}

void CMgrIwfDbInterface::mysql_set_error_for_iwfCfgResp_Config_Reqs(IWFCfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(iwfErrorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (iwfErrorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}



