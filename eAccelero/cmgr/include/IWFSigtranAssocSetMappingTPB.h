/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#ifndef IWF_SIGTRAN_ASSOC_SET_MAPPING_T_PB_H
#define IWF_SIGTRAN_ASSOC_SET_MAPPING_T_PB_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <CMAPICMgr.h>
#include <CMAPICommon.h>

#include <CommonStructure.h>
#include <config.h>


class IWFSigtranAssocSetMappingTPBQuery
{
	public:
        void sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
		void sql_IWFSigtranAssocSetMapping_Create_Check_Modifcation_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex);
		void sql_IWFSigtranAssocSetMapping_Create_Add_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex);
        void sql_IWFSigtranAssocSetMapping_Create_Add_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
		void sql_IWFSigtranAssocSetMapping_Create_Mod_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex);
		void sql_IWFSigtranAssocSetMapping_Create_Delete_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex);
        void sql_IWFSigtranAssocSetMapping_Create_Delete_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
		DbStatus_e sql_IWFSigtranAssocSetMapping_Payload_Validation(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,int iIndex);
        void sql_IWFSigtranAssocSetMapping_Create_Select_Query(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,char *pStatement,int iIndex);
        void sql_IWFSigtranAssocSetMapping_Create_OrderBy_Select_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
        void sql_IWFSigtranAssocSetMapping_Create_Select_Query(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
		DbStatus_e sql_IWFSigtranAssocSetMapping_Check_All_Invalid(IwfSigtranAssociationSetConfig *IwfSigtranAssociationSetConfigReq,int iIndex);
        void sql_IWFSigtranAssocSetMapping_Create_Select_Query_For_Delete_Association_Validation(IwfSigtranAssociationConfig *IwfSigtranAssociationConfigReq,char *pStatement);
};

#endif

