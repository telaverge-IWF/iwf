#ifndef _DIA_MSG_FLOW_H_
#define _DIA_MSG_FLOW_H_

// eAccelero tracer
#include "Tracer.h"

namespace diameter {

// This is a bitset value
// 24 bits are reserved for th stack
// the rest 8 bits the applciation may use it
enum DiaMsgFlowFlags
{
    DIA_REENCODE_REQ = (1 << 1),  // Stack needs to reencode this. Message changed by THF
    DIA_GET_H2H_FROM_MSG = (1 << 2), // Populate the H2H from message send from app
    DIA_ERROR_RESP_MSG = (1 << 3), // error response message send from app
    DIA_REROUTE_REQ = (1 << 4), // perform routing/forwarind again

    DIA_MSG_FLOW_FLAG_APP_START = (1 << 16),  // Can be used by application
};

class DiaMsgFlow : public BaseCommand
{
public:

    //DiaMsgFlow(const unsigned char *buff, int len);
    DiaMsgFlow(const unsigned char *buff, int len, ITS_UINT dictId);
    DiaMsgFlow(ITS_UINT dictId) {m_dictId = dictId;m_InPeerInst=0;}
    DiaMsgFlow(ITS_USHORT peerInst, ITS_UINT dictId) {
		m_InPeerInst = peerInst;
		m_dictId = dictId;		
                m_baseGenericCmd = NULL;
	}

    DiaMsgFlow(diameter::base::BaseGenericCommand* cmd);


// CopyFlag :: used to check if m_baseGenericCmd has to initialised or not
    DiaMsgFlow(diameter::base::BaseGenericCommand* cmd,bool copyFlag);

    DiaMsgFlow(DiaMsgFlow& msgFlow);

    ~DiaMsgFlow() 
    {
        DT_DBG(("DiaMsgFlow Destructor"));
        if(m_baseGenericCmd)
        {
            delete m_baseGenericCmd;
            m_baseGenericCmd=NULL;
        }
    }

    /*Get Dictionary Id*/
    ITS_UINT GetDictId() {return m_dictId;}

    /*Set Dictionary Id*/
    void SetDictId( ITS_UINT dictionaryId) {m_dictId = dictionaryId;}

    /*Get BaseGenericCommand */
    diameter::base::BaseGenericCommand* GetBaseGenCommand() {return m_baseGenericCmd;}

    /*Set BaseGenericCommand */
    void SetBaseGenCommand(diameter::base::BaseGenericCommand *pBaseGenCmd) {m_baseGenericCmd = pBaseGenCmd;}

    /*Get Peer Instance*/
    ITS_UINT GetIncomingPeerInst() {return m_InPeerInst;}

    /*Set Peer Instance*/
    void SetIncomingPeerInst( ITS_USHORT peerInst) {m_InPeerInst = peerInst;}

	/*This function is for generic AVP Access.*/
	int getAvpValue(unsigned int avpCode, unsigned int index, void* val, ValueDiscriminator D, unsigned int venId=0);

	/*This function is to get count for an AVP using generic Access.*/
	int getAvpCount(unsigned int avpCode,unsigned int venId);

	/*This function sets the appropriate Command Attribute based on the dictionary id.*/
	int init_reflection();

    // Get the session tracing object
    eAccelero::TraceRef& GetTraceObj()
    {
        return m_traceObj;
    }
    // Set the trace object
    void SetTraceObj(eAccelero::TraceRef& traceObj)
    {
        m_traceObj = traceObj;
    }
    // Get the trace Id. If no trace object, then return 0
    uint16_t GetTraceId()
    {
        if (!m_traceObj)
        {
            // Trace object is Not set
            return 0;
        }
        return m_traceObj->RuleId();
    }
    uint32_t GetFlags() const
    {
        return m_flags;
    }
    void OverwriteFlags(uint32_t flags)
    {
        m_flags = flags;
    }
    // Apply with the existing flags
    void ApplyFlags(uint32_t flags)
    {
        m_flags |= flags;
    }
private:
    diameter::base::BaseGenericCommand *m_baseGenericCmd;
    ITS_UINT m_dictId;
	ITS_USHORT m_InPeerInst;

    // Used for session tracing
    eAccelero::TraceRef m_traceObj;

    uint32_t m_flags; // see the DiaMsgFlowFlags
};

}
#endif 
