
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
// CONTRACT:  TCAP Interface Module                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: main.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: main.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:09  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.2  2002/09/20 13:40:30  ngoel
// LOG: add support for ITU TCAP
// LOG:
// LOG: Revision 1.1.2.1  2002/09/19 17:36:36  ngoel
// LOG: TCAP Interface Module
// LOG:
// LOG:
// LOG:
//
////////////////////////////////////////////////////////////////////////////////
//

#include <engine++.h>
#include <engine.h>
#include <tim_api.h>

using namespace std;
using namespace its;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None 
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
 *
 ****************************************************************************/
int
main(int argc, char **argv)
{
      int res;
      int choice;
      TIM_Api* api_classptr = new TIM_Api();

       res = api_classptr->Initialize(argc, argv);
  
       if (res != ITS_SUCCESS)
       {
           printf("\n Initialization FAILED !!!!!!!!!");
           /*api_classptr->Terminate();
           exit(0);*/
       }
       else
       {
           printf("\n SUCCESS FROM INITIALIZATION API !!\n");
       }

       for(;;)
       {
            cout << "Send TCAP Message " << endl;
            cout << "1) Send TCAP Query" << endl;
            cout << "99) Exit Test Program" << endl;
            cin >> choice;

            if (choice == 1)
            {
                TimSend(TCAP_BEGIN_TYPE, 0, 0, 0);
            }
            else if (choice == 99)
            {
                 cout << "exiting test program " << endl;
                 exit(0);
            }
            else
            {
                cout << "Try Again " << endl;
            }
            sleep(1);
       }

}
