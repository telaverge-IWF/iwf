//package .;

class globals
{

    //public static int mode;
    // public static int choice;

    public static String oHost;
    public static String oRealm;
    public static String dHost;
    public static String dRealm;

    public static String GetOriginHost()
    {
        return oHost;
    }
    public static String GetOriginRealm()
    {
        return oRealm;
    }
    public static String GetDestinationHost()
    {
        return dHost;
    }
    public static String GetDestinationRealm()
    {
        return dRealm;
    }
    public static void SetOriginHost(String oH)
    {
        oHost = oH;
    }
    public static void SetOriginRealm(String oR)
    {
        oRealm = oR;
    }
    public static void SetDestinationHost(String dH)
    {
        dHost = dH;
    }
    public static void SetDestinationRealm(String dR)
    {
        dRealm = dR;
    }

} 
