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

#ifndef __CMAPISTATSLIB_H_
#define __CMAPISTATSLIB_H_


using namespace std;

#include <string.h>
#include "StackStats.h"
#include "StackStats_caller.h"
#include "InterfaceStat.h"
#include "InterfaceStat_caller.h"
#include "CMAPICommon.h"

// Common Management Library Class

class CMAPIStatsConfig :public Stub::StackStatsRespCbk , public Stub::InterfaceStatRespCbk
{
public:
 CMAPIStatsConfig() {}
 ~CMAPIStatsConfig() {}

 int InitializeLibrary();

//CMAPI Stack Stats API

int GetApplicationSpecificStats(ApplicationspecStatsReq& req, ApplicationspecStatsResp& resp);
int GetStackIndicationStats(StackIndicationStatsReq& req, StackIndicationStatsResp& resp);
int GetGenericErrorStats(GenericErrorStatsReq& req, GenericErrorStatsResp& resp);
int GetGenericStats(GenericStatsReq& req, GenericStatsResp& resp);
int ResetApplicationspecStats(ResetApplicationspecStatsReq& req, ResetApplicationspecStatsResp& resp);
int ResetStackIndicationStats(ResetStackIndicationStatsReq& req, ResetStackIndicationStatsResp& resp);
int ResetGenericErrorStats(ResetGenericErrorStatsReq& req, ResetGenericErrorStatsResp& resp);
int ResetGenericStats(ResetGenericStatsReq& req, ResetGenericStatsResp& resp);

//CMAPI Interface Stats API
int GetInterfaceStats(InterfaceStatsReq& req, InterfaceStatsResp& resp);
int ResetInterfaceStats(InterfaceStatsReq& req, ResetInterfaceStatsResp& resp);

//Response Callbacks for Interface Stats Implementation Methods
int FetchInterfaceStatsRespCbk(InterfaceStatsResp *resp);
int ResetInterfaceStatsRespCbk(ResetInterfaceStatsResp *resp);


//Response Callbacks for Stack Stats Implementation Methods
int FetchApplicationSpecificMessageStatsRespCbk(ApplicationspecStatsResp *resp);
int FetchStackIndicationStatsRespCbk(StackIndicationStatsResp *resp);
int ResetApplicationSpecificMessageStatsRespCbk(ResetApplicationspecStatsResp *resp);
int ResetStackIndicationStatsRespCbk(ResetStackIndicationStatsResp *resp);
int FetchGenericErrorStatsRespCbk(GenericErrorStatsResp *resp);
int ResetGenericErrorStatsRespCbk(ResetGenericErrorStatsResp *resp);
int FetchGenericStatsRespCbk(GenericStatsResp *resp);
int ResetGenericStatsRespCbk(ResetGenericStatsResp *resp);



private:
    int IsResponseOK(InterfaceStatsResp *Resp);
    int IsResponseOK(ResetInterfaceStatsResp *Resp);
    
    Stub::StackStats     *m_StackStatsObj;
    Stub::InterfaceStat  *m_InterfaceStatObj;
    CMAPIIntSync         *m_CMAPIResponse;
    volatile bool         m_SendSuccess;
};

#endif  // __CMAPISTATSLIB_H_
