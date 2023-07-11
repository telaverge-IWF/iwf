/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/
#ifndef _DIAMETER_DICTIONARY_STATS_H_
#define _DIAMETER_DICTIONARY_STATS_H_

#include "Statistics.h"
#include "GenericStatsCounter.h"
#include "MsgStatsCounter.h"
#include "DiameterDictionary.h"

namespace diameter {

#define DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it = dictRef->DictStatsMap.find(commandCode); \
            if((it != dictRef->DictStatsMap.end())) \
            { \
                it->second->MsgStats[eAccelero::StatsIndex].IncrementRxReqCount(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef1; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId, dictRef1))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it1 = dictRef1->DictStatsMap.find(commandCode); \
            if((it1 != dictRef1->DictStatsMap.end())) \
            { \
                it1->second->MsgStats[eAccelero::StatsIndex].GetRxReqCount(); \
            } \
        } \
    }

#define DIA_INC_INTERFACE_TOTAL_REQUEST_SENT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef2; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef2))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it2 = dictRef2->DictStatsMap.find(commandCode); \
            if((it2 != dictRef2->DictStatsMap.end())) \
            { \
                it2->second->MsgStats[eAccelero::StatsIndex].IncrementTxReqCount(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_TOTAL_REQUEST_SENT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef3; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef3))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it3 = dictRef3->DictStatsMap.find(commandCode); \
            if((it3 != dictRef3->DictStatsMap.end())) \
            { \
                it3->second->MsgStats[eAccelero::StatsIndex].GetTxReqCount(); \
            } \
        } \
    }

#define DIA_INC_INTERFACE_TOTAL_RESPONSE_RECEIVED(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef4; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef4))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it4 = dictRef4->DictStatsMap.find(commandCode); \
            if((it4 != dictRef4->DictStatsMap.end())) \
            { \
                it4->second->MsgStats[eAccelero::StatsIndex].IncrementRxRspCount(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_TOTAL_RESPONSE_RECEIVED(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef5; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef5))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it5 = dictRef5->DictStatsMap.find(commandCode); \
            if((it5 != dictRef5->DictStatsMap.end())) \
            { \
                it5->second->MsgStats[eAccelero::StatsIndex].GetRxRspCount(); \
            } \
        } \
    }

#define DIA_INC_INTERFACE_TOTAL_RESPONSE_SENT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef6; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef6))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it6 = dictRef6->DictStatsMap.find(commandCode); \
            if((it6 != dictRef6->DictStatsMap.end())) \
            { \
                it6->second->MsgStats[eAccelero::StatsIndex].IncrementTxRspCount(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_TOTAL_RESPONSE_SENT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef7; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef7))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it7 = dictRef7->DictStatsMap.find(commandCode); \
            if((it7 != dictRef7->DictStatsMap.end())) \
            { \
                it7->second->MsgStats[eAccelero::StatsIndex].GetTxRspCount(); \
            } \
        } \
    }

#define DIA_RESET_INTERFACE_TOTAL_MSGS(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef8; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef8))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it8 = dictRef8->DictStatsMap.find(commandCode); \
            if((it8 != dictRef8->DictStatsMap.end())) \
            { \
                it8->second->MsgStats[eAccelero::StatsIndex].Reset(); \
            } \
        } \
    }

#define DIA_INC_INTERFACE_ERROR_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef9; \
        if((DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef9))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it9 = dictRef9->DictStatsMap.find(commandCode); \
            if((it9 != dictRef9->DictStatsMap.end())) \
            { \
                it9->second->ErrorStats[eAccelero::StatsIndex].Increment(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_ERROR_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef10; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef10))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it10 = dictRef10->DictStatsMap.find(commandCode); \
            if((it10 != dictRef10->DictStatsMap.end())) \
            { \
                it10->second->ErrorStats[eAccelero::StatsIndex].GetCount(); \
            } \
        } \
    }

#define DIA_RESET_INTERFACE_ERROR_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef11; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef11))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it11 = dictRef11->DictStatsMap.find(commandCode); \
            if((it11 != dictRef11->DictStatsMap.end())) \
            { \
                it11->second->ErrorStats[eAccelero::StatsIndex].Reset(); \
            } \
        } \
    }

#define DIA_INC_INTERFACE_INVALID_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef12; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef12))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it12 = dictRef12->DictStatsMap.find(commandCode); \
            if((it12 != dictRef12->DictStatsMap.end())) \
            { \
                it12->second->InvalidMsgs[eAccelero::StatsIndex].Increment(); \
            } \
        } \
    }

#define DIA_GET_INTERFACE_INVALID_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef13; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef13))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it13 = dictRef13->DictStatsMap.find(commandCode); \
            if((it13 != dictRef13->DictStatsMap.end())) \
            { \
                it13->second->InvalidMsgs[eAccelero::StatsIndex].GetCount(); \
            } \
        } \
    }

#define DIA_RESETT_INTERFACE_INVALID_MSG_COUNT(dictId,commandCode) \
    if (DiaStackClass::InterfaceStatsEnabled()) \
    { \
        DiameterDictionaryRef dictRef14; \
        if(( DiaStackClass::GetDictionaryTable().fetchDictionaryObject(dictId,dictRef14))) \
        { \
            std::map<uint32_t,DiameterDictionaryStats*>::iterator it14 = dictRef14->DictStatsMap.find(commandCode); \
            if((it14 != dictRef14->DictStatsMap.end())) \
            { \
                it14->second->InvalidMsgs[eAccelero::StatsIndex].Reset(); \
            } \
        } \
    }
}
namespace diameter {

    class DiameterDictionaryStats {
        public:
            eAccelero::MsgStatsCounter MsgStats[EACC_MAX_THREADS];
            eAccelero::GenericStatsCounter ErrorStats[EACC_MAX_THREADS];
            eAccelero::GenericStatsCounter InvalidMsgs[EACC_MAX_THREADS];
    };

}

#endif //#ifndef _DIAMETER_DICTIONARY_STATS_H_
