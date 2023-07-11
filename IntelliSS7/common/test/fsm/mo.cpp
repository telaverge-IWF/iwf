#include <iostream.h>

#include <its_exception.h>
#include <its_fsm.h>
#include "BSSAP.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)

class BSSAPEvent : public ITS_BasicEvent
{
    public:
        BSSAPEvent(ITS_UINT eventID) :  ITS_BasicEvent(eventID)
        {};
};


#define   BSSAP_INIT_TIMEOUT                      10
#define   BSSAP_PROC_TIMEOUT                      20
#define   BSSAP_DISCONNECT_TIMEOUT                30
#define   BSSAP_RELEASE_TIMEOUT                   40
#define   BSSAP_CC_MSG_DISCONNECT_IND             50


class FsmMO : public ITS_FiniteStateMachine<ITS_BasicEvent>
{
    public:
        FsmMO()
        {
            stateNull = new StateNull(*this);
            statePend = new StatePending(*this);
            stateInit  =  new StateInitiate(*this);
            stateProc = new StateProceed(*this);
            stateDelv = new StateDeliver(*this);
            stateActv = new StateActive(*this);
            stateDiscReq = new StateDisconnectRequest(*this);
            stateDiscInd  = new StateDisconnectIndication(*this);
            stateRelReq  =  new StateReleaseRequest(*this);
            stateRelInd  =  new StateReleaseInd(*this);
               

            SetInitialState(
                     reinterpret_cast<
                           ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                   ITS_BasicEvent>&>
                                        (*stateNull));

            transition_null_to_pend =  
               new ITS_BasicTransition<FsmMO>( *this, *stateNull, *statePend);
            transition_pend_to_init  =  
               new ITS_BasicTransition<FsmMO>( *this, *statePend, *stateInit);
            transition_init_to_proc  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateProc);
            transition_init_to_delv  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateDelv);
            transition_init_to_actv  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateActv);
            transition_proc_to_delv  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateDelv); 
            transition_proc_to_actv  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateActv);
            transition_delv_to_actv  =  
               new ITS_BasicTransition<FsmMO>( *this, *stateDelv, *stateActv);

            /* Disconnect request from Applicaiton */
            transition_actv_to_disreq =  
              new ITS_BasicTransition<FsmMO>( *this, *stateActv, *stateDiscReq);
            transition_disreq_to_relInd =  
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscReq, *stateRelInd);
            transition_relInd_to_null =  
            new ITS_BasicTransition<FsmMO>( *this, *stateRelInd, *stateNull);
               
            /* Disconnect request from remote */
            transition_actv_to_disind =
            new ITS_BasicTransition<FsmMO>( *this, *stateActv, *stateDiscInd);
            transition_disind_to_relreq  =  
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscInd, *stateRelReq);
            transition_relreq_to_null  =  
            new ITS_BasicTransition<FsmMO>( *this, *stateRelReq, *stateNull);
               
            /* Time out state transition */
            transition_disreq_to_relreq =
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscReq, *stateRelReq);
            transition_relreq_to_relreq  =  
             new ITS_BasicTransition<FsmMO>( *this, *stateRelReq, *stateRelReq);
            transition_init_to_disreq =
              new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateDiscReq);
            transition_proc_to_disreq =
              new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateDiscReq);

            stateNull->DefineTransition(*transition_null_to_pend, 
                                                BSSAP_MSG_CM_SERVICE_REQUEST);
            statePend->DefineTransition(*transition_pend_to_init, 
                                                BSSAP_CC_MSG_SETUP);
            stateInit->DefineTransition(*transition_init_to_proc, 
                                                BSSAP_CC_MSG_CALL_PROCEEDING);
            stateInit->DefineTransition(*transition_init_to_actv, 
                                                BSSAP_CC_MSG_CONNECT);
            stateInit->DefineTransition(*transition_init_to_delv, 
                                                BSSAP_CC_MSG_ALERTING);
            stateProc->DefineTransition(*transition_proc_to_delv, 
                                                BSSAP_CC_MSG_ALERTING);
            stateProc->DefineTransition(*transition_proc_to_actv, 
                                                BSSAP_CC_MSG_CONNECT);
            stateDelv->DefineTransition(*transition_delv_to_actv, 
                                                BSSAP_CC_MSG_CONNECT);

            // Local Disconnect 
            stateActv->DefineTransition(*transition_actv_to_disreq, 
                                               BSSAP_CC_MSG_DISCONNECT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relInd, 
                                                BSSAP_CC_MSG_RELEASE);
            stateRelInd->DefineTransition(*transition_relInd_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Remote Disconnect
            stateActv->DefineTransition(*transition_actv_to_disind, 
                                                BSSAP_CC_MSG_DISCONNECT_IND);
            stateDiscInd->DefineTransition(*transition_disind_to_relreq, 
                                                BSSAP_CC_MSG_RELEASE);
            stateRelReq->DefineTransition(*transition_relreq_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Timeout 
            stateInit->DefineTransition(*transition_init_to_disreq, 
                                                BSSAP_INIT_TIMEOUT);
            stateProc->DefineTransition(*transition_proc_to_disreq, 
                                                BSSAP_PROC_TIMEOUT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relreq, 
                                                BSSAP_DISCONNECT_TIMEOUT);
            stateRelReq->DefineTransition(*transition_relreq_to_relreq, 
                                                BSSAP_RELEASE_TIMEOUT);
        }               

        virtual ~FsmMO()
        {
            cout << endl << "State objects deleted " << endl;

            delete stateNull;
            delete statePend;
            delete stateInit;
            delete stateProc;
            delete stateDelv;
            delete stateActv;
            delete stateDiscReq;
            delete stateDiscInd;
            delete stateRelReq;
            delete stateRelInd;

            cout << endl << "transition objects deleted " << endl;

            delete transition_null_to_pend;
            delete transition_pend_to_init;
            delete transition_init_to_proc;
            delete transition_init_to_delv;
            delete transition_init_to_actv;
            delete transition_proc_to_delv; 
            delete transition_proc_to_actv;
            delete transition_delv_to_actv;
            delete transition_actv_to_disreq;
            delete transition_relreq_to_null;
            delete transition_disreq_to_relreq;
            delete transition_relInd_to_null;
            delete transition_actv_to_disind;
            delete transition_disind_to_relreq;
            delete transition_disreq_to_relInd;
            delete transition_init_to_disreq;
            delete transition_proc_to_disreq;
            delete transition_relreq_to_relreq;
        }

               
        class StateNull : public ITS_BasicState<FsmMO>
        {
            public:
                StateNull(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateNull()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state NULL..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state NULL...Sending message -> " << 
                  event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Error Event in state NULL" << event.GetId() 
                  << endl; }
        };


        class StatePending : public ITS_BasicState<FsmMO>
        {
            public:
                StatePending(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StatePending()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state PENDING..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state PENDING...sending message -> " 
                  << event.GetId() << endl;                }
 
                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state PENDING..." << event.GetId()
                 << endl;
                }
        };
   
        class StateInitiate : public ITS_BasicState<FsmMO>
        {
            public:
                StateInitiate(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateInitiate()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state INITIATE..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state INITIATE...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state INITIATE..." << event.GetId()                  << endl; }
  
        };

            
        class StateProceed : public ITS_BasicState<FsmMO>
        {
            public:
                StateProceed(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateProceed()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state PROCEED..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state PROCEED...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state PROCEED..." << event.GetId() 
                  << endl; }
  
        };

         
        class StateDeliver: public ITS_BasicState<FsmMO>
        {
            public:
                StateDeliver(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateDeliver()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state DELIVER..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state DELIVER...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state DELIVER..." << event.GetId()                   << endl; }
        };

        class StateActive: public ITS_BasicState<FsmMO>
        {
            public:
                StateActive(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateActive()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state ACTIVE..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state ACTIVE..." << event.GetId() 
                  << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state ACTIVE..." << event.GetId() 
                  << endl; }
  
        };


        class StateDisconnectRequest: public ITS_BasicState<FsmMO>
        {
            public:
                StateDisconnectRequest(FsmMO& fsmParam) : 
                                        ITS_BasicState<FsmMO>(fsmParam)
            {};

            virtual ~StateDisconnectRequest()
            {};

            void ExecuteIn(ITS_BasicEvent& event)
            { cout << "Go in state DISC REQ... sending -> " 
              << event.GetId() << endl; }

            void ExecuteOut(ITS_BasicEvent& event)
            { cout << "Go out of state DISC REQ..." << event.GetId() << endl; }

            void ExecuteEventNotDefined(ITS_BasicEvent& event)
            { cout << "Abnormal Event in state DISC REQ..." << event.GetId() 
              << endl; }
  
        };


        class StateDisconnectIndication: public ITS_BasicState<FsmMO>
        {
            public:
                StateDisconnectIndication(FsmMO& fsmParam) : 
                                                ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateDisconnectIndication()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state DISC IND...received <- " 
                  << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state DISC IND..." << event.GetId() 
                  << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state DISC IND..." << event.GetId()
                  << endl; }
  
        };

        class StateReleaseRequest: public ITS_BasicState<FsmMO>
        {
            public:
                StateReleaseRequest(FsmMO& fsmParam) : 
                                             ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateReleaseRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state REL REQ...sending -> " << event.GetId() 
                  << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state REL REQ...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state REL REQ..." << event.GetId()                   << endl; }
  
        };

        class StateReleaseInd: public ITS_BasicState<FsmMO>
        {
            public:
                StateReleaseInd(FsmMO& fsmParam) :  
                                           ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateReleaseInd()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state REL IND...received <- " 
                  << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state REL IND...sending ->" 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state REL IND..." << event.GetId()                   << endl; }
        };


        StateNull* stateNull;
        StatePending* statePend;
        StateInitiate* stateInit;
        StateProceed* stateProc;
        StateDeliver* stateDelv;
        StateActive* stateActv;
        StateDisconnectRequest* stateDiscReq;
        StateDisconnectIndication* stateDiscInd;
        StateReleaseRequest* stateRelReq;
        StateReleaseInd* stateRelInd;

        ITS_BasicTransition<FsmMO>* transition_null_to_pend;
        ITS_BasicTransition<FsmMO>* transition_pend_to_init;
        ITS_BasicTransition<FsmMO>* transition_init_to_proc;
        ITS_BasicTransition<FsmMO>* transition_init_to_delv;
        ITS_BasicTransition<FsmMO>* transition_init_to_actv;
        ITS_BasicTransition<FsmMO>* transition_proc_to_delv; 
        ITS_BasicTransition<FsmMO>* transition_proc_to_actv;
        ITS_BasicTransition<FsmMO>* transition_delv_to_actv;
        ITS_BasicTransition<FsmMO>* transition_actv_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_disreq_to_relreq;

        ITS_BasicTransition<FsmMO>* transition_actv_to_disind;
        ITS_BasicTransition<FsmMO>* transition_disind_to_relreq;
        ITS_BasicTransition<FsmMO>* transition_relreq_to_null;
        ITS_BasicTransition<FsmMO>* transition_disreq_to_relInd;
        ITS_BasicTransition<FsmMO>* transition_relInd_to_null;
        ITS_BasicTransition<FsmMO>* transition_init_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_proc_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_relreq_to_relreq;

};



