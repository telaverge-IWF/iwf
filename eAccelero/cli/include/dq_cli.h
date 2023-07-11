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


#ifndef _DQ_CLI_H_
#define _DQ_CLI_H_

#include "LibCli.h"

/* Exported Function Declarations */
extern int Add_CLI(struct cli_def *cli, int (*funCalllback)(struct cli_def *, char *commad, char **argv, int),
        unsigned int interfaceId, unsigned int methodId, unsigned short Cli_Id, char const* cmd_str, ...);

extern void cli_install(struct cli_def *cli, int mode, int prev, int cmd_enumId);
extern "C" int dre_cli_init(struct cli_def *ctree);
extern "C" int iwf_cli_init(struct cli_def *ctree);
extern "C" int avamgr_cli_init(struct cli_def *ctree);
extern "C" int repmgr_cli_init(struct cli_def *ctree);
#endif

