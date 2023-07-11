/* ********************************-*-C++-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/
#include "engine++.h"
#include "HAMeSSComponent.h"
#include "iwf_mess.h"
#include "iwf.h"
#include "iwf_transport_controller.h"

using namespace eAccelero;

namespace iwf {

    bool IWFTransportController::_doExit = false;
    ThreadSharedData<bool> IWFTransportController::tsData;


    IWFTransportController::IWFTransportController()
    {        
    }

    IWFTransportController::~IWFTransportController()
    {
        //bool status = false;
        //tsData.Set(status);
        _doExit = true;
    }

    void IWFTransportController::Run(void *args)
    {
        bool status = false;
        while(!_doExit)
        {
            if(tsData.Get(status,1000000))
            {
                if(status)
                {
                    //Perform procedures since DRE is going Active
                    sleep(1);
                    IwfController::GoActive();
                }else
                {
                    //Perform procedures since DRE is going Standby
                    if(_doExit)
                    {
                        return;
                    }
                    IwfController::GoStandby();
                }
            }
        }
    }

    void IWFTransportController::SetTransportStatus(bool newStatus)
    {
        tsData.Set(newStatus);
    }

    void IWFTransportController::SetExit(bool exitStatus)
    {
        _doExit = exitStatus;
    }

}//namespace dre
