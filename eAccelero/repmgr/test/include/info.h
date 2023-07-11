


typedef struct SessionBindingKey
{
    bool isIPv4Address;
    std::string key;
}sessBindKey;

typedef struct SessionInfo
{
    std::string serverName;
    unsigned int counter;
    unsigned int   sessionTerminateTimerId;

    unsigned char  gxSessionFlag:1;
    unsigned char  gxxSessionFlag:1;
    unsigned char  rxSessionFlag:1;
    unsigned char  s9SessionFlag:1;

    

   

}sessInfo;


