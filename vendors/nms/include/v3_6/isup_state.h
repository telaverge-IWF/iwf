#ifndef ISUP_STATE_H
#define ISUP_STATE_H
 
typedef struct checkPointMsg
{
    U32     msgId;
    CirId   cirId;
    CirId   mateId;
    U8      transient;
    U8      callState;
    U8      blkState;

} ChkPntMsg;

#define CHKPNT_MSG  0x434b5054
#define APPRDY_MSG  0x41524459

typedef struct
{
    IsupRcvInfoBlk  info;
    SiAllSdus       sdu;
    ChkPntMsg       chkPntMsg;
} Event;

typedef struct circuit
{
    short       state;
    CTAQUEUEHD  ctaQueue;
    CTAHD       ctaHndl;
    CirId       cirId;
    CirId       mateId;
    SuId        suId;
    SiInstId    suInstId;
    SiInstId    spInstId;
    U8          callState;
    U8          blkState;
    U8          transient;

} Circuit;

typedef struct
{
    char               *stateName;  /* pointer to state name */
    void              (*state)();   /* pointer to state function */
} StateDesc;

#endif
