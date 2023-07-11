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


/**
 *
 *   @file  CMAPIErlbf.h
 *
 *  @brief  Implementation of CMGR Method Implementors for CMAPI
 *  Calls.
 *
 **/

#ifndef __CMAPIERLBF_H_
#define __CMAPIERLBF_H_

#include <Compo.h>
#include <HA.h>
#include <HA_def.h>
#include <Compo_def.h>
#include <dreconfig_def.h>
#include <string.h>
#include "MysqlInterfacePB.h"

class mysql_cli_interface_PB;

class CMAPIErlbf  : public CmgrComponents , public FetchConfiguration, public CMgrHAInterface
{
	public:

		mysql_cli_interface_PB *mysqlHandler;

		CMAPIErlbf(string sHostName,string sUserName,string sPassword,string sDataBase);
		~CMAPIErlbf();
		int CMgrGetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);
		int CMgrSetLBPeerConfigs(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);
		int FetchErlbfConfiguration(LBPeerGroupReq *Req,LBPeerGroupResp *Resp);

        // Response call backs for ERLBF call backs
        int ErlbfSetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp);

		int FetchDTFConfiguration(DynDictionaryRequest *Req,DynDictionaryResponse *Resp);
		int CMgrDTFConfig(DynDictionaryRequest *Req,DynDictionaryResponse *Resp);

        // Response call backs for DTF call backs
        int DreDTFConfigRespCbk(DynDictionaryResponse *Resp);

		int CMgrAMSetConfiguration(AvaMgrConfig *Request,AvaMgrConfigResp *Response);
		int CMgrRMSetConfiguration(RepMgrConfig *Request,RepMgrConfigResp *Response);
		int CMgrDreSetConfiguration(DreHAConfig *Request,DreHAConfigResp *Response);
		int FetchAvaMgrConfiguration(AvaMgrConfig *Request,AvaMgrConfigResp *Response);
		int FetchRepMgrConfiguration(RepMgrConfig *Request,RepMgrConfigResp *Response);
		int FetchDreHAConfiguration(DreHAConfig *Request,DreHAConfigResp *Response);

	private:

};

#endif // __CMAPIMGR_H_
