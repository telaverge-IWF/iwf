/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *
 *  ID: $Id: dia_config.h,v 3.7.46.1 2013/02/27 08:49:06 jvikram Exp $
 *
 *  LOG: $Log: dia_config.h,v $
 *  LOG: Revision 3.7.46.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.7  2010/08/19 11:26:01  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.6  2010/07/10 08:06:09  nvijikumar
 *  LOG: APIs to enable/disable OAM/MML/DCCA feature in XML data
 *  LOG:
 *  LOG: Revision 3.5  2010/07/09 07:04:51  nvijikumar
 *  LOG: Support MML feature enable/disable for TCS
 *  LOG:
 *  LOG: Revision 3.4  2010/06/21 04:24:20  nvijikumar
 *  LOG: Accelero xmlData is returned as heap object, so app no need to do strdup
 *  LOG:
 *  LOG: Revision 3.3  2010/06/17 04:38:16  nvijikumar
 *  LOG: APIs to build default accelero engine XML
 *  LOG:
 *  LOG: Revision 3.2  2009/05/11 05:14:56  rajeshak
 *  LOG: API to set the Heartbeat Interval and Retry.
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:21  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.2  2006/11/14 06:31:31  kamakshilk
 *  LOG: Added GetRouteScheme() required for IDS
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.3  2006/04/17 10:28:57  adutta
 *  LOG: Setting Heart beat params from xml.
 *  LOG:
 *  LOG: Revision 1.2  2006/04/07 11:35:46  yranade
 *  LOG: DoxyGen Compatible Code Comments.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 *  LOG: Building IMS Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_config.h,v 3.7.46.1 2013/02/27 08:49:06 jvikram Exp $"

#if !defined(_DIACORE_CONFIGURATION_H_)
#define _DIACORE_CONFIGURATION_H_


#define MAX_ROUTE_SCHEME_LENGTH   50

/** Interface:
 *      DiaConfig
 *      
 *  Purpose:
 *      DiaConfig class is used to encapsulate all Diameter stack 
 *      abstraction related configuration.
 **/
class DiaConfig
{
public:
   ~DiaConfig();
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the DiaConfig instance. 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Pointer to the singleton DiaConfig object.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    static DiaConfig* GetDiaConfig();

    void Lock() const;

    void Unlock() const;
    
    /********************************************************************/
    /** Purpose:
    *      Function to get the OD Configuration File 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Pointer to the OD Configuration File.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    char *GetConfigFile() const
    {         
        return configFile; 
    }

    
    /********************************************************************/
    /** Purpose:
    *      Function to Set the OD Configuration File. 
    *
    *  Input Parameters:
    *      Pointer to the OD Configuraton File.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void SetConfigFile(char *cfgFile)
    {         
        configFile = cfgFile; 
    }

    /********************************************************************/
    /** Purpose:
    *      Function to get HeartBeat interval
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      HeartBeat interval.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    ITS_UINT GetHeartBeatInterval() const
    {
        return hbIntvl;
    }

    /********************************************************************/
    /** Purpose:
    *      Function to set HeartBeat interval
    *
    *  Input Parameters:
    *      hbInterval - unsigned int.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void SetHeartBeatInterval(ITS_UINT hbInterval)
    {
        hbIntvl = hbInterval;
    }


    /********************************************************************/
    /** Purpose:
    *      Function to get HeartBeat re-tries
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      HeartBeat re-tries.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    ITS_UINT GetHeartBeatRetry() const
    {
        return hbRetry;
    }

    /********************************************************************/
    /** Purpose:
    *      Function to set HeartBeat re-tries
    *
    *  Input Parameters:
    *      retry - unsigned int.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    void SetHeartBeatRetry(ITS_UINT retry)
    {
        hbRetry = retry;
    }

    /********************************************************************/
    /** Purpose:
    *      Function to get Routing Scheme, required for IDS
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *    
    *  Return Value:
    *      String read.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    char *GetRouteScheme() const
    {         
        return (char*)routeScheme.c_str(); 
    }
    int ParserInitialize()
    {
        return ParseResourceManager();
    }
    void SetMMLPort(ITS_UINT mmlPort)
    {
       _mmlPort = mmlPort;
    }
    ITS_UINT GetMMLPort()
    {
        return _mmlPort;
    }
    void SetOAMPort(ITS_UINT oamPort)
    {
        _oamPort = oamPort;
    }
    ITS_UINT GetOAMPort()
    {
        return _oamPort;
    }
    char *GetEngineXMLData();
    void EnableOAMFeatureInXMLData(bool flag)
    {
        enableOam = flag;
    }
    void EnableMMLFeatureInXMLData(bool flag)
    {
        enableMml = flag;
    }
    void EnableDccaFeatureInXMLData(bool flag)
    {
        enableDcca = flag;
    }
    bool IsMMLFeatureEnabledInXMLData()
    {
        return enableMml;
    }
    bool IsOAMFeatureEnabledInXMLData()
    {
        return enableOam;
    }
    bool IsDccaFeatureEnabledInXMLData()
    {
        return enableDcca;
    }
    /********************************************************************
    * Purpose:
    *      Function to set Routing Scheme, required for IDS
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      String read.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    *
    * Revision History:
    *
    *************************************************************************/
    char *SetRouteScheme(char *rtScheme)
    {
        //routeScheme = rtScheme;
        routeScheme.assign(rtScheme);
        return (char*)routeScheme.c_str();
    }

protected:
    bool isDebugDump;
    int ParseResourceManager();
    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;
    char *configFile;
    char *xmlData;
    ITS_UINT hbIntvl;
    ITS_UINT hbRetry;
    ITS_UINT _mmlPort;
    ITS_UINT _oamPort;
    bool enableOam;
    bool enableMml;
    bool enableDcca;
    //char *routeScheme;  /* roundrobin or broadcast, used by IDS */
    //char routeScheme[MAX_ROUTE_SCHEME_LENGTH+1];  /* roundrobin or broadcast, used by IDS */
    std::string routeScheme;


private:
    DiaConfig();                           /* Private Constructor */
    DiaConfig(const DiaConfig&);            /* Prevent Copy Constructor */
    DiaConfig& operator=(const DiaConfig&); /* Prevent assignment */
    char * BuildAcceleroXML(int mmlPort, int oamPort);
};


#endif    
