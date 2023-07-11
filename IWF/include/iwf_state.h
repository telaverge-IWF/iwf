/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 */
/*
 * File:   State.h
 * Author: adey
 *
 * Created on December 18, 2012, 3:14 PM
 */

#ifndef STATE_H
#define	STATE_H

#include "iwf_sm_defines.h"

class State;

class IwfFsm;

typedef void (State::* Action)(IwfFsm*);

struct Mapping {
    States from;
    Events input;
    States to;
    Action before;
    Action after;
};

class State {
public:

    State(uint16_t id);

    ~State();

    void SendUpstrmReq(IwfFsm* iwfFsm);

    void SendDnstrmReq(IwfFsm* iwfFsm);

    void SendUpstrmResp(IwfFsm* iwfFsm);

    void SendDnstrmResp(IwfFsm* iwfFsm);

    void SendIntrmUpstrmResp(IwfFsm* iwfFsm);

    void SendIntrmUpstrmReq(IwfFsm* iwfFsm);

    void SendIntrmDnstrmReq(IwfFsm* iwfFsm);

    void ProcessErr(IwfFsm* iwfFsm);

    void CheckForRollback(IwfFsm* iwfFsm);

    States GetStateId();

    const char* GetStateName();

protected:

    uint16_t m_id;

    char m_name[MAX_STATE_NAME_LEN];

private:

    friend class IwfFsm;

    State *m_transition[IWF_MAX_EVENTS];

    Action m_before[IWF_MAX_EVENTS];

    Action m_after[IWF_MAX_EVENTS];

};



#endif	/* STATE_H */

