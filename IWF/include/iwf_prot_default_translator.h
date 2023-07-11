#ifndef __IWF_PROT_DEFAULT_TRANSLATOR_H__
#define __IWF_PROT_DEFAULT_TRANSLATOR_H__

#include "iwf_prot_defines.h"

#include <itu/map_cpp.h>
#include <itu/map_v13_update_gprs_location_arg.h>
#include <itu/map_v13_update_gprs_location_res.h>
#include <itu/map_v13_insert_subscriber_data_arg.h>
#include <itu/map_v13_insert_subscriber_data_res.h>
#include <itu/map_v13_provide_subscriber_info_arg.h>
#include <itu/map_v13_provide_subscriber_info_res.h>
#include <itu/map_v13_unknown_subscriber_param.h>
#include <itu/map_v13_roaming_not_allowed_param.h>
#include <itu/map_v13_data_missing_param.h>
#include <itu/map_v13_unexpected_data_param.h>
#include <itu/map_v13_facility_not_sup_param.h>
#include <itu/map_v13_system_failure_param.h>
#include <itu/map_v13_illegal_subscriber_param.h>
#include <itu/map_v13_illegal_equipment_param.h>
#include <itu/map_v13_absent_subscriber_param.h>
#include <itu/map_v13_unidentified_sub_param.h>
#include <itu/map_v13_reset_arg.h>
#include <itu/map_v13_ready_for_sm_arg.h>
#include <itu/map_v13_ready_for_sm_res.h>
#include <itu/map_v13_delete_subscriber_data_arg.h>
#include <itu/map_v13_delete_subscriber_data_res.h>
#include <itu/map_v13_activate_trace_mode_arg.h>
#include <itu/map_v13_activate_trace_mode_res.h>
#include <itu/map_v13_deactivate_trace_mode_arg.h>
#include <itu/map_v13_deactivate_trace_mode_res.h>
#include <itu/map_v13_send_authentication_info_arg.h>
#include <itu/map_v13_send_authentication_info_res.h>
#include <itu/map_v13_purge_ms_arg.h>
#include <itu/map_v13_purge_ms_res.h>
#include <itu/map_v13_cancel_location_arg.h>
#include <itu/map_v13_cancel_location_res.h>

#include <itu/map_v13_check_imei_arg.h>
#include <itu/map_v13_check_imei_res.h>

#include <diameter/s6a_r10/UpdateLocation.h>
#include <diameter/s6a_r10/InsertSubscriberData.h>
#include <diameter/s6a_r10/DeleteSubscriberData.h>
#include <diameter/s6a_r10/Reset.h>
#include <diameter/s6a_r10/Notify.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>
#include <diameter/s6a_r10/PurgeUE.h>
#include <diameter/s6a_r10/CancelLocation.h>
#include <diameter/nasreq/NasreqAVP.h>
#include <diameter/ro_r10/Ro_r10AVP.h>
#include <diameter/ro_r10/CreditControl.h>

#include <diameter/s13_r10/MEIdentityCheck.h>

#include "iwf_fsm.h"
#include "iwf_config.h"
#include "iwf_prot_translator.h"

#define DEF_TRANSLATOR_STR "Def-Trans"

using namespace its;
using namespace map_v13;
namespace s6a = diameter::s6a_r10;
namespace s13 = diameter::s13_r10;
namespace Ro = diameter::ro_r10;

// Populate the config
class DefaultConfig
{
    public:
        DefaultConfig()
        {
        }
        ~DefaultConfig()
        {
        }
        void Parse(Json::Value& val, IwfConfig& conf);
};

class DefaultHandler: public IwfTranslator
{
    public:
        DefaultHandler();
        virtual ~DefaultHandler();

        // Translator methods
        virtual int BuildTCAPMsg(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        virtual int BuildDiaMsg(IwfFsm *ctxt,
                TCAP_Component *cpt,
                DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret);

        virtual int BuildInterimTCAPMsg(IwfFsm *ctxt, 
                TCAP_Component *in,
                TCAP_Component *&out,
                IwfReturnAction& ret);

        virtual int BuildTcapResponse(IwfFsm *ctxt,
                TCAP_Component *in,  TCAP_Component *&out,
                IwfReturnAction& ret);

        virtual int BuildDiaResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&out,
                IwfReturnAction& ret);

        virtual int BuildDiaErrorResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret);

        virtual int BuildDiaErrorAnswer(IwfFsm *ctxt,
                int cmdCode, 
                int error, 
                DIA_BASE_CMD **out);

        virtual bool IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, 
                TCAP_Component *tcapCpt, bool &isReq);

        virtual bool IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq);

        // parse the config details required for MAPToS6aHandler
        virtual int ParseConfig(Json::Value& val, IwfConfig& conf)
        {
            m_config.Parse(val, conf);
            return 0;
        }

        virtual int BuildMultiTCAPMsg(IwfFsm *ctxt,
                TCAP_Component *in,
                TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        template <class T> 
            void ConstructErrorAnswer(int error, 
                    T *out);

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt);

        virtual int SetConfig(IwfTranslationDataConfig *req);

        virtual int DeleteConfig(IwfTranslationDataConfig *req);

        void EncodeMsg(AsnObject* p, Octets** octets);

        virtual void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction);

        virtual void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType);

        void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt);		

        virtual int SetTimerConfig(IwfTimersConfig *req);

        virtual int SetMsgSpecCfg(IwfProtocolActionConfig *req);        

        virtual int DeleteMsgSpecCfg(IwfProtocolActionConfig *req);        

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause);

        virtual int TerminateSession(IwfFsm *ctxt,
                TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd);
        
        virtual int OnUpstrmFinalReqSent(IwfFsm *ctxt);

        virtual ITS_UINT SetFeaturesConfig(IwfFeatureConfig *req);

        virtual ITS_UINT GetCDRConfig();

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm);

        virtual ITS_INT HandleError(IwfFsm* inFsmCtxt,
                            DIA_BASE_CMD*& outCmd,
                            TCAP_Component*& outCpt,
                            IwfReturnAction& outRetAction)
        {
            return ITS_SUCCESS;
        }

        ITS_UINT ConstructCreditControlAnswer(IwfFsm *ctxt, 
                DIA_BASE_CMD *in, DIA_BASE_CMD **&out);

        DefaultConfig m_config; 

};
#endif  //  IWF_PROT_DEFAULT_TRANSLATOR_H
