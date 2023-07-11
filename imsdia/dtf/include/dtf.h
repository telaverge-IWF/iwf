/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 ****************************************************************************/
#ifndef _DTF_H_
#define _DTF_H_

#include <json/json.h>

namespace diameter {


typedef eAccelero::Reference<DiameterTransformer,eAccelero::PluginObjRP> TransformerObjRef;

class DTF {

    public:
		DTF();
	     ~DTF();

		//Logging related
		void InitLog();
		eAccelero::Logger& GetLogger();

		void SetLogChannel(const unsigned int channel);
		void SetLogLevel(const unsigned int level);

        int CheckAndInvokeTransform(DiaMsgFlow& inMsg,unsigned int outDictId,DiaMsgFlow** outMsg);
        int LoadTransformerObject(unsigned int dict1,unsigned int dict2,std::string pluginName, std::string Config);
        void UnloadTransformerObject(unsigned int dict1,unsigned int dict2);
        unsigned int getDictIdForAppId(unsigned int appId,diameter::DictionaryTable& dictTable,unsigned int dictIds[]);

        bool validateDictIds(diameter::DictionaryTable& dictTable, unsigned int dictIds[]);

    private:

        uint64_t createTransformerKey(unsigned int dict1, unsigned int dict2);

        std::map<uint64_t,TransformerObjRef> m_transformerTable;
        eAccelero::Mutex m_tableLock;
        Json::Value parsePluginConfig(std::string cfgFileName);

		Json::Reader m_jsonConfigFileReader;
		Json::Value m_jsonRoot;

		//Logging ralated
		eAccelero::Logger *m_logger;
		eAccelero::SyslogChannel m_syslogChannel;
        /* currently we are using syslogchannel to avoid unneccessary log 
         * file being generated under /var/log/dre commenting filelogchannel
         */
		//eAccelero::FileLogChannel m_fileLogChannel;
};

}

#endif
