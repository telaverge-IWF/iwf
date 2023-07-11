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


#define   BSSAP_DISCONNECT_TIMEOUT                30
#define   BSSAP_RELEASE_TIMEOUT                   40
#define   BSSAP_CC_MSG_DISCONNECT_IND             50
#define   BSSAP_CONNECT_TIMEOUT                   60


class FsmMT : public ITS_FiniteStateMachine<ITS_BasicEvent>
{
    public:
        FsmMT()
        {
            stateNull = new StateNull(*this);
            stateInd = new StateIndication(*this);
            stateConf  =  new StateConfirm(*this);
            stateRecv = new StateReceived(*this);
            stateConReq = new StateConnectionRequest(*this);
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

            transition_null_to_ind =  
               new ITS_BasicTransition<FsmMT>( *this, *stateNull, *stateInd);
            transition_ind_to_conf  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateConf);
            transition_conf_to_recv  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateRecv);
            transition_recv_to_conreq  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateRecv, *stateConReq);
            transition_conreq_to_actv  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConReq, *stateActv);
            transition_conf_to_conreq  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateConReq);

            /* Disconnect request from Applicaiton */
            transition_actv_to_disreq =
              new ITS_BasicTransition<FsmMT>( *this, *stateActv, *stateDiscReq);
            transition_disreq_to_relInd =
            new ITS_BasicTransition<FsmMT>( *this, *stateDiscReq, *stateRelInd);
            transition_relInd_to_null =
            new ITS_BasicTransition<FsmMT>( *this, *stateRelInd, *stateNull);
            transition_conf_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateDiscReq);
            transition_recv_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateRecv, *stateDiscReq);
            transition_ind_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateDiscReq);
            transition_ind_to_null  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateNull);


               
            /* Disconnect request from remote */
            transition_actv_to_disind =
            new ITS_BasicTransition<FsmMT>( *this, *stateActv, *stateDiscInd);
            transition_disind_to_relreq  =  
            new ITS_BasicTransition<FsmMT>( *this, *stateDiscInd, *stateRelReq);
            transition_relreq_to_null  =  
            new ITS_BasicTransition<FsmMT>( *this, *stateRelReq, *stateNull);

            /* Time out state transition */
            transition_disreq_to_relreq =
            new ITS_BasicTransition<FsmMT>( *this, *stateDiscReq, *stateRelReq);
            transition_conreq_to_disreq =
            new ITS_BasicTransition<FsmMT>( *this, *stateConReq, *stateDiscReq);


               

            stateNull->DefineTransition(*transition_null_to_ind, 
                                                BSSAP_CC_MSG_SETUP);
            stateInd->DefineTransition(*transition_ind_to_conf, 
                                                BSSAP_CC_MSG_CALL_CONFIRMED);
            stateConf->DefineTransition(*transition_conf_to_recv, 
                                                BSSAP_CC_MSG_ALERTING);
            stateConf->DefineTransition(*transition_conf_to_conreq, 
                                                BSSAP_CC_MSG_CONNECT);
            stateRecv->DefineTransition(*transition_recv_to_conreq, 
                                                BSSAP_CC_MSG_CONNECT);
            stateConReq->DefineTransition(*transition_conreq_to_actv, 
                                              BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);

            // Local Disconnect 
            stateActv->DefineTransition(*transition_actv_to_disreq, 
                                               BSSAP_CC_MSG_DISCONNECT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relInd, 
                                                BSSAP_CC_MSG_RELEASE);
            stateRelInd->DefineTransition(*transition_relInd_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);
            stateConf->DefineTransition(*transition_conf_to_disreq, 
                                                BSSAP_CC_MSG_DISCONNECT);
            stateRecv->DefineTransition(*transition_recv_to_disreq, 
                                                BSSAP_CC_MSG_DISCONNECT);
            stateInd->DefineTransition(*transition_ind_to_disreq, 
                                                BSSAP_CC_MSG_DISCONNECT);
            stateInd->DefineTransition(*transition_ind_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Remote Disconnect
            stateActv->DefineTransition(*transition_actv_to_disind, 
                                                BSSAP_CC_MSG_DISCONNECT_IND);
            stateDiscInd->DefineTransition(*transition_disind_to_relreq, 
                                                BSSAP_CC_MSG_RELEASE);
            stateRelReq->DefineTransition(*transition_relreq_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Timeout 
            stateConReq->DefineTransition(*transition_conreq_to_disreq, 
                                                BSSAP_CONNECT_TIMEOUT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relreq, 
                                                BSSAP_DISCONNECT_TIMEOUT);
            stateRelReq->DefineTransition(*transition_relreq_to_null, 
                                                BSSAP_RELEASE_TIMEOUT);
        }               

        virtual ~FsmMT()
        {
            cout << endl << "State objects deleted " << endl;

            delete stateNull;
            delete stateInd;
            delete stateConf;
            delete stateRecv;
            delete stateConReq;
            delete stateActv;
            delete stateDiscReq;
            delete stateDiscInd;
            delete stateRelReq;
            delete stateRelInd;

            cout << endl << "transition objects deleted " << endl;

            delete transition_null_to_ind;
            delete transition_ind_to_conf;
            delete transition_conf_to_recv;
            delete transition_recv_to_conreq;
            delete transition_conreq_to_actv;


            delete transition_actv_to_disreq;
            delete transition_relreq_to_null;
            delete transition_disreq_to_relreq;
            delete transition_relInd_to_null;
            delete transition_actv_to_disind;
            delete transition_disind_to_relreq;
            delete transition_disreq_to_relInd;
            delete transition_conreq_to_disreq;
            delete transition_conf_to_conreq;
            delete transition_conf_to_disreq;
            delete transition_recv_to_disreq;
            delete transition_ind_to_disreq;
            delete transition_ind_to_null;
        }

               
        class StateNull : public ITS_BasicState<FsmMT>
        {
            public:
                StateNull(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
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


        class StateIndication : public ITS_BasicState<FsmMT>
        {
            public:
                StateIndication(FsmMT& fsmParam) : 
                                           ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateIndication()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state INIDICATION..." << event.GetId() 
                  << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state INIDICATION...sending message -> " 
                  << event.GetId() << endl;                }
 
                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state INIDICATION..." 
                  << event.GetId() << endl;
                }
        };
   
        class StateConfirm : public ITS_BasicState<FsmMT>
        {
            public:
                StateConfirm(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateConfirm()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state CONFIRM..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state CONFIRM...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state CONFIRM..." << event.GetId()                  << endl; }
  
        };

            
        class StateReceived : public ITS_BasicState<FsmMT>
        {
            public:
                StateReceived(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateReceived()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state RECV..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state RECV...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state RECV..." << event.GetId() 
                  << endl; }
  
        };

         
        class StateConnectionRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateConnectionRequest(FsmMT& fsmParam) : 
                                         ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateConnectionRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { cout << "Go in state CONREQ..." << event.GetId() << endl; }

                void ExecuteOut(ITS_BasicEvent& event)
                { cout << "Go out of state CONREQ...received <- " 
                  << event.GetId() << endl; }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { cout << "Abnormal Event in state CONREQ..." << event.GetId()                   << endl; }
        };

        class StateActive: public ITS_BasicState<FsmMT>
        {
            public:
                StateActive(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
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


        class StateDisconnectRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateDisconnectRequest(FsmMT& fsmParam) : 
                                        ITS_BasicState<FsmMT>(fsmParam)
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


        class StateDisconnectIndication: public ITS_BasicState<FsmMT>
        {
            public:
                StateDisconnectIndication(FsmMT& fsmParam) : 
                                                ITS_BasicState<FsmMT>(fsmParam)
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

        class StateReleaseRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateReleaseRequest(FsmMT& fsmParam) : 
                                             ITS_BasicState<FsmMT>(fsmParam)
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

        class StateReleaseInd: public ITS_BasicState<FsmMT>
        {
            public:
                StateReleaseInd(FsmMT& fsmParam) :  
                                           ITS_BasicState<FsmMT>(fsmParam)
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
        StateIndication* stateInd;
        StateConfirm* stateConf;
        StateReceived* stateRecv;
        StateConnectionRequest* stateConReq;
        StateActive* stateActv;
        StateDisconnectRequest* stateDiscReq;
        StateDisconnectIndication* stateDiscInd;
        StateReleaseRequest* stateRelReq;
        StateReleaseInd* stateRelInd;

        ITS_BasicTransition<FsmMT>* transition_null_to_ind;
        ITS_BasicTransition<FsmMT>* transition_ind_to_conf;
        ITS_BasicTransition<FsmMT>* transition_conf_to_recv;
        ITS_BasicTransition<FsmMT>* transition_recv_to_conreq;
        ITS_BasicTransition<FsmMT>* transition_conreq_to_actv;
        ITS_BasicTransition<FsmMT>* transition_actv_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_disreq_to_relreq;

        ITS_BasicTransition<FsmMT>* transition_actv_to_disind;
        ITS_BasicTransition<FsmMT>* transition_disind_to_relreq;
        ITS_BasicTransition<FsmMT>* transition_relreq_to_null;
        ITS_BasicTransition<FsmMT>* transition_disreq_to_relInd;
        ITS_BasicTransition<FsmMT>* transition_relInd_to_null;
        ITS_BasicTransition<FsmMT>* transition_conreq_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_conf_to_conreq;
        ITS_BasicTransition<FsmMT>* transition_conf_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_recv_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_ind_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_ind_to_null;

};


////////////// END OF CLASS /////////////////

void TestMTConnectTimeout()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev3(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev4(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev5(BSSAP_CONNECT_TIMEOUT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev3);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev5);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}


void TestMTIndRelComplReq()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
}

void TestMTRecvDisReq()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev4(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev6);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}

void TestMTConDisReq()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev4(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}

void TestMTConfToCon()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev4(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev5);
    fsmMT.ProcessEvent(ev6);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}

/* Disconnect from App */
void TestMTDiscReq()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev3(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev4(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev3);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev5);
    fsmMT.ProcessEvent(ev6);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}


