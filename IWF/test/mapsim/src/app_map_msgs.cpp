#include <sys/time.h>
char* sim;
extern ApplicationStats appStats;
extern void GetMode();

//////////////////////////////////////////////////////////////////////////
// Have Few global constants in encoding the messages.
//
byte gImsi[]    = { 0x04, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF1 };
byte gHlrAddr[] = { 0x99, 0x99, 0x88, 0x88, 0x88 };
byte gMsIsdn[]  = { 0x66, 0x66, 0x77, 0x77, 0x88 };
byte gExtTele[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

std::vector<byte> gImsiList[4];

void BuildImsiList()
{
    byte a1[] = { 0x04, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF1 };
    byte a2[] = { 0x04, 0x55, 0x03, 0x00, 0x00, 0x00, 0x00, 0xF1 };
    byte a3[] = { 0x04, 0x55, 0x06, 0x00, 0x00, 0x00, 0x00, 0xF1 };

    gImsiList[0].insert(gImsiList[0].begin(), a1, a1 + sizeof(a1));
    gImsiList[1].insert(gImsiList[1].begin(), a2, a2 + sizeof(a2));
    gImsiList[2].insert(gImsiList[2].begin(), a3, a3 + sizeof(a3));
}

int GetRecvImsiIndex()
{
    static int index = 0;

    if (gRecvImsi.length() >= 15)
    {
        // We have strip here becase the IWFArray is sending some extra junk.
        gRecvImsi.erase(15, std::string::npos);
        if (gRecvImsi.compare("404120000000001") == 0)
        {
            return 0;
        }
        else if (gRecvImsi.compare("405530000000001") == 0)
        {
            return 1;
        }
        else if (gRecvImsi.compare("405560000000001") == 0)
        {
            return 2;
        }
    }

    index = (index++ % 3);

    return index;
}

AsnObject* BuildMapMsg(MAP_OPCODE opCode)
{
    AsnObject *obj = 0;

    switch (opCode)
    {
        case MAP_V13_UPDATE_LOC:
            obj = BuildUpdateLocV13();
            break; 

        case MAP_V13_UPDATE_LOC_RES:
            obj = BuildMapResMsgV13();
            break;

        case MAP_V13_INSERT_SUB_DATA:
            obj = BuildInsertSubDataV13();
            break;

        case MAP_V13_UPDATE_GPRS_LOC:
            obj = BuildUpdateGPRSLocV13();
            break;

        case MAP_V13_UPDATE_GPRS_LOC_RES:
            obj = BuildUpdateGPRSLocResV13();
            break;

        case MAP_V13_PROVIDE_SUB_INFO:
            obj = BuildProvideSubscriberInfoArgV13();
            break;

        case MAP_V13_DELETE_SUB_DATA:
            obj = BuildDeleteSubscriberDatArgV13(); 
            break;
            
        case MAP_V13_SEND_AUTHENTICATION_INFO_RES:
            obj = BuildSendAuthenticationInfoResV13();
            break;

        case MAP_V13_READY_FOR_SM_RES:
            obj = BuildReadyForSM_ResV13();
            break;

        case MAP_V13_CANCEL_LOCATION:
            obj = BuildCancelLocationArgV13();
            break;

        case MAP_V13_PURGEMS_RES:
            obj = BuildPurgeMSResV13();
            break;

        default:
            break;
    }

    return obj;
}

AsnObject* BuildUpdateGPRSLocV13() {
    return 0;
}

AsnObject* BuildUpdateGPRSLocResV13() {
    map_v13::UpdateGprsLocationRes       *gprsl = new map_v13::UpdateGprsLocationRes();

    map_v13::UpdateGprsLocationRes::Sgsn_mmeSeparationSupported smmeSupp;
    map_v13::UpdateGprsLocationRes::Add_Capability              addCap;

    std::vector<byte> iaddr(gHlrAddr, gHlrAddr + sizeof(gHlrAddr));

    map_v13::ISDN_AddressString isdnAddr(iaddr);
    gprsl->SetHlr_Number(isdnAddr);

    gprsl->SetSgsn_mmeSeparationSupported(smmeSupp);
    gprsl->SetAdd_Capability(addCap);
   
    return gprsl;
}

AsnObject* BuildUpdateLocV13()
{
    int idx = GetRecvImsiIndex();
    map_v13::UpdateLocationArg *upArg = new map_v13::UpdateLocationArg();
    //std::vector<byte>          iaddr(gImsi, gImsi + sizeof(gImsi));
    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);
    //std::vector<byte>          imsiData(gMsIsdn, gMsIsdn + 5);

    //map_v13::IMSI               imsi(imsiData);
    map_v13::IMSI               imsi(gImsiList[idx]);
    map_v13::ISDN_AddressString isdnAddr(iaddr);

    upArg->SetImsi(imsi);
    upArg->SetMsc_Number(isdnAddr);
    upArg->SetVlr_Number(isdnAddr);

    return upArg;
}

