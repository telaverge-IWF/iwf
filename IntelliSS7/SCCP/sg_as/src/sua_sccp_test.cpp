#include <engine++.h>
#include <sg_as.h>
#include <sua_sccp_test.h>
#include <sccp_pprint.h>
#include <iostream>

using namespace its;
using namespace std;

ITS_HDR shdr, rhdr;             /* Send and receive headers */
ITS_UINT srcLocalRef;           /* Source Local Reference */
ITS_UINT destLocalRef;          /* Destination Local Reference */

ITS_INT TEST_SendConnectionConfirm(ITS_INT var, SCCP_SourceLocalRef *slr,
                                   ITS_HDR &hdr);

ITS_INT
TEST_SendSCMG(ITS_OCTET scmgType)
{
    SCCP_UnitData           udt;
    SCCP_ProtocolClass      protClass(SCCP_PCLASS_0);
    SCCP_CalledPartyAddr    cdp;
    SCCP_CallingPartyAddr   cgp;
    SCCP_UserData           userData;
    ITS_INT                 ret = 0;
    SCCP_SCMG               ssa;
    ITS_OCTET               ssaData[20];
    int                     ssaLen = sizeof(SCCP_SCMG_ANSI);

    /* Build SSA message */
    ssa.type = scmgType;
    ssa.ssn = app_ossn;
    ssa.multiplicity = 1;

#ifdef ANSI
    SCCP_ANSI_SET_PC(ssa.pointCode.data, app_opc);
#elif defined(CCITT)
    SCCP_ITU_SET_PC(ssa.pointCode.data, app_opc);
#else
#error "Undefined Protocol"
#endif

    /*
     * TODO: Set Global title for GTT based routing.
     */

    cdp.SetPointCode(app_dpc);
    cdp.SetSSN(1);
    cdp.SetRouteByPCSSN(true);

    cgp.SetPointCode(app_opc);
    cgp.SetSSN(app_ossn);
    cgp.SetRouteByPCSSN(true);
 
    udt.AddIE(&cdp);
    udt.AddIE(&cgp);
    udt.AddIE(&protClass);

    udt.SetSIO(MTP3_SIO_SCCP);

    memcpy(ssaData, &ssa, ssaLen);
    userData.SetUserData(ssaData, ssaLen);
    udt.AddIE(&userData);

    PrintSCCPMessage(&udt);

    /* send the message */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &udt);
    if (ret == ITS_SUCCESS)
    {
        cout << "UDT send success." << endl;
    }
    else
    {
        cout << "Failed to send UDT." << endl;
    }

    return ret;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
TEST_SendUDT()
{
    SCCP_UnitData         udt;
    SCCP_ProtocolClass    protClass(SCCP_PCLASS_0);
    SCCP_CalledPartyAddr  cdp;
    SCCP_CallingPartyAddr cgp;
    SCCP_UserData         userData;
    ITS_OCTET             data[40];
    int                   len = 40;
    ITS_INT               ret = 0;

    /*
     * TODO: Set Global title for GTT based routing.
     */

    cdp.SetPointCode(app_dpc);
    cdp.SetSSN(app_dssn);
    cdp.SetRouteByPCSSN(true);

    cgp.SetPointCode(app_opc);
    cgp.SetSSN(app_ossn);
    cgp.SetRouteByPCSSN(true);
 
    udt.AddIE(&cdp);
    udt.AddIE(&cgp);
    udt.AddIE(&protClass);

    udt.SetSIO(MTP3_SIO_SCCP);

    for (int i = 0; i < 40; i++)
    {
        data[i] = i;
    }

    userData.SetUserData(data, len);
    udt.AddIE(&userData);

    PrintSCCPMessage(&udt);

    /* send the message */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &udt);
    if (ret == ITS_SUCCESS)
    {
        cout << "UDT send success." << endl;
    }
    else
    {
        cout << "Failed to send UDT." << endl;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
TEST_SendCR(ITS_OCTET protClassVal)
{
    ITS_OCTET data[40];
    SCCP_ConnectionRequest cr;

    int ret = SCCP_GetNextLocalRef(ISS7_Stack, &shdr.context.conref);
    ITS_ASSERT(ret == ITS_SUCCESS);

    // Mandatory parameters
    SCCP_SourceLocalRef     slr(shdr.context.conref);
    SCCP_CalledPartyAddr    cdp;
    SCCP_ProtocolClass      protClass(protClassVal);
    
    // Optional parameters
    SCCP_CallingPartyAddr   cgp;
    SCCP_Credit             credit(9); // For prot class 3 only
    SCCP_UserData           userData;
    SCCP_HopCount           hopCount(5);
#if defined(CCITT)
    SCCP_Importance         importance(1);
#endif

    cdp.SetPointCode(app_dpc);
    cdp.SetSSN(app_dssn);
    cdp.SetRouteByPCSSN(true);

    cgp.SetPointCode(app_opc);
    cgp.SetSSN(app_ossn);
    cgp.SetRouteByPCSSN(true);

    int len = 40;
    for (int i = 0; i < len; i++)
    {
        data[i] = i;
    }

    userData.SetUserData(data, len);

    // Mandatory parameters
    cr.AddIE(&slr);
    cr.AddIE(&cdp);
    cr.AddIE(&protClass);
    // Optional parameters
    cr.AddIE(&cgp);
    cr.AddIE(&credit);
    cr.AddIE(&userData);
    cr.AddIE(&hopCount);

    cr.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&cr);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &cr);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendCC(its::SCCP_MessageClass* recvMsg)
{
   return 0;
}

