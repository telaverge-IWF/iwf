#ifndef __IWF_PROTO_TRANSLATOR_H__
#define __IWF_PROTO_TRANSLATOR_H__

#include "iwf_config.h"
#include "ErrorResp.h"
#include "iwf_prot_defines.h"
#include "iwf_fsm.h"

class TcapCptList;

enum IwfReturnActionCode
{
    IWF_RA_DROP,
    IWF_RA_CONSUME = IWF_RA_DROP,
    IWF_RA_FORWARD,
    IWF_RA_RESPOND_AND_FORWARD,
    IWF_RA_RESPOND_ONLY,  // In case of interim TCAP invokes
    IWF_RA_CONSUME_AND_RESPOND,  // In case of interim TCAP invokes
    IWF_RA_ERROR,
    IWF_RA_RESPOND_AND_FORWARD_WITH_TERM,
    IWF_RA_FORWARD_DUMMY_TCEND,    //In case to bring down the session successfully even after sending release
    IWF_RA_CONSUME_AND_RETRY
};

enum IwfRetDirection
{
    IWF_RD_DIA,
    IWF_RD_TCAP
};

struct IwfReturnAction
{
    IwfReturnActionCode action;
    IwfRetDirection     dir;
    map_common::MAP_AC  appContext; // ACN + Version
    ITS_ByteArray app_ctxt;
    bool isReleaseEnd;
    bool isASRReceived;

    IwfReturnAction():isReleaseEnd(false),isASRReceived(false)
    {
    }

};

class IwfTranslator
{
    public:
        static const int InvalidId = -1;

        IwfTranslator(const char* name)
            : m_name(name),
            m_id(InvalidId)
    {
    }

        virtual ~IwfTranslator()
        {
        }

        void Id(int id)
        {
            m_id = id;
        }
        const int& Id() const
        {
            return m_id;
        }

        const std::string& Name() const
        {
            return m_name;
        }

        // For json configuration
        virtual int ParseConfig(Json::Value& val, IwfConfig& conf) = 0;

        // Translator methods
        /*virtual int BuildTCAPMsg(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt,
                IwfReturnAction& ret) = 0;*/

        virtual int BuildTCAPMsg(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret) = 0;

        virtual int BuildDiaMsg(IwfFsm *ctxt,
                TCAP_Component *cpt,
                DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret) = 0;

        virtual int BuildInterimTCAPMsg(IwfFsm *ctxt, 
                TCAP_Component *in,
                TCAP_Component *&out,
                IwfReturnAction& ret) = 0;

        virtual int BuildTcapResponse(IwfFsm *ctxt,
                TCAP_Component *in,  TCAP_Component *&out,
                IwfReturnAction& ret) = 0;

        virtual int BuildDiaResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&out,
                IwfReturnAction& ret) = 0;

        virtual int BuildDiaErrorResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&out,
                IwfReturnAction& ret) = 0;

        virtual int BuildDiaErrorAnswer(IwfFsm *ctxt,
                int cmdcode, 
                int error, 
                DIA_BASE_CMD **out)=0;

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt) = 0;

        virtual int BuildMultiTCAPMsg(IwfFsm *ctxt,
                TCAP_Component *in,
                TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret) = 0;

        virtual bool IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, 
                TCAP_Component *tcapCpt, bool &isReq) = 0;

        virtual bool IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq) = 0;


        virtual int SetConfig(IwfTranslationDataConfig *req) = 0; 

        virtual int DeleteConfig(IwfTranslationDataConfig *req) = 0; 

        virtual void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction) = 0;

        virtual void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType) = 0;

        virtual void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt) = 0;

        virtual int SetTimerConfig(IwfTimersConfig *req) = 0;

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause) = 0;

        virtual int TerminateSession(IwfFsm *ctxt,
                TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd) = 0;

        virtual int OnUpstrmFinalReqSent(IwfFsm *ctxt) = 0;

        virtual ITS_UINT SetFeaturesConfig(IwfFeatureConfig *req) = 0;

        virtual ITS_UINT GetCDRConfig() = 0;

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm) = 0;

        virtual int SetMsgSpecCfg(IwfProtocolActionConfig *req) = 0;

        virtual int DeleteMsgSpecCfg(IwfProtocolActionConfig *req) = 0;

        // Called when ProcessErr in transaction manager is invoked
        virtual ITS_INT HandleError(IwfFsm* inFsmCtxt,
                            DIA_BASE_CMD*& outCmd,
                            TCAP_Component*& outCpt,
                            IwfReturnAction& outRetAction) = 0;

        virtual void CheckAndLogCDR(IwfFsm *ctxt)
        {
            /* As this function implementation is done only in CAP-Ro-TSL 
             * translator and it is virtual function and other translator 
             * its not implemented so defining it empty here if it is called  
             * for other translator */
        }

        virtual pbCapRoTsl& GetReplicableData()
        {
            /* This method will be implemented by the translator derived classes 
             * currently only CAP-Ro-Tsl class will override this method. */
        }

        virtual void CreateUserDataContext(IwfFsm *ctxt, pbStoredUserData storedUserData)
        {
            /* This method is implemented by the translator derived classes */
        }

        virtual void StartTimerHandling(IwfFsm* ctxt, const pbIwfTimerData timerData)
        {
            /* This method will only be used during the switchover, to start the
             * timer which is different from the other method. Please do not use
             * this method anywhere apart from switchover time */
        }

        virtual void SetTranslatorState(IwfFsm *ctxt, TransState state)
        {
            /*This method is currently used only for CAP-Ro-Tsl and is used to
             * set the translator state to decide on the replciation and staring
             * timer after switchover */
        }

        virtual TransState GetTranslatorState(IwfFsm *ctxt)
        {
            /*This method is currently used only for CAP-Ro-Tsl and is used to
             * get the translator state to decide on the replciation and staring
             * timer after switchover */
        }

    protected:
        std::string m_name;
        int         m_id;
};

#endif // __IWF_PROTO_TRANSLATOR_H__