AsnObject* BuildMapResMsgV13()
{
    map_v13::UpdateLocationRes *upRes = new map_v13::UpdateLocationRes();
    std::vector<byte> addrStr(gHlrAddr, gHlrAddr + 5);

    map_v13::ISDN_AddressString hlrNum(addrStr);

    upRes->SetHlr_Number(hlrNum);
    return upRes;
}

AsnObject* BuildInsertSubDataV13()
{
    int idx = GetRecvImsiIndex();
    map_v13::InsertSubscriberDataArg *isdArg =
                            new map_v13::InsertSubscriberDataArg();
    std::vector<byte>           imsidata(gImsi, gImsi + sizeof(gImsi));
    std::vector<byte>           msdata(gMsIsdn, gMsIsdn + 5);
    std::vector<byte>           extdata(gExtTele, gExtTele + 9);

    map_v13::IMSI                imsi(gImsiList[0]);
    //map_v13::IMSI                imsi(imsidata);
    map_v13::ISDN_AddressString  msisdn(msdata);
    map_v13::SubscriberStatus    subStatus(
                                 map_v13::SubscriberStatus::SUBSCRIBER_STATUS_SERVICE_GRANTED);
    map_v13::TeleserviceList     telServ;
    map_v13::Ext_TeleserviceCode extService(extdata);
    map_v13::InsertSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature rrest;

    telServ.AddElement(extService);

    isdArg->SetImsi(imsi);
    isdArg->SetMsisdn(msisdn);
    isdArg->SetRoamingRestrictionDueToUnsupportedFeature(rrest);

    map_v13::GPRSSubscriptionData gprsSD;
    map_v13::GPRSSubscriptionData::CompleteDataListIncluded cdnull;
    map_v13::GPRSDataList datalist;

    gprsSD.SetCompleteDataListIncluded(cdnull);
    byte arr[2] = { 0x011, 0x22};
    byte arqos[3] = { 0x01, 0x02, 0x03 };
    byte arapn[10] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    std::vector<byte> type(arr, arr + 2);
    std::vector<byte> qos(arqos, arqos + 3);
    std::vector<byte> apn(arapn, arapn + 10);

    map_v13::ContextId ctxtid(0xBEEF);
    map_v13::PDP_Type  pdpty(type);
    map_v13::QoS_Subscribed qoss(qos);
    map_v13::APN            apno(apn);
    map_v13::PDP_Context    pdp;

    pdp.SetPdp_ContextId(ctxtid);
    pdp.SetPdp_Type(pdpty);
    pdp.SetQos_Subscribed(qoss);
    pdp.SetApn(apno);

    datalist.AddElement(pdp); 
    gprsSD.SetGprsDataList(datalist);

    isdArg->SetGprsSubscriptionData(gprsSD);
 
    return isdArg;
}