ITS_INT
TEST_SendConnectionConfirm(SCCP_SourceLocalRef *rslr, ITS_HDR &hdr,
                           its::SCCP_MessageClass* recvMsg)
{
    int ret;
    ITS_OCTET protClassVal = 0;

    /* Create received CR message */
    SCCP_ConnectionRequest* cr = (SCCP_ConnectionRequest*)recvMsg;
    SCCP_ProtocolClass *pProtClass = (SCCP_ProtocolClass *)cr->FindIE(SCCP_PRM_PROTOCOL_CLASS);
    if (pProtClass != NULL)
    {
        protClassVal = pProtClass->GetProtocolClass();
        cout << "CR Protocol Class " << (int)protClassVal << endl;
    }

    cout << "****** TEST_SendConnectionConfirm ****" << endl;
    /* Create message */
    SCCP_ConnectionConfirm cc;

    /* Destination Local Reference */
    cout << "DestinationLocalRef: " << hdr.context.conref << endl;

    SCCP_DestinationLocalRef dlr(rslr->GetRefNum());

    cc.AddIE(&dlr);

    SCCP_SourceLocalRef slr(hdr.context.conref);
    cc.AddIE(&slr);

    /* Protocol Class */
    SCCP_ProtocolClass pc(protClassVal);
    cc.AddIE(&pc);

    /* Credit */                                //len=3
    SCCP_Credit credit;
    credit.SetCredit(9);
    cc.AddIE(&credit);
    
    /* Called Party Address */                  //len=4 min
    SCCP_CalledPartyAddr called_pa;
    called_pa.SetPointCode(app_dpc);           //octet 3 - any
    called_pa.SetSSN(app_dssn);                 //octet 2 - 0000 0001
    called_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
    called_pa.SetInternationalRouting(false);   //octet 1 bit 8 
    cc.AddIE(&called_pa);

    // Data                                     //len=3-130
    SCCP_UserData ud;
    int len = 100;
    ITS_OCTET data[100];
    //fill data
    for(ITS_OCTET i=0;i<len;i++)
    {
        data[i] = i;
    }
    ud.SetUserData(data, len);
    cc.AddIE(&ud);
    
    cc.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&cc);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &cc);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

int
TEST_DecodeSCCPMsg(ITS_HDR &hdr, SCCP_MessageClass* msg)
{
    SCCP_SourceLocalRef *slr = NULL;
    srcLocalRef = hdr.context.conref;

    switch (msg->GetMsgType())
    {
        case SCCP_MSG_CR:
        {
            SCCP_ConnectionRequest *cr = (SCCP_ConnectionRequest *)msg;
            slr = (SCCP_SourceLocalRef *)cr->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            TEST_SendConnectionConfirm(slr, hdr, msg);
        }
            break;
        

        case SCCP_MSG_CC:
        {
            SCCP_ConnectionConfirm *cc = (SCCP_ConnectionConfirm *)msg;
            slr = (SCCP_SourceLocalRef *)cc->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            destLocalRef = slr->GetRefNum();
        }
            break;

        default:
            break;
    }

    return ITS_SUCCESS;
}