/* Disconnect from Remote */
void TestMTDiscInd()
{
    BSSAPEvent ev1(BSSAP_CC_MSG_SETUP);
    BSSAPEvent ev2(BSSAP_CC_MSG_CALL_CONFIRMED);
    BSSAPEvent ev3(BSSAP_CC_MSG_ALERTING);
    BSSAPEvent ev4(BSSAP_CC_MSG_CONNECT);
    BSSAPEvent ev5(BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);
    BSSAPEvent ev6(BSSAP_CC_MSG_DISCONNECT_IND);
    BSSAPEvent ev7(BSSAP_CC_MSG_RELEASE);
    BSSAPEvent ev8(BSSAP_CC_MSG_RELEASE_COMPLETE);

    FsmMT fsmMT;

    fsmMT.ProcessEvent(ev1);
    fsmMT.ProcessEvent(ev2);
    fsmMT.ProcessEvent(ev3);
    fsmMT.ProcessEvent(ev4);
    fsmMT.ProcessEvent(ev5);
    fsmMT.ProcessEvent(ev6);
    fsmMT.ProcessEvent(ev7);
    fsmMT.ProcessEvent(ev8);
}


int main()
{
    cout << "Begin MT test..." << endl << endl;

    cout << "######## DISCONNECT REQ ######################" << endl << endl;

        TestMTDiscReq();
   
    cout << "######## DISCONNECT IND ######################" << endl << endl;

        TestMTDiscInd();

    cout << "######## CONFIRM -> CONNECT ##################" << endl << endl;

        TestMTConfToCon();

    cout << "######## CONFIRM -> DISCONNECT ###############" << endl << endl;

        TestMTConDisReq();

    cout << "######## RECV -> DISCONNECT ##################" << endl << endl;

        TestMTRecvDisReq();

    cout << "######## INDICATION -> RELCOMPL ##############" << endl << endl;

        TestMTIndRelComplReq();

    cout << "######## CONNECT TIMEOUT #####################" << endl << endl;


        TestMTConnectTimeout();

    cout << endl << "End of MT test..." << endl << endl;


    return 0;
}