AsnObject* BuildProvideSubscriberInfoArgV13()
{
    int idx = GetRecvImsiIndex();
    map_v13::ProvideSubscriberInfoArg *psiArg = new map_v13::ProvideSubscriberInfoArg();

    //std::vector<byte> imsidata(gImsi, gImsi + sizeof(gImsi));
    map_v13::IMSI     imsi(gImsiList[idx]);
    //map_v13::IMSI     imsi(imsidata);

    psiArg->SetImsi(imsi);

    map_v13::RequestedInfo                      reqInfo;
    map_v13::RequestedInfo::T_adsData           tads;
    map_v13::RequestedInfo::SubscriberState     subs;
    map_v13::RequestedInfo::LocationInformation linfo;
    map_v13::RequestedInfo::CurrentLocation     curloc;

    reqInfo.SetLocationInformation(linfo);
    reqInfo.SetSubscriberState(subs);
    reqInfo.SetCurrentLocation(curloc);
    reqInfo.SetT_adsData(tads);

    psiArg->SetRequestedInfo(reqInfo);

    return psiArg;
}

AsnObject* BuildDeleteSubscriberDatArgV13()
{
    int idx = GetRecvImsiIndex();
    map_v13::DeleteSubscriberDataArg *dsdArg = new map_v13::DeleteSubscriberDataArg();

    //std::vector<byte> imsidata(gImsi, gImsi + sizeof(gImsi));
    map_v13::IMSI     imsi(gImsiList[idx]);
    //map_v13::IMSI     imsi(imsidata);

    dsdArg->SetImsi(imsi);

    map_v13::DeleteSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature rrst;
    dsdArg->SetRoamingRestrictionDueToUnsupportedFeature(rrst);

    uint8_t zca[] = { 0x01, 0x02 };
    std::vector<byte> zc(zca, zca + sizeof(zca));
    map_v13::ZoneCode regZone(zc);

    dsdArg->SetRegionalSubscriptionIdentifier(regZone);

    // TODO: Select Context ID choice.
    map_v13::EPS_SubscriptionDataWithdraw epsSubData;
    map_v13::EPS_SubscriptionDataWithdraw::AllEPS_Data aed;
    epsSubData.SetChoiceAllEPS_Data(aed);
    dsdArg->SetEpsSubscriptionDataWithdraw(epsSubData);

    map_v13::GPRSSubscriptionDataWithdraw gprs;
    map_v13::GPRSSubscriptionDataWithdraw::AllGPRSData agprs;
    gprs.SetChoiceAllGPRSData(agprs);
    dsdArg->SetGprsSubscriptionDataWithdraw(gprs);

    return dsdArg;
}

AsnObject* BuildSendAuthenticationInfoResV13() 
{
    map_v13::SendAuthenticationInfoRes *sair = new map_v13::SendAuthenticationInfoRes();
    
    map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList eps_AuthenticationSetList;
    map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList::EPC_AV epc_AV;

    byte rand_a[] = {
        0x3f, 0x18, 0xeb, 0xdd,
        0xdb, 0x84, 0x29, 0x3d,
        0x64, 0x79, 0xca, 0xd7,
        0x81, 0x1e, 0x26, 0x58
    };    
    std::vector<byte> rand_bv(rand_a, rand_a + sizeof(rand_a));
    map_v13::RAND rand_os(rand_bv);
    epc_AV.SetRand(rand_os);
    
    byte xres_a[] = {
        0x19, 0xe6, 0xcf, 0xf9,
        0x43, 0x79, 0x68, 0x61
    };
    std::vector<byte> xres_bv(xres_a, xres_a + sizeof(xres_a));
    map_v13::XRES xres_os(xres_bv);
    epc_AV.SetXres(xres_os);
    
    byte autn_a[] = {
        0x61, 0x70, 0x23, 0xab,
        0xb2, 0x5a, 0x00, 0x00,
        0x93, 0xf3, 0x3b, 0xb4,
        0x9a, 0x2e, 0x11, 0xc6
    };
    std::vector<byte> autn_bv(autn_a, autn_a + sizeof(autn_a));
    map_v13::AUTN autn_os(autn_bv);
    epc_AV.SetAutn(autn_os); 
    
    byte kasme_a[] = {
        0xdc, 0x86, 0x08, 0x5f,
        0xa0, 0xba, 0xcf, 0x31,
        0x67, 0xc0, 0xc9, 0xb4,
        0x20, 0xbf, 0x3f, 0xdc,
        0xdc, 0x86, 0x08, 0x5f,
        0xa0, 0xba, 0xcf, 0x31,
        0x67, 0xc0, 0xc9, 0xb4,
        0x20, 0xbf, 0x3f, 0xdc        
    };
    std::vector<byte> kasme_bv(kasme_a, kasme_a + sizeof(kasme_a));
    map_v13::KASME kasme_os(kasme_bv);
    epc_AV.SetKasme(kasme_os);
    
    eps_AuthenticationSetList.AddElement(epc_AV);
    
    sair->SetEps_AuthenticationSetList(eps_AuthenticationSetList);
    
    return sair;
}

