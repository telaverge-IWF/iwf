/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: server.java,v $
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
//#ident "$Id: server.java,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $"

package app;

import java.io.*;
import java.net.*;

/**
 * Class       : server
 *
 * Purpose     : This class implements a test tcpip based java diameter server
 *
 */
class server
{
    public static void main(String[] args) throws Exception
    {
        try
        {
            ServerSocket serverSocket = new ServerSocket(8001);
            System.out.println("Waiting for client to connect");
            Socket connection = serverSocket.accept();
            System.out.println("Connected");

            InputStream inputStream = connection.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(dataInputStream));

            OutputStream outputStream = connection.getOutputStream();
            PrintStream printStream = new PrintStream(outputStream);

            while(true)
            {
//              String line = dataInputStream.readLine();
                String line = bufferedReader.readLine();

                printStream.println("########" + line);

                if(line.equals("end"))
                {
                    System.out.println("Closing Connection");
                    serverSocket.close();
                    System.exit(0);
                }//if
                else
                {
                      System.out.println(line);
                }//else
            }//while
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }        
    }//main
}