ITS_INT
TEST_SendCREF(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* Build a message */
    SCCP_ConnectionRefused cr;
    cout<<"\nmsg";

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    cr.AddIE(&dlr);
    cout<<"\nslr";

    /* Refusal Cause */
    SCCP_RefusalCause rc(SCCP_REF_END_USER_ORG);
    cr.AddIE(&rc);
    cout<<"\nref cause";

    /* Called Party Address */                  //len=4 min
    SCCP_CalledPartyAddr called_pa;
    called_pa.SetPointCode(0);                  //1=address contains subsystem number
    called_pa.SetSSN(app_dssn);          
    called_pa.SetRouteByPCSSN(true); 
    called_pa.SetInternationalRouting(false);   //set to national
    cr.AddIE(&called_pa);
    cout<<"\ncalled pa";

    // Data 
    SCCP_UserData ud;
    int len = 100;                              //len=3-130
    ITS_OCTET data[100];
    // fill data 
    for(ITS_OCTET i=0;i<len;i++)
    {
        data[i] = i;
    }
    ud.SetUserData(data, len);
    cr.AddIE(&ud);
    cout<<"\ndata";

    cr.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&cr);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &cr);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendRLSD(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* create a message */
    SCCP_Released rm;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    rm.AddIE(&dlr);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srcLocalRef);
    rm.AddIE(&slr);

    /* Released Cause */
    SCCP_ReleaseCause rc(SCCP_RLC_END_USER_ORG);
    rm.AddIE(&rc);
    
    // Data 
    SCCP_UserData ud;
    int len = 100;                              //len=3-130
    ITS_OCTET data[100];
    // fill data 
    for(ITS_OCTET i=0;i<len;i++)
    {
        data[i] = i;
    }
    ud.SetUserData(data, len);
    rm.AddIE(&ud);
    
    rm.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&rm);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &rm);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendRLC(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* make a message */
    SCCP_ReleaseComplete rc;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    rc.AddIE(&dlr);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(shdr.context.conref);
    rc.AddIE(&slr);

    rc.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&rc);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &rc);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendDT1(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* create a message */
    SCCP_DataForm1 dt1;
    
    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    dt1.AddIE(&dlr);

    /* segmenting/reassembling */
    SCCP_SegmentReassem sr(1); //more data
    /*  implementation can be changed to:
        SCCP_SegmentReassem sr();
        sr.SetSegmentReassem(1);    //0 means no data */
    dt1.AddIE(&sr);
    
    /* Data */                                  //2-256
    SCCP_UserData ud;
    ITS_OCTET data[100];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    dt1.AddIE(&ud);
    
    dt1.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&dt1);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &dt1);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendDT2(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* create a message */
    SCCP_DataForm2 dt2;
            
    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    dt2.AddIE(&dlr);

    /* Sequencing/segmenting */
    SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
    dt2.AddIE(&ss);

    /* Data */                                  // 2-256
    SCCP_UserData ud;
    ITS_OCTET data[150];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    dt2.AddIE(&ud);
    
    dt2.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&dt2);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &dt2);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendAK(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* build a message */
    SCCP_Acknowledge ack;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    ack.AddIE(&dlr);

    /* receive sequence number */
    SCCP_ReceiveSequenceNum rsn(1,0); //rsn=1, haveMore=0
    ack.AddIE(&rsn);

    /* Credit */
    SCCP_Credit credit(1);
    ack.AddIE(&credit);

    ack.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&ack);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &ack);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendED()
{
    int ret;

    /* build a message */
    SCCP_ExpeditedData ed;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    ed.AddIE(&dlr);

    /* Data */                                      //2-33
    SCCP_UserData ud;
    ITS_OCTET data[20];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    ed.AddIE(&ud);

    ed.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&ed);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &ed);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendEA(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* build a message */
    SCCP_ExpeditedDataAcknowledge eda;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    eda.AddIE(&dlr);

    eda.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&eda);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &eda);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendRSR()
{
    int ret;

    /* build a message */
    SCCP_ResetRequest rr;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    rr.AddIE(&dlr);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(shdr.context.conref);
    rr.AddIE(&slr);

    /* Reset cause */
    SCCP_ResetCause rc(SCCP_RES_END_USER_ORG);
    rr.AddIE(&rc);

    rr.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&rr);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &shdr, &rr);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendRSC(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* build a message */
    SCCP_ResetConfirm rm;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(shdr.context.conref);
    rm.AddIE(&dlr);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(rhdr.context.conref);
    rm.AddIE(&slr);

    rm.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&rm);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &rm);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendERR(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* build a message */
    SCCP_Error em;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    em.AddIE(&dlr);

    /* error cause */
    SCCP_ErrorCause ec(SCCP_ERR_LRN_MISS_DRN);
    em.AddIE(&ec);

    em.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&em);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &em);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendIT()
{
    int ret;

    /* build a message */
    SCCP_InactivityTest it;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(rhdr.context.conref);
    it.AddIE(&dlr);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srcLocalRef);
    it.AddIE(&slr);

    /* Protocol Class */
    SCCP_ProtocolClass pc(SCCP_PCLASS_3);
    it.AddIE(&pc);
    
    /* Sequencing/segmenting */
    SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
    it.AddIE(&ss);

    /* Credit */
    SCCP_Credit credit(9);
    it.AddIE(&credit);

    it.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&it);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &rhdr, &it);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendUDTS(its::SCCP_MessageClass* recvMsg)
{
    int ret;

    /* build a message */
    SCCP_UnitDataService udts;

    /*return cause */
    SCCP_ReturnCause rc(SCCP_RET_NO_TRANS_ADDR_NAT);
    udts.AddIE(&rc);

    /* Called Party Address */                  //len=3 min
    SCCP_CalledPartyAddr called_pa;
    called_pa.SetPointCode(app_dpc);            //1=address contains subsystem number
    called_pa.SetSSN(app_dssn);          
    called_pa.SetRouteByPCSSN(true); 
    called_pa.SetInternationalRouting(false);   //set to national by default
    udts.AddIE(&called_pa);

    /* Calling Party Address */                 //len=2 min
    SCCP_CallingPartyAddr calling_pa;
    calling_pa.SetPointCode(app_opc);
    calling_pa.SetSSN(app_ossn);
    calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
    calling_pa.SetInternationalRouting(false);   //set to national
    udts.AddIE(&calling_pa);        

    /* Data */                                  //2-254
    SCCP_UserData ud;   
    ITS_OCTET data[100];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    udts.AddIE(&ud);

    
    ITS_HDR hdr;
    hdr.type = ITS_SCCP;
    hdr.context.ssn = app_dssn;

    udts.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&udts);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &hdr, &udts);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}

