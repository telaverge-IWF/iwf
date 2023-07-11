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
 * Log: $Log $  
 ****************************************************************************/

#include <map>
#include <itsdiameter.h>
#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <its_dia_config.h>
#include <dia_msg_flow.h>
#include <dia_stack.h>
#include <Sync.h>
#include <PluginObj.h>
#include <DiameterDictionary.h>
#include <DictionaryTable.h>

namespace diameter
{
	DiaMsgFlow::DiaMsgFlow(const unsigned char *buff, int len, ITS_UINT dictId)
		:BaseCommand(buff,len),m_baseGenericCmd(NULL)
	{
        m_dictId = dictId;
        m_InPeerInst = 0;
        m_flags = 0;
	}

	DiaMsgFlow::DiaMsgFlow(diameter::base::BaseGenericCommand* cmd)
		: BaseCommand(cmd),m_baseGenericCmd(cmd)
	{
                m_dictId = 0;
                m_InPeerInst = 0;
                m_flags = 0;
	}
	DiaMsgFlow::DiaMsgFlow(diameter::base::BaseGenericCommand* cmd,bool copyFlag)
		: BaseCommand(cmd)
	{
        m_baseGenericCmd=NULL;
        m_InPeerInst = 0;
        m_dictId = 0;
        m_flags = 0;
	}

    DiaMsgFlow::DiaMsgFlow(DiaMsgFlow& msgFlow)
        :BaseCommand(msgFlow)
    {
        if( msgFlow.m_baseGenericCmd != NULL )
        {
            m_baseGenericCmd = new DIA_GEN_CMD(*(msgFlow.m_baseGenericCmd));
        }
        m_InPeerInst = msgFlow.m_InPeerInst;
        m_dictId = msgFlow.m_dictId;
        m_flags = 0;
    }

	/*	This function is for generic AVP Access.
	 *
	 * Arguments:
	 * 	avpCode: The code for which the AVP value is requried.
	 * 	val: Pointer to the type of AVP for which value is required. This is output argument.
	 * 	D: This is an enum which specifies what is the type of the AVP.
	 * 	index: The index from which AVP should be fetched. In case an AVP occurs multiple 
	 * 	times in a message this function has to be invoked with incrementing index until output is NULL.
	 *
	 * */
	int DiaMsgFlow::getAvpValue(unsigned int avpCode, unsigned int index, void* val, ValueDiscriminator D, unsigned int venId) 
	{
		CommandImpl& cmdImpl = const_cast<CommandImpl&>(m_baseGenericCmd->getImpl());
		/*Get the AVP Value*/
                //Fixing Missing return statement
		return cmdImpl.getAvpValue(avpCode,index,val,D,venId);

	}

	int DiaMsgFlow::getAvpCount(unsigned int avpCode,unsigned int venId) 
	{
		CommandImpl& cmdImpl = const_cast<CommandImpl&>(m_baseGenericCmd->getImpl());
		/*Get the AVP Value*/
                //Fixing Missing return statement
		return cmdImpl.getAvpCount(avpCode,venId);

	}

	/*This function sets the appropriate Command Attribute based on the dictionary id.*/
	int DiaMsgFlow::init_reflection()
	{
		try {
			//TODO: If cmdAttribute is already set in the CommandImpl, have a check to avoid setting it again.
			/*if(cmdImpl.GetCmdAttribute()!=NULL)
			{
				return ITS_SUCCESS;
			}*/
			/*Fetch the appropriate dictionary object from the dictionary table.*/
			DiameterDictionaryRef dictRef = DiaStackClass::GetDictionaryTable().fetchDictionaryObject(m_dictId);

			/*Get the CommandImpl ref from BaseGeneric Command.*/
			CommandImpl& cmdImpl = const_cast<CommandImpl&>(m_baseGenericCmd->getImpl());

			/*Set The CommandAttribute in the CommandImpl which will be useful in getting a Grouped AVP.*/
			cmdImpl.SetCmdAttribute(dictRef->getCommandAttribute(cmdImpl.getCommandCode(),cmdImpl.isRequest()));

		} catch(eAccelero::PluginException& e) { //Fixing Big parameter passing by value
			DT_ERR(("Plugin Exception Caught %s.",e.what()));
			return -1;
		}
		return ITS_SUCCESS;

	}

}