AsnObject* BuildReadyForSM_ResV13()
{
    map_v13::ReadyForSM_Res *rfsr = new map_v13::ReadyForSM_Res();
    // nothing to be built!!
    
    return rfsr;
}

AsnObject* BuildCancelLocationArgV13()
{
    map_v13::CancelLocationArg *clArg = new map_v13::CancelLocationArg();

    // Set IMSI
    std::vector<byte> imsidata(gImsi, gImsi + sizeof(gImsi));
    map_v13::IMSI     imsi(imsidata);
    map_v13::Identity id;
    id.SetChoiceImsi(imsi);

    clArg->SetIdentity(id);

    // Set the Cancellation Type
    clArg->SetCancellationType(new map_v13::CancellationType(
        map_v13::CancellationType::CANCELLATION_TYPE_UPDATE_PROCEDURE));

    // Set TypeOfUpdate to MME
    clArg->SetTypeOfUpdate(new map_v13::TypeOfUpdate(
        map_v13::TypeOfUpdate::TYPE_OF_UPDATE_MME_CHANGE));

    return clArg;
}

AsnObject* BuildPurgeMSResV13()
{
    map_v13::PurgeMS_Res *puaRes = new map_v13::PurgeMS_Res();
    map_v13::PurgeMS_Res::FreezeM_TMSI mtmsi;
    map_v13::PurgeMS_Res::FreezeP_TMSI ptmsi;

    //Set freeze MTMSI and freeze PTMSI
    puaRes->SetFreezeP_TMSI(ptmsi);
    puaRes->SetFreezeM_TMSI(mtmsi);
    
    return puaRes;
}


#ifdef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
    printf("|------------------------+---------------------------+-------------------------|\r\n")

#define DISPLAY_HEADER()\
    printf("|    Counter Name        |      Periodic value       |     Cumulative value    |\r\n")
#define DISPLAY_TXT_COL(T1, V1, V2)\
    printf("| %-22.22s | %-25.25s |", T1, V1); printf(" %-24.24s|\r\n", V2)

#define DISPLAY_TXT_COL_1(T1)\
    printf("| %-27.27s:", T1)

#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-22.22s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-22.22s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-22.22s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-22.22s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-22.22s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-22.22s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-22.22s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-22.22s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-22.22s | %-52.52s|\r\n", T1, V1)
#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-22s | %25s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//	printf("| %-22.22s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
    printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
    printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
    printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
    printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
    printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-22.22s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}

#define RESET_PL_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
    struct tm *L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL)
    {
        memset (P_time, 0, TIME_LENGTH);
    }
    else
    {
        sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

    static char L_time [TIME_LENGTH];
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (L_time, 0, TIME_LENGTH);
    } else {
        sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec);
    }
    return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;

    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;

    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
    mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
    long L_val_sec, L_val_usec;

    L_val_sec = P_final->tv_sec - P_init->tv_sec;
    L_val_usec = P_final->tv_usec - P_init->tv_usec;
    if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
    return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