ITS_INT
TEST_SendXUDT()
{
    int ret = 0;

    /* build a message */
    SCCP_ExtendedUnitData xudt;

    /* protocol class */
    SCCP_ProtocolClass pc(SCCP_PCLASS_3);
    xudt.AddIE(&pc);

    /* SCC hop Counter  */
    SCCP_HopCount hc(15);   //initial value <16 is recommended
    xudt.AddIE(&hc);

    /* Called Party Address */                  //len=3 min
    SCCP_CalledPartyAddr called_pa;
    called_pa.SetPointCode(app_dpc);                  //1=address contains subsystem number
    called_pa.SetSSN(app_dssn);          
    called_pa.SetRouteByPCSSN(true); 
    called_pa.SetInternationalRouting(false);   //set to national by default
    xudt.AddIE(&called_pa);

    /* Calling Party Address */                 //len=2 min
    SCCP_CallingPartyAddr calling_pa;
    calling_pa.SetPointCode(app_opc);
    calling_pa.SetSSN(app_ossn);
    calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
    calling_pa.SetInternationalRouting(false);   //set to national
    xudt.AddIE(&calling_pa);        

    /* Data */                                  //2-254
    SCCP_UserData ud;
    ITS_OCTET data[254];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    xudt.AddIE(&ud);

    ITS_HDR hdr;
    hdr.type = ITS_SCCP;
    hdr.context.ssn = app_dssn;

    xudt.SetSIO(MTP3_SIO_SCCP);

    PrintSCCPMessage(&xudt);

    /* Send the message  */
    cout << "Send results in: "
         << SCCP_MessageClass::Send(ISS7_Stack, &hdr, &xudt)
         << endl;

    return ret;
}

ITS_INT
TEST_SendXUDTS(its::SCCP_MessageClass* recvMsg)
{
    int ret = 0;

    /* build a message */
    SCCP_ExtendedUnitDataService xudts;

    /* return cause */
    SCCP_ReturnCause rc(SCCP_RET_NO_TRANS_ADDR_NAT);
    xudts.AddIE(&rc);

    /* hop counter */
    SCCP_HopCount hc(12);   //initial value <16 is recommended
    xudts.AddIE(&hc);

    /* Called Party Address */                  //len=3 min
    SCCP_CalledPartyAddr called_pa;
    called_pa.SetPointCode(app_dpc);                  //1=address contains subsystem number
    called_pa.SetSSN(app_dssn);
    called_pa.SetRouteByPCSSN(true);
    called_pa.SetInternationalRouting(false);   //set to national by default
    xudts.AddIE(&called_pa);

    /* Calling Party Address */                 //len=2 min
    SCCP_CallingPartyAddr calling_pa;
    calling_pa.SetPointCode(app_opc);
    calling_pa.SetSSN(app_ossn);
    calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
    calling_pa.SetInternationalRouting(false);   //set to national
    xudts.AddIE(&calling_pa);        

    /* Data */                                  //2-254
    SCCP_UserData ud;   
    ITS_OCTET data[100];
    int len = 5;
    /*fill data */
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    ud.SetUserData(data, len);
    xudts.AddIE(&ud);
    
    ITS_HDR hdr;
    hdr.type = ITS_SCCP;
    hdr.context.ssn = app_dssn;

    xudts.SetSIO(MTP3_SIO_SCCP);
    PrintSCCPMessage(&xudts);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &hdr, &xudts);
    cout << "Send results in: "
         << ret
         << endl;

    return ret;
}


/*
 * CCITT Prototypes
 */
#if defined(CCITT)

ITS_INT
TEST_SendLUDT()
{
    int ret = 0;
    return ret;
}

ITS_INT
TEST_SendLUDTS(its::SCCP_MessageClass* recvMsg)
{
    int ret = 0;
    return ret;
}

#endif // CCITT
