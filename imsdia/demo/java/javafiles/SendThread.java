//package .;

import java.lang.Thread;

class SendThread extends Thread implements app{

    private String[] args;
    public SendThread(String[] cmdArgs)
    {
        System.out.println("Send Thread Created");
        args = cmdArgs;
    }

    public void Run()
    {
        PrintMenu();
    }

    void PrintMenu() throws Exception
    {
        try
        {
            int input = 0;
            int choice = 0;
            char[] buffer = new char[256];
            //IDS_MESSAGE reg;
            //IDSCLApi api;

            while(true)
            {
                System.out.println("\n###############CHOICE###########\n");
                System.out.println("1.Connect\n");
                System.out.println("2.Register\n");
                System.out.println("3.DeRegister\n");
                System.out.println("4.Send\n");
                System.out.println("0.Terminate\n");
                System.out.println("\n###############################\n");

                input = System.in.read();

                switch(input)
                {
                    case 1:
                        // Initializes the connectivity with the IDS_Server
//                      api.Initialize(hostIpAddress,serverPort); - //tcp port connectivity to server
                        break;
                    case 2:
                        System.out.println("\nClient ID\n");
                        input = System.in.read();
                        //reg.clientID = input; 
                        //reg.msg_type = REGISTER_MSG;
                        //reg.u.regInfo.routing_criteria = IDS_APP_IDENTIFIER;
                        System.out.println("\nApp ID \n");
                        //SendAppId = System.in.read();
                        //reg.u.regInfo.appIdentifier = SendAppId;
                        //reg.u.regInfo.connectionType = conType;
  
                        // Registers the client wrt Client ID and Application ID.
                        //api.Register(reg);
                        break;
                    case 3:
                        //reg.msg_ype = DEREGISTER_MSG;
                   
                        //De-Register the Registered Client
                        //api.DeRegister(reg);
                        break;
                    case 4:
                       //Display the Menu to send the message to stack based on the Registered Application ID.

                       switch(SendAppId)
                       {
                           case BASE_INTERFACE_APP_ID:
                               sample_base.BaseMenu();
                               break;
                           /*case CXDX_INTERFACE_APP_ID:
                               CxdxMenu();
                               break;
                           case SH_INTERFACE_APP_ID:
                               ShMenu();
                               break;
                           case GQGQ_INTERFACE_APP_ID:
                               GqMenu();
                               break;*/
                           default:
                               System.out.println("Please enter valid AppID");
                               break;
                       }//end switch
                       break;
                   case 0:
                       System.exit(1);
                       break;
                }//end switch
            }//end while
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }//end of PrintMenu
}
