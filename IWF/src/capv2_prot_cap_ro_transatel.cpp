#include "iwf.h"
#include "iwf_prot_cap_ro_transatel.h"
#include "iwf_prot_utils.h"
#include <sstream>
#include <bitset>

using namespace cap_v2;


int TransatelCAPToRoHandler::PopulateV2SpecificIE(IwfFsm *ctxt,
        const cap_v2::InitialDPArg& in,
        Ro_TSL::CreditControlRequest *&inout)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;

    TransatelCAPRoTransactionContext* userData = NULL; 
    userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    //Set CAP-Information AVP values
    //Set Diameter Base AVP values 
    if(true != inout->containsServiceInformation())
    {
        DLOG_ERROR("PopulateV2SpecificIE:: ServiceInformation not present in Incoming CCR param.");
        return !ITS_SUCCESS;    
    }
    else if(true != inout->getServiceInformation().containsCSInformation())
    {
        DLOG_ERROR("PopulateV2SpecificIE:: CSInformation not present in Incoming CCR param.");
        return !ITS_SUCCESS;    
    }
    else if(true != inout->getServiceInformation().getCSInformation().containsCAPInformation())
    {
        DLOG_ERROR("PopulateV2SpecificIE:: CAPInformation not present in Incoming CCR param.");
        return !ITS_SUCCESS;    
    }

    Ro_TSL::ServiceInformation si(inout->getServiceInformation());
    TransCustomAvp::CSInformation csinfo(si.getCSInformation());    
    TransCustomAvp::CAPInformation capInfoVal(csinfo.getCAPInformation());
    IDPToCCRIData ccriData;
    ccriData.CopyFrom(userData->GetIDPToCCRIData());
    
    if(in.OptionInitialDPArgExtension() && in.GetInitialDPArgExtension().OptionGmscAddress())
    {
        std::string gmscAddr = "";;
        const std::vector<byte>& vec = in.GetInitialDPArgExtension().GetGmscAddress().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), gmscAddr);
        size_t fPos = gmscAddr.find('F'); 
        if (fPos != std::string::npos)
        {
            gmscAddr.erase(fPos, std::string::npos);
        }
    
        TransCustomAvp::CAPGMSCAddress gmsc(gmscAddr.substr(SUB_STR_POS_2));
        capInfoVal.setCAPGMSCAddress(gmsc);
        ccriData.set_gmsc(gmscAddr.substr(SUB_STR_POS_2));
    
    }
    
    if(in.OptionGsm_ForwardingPending())
    {
        TransCustomAvp::CAPGSMForwardingPending capGSMForwardingInfo(CAP_GSM_FORWARDING_PENDING_PRESENT);
        capInfoVal.setCAPGSMForwardingPending(capGSMForwardingInfo);
        ccriData.set_gsm_forwarding_pending(CAP_GSM_FORWARDING_PENDING_PRESENT);
    } 

    csinfo.setCAPInformation(capInfoVal);
    userData->SetIDPToCCRIData(ccriData);
    si.setCSInformation(csinfo);
    inout->setServiceInformation(si);

                                                                        
    return ret;
}

void TransatelCAPToRoHandler::ApplyChargingReport_V2_To_CCR_Update(IwfFsm *ctxt,
         const cap_v1::EventReportBCSMArg *in,
         Ro_TSL::CreditControlRequest *out)
{

    cap_v2::CAMEL_CallResult camelcr;
    //const std::vector<byte>& vec = camelcr.GetArray();
    //Octets oct(vec,vec.size());
    //camelcr.Decode(oct);


    /* TimeIfNoTarrifSwitch is mapped to MSU.USU.CC-Time */



}
