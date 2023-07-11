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


#ifndef __EACC_RepMgrCfg_h__
#define  __EACC_RepMgrCfg_h__

//using namespace eAccelero;

struct ReplFlagReq
{
    bool bRepl;
};

struct ReplFlagResp
{
    int RespCode;
};

struct ReplLogLevelReq
{
    int   bReplLogLvl;
    bool  bLogFlag;
};

struct ReplLogLevelResp
{
    int RespCode;
};

struct RepMgrCmnStr
{
    int ReqID;  
    union RepMgrCmd {
        struct ReplFlagReq cli_repmgr_rplflag;
        struct ReplLogLevelReq cli_repmgr_loglvl;
    }RepMgrCmdObj;
};

#endif   // __EACC_RepMgrCfg_h__