#endif // _STAT_MACROS_H
#endif // SEAGUL_STYLE_OUTPUT

#ifndef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_EMPTY_LINE()\
    printf("|                                                                              |\r\n")
#define DISPLAY_OPEN_TEXT(T1)\
    printf("| %s", T1);fflush(stdout)

#define DISPLAY_EMPTY_TEXT(T1)\
    printf("| %-77.77s|\r\n", T1)
    //printf("| %s |\r\n", T1)

    //printf("| %-77.77s|\r\n", T1)

/*#define DISPLAY_EMPTY_TEXT(T1)\
    printf("| %s                                                                           |\r\n", T1)*/

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
    printf("|-----------------------------+----------------------+-------------------------|\r\n")

#define DISPLAY_BANNER()\
    printf("|                    Diametriq MAP-HLR Simulator                               |\r\n", sim)

#define DISPLAY_BANNER2()\
    printf("|                Simulator Logs After Transformation                           |\r\n", sim)

#define DISPLAY_HEADER()\
    printf("|        Main Menu            |                     Statistics                 |\r\n")

#define DISPLAY_CROSS_LINE2()\
    printf("|-----------------------------|------------------------------------------------|\r\n")

#define DISPLAY_TXT_COL(T1, T2, V1)\
    printf("| %-27.27s | %-35.35s :", T1, T2); printf(" %-9d|\r\n", V1)

#define DISPLAY_TXT_COL_1(T1)\
    printf("| %-27.27s:", T1)

#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-27.27s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-27.27s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-27.27s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-27.27s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-27.27s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-27.27s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-27.27s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-27.27s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-27.27s | %-52.52s|\r\n", T1, V1)

#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-27s | %20s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//	printf("| %-27.27s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
    printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
    printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
    printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
    printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
    printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-27.27s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}

#define RESET_PL_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
    struct tm *L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL)
    {
        memset (P_time, 0, TIME_LENGTH);
    }
    else
    {
        sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

    static char L_time [TIME_LENGTH];
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (L_time, 0, TIME_LENGTH);
    } else {
        sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec);
    }
    return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;

    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;

    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
    mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
    long L_val_sec, L_val_usec;

    L_val_sec = P_final->tv_sec - P_init->tv_sec;
    L_val_usec = P_final->tv_usec - P_init->tv_usec;
    if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
    return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

#endif // _STAT_MACROS_H
#endif // not SEAGUL_STYLE_OUTPUT

void printHLRMenu()
{
    printf("\n");
    /*DISPLAY_CROSS_LINE (); 
    DISPLAY_BANNER();
    DISPLAY_CROSS_LINE();

    DISPLAY_CROSS_LINE();
    DISPLAY_HEADER();*/
    DISPLAY_TXT_COL_1("1. Send MAP CancelLocation Request");
    DISPLAY_TXT_COL_1("2. Send MAP InsertSubscriberData Request");
    DISPLAY_TXT_COL_1("3. Send MAP DeleteSubscriberData Request");
    //DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
    DISPLAY_LINE();
    DISPLAY_OPEN_TEXT ("Enter your choice _");
}

