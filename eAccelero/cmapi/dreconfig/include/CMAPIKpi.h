/* ********************************-*-H-*-************************************
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

#ifndef __CMAPIKPI_H_
#define __CMAPIKPI_H_


using namespace std;

#include <string.h>

#include "CMAPICommon.h"
#include "ResourceUsageStat_caller.h"
#include "AvaMgrKPIInterface_caller.h"
#include "DreKPIInterface_caller.h"
#include "ComponentDefines.h"

// Common Management Library Class

class CMAPIKPIConfig :
    public Stub::ResourceUsageStatRespCbk,public Stub::AvaMgrKPIInterfaceRespCbk,public Stub::DreKPIInterfaceRespCbk
{
public:
 CMAPIKPIConfig() {}
 ~CMAPIKPIConfig() {}

 int InitializeLibrary();

//KPI
int GetClusterInfoReq(ClusterInfoResp& resp);
int GetActiveSystemResource(SystemResourceReq& req,SystemResourceResp& resp);
int GetStandBySystemResource(SystemResourceReq& req,SystemResourceResp& resp);
int GetActiveProcessStateRequest(ProcessStateReq& req,ProcessStateResp& resp);
int GetStandByProcessStateRequest(ProcessStateReq& req,ProcessStateResp& resp);
int GetApplicationKPIReq(DiaGeneralKPIReq& req,DiaGeneralKPIResp& resp);
int GetTpsReq(TPSReq& req,TPSResp& resp);
int GetCasReq(DiaCASReq& req, DiaCASResp& resp);

//KPI RespCallback
int FetchSystemResourceUsageRespCbk(SystemResourceResp *Resp);
int FetchClusterInfoRespCbk(ClusterInfoResp *Resp);
int FetchApplicationKPIRespCbk(DiaGeneralKPIResp*Resp);
int FetchTPSRespCbk(TPSResp *Resp);
int FetchCASRespCbk(DiaCASResp *Resp);
int FetchProcessStateRespCbk(ProcessStateResp *Resp);

private:

  Stub::ResourceUsageStat *m_ActiveRsrcMgrCallerObj;
  Stub::ResourceUsageStat *m_StandByRsrcMgrCallerObj;
  Stub::AvaMgrKPIInterface *m_MutiActiveAvaMgrCallerObj;
  Stub::AvaMgrKPIInterface *m_StandByAvaMgrCallerObj;
  Stub::AvaMgrKPIInterface *m_ActiveAvaMgrCallerObj;
  Stub::DreKPIInterface *m_ActiveDRECallerObj;
  CMAPIIntSync        *m_CMAPIResponse;

  static const unsigned int m_waitTime = 32000000;
  ErrorDetails m_lastError;
  volatile bool m_SendSuccess;
};

#endif  // __CMAPILIB_H_
