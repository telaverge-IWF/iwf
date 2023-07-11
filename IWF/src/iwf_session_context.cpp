/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2014 IntelliNet Technologies, Inc.                 *
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
 */

#include "iwf.pb.h"
#include "iwf_prot_defines.h"
#include "iwf_prot_utils.h"
#include "iwf_transaction_manager.h"

void SessionCtxt::SetPbSccpParameters(SCCPParameters& sccpParams)
{
    pbSCCPParameters* sccpParameters = m_pbIwfSessionCtxtData.mutable_sccpparameters();
    pbSccpAddress *cpa_itu = sccpParameters->mutable_sccpcallingpartyaddr();
    pbSccpAddress *cpd_itu = sccpParameters->mutable_sccpcalledpartyaddr();
    // TODO:: fill the necessary params

    FillPbFromSccpAddress(&sccpParams.cpa_itu, cpa_itu);
    FillPbFromSccpAddress(&sccpParams.cpd_itu, cpd_itu);

    sccpParameters->set_opc(sccpParams.m_opc);
    sccpParameters->set_dpc(sccpParams.m_dpc);
    sccpParameters->set_isroutebygt(sccpParams.isRouteByGT);
}

void SessionCtxt::FillPbFromSccpAddress(SCCPGTTInfo* sccpAddr, pbSccpAddress* outPbSccpAddr)
{
    if (!sccpAddr || !outPbSccpAddr)
    {
        return;
    }

    if (sccpAddr->m_addrIndicator & SCCP_CPA_HAS_PC)
    {
        outPbSccpAddr->set_haspc(true);
        outPbSccpAddr->set_pointcode(sccpAddr->m_pointcode);
    }

    if (sccpAddr->m_addrIndicator & SCCP_CPA_HAS_SSN)
    {
        outPbSccpAddr->set_hasssn(true);
        outPbSccpAddr->set_ssn(sccpAddr->m_ssn);
    }

    if(sccpAddr->m_gttLength)
    {
        outPbSccpAddr->set_globaltitle(true);
        outPbSccpAddr->set_gtttype(sccpAddr->m_gttType);
        outPbSccpAddr->set_gttlen(sccpAddr->m_gttLength);
        outPbSccpAddr->set_globtitle((void*)sccpAddr->m_gttInfo, sccpAddr->m_gttLength);
    }

    if (sccpAddr->m_addrIndicator & SCCP_CPA_ROUTE_SSN)
    {
        outPbSccpAddr->set_routepcssn(true);
    }

    if (sccpAddr->m_addrIndicator & SCCP_CPA_ROUTE_NAT)
    {
        outPbSccpAddr->set_internationalroute(false);
    }
    else
        outPbSccpAddr->set_internationalroute(true);
}

void SessionCtxt::FillPbFromSccpAddress(SCCP_Address* sccpAddr, pbSccpAddress* outPbSccpAddr)
{
    if (!sccpAddr || !outPbSccpAddr)
    {
        return;
    }
    if (sccpAddr->HasPointCode())
    {
        outPbSccpAddr->set_haspc(true);
        outPbSccpAddr->set_pointcode(sccpAddr->GetPointCode());
    }
    if (sccpAddr->HasSSN())
    {
        outPbSccpAddr->set_hasssn(true);
        outPbSccpAddr->set_ssn(sccpAddr->GetSSN());
    }

    if(sccpAddr->HasGlobalTitle())
    {
        ITS_USHORT gttLength;
        ITS_OCTET  gttType;
        ITS_OCTET  gttInfo[64] = {0};
        sccpAddr->GetGlobalTitle(gttType, gttInfo, gttLength);
        outPbSccpAddr->set_globaltitle(true);
        outPbSccpAddr->set_gtttype(gttType);
        outPbSccpAddr->set_gttlen(gttLength);
        outPbSccpAddr->set_globtitle((void*)gttInfo, gttLength);
    }

    if (sccpAddr->IsRoutedByPCSSN())
    {
        outPbSccpAddr->set_routepcssn(true);
    }

    if (sccpAddr->IsInternationalRouting())
    {
        outPbSccpAddr->set_internationalroute(true);
    }
    else
    {
        outPbSccpAddr->set_internationalroute(false);
    }

}

void SessionCtxt::GetCalledPartyAddr(SCCP_CalledPartyAddr* cpd_itu)
{
    FillSccpAddressFromPb(m_pbIwfSessionCtxtData.sccpparameters().sccpcalledpartyaddr(), (SCCP_Address*)(cpd_itu));
}

void SessionCtxt::GetCallingPartyAddr(SCCP_CallingPartyAddr* cpa_itu)
{
    FillSccpAddressFromPb(m_pbIwfSessionCtxtData.sccpparameters().sccpcallingpartyaddr(), (SCCP_Address*)(cpa_itu));
}

void SessionCtxt::GetOldCallingPartyAddress(SCCP_CallingPartyAddr* cpa_itu)
{
    FillSccpAddressFromPb(m_pbIwfSessionCtxtData.oldcpaitu(), (SCCP_Address*)(cpa_itu));
}

void SessionCtxt::UpdateSessionContext(SCCP_CallingPartyAddr& cpa_itu, ITS_UINT opc)
{
    DLOG_DEBUG("SessionCtxt::UpdateSessionContext Entry");
    SetOldCallingPartyAddress(m_pbIwfSessionCtxtData.sccpparameters().sccpcallingpartyaddr());
    pbSccpAddress *sccpCPA = m_pbIwfSessionCtxtData.mutable_sccpparameters()->mutable_sccpcallingpartyaddr();
    FillPbFromSccpAddress((SCCP_Address*)&cpa_itu, sccpCPA);
    SetOldOPC(GetPbSccpParameters().opc());
    m_pbIwfSessionCtxtData.mutable_sccpparameters()->set_opc(opc);
    DLOG_DEBUG("SessionCtxt::UpdateSessionContext Exit");
}

void SessionCtxt::FillSccpAddressFromPb(const pbSccpAddress& pbSccpAddr, SCCP_Address* sccpAddr) 
{
    DLOG_DEBUG("SessionCtxt::FillSccpAddressFromPb Entry");
    if (pbSccpAddr.has_pointcode())
        sccpAddr->SetPointCode(pbSccpAddr.pointcode());
    if (pbSccpAddr.has_ssn())
        sccpAddr->SetSSN(pbSccpAddr.ssn());
    if (pbSccpAddr.has_routepcssn())
        sccpAddr->SetRouteByPCSSN(pbSccpAddr.routepcssn());
    if (pbSccpAddr.has_internationalroute())
    {
        sccpAddr->SetInternationalRouting(pbSccpAddr.internationalroute());
    }

    if (pbSccpAddr.has_globtitle())
    {
        const std::string& gtdigits = pbSccpAddr.globtitle();
        //ITS_OCTET gttInfo[32] = {0};
        //int gttLen = IWFUtils::StringToTBCD(gtdigits, gttInfo, gtdigits.length());
        //sccpAddr->SetGlobalTitle(pbSccpAddr.gtttype(), gttInfo,gttLen);
        DLOG_DEBUG("SessionCtxt::FillSccpAddressFromPb pbSccpAddr.gtttype() = %d", pbSccpAddr.gtttype());
        sccpAddr->SetGlobalTitle(pbSccpAddr.gtttype(), (const ITS_OCTET*)gtdigits.c_str() , gtdigits.length());
    }
    DLOG_DEBUG("SessionCtxt::FillSccpAddressFromPb Exit");
}

