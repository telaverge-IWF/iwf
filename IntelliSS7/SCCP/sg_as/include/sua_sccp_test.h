#ifndef SUA_SCCP_TEST_H
#define SUA_SCCP_TEST_H

/*
 * ANSI/CCITT Prototypes
 */
ITS_INT TEST_SendCR(ITS_OCTET protClassVal);
ITS_INT TEST_SendCC(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendCREF(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendRLSD(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendRLC(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendDT1(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendDT2(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendAK(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendUDT();
ITS_INT TEST_SendUDTS(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendED();
ITS_INT TEST_SendEA(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendRSR();
ITS_INT TEST_SendRSC(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendERR(its::SCCP_MessageClass* recvMsg);
ITS_INT TEST_SendIT();
ITS_INT TEST_SendXUDT();
ITS_INT TEST_SendXUDTS(its::SCCP_MessageClass* recvMsg);

ITS_INT TEST_SendSCMG(ITS_OCTET scmgType);

/*
 * CCITT Prototypes
 */
#if defined(CCITT)

ITS_INT TEST_SendLUDT();
ITS_INT TEST_SendLUDTS(its::SCCP_MessageClass* recvMsg);

#endif // CCITT

int TEST_DecodeSCCPMsg(ITS_HDR &hdr, its::SCCP_MessageClass* msg);


#endif // SUA_SCCP_TEST_H