void printMainMenu()
{
    printf("\n");
    DISPLAY_CROSS_LINE (); 
    DISPLAY_BANNER();
    DISPLAY_CROSS_LINE();

    DISPLAY_CROSS_LINE();
    DISPLAY_HEADER();
    DISPLAY_TXT_COL ("1. Send Server Initated Messages","1. Total Number of UpdateGPRS Loc Request Received",   appStats.u.hlrmap.ulr.m_in);
    DISPLAY_TXT_COL (" ", "2. Total Number of UpdateGPRS Responses Sent",   appStats.u.hlrmap.ula.m_out);
    DISPLAY_TXT_COL ("2. Reset Statistics  ", "3. Total Number of SendAuthInfo Requests Received",   appStats.u.hlrmap.air.m_in);
    DISPLAY_TXT_COL (" ", "4. Total Number of SendAuthInfo Responses sent",   appStats.u.hlrmap.aia.m_out);
    DISPLAY_TXT_COL (" ", "5. Total Number of InsertSubscriberData Requests Sent",   appStats.u.hlrmap.idr.m_out);
    DISPLAY_TXT_COL (" ", "6. Total Number of InsertSubscriberData Responses Received ",   appStats.u.hlrmap.idr.m_in);
    DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
    DISPLAY_LINE();
    DISPLAY_OPEN_TEXT ("Enter your choice _");

}

void DisplayMessageDetails()
{
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);
    struct timeval currentTime;
    long globalElapsedTime;
    long localElapsedTime;
    string inStr;
    int choice;

    printf("\n");
    DISPLAY_DLINE();
   // Display the data
    char L_start_time[TIME_LENGTH];
    char L_current_time[TIME_LENGTH];
    gettimeofday (&currentTime, NULL);
    formatTime(L_start_time, &startTime);
    formatTime(L_current_time, &currentTime);
    DISPLAY_3TXT ("Start/Current Time", 
            L_start_time, 
            L_current_time);
    globalElapsedTime   = ms_difftime (&currentTime, &startTime);
    localElapsedTime    = ms_difftime (&currentTime, &periodicStartTime);

    if(displayMode == 20)
    {
        DISPLAY_DLINE();
        DISPLAY_BANNER();
        DISPLAY_DLINE();
        DISPLAY_HEADER();
        DISPLAY_DLINE();
        /*DISPLAY_TXT_COL ("1. Send MAP CancelLocation Req", "* Total UGL Request Received",   appStats.u.hlrmap.ulr.m_in);
        DISPLAY_TXT_COL ("2. Display Message Details", "* Total UGL Responses Sent",   appStats.u.hlrmap.ula.m_out);
        DISPLAY_TXT_COL ("3. Reset Statistics", "* Total SAI Requests Received",   appStats.u.hlrmap.air.m_in);
        DISPLAY_TXT_COL ("", "* Total SAI Responses Sent",   appStats.u.hlrmap.aia.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Requests Sent",   appStats.u.hlrmap.idr.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Response Received ",   appStats.u.hlrmap.idr.m_in);
        DISPLAY_TXT_COL ("", "* Total CancelLocation Requests Sent",   appStats.u.hlrmap.clr.m_out);
        DISPLAY_TXT_COL ("", "* Total CcancelLocation Response Received ",   appStats.u.hlrmap.clr.m_in);
        DISPLAY_TXT_COL ("", "* Total Rejected messages ", appStats.m_failedCalls);
        DISPLAY_DLINE();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE();
        DISPLAY_OPEN_TEXT ("Enter Your Choice _");
        printf("\n");*/
        DISPLAY_DLINE();
        DISPLAY_EMPTY_TEXT (" IWF <--> MAP Messages ::");
        DISPLAY_LINE();
        DISPLAY_EMPTY_LINE ();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx].c_str())
        {
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+1].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+2].c_str());
        }
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str());

        if(appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str());
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str());
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str());
        //DISPLAY_LINE();
        DISPLAY_DLINE();
        printf("\n");
        printf("\n");
    }
    int numberOfCall        = appStats.m_outMsgs + appStats.m_inMsgs;
    //float averageCallRate     = (globalElapsedTime > 0 ? 1000*(float)numberOfCall/(float)globalElapsedTime : 0.0);
    numberOfCall        = (appStats.m_outMsgs - appStats.m_lastOutMsgs) + (appStats.m_inMsgs - appStats.m_lastInMsgs);
    /*float realInstantCallRate = (localElapsedTime  > 0 ? 
            1000*(float)numberOfCall / (float)localElapsedTime :
            0.0);*/

    gettimeofday (&periodicStartTime, NULL);
    appStats.m_lastSuccessfulCalls = appStats.m_successfulCalls;
    appStats.m_lastFailedCalls = appStats.m_failedCalls;
    appStats.m_lastOutMsgs = appStats.m_outMsgs;
    appStats.m_lastInMsgs = appStats.m_inMsgs;
}


