#ifndef _ITS_HMI_H
#define _ITS_HMI_H

#define VMI_MAX_INSTANCE       5

/********************************************  
 *******       HMI Primitive Tag   
 ********************************************/

#define VMI_BACKUP             (0x01U)
#define VMI_HALT_BOARD         (0x02U)
#define VMI_LOAD_BOARD         (0x03U)
#define VMI_PRIMARY            (0x04U)
#define VMI_RESET              (0x05U)
#define VMI_SHUTDOWN           (0x06U)
#define VMI_STANDALONE         (0x07U)
#define VMI_STATUS_REQUEST     (0x08U)

#define VMI_PRIMITIVE_FLAG     (0x0FU)  


/*********************************************
 *******     HMI Return Codes
 *********************************************/

#define VMI_SUCCESS           (0x11U)
#define VMI_ERR_CLOSED        (0x12U)
#define VMI_ERR_BADCMD        (0x13U)
#define VMI_ERR_TIMEOUT       (0x14U)
#define VMI_ERR_INVHANDLE     (0x15U)
#define VMI_ERR_NOMEM         (0x16U)
#define VMI_ERR_REFUSED       (0x17U)
#define VMI_ERR_INTERROR      (0x18U)

/**********************************************
 ************* HMI Events            
 **********************************************/

#define VMI_EVN_ISOLATED      (0x20U)
#define VMI_EVN_CONNECTED     (0x21U)
#define VMI_EVN_NOWPRIMARY    (0x22U)
#define VMI_EVN_BRDDEAD       (0x23U)
#define VMI_EVN_TASKDEAD      (0x24U)
#define VMI_EVN_HALTED        (0x25U)
#define VMI_EVN_LOADING       (0x26U)
#define VMI_EVN_NOWBACKUP     (0x27U)
#define VMI_EVN_NOWSTANDALONE (0x28U)
#define VMI_EVN_STARTING      (0x29U)
#define VMI_EVN_CONFLICT      (0x2AU)
#define VMI_EVN_SERVICE_DOWN  (0x2BU)

#ifdef __cplusplus
extern "C"
{
#endif
//extern int VMI_SendPrimitive(ITS_UINT mask, ITS_USHORT instance);
/* Asynchronous event are sent to all registered transports) */
extern int VMI_RegisterInstance(ITS_USHORT instance);
/* To deregister a transport */
extern int VMI_DeregisterInstance(ITS_USHORT instance);
extern int  VMI_Initialize(ITS_Class);
extern void VMI_Terminate(ITS_Class);

#ifdef __cplusplus
}
#endif


#endif
