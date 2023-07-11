


#ifndef _ITS_SCTP_EVENT_INTERFACE_H_
#define _ITS_SCTP_EVENT_INTERFACE_H_

/****************************
 * Include Files
 ***************************/

/****************************
 * Class forward declarations
 ***************************/
class SCTPEndPoint;
class SCTPAssociation;
/****************************
 * Class declaration
 ***************************/
/* 
 * This is an abstract class that defines the methods to receive SCTP events from
 * the SCTP configuration manager. Typically the OAM interface layer (if present) 
 * will implement this interface. The interface methods in the implementor will 
 * be called by the SCTP configuration manager on receiving SCTP events from the
 * the SCTP transport layer
 */

class ISCTPEvent
{
        /* The interface methods */
        public:
                virtual void OnUp(SCTPAssociation& sctp_association_obj)            = 0;
                virtual void OnDown(SCTPAssociation& sctp_association_obj)          = 0;
                virtual void OnRestart(SCTPAssociation& sctp_association_obj)       = 0;
                virtual void OnAbort(SCTPAssociation& sctp_association_obj)         = 0;
                virtual void OnShutdown(SCTPAssociation& sctp_association_obj)      = 0;
                virtual void OnCantStart(SCTPAssociation& sctp_association_obj)     = 0;
                virtual void OnAddressUnreachable(SCTPEndPoint& endPointObj)        = 0;
                virtual void OnAddressReachable(SCTPEndPoint& endPointObj)          = 0;

};
#endif /*#ifndef _ITS_SCTP_EVENT_INTERFACE_H_ */


