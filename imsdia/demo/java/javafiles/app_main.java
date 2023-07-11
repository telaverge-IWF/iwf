/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 ****************************************************************************
 *
 * LOG: $Log: app_main.java,v $
 * LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/05/23 05:55:02  sumag
 * LOG: This is version 1.0 of the tcpip based java diameter client and the test
 * LOG: java server.
 * LOG: The client and server applications in app directory are operational
 * LOG: javafiles directory files - to be completed
 * LOG:
 ****************************************************************************/
//#ident "$Id: app_main.java,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $"

//package .;

import java.lang.Integer;
import java.lang.Thread;
import java.net.*;

class Main implements app{

    /* global variables */

//    static InetAddress hostIpAddress;
    static String hostIpAddress;
    static int serverport;
    static int  conType;
    //static char connectType[20];
    static String connectType;

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method is used to print the Parameters, those are taken at
 *           Run time.
 *
 *  Input Parameters:
 *      String[] args: Arguments.
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
    static void Usage(String[] args)
    {
        System.out.println("Usage: " + args[0]);
        System.out.println("interactive\n");
        System.out.println("Usage: "+ args[0]);
        System.out.println("-oh <value> | ");
        System.out.println("-or <value> | ");
        System.out.println("-dh <value> | ");
        System.out.println("-dr <value>| ");
        System.out.println("-sp <value>| ");
        System.out.println("-srvip <value>| ");
        System.out.println("-contype <value>| ");
        System.out.println("\n");
        System.exit(0);
    }

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method is used to parse the parameters according to the
 *      pre-string given. Set those values to the global variables.
 *
 *  Input Parameters:
 *      int argc: Number of arguments.
 *      String[] args: Arguments.
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

    static void parseArguments(String[] args)
    {
        int i = 1;
        boolean flag = true;
        int ret = 0;

        if(args.length == 1)
        {
            Usage(args);
        }
        for(;i<args.length && flag;i++)
        {
            if(args[i].compareTo("-oh") == 0)
            {
                globals.SetOriginHost(args[++i]);
                System.out.println("OH = "+  args[i] + "\n");
            }
            else if(args[i].compareTo("-or") == 0)
            {
                globals.SetOriginRealm(args[++i]);
                System.out.println("OriginRealm = " + args[i] + "\n");
            }
            else if(args[i].compareTo("-dh") == 0)
            {
                globals.SetDestinationHost(args[++i]);
                System.out.println("DH = " +  args[i] + "\n");
            }
            else if(args[i].compareTo("-dr") == 0)
            {
                globals.SetDestinationRealm(args[++i]);
                System.out.println("DR = " +  args[i] + "\n");
            }
            else if(args[i].compareTo("-sp") == 0)
            {
                serverport=Integer.parseInt(args[++i],10);
                System.out.println("SP = " + args[i] + "\n");
            }
            else if(args[i].compareTo("-srvip") == 0)
            {
                //hostIpAddress = args[++i];
  //            strcpy(hostIpAddress,args[++i]);
                System.out.println("IDS Server = " + args[i] + "\n");
            }
            else if(args[i].compareTo("-contype") == 0)
            {
                // strcpy(connectType,args[++i]);
                connectType = args[++i];
                if(connectType.compareTo("primary") == 0)
                {
                     conType=0;//IDS_PRIMARY_CONNECTION;
                     System.out.println("Connection Type: IDS_PRIMARY_CONNECTION\n");
                }
                else if(connectType.compareTo("backup") == 0)
                {
                     conType=1;//IDS_BACKUP_CONNECTION;
                     System.out.println("Connection Type: IDS_BACKUP_CONNECTION\n");
                }
                else
                {
                     System.out.println(" invalid connection type\n");
                }
           }
           else
           {
                Usage(args);
           }

        }

     }

/*.implementation:static
 ****************************************************************************
 *  Purpose: Main function starts here, it creates two threads one for
 *      Sending the messages and another one for Recieving.
 *
 *  Input Parameters:
 *      String[] argv: commandline arguments.
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
    public static void  main(String[] args) throws Exception
    {
        try
        {
             parseArguments(args);
             SendThread sendThread = new SendThread(args);
             ReceiveThread receiveThread = new ReceiveThread();
             int ret =0;
             //IDSCLApi api;
                                                                                                                          
             /* Specify absolute path if not in the pwd */

             //    api.SetDictionaryFile("dictionary");
                                                                                                                          
                                                                                                                          
             System.out.println("\n\t *******************************************\n");
             System.out.println("\t *****  IntelliNet Technologies, Inc.    *****\n");
             System.out.println("\t *****  IntelliNet Diameter Client Test  *****\n");
             System.out.println("\t *******************************************\n\n\n");
                                                                                                                          
             /* Receive thread */
             receiveThread.start();
                                                                                                                          
             /* Send thread */
             sendThread.start();
                                                                                                                          
             /* Suspend the main */
             receiveThread.join();
                                                                                                                          
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }
}