void DisplayMainWindow()
{
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);
    struct timeval currentTime;
    long globalElapsedTime;
    long localElapsedTime;
    string inStr;
    int choice;

    printf("\n");
    DISPLAY_DLINE();
   // Display the data
    char L_start_time[TIME_LENGTH];
    char L_current_time[TIME_LENGTH];
    gettimeofday (&currentTime, NULL);
    formatTime(L_start_time, &startTime);
    formatTime(L_current_time, &currentTime);
    DISPLAY_3TXT ("Start/Current Time", 
            L_start_time, 
            L_current_time);
    globalElapsedTime   = ms_difftime (&currentTime, &startTime);
    localElapsedTime    = ms_difftime (&currentTime, &periodicStartTime);

    if(displayMode == 40)
    {
        DISPLAY_DLINE();
        DISPLAY_BANNER();
        DISPLAY_DLINE();
        DISPLAY_HEADER();
        DISPLAY_DLINE();
        DISPLAY_TXT_COL (" 100. CancelLocationArg", "* Total UGL Request Received",   appStats.u.hlrmap.ulr.m_in);
        DISPLAY_TXT_COL (" 55.  InsertSubscriberData", "* Total UGL Responses Sent",   appStats.u.hlrmap.ula.m_out);
        DISPLAY_TXT_COL (" 85.  DeleteSubscriberDataArg", "* Total SAI Requests Received",   appStats.u.hlrmap.air.m_in);
        DISPLAY_TXT_COL (" 75.  ProvideSubscriberInfoArg", "* Total SAI Responses Sent",   appStats.u.hlrmap.aia.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Requests Sent",   appStats.u.hlrmap.idr.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Response Received ",   appStats.u.hlrmap.idr.m_in);
        DISPLAY_TXT_COL ("", "* Total CL Requests Sent",   appStats.u.hlrmap.clr.m_out);
        DISPLAY_TXT_COL ("", "* Total CL Response Received ",   appStats.u.hlrmap.clr.m_in);
        DISPLAY_TXT_COL ("", "* Total Rejected messages ", appStats.m_failedCalls);
        DISPLAY_DLINE();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE();
        //DISPLAY_OPEN_TEXT ("Enter Your Choice _");
        printf("\n");
        DISPLAY_OPEN_TEXT ("Press '9' to return to Main Menu");
        printf("\n");
 
    }
    else if(displayMode == 20)
    {
        DISPLAY_DLINE();
        DISPLAY_BANNER();
        DISPLAY_DLINE();
        DISPLAY_HEADER();
        DISPLAY_DLINE();
        DISPLAY_TXT_COL ("1. Send HLR Messages", "* Total UGL Request Received",   appStats.u.hlrmap.ulr.m_in);
        DISPLAY_TXT_COL ("2. Display Message Details", "* Total UGL Responses Sent",   appStats.u.hlrmap.ula.m_out);
        DISPLAY_TXT_COL ("3. Reset Statistics", "* Total SAI Requests Received",   appStats.u.hlrmap.air.m_in);
        DISPLAY_TXT_COL ("", "* Total SAI Responses Sent",   appStats.u.hlrmap.aia.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Requests Sent",   appStats.u.hlrmap.idr.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Response Received ",   appStats.u.hlrmap.idr.m_in);
        DISPLAY_TXT_COL ("", "* Total CL Requests Sent",   appStats.u.hlrmap.clr.m_out);
        DISPLAY_TXT_COL ("", "* Total CL Response Received ",   appStats.u.hlrmap.clr.m_in);
        DISPLAY_TXT_COL ("", "* Total Rejected messages ", appStats.m_failedCalls);
        DISPLAY_DLINE();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE();
        printf("\n");
        DISPLAY_OPEN_TEXT ("Enter Your Choice _");
        printf("\n");
        /*DISPLAY_DLINE();
        DISPLAY_EMPTY_TEXT (" IWF <--> MAP Messages ::");
        DISPLAY_LINE();
        DISPLAY_EMPTY_LINE ();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx].c_str())
        {
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+1].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+2].c_str());
        }
        DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str());
        DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str());

        if(appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str());
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str());
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str());
        DISPLAY_LINE();
        DISPLAY_DLINE();
        printf("\n");
        printf("\n");*/

    }
    else if(displayMode == 30)
    {
        DISPLAY_DLINE();
        DISPLAY_BANNER();
        DISPLAY_DLINE();
        DISPLAY_BANNER2();

        /*DISPLAY_DLINE();
        DISPLAY_HEADER();
        DISPLAY_DLINE();
        DISPLAY_TXT_COL ("1. Send MAP CancelLocation Req", "* Total UGL Request Received",   appStats.u.hlrmap.ulr.m_in);
        DISPLAY_TXT_COL ("2. Display Message Details", "* Total UGL Responses Sent",   appStats.u.hlrmap.ula.m_out);
        DISPLAY_TXT_COL ("3. Reset Statistics", "* Total SAI Requests Received",   appStats.u.hlrmap.air.m_in);
        DISPLAY_TXT_COL ("", "* Total SAI Responses Sent",   appStats.u.hlrmap.aia.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Requests Sent",   appStats.u.hlrmap.idr.m_out);
        DISPLAY_TXT_COL ("", "* Total ISD Response Received ",   appStats.u.hlrmap.idr.m_in);
        DISPLAY_TXT_COL ("", "* Total CL Requests Sent",   appStats.u.hlrmap.clr.m_out);
        DISPLAY_TXT_COL ("", "* Total CL Response Received ",   appStats.u.hlrmap.clr.m_in);
        DISPLAY_TXT_COL ("", "* Total Rejected messages ", appStats.m_failedCalls);
        DISPLAY_DLINE();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE();
        DISPLAY_OPEN_TEXT ("Enter Your Choice _");
        printf("\n");*/
        DISPLAY_DLINE();
        //DISPLAY_EMPTY_TEXT ("        MAP-HLR Messages After Transformation  ");
        //DISPLAY_LINE();
        DISPLAY_EMPTY_LINE ();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx].c_str())
        {
            DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx].c_str());
            DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+1].c_str());
            DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+2].c_str());
        }
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+3].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+4].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+5].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+6].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+7].c_str());
        //DISPLAY_LINE();

        if(appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+8].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+9].c_str());
        //DISPLAY_LINE();
        if(appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str())
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx+10].c_str());
        DISPLAY_DLINE();
        printf("\n");
        DISPLAY_OPEN_TEXT ("Press '9' to return to Main Menu");
        printf("\n");
        printf("\n");
    }

    int numberOfCall        = appStats.m_outMsgs + appStats.m_inMsgs;
    //float averageCallRate     = (globalElapsedTime > 0 ? 1000*(float)numberOfCall/(float)globalElapsedTime : 0.0);
    numberOfCall        = (appStats.m_outMsgs - appStats.m_lastOutMsgs) + (appStats.m_inMsgs - appStats.m_lastInMsgs);
    /*float realInstantCallRate = (localElapsedTime  > 0 ? 
            1000*(float)numberOfCall / (float)localElapsedTime :
            0.0);*/

    gettimeofday (&periodicStartTime, NULL);
    appStats.m_lastSuccessfulCalls = appStats.m_successfulCalls;
    appStats.m_lastFailedCalls = appStats.m_failedCalls;
    appStats.m_lastOutMsgs = appStats.m_outMsgs;
    appStats.m_lastInMsgs = appStats.m_inMsgs;
}