/* Disconnect from App */
void TestMODiscReq()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_CC_MSG_CALL_PROCEEDING);
    BSSAPEvent ev4(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
    fsmMO.ProcessEvent(ev6);
    fsmMO.ProcessEvent(ev7);
    fsmMO.ProcessEvent(ev8);
}

void TestMORelReqTimeout()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_CC_MSG_CALL_PROCEEDING);
    BSSAPEvent ev4(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_DISCONNECT_TIMEOUT);
    BSSAPEvent ev8(BSSAP_RELEASE_TIMEOUT);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
    fsmMO.ProcessEvent(ev6);
    fsmMO.ProcessEvent(ev7);
    fsmMO.ProcessEvent(ev8);
}

void TestMODiscReqTimeout()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_CC_MSG_CALL_PROCEEDING);
    BSSAPEvent ev4(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_DISCONNECT_TIMEOUT);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
    fsmMO.ProcessEvent(ev6);
    fsmMO.ProcessEvent(ev7);
    fsmMO.ProcessEvent(ev8);
}

void TestMOInitTimeout()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_INIT_TIMEOUT);
    BSSAPEvent ev4(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev5(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
}

void TestMOProcTimeout()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_CC_MSG_CALL_PROCEEDING);
    BSSAPEvent ev4(BSSAP_PROC_TIMEOUT);
    BSSAPEvent ev5(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev6(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
    fsmMO.ProcessEvent(ev6);
}

/* Disconnect from Remote */
void TestMODiscInd()
{
    BSSAPEvent ev1(BSSAP_MSG_CM_SERVICE_REQUEST);
    BSSAPEvent ev2(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev3(BSSAP_CC_MSG_CALL_PROCEEDING);
    BSSAPEvent ev4(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT_IND);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMO fsmMO;

    fsmMO.ProcessEvent(ev1);
    fsmMO.ProcessEvent(ev2);
    fsmMO.ProcessEvent(ev3);
    fsmMO.ProcessEvent(ev4);
    fsmMO.ProcessEvent(ev5);
    fsmMO.ProcessEvent(ev6);
    fsmMO.ProcessEvent(ev7);
    fsmMO.ProcessEvent(ev8);
}


int main()
{
    cout << "Begin MO test..." << endl << endl;


        TestMODiscReq();
   
    cout << "###############################" << endl << endl;

        TestMODiscInd();

    cout << "###############################" << endl << endl;

        TestMOInitTimeout();

    cout << "###############################" << endl << endl;

        TestMOProcTimeout();

    cout << "###############################" << endl << endl;

        TestMODiscReqTimeout();

    cout << "###############################" << endl << endl;

        TestMORelReqTimeout();

    cout << endl << "End of MO test..." << endl << endl;


    return 0;
}
