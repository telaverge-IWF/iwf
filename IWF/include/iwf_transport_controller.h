/* ********************************-*-H-*-************************************
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
#ifndef _IWF_TRANSPORT_CONTROLLER_
#define _IWF_TRANSPORT_CONTROLLER_

#include "ThreadQueue.h"

namespace iwf {

#define   IWF_ACTIVATE_TRANSPORTS  true
#define   IWF_DEACTIVATE_TRANSPORTS  false

class IWFTransportController:public eAccelero::Runnable {

    public:

    IWFTransportController();

    ~IWFTransportController();

    void Run(void *args);
    
    static void SetTransportStatus(bool newStatus);

    static bool _doExit;

    static void SetExit(bool exitStatus);

    private:

    static eAccelero::ThreadSharedData<bool> tsData;
};

} //namespace dre

#endif
