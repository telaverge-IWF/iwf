////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: TCAP Interface Module                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: tim_api.h,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: tim_api.h,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:10  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.4  2002/09/20 14:41:21  ngoel
// LOG: add support for ITU
// LOG:
// LOG: Revision 1.1.2.3  2002/09/20 13:40:30  ngoel
// LOG: add support for ITU TCAP
// LOG:
// LOG: Revision 1.1.2.2  2002/09/19 17:53:40  ngoel
// LOG: add response encode/decode
// LOG:
// LOG:
// LOG:
//
////////////////////////////////////////////////////////////////////////////////
//

#include <engine++.h>
#include <vframe.h>
#include <engine.h>
#include <tcap++.h>
#include <Asn.h>

using namespace std;
using namespace its;

extern int opc;
extern int dpc;
extern int ossn;
extern int dssn;
extern int gwpc;
extern char gwip1[20];
extern char gwip2[20];
extern char gwip3[20];
extern char gwip4[20];

int TimSend(int dlgType, ITS_USHORT dialogueID, ITS_OCTET invId, int operation);
vector <byte> TIM_Encode();
int TIM_Decode(vector <byte> &data);
vector <byte> TIM_EncodeResponse();
int TIM_DecodeResponse(vector <byte> &data);

#define TIM_INVOKE_ID              0x01

#if defined(CCITT)
#define TCAP_L_CANCEL_TYPE   TCPPT_TC_L_CANCEL
#define TCAP_END_TYPE        TCPPT_TC_END
#define TCAP_BEGIN_TYPE      TCPPT_TC_BEGIN
#define TCAP_CONTINUE_TYPE   TCPPT_TC_CONTINUE
#define TCAP_P_ABORT_TYPE    TCPPT_TC_P_ABORT
#define ISS7_Stack           ISS7_CCITT_Stack
#define CLASS_1              0x01
#define DUMMY_OP             100
#define TCPPT_TC_RESULT_L       TCAP_PT_TC_RESULT_L_CCITT
#else
#define TCAP_L_CANCEL_TYPE   TCPPT_TC_CANCEL
#define TCAP_END_TYPE        TCPPT_TC_RESP
#define TCAP_BEGIN_TYPE      TCPPT_TC_QUERY_W_PERM
#define TCAP_CONTINUE_TYPE   TCPPT_TC_CONV_W_PERM
#define TCAP_P_ABORT_TYPE    TCPPT_TC_ABORT
#define ISS7_Stack           ISS7_ANSI_Stack
#define TCPPT_TC_RESULT_L       TCAP_PT_TC_RESULT_L_ANSI
#endif

/*.interface:TIM_Api
 *****************************************************************************
 *  Interface:
 *      TIM_Api
 *
 *  Purpose:
 *      TIM_Api class defines the methods to be called by the Application
 *      in order to initialize, send SMS message receive SMS message and 
 *      finally terminate.
 *
 *  Usage:
 *     // instantiate an Api object and call initialize
 *     TIM_Api* api_classptr = new TIM_Api();
 *     res= api_classptr->Initialize(argc, argv);
 *
 *     if (res != ITS_SUCCESS)
 *     {
 *         printf("\n Initialization FAILED !!!!!!!!!");
 *         api_classptr->Terminate();
 *         exit(0);
 *     }
 *     else
 *     {
 *         printf("\n SUCCESS FROM INITIALIZATION API !!");
 *     }
 * 
 *****************************************************************************/
class TIM_Api
{
public:

    TIM_Api()
    {
    };

    int Initialize(int argc, char** argv);
    
    static int Terminate();

    ~TIM_Api()
    { };

    static int GetLocalPC()
    {
        return opc;
    }

    static int GetRemotePC()
    {
        return dpc;
    }

    static int GetLocalSSN()
    {
        return ossn;
    }

    static int GetRemoteSSN()
    {
        return dssn;
    }

    static int GetGwPC()
    {
        return gwpc;
    }

    static char * GetGwIP1()
    {
        return gwip1;
    }

    static char * GetGwIP2()
    {
        return gwip2;
    }

    static char * GetGwIP3()
    {
        return gwip3;
    }

    static char * GetGwIP4()
    {
        return gwip4;
    }




};
