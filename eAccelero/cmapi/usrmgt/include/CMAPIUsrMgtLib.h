/* ********************************-*-H-*-************************************
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

#ifndef __CMAPIUSERLIB_H_
#define __CMAPIUSERLIB_H_


using namespace std;

#include <string.h>

#include "UserManagement.h"
#include "CMgrUserManagementMethods_caller.h"

// Common Management Library Class

class CMAPIUserConfig : public Stub::CMgrUserManagementMethodsRespCbk
{
public:
 CMAPIUserConfig() {}
 ~CMAPIUserConfig() {}

 int InitializeLibrary();

//CMAPI Library Methods

 int AddUserRole(Roles RoleList,UserDetailResp* Resp);
 int DelUserRole(Roles RoleList,UserDetailResp* Resp);
 int ModUserRole(Roles RoleList,UserDetailResp* Resp);
 int GetUserRole(Roles RoleList,UserDetailResp* Resp);
 int GetPrevilage(Previlages PrevilageList,UserDetailResp* Resp);
 int GetUser(UserDetails RoleList,UserDetailResp* Resp);
 int ModUser(UserDetails UserList,UserDetailResp* Resp);
 int DelUser(UserDetails UserList,UserDetailResp* Resp);
 int AddUser(UserDetails UserList,UserDetailResp* Resp);
 int GetEmailContentDetails(EmailContentReq Req, EmailContentResp* Resp);
 int GetEmailServerDetails(EmailServerReq Req, EmailServerResp* Resp);
 int SetEmailServerDetails(EmailServerReq Req,EmailServerResp* Resp);
 int DelEmailServerDetails(EmailServerReq Req,EmailServerResp* Resp);
 int ModEmailContentDetails(EmailContentReq Req,EmailContentResp* Resp);
 int HandleGetUserConfigReqsRespCbk(UserDetailResp *Resp);
 int HandleSetUserConfigReqsRespCbk(UserDetailResp *Resp);
 int HandleSetEmailContentReqsRespCbk(EmailContentResp *Resp);
 int HandleGetEmailContentReqsRespCbk(EmailContentResp *Resp);
 int HandleSetEmailServerReqsRespCbk(EmailServerResp *Resp);
 int HandleGetEmailServerReqsRespCbk(EmailServerResp *Resp);

 void EncryptEmailServerPassword(EmailServerReq *Req,EmailServerResp *Resp);
/*
 * User has to give te correct iLength, there is no validation for the same
 * and undefined behaviour will be observed
 */
 void EncryptString(char *sInBuffer, char *sOutBuffer,int iLength);
 void DecryptEmailServerPassword(EmailServerReq Req,EmailServerResp *Resp);
/*
 * User has to give te correct iLength, there is no validation for the same
 * and undefined behaviour will be observed
 */
 void DecryptString(char *sInBuffer, char *sOutBuffer,int iLength);

private:
  int IsResponseOK(UserDetailResp *Resp);
  int IsResponseOK(EmailServerResp *Resp);
  int IsResponseOK(EmailContentResp *Resp);

  Stub::CMgrUserManagementMethods   *m_CMgrUserMgmtCallerObj;
  CMAPIIntSync        *m_CMAPIResponse;

  static const unsigned int m_waitTime = 32000000;
  ErrorDetails m_lastError;
  volatile bool m_SendSuccess;
};

#endif  // __CMAPILIB_H_
