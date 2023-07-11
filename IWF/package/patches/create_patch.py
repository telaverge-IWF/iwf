#!/usr/bin/python

#*******************************-*-PYTHON-*-*********************************
 #                                                                          *
 #          Copyright 2013 Diametriq, LLC All Rights Reserved.              *
 #            Manufactured in the United States of America.                 *
 #      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 #                                                                          *
 #   This product and related documentation is protected by copyright and   *
 #   distributed under licenses restricting its use, copying, distribution  *
 #   and decompilation.  No part of this product or related documentation   *
 #   may be reproduced in any form by any means without prior written       *
 #   authorization of Diametriq and its licensors, if any.                  *
 #                                                                          *
 #   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 #   government is subject to restrictions as set forth in subparagraph     *
 #   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 #   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 #                                                                          *
 #***************************************************************************/

import sys
import os
import commands
sys.path.append('.')
sys.path.append(os.path.expandvars('$EACC_ROOT/scripts/utils/patch/logger/'))
sys.path.append(os.path.expandvars('$EACC_ROOT/scripts/utils/patch/json_parser/'))
sys.path.append(os.path.expandvars('$EACC_ROOT/scripts/utils/patch/patch_functions/'))


from logger import *
from JsonParser_class import *
from patch_functions import *

def main():
    log=GetLogger()
    if len(sys.argv) != 2:
        log.info('Usage:'+sys.argv[0]+' <Patch_config.json>')
        sys.exit()

    product='iwf'
    #set the product flag
    patchFunctionsPath=os.path.expandvars('$EACC_ROOT/scripts/utils/patch/patch_functions/patch_functions.py')
    removePatchPath=os.path.expandvars('$EACC_ROOT/scripts/utils/patch/patch_functions/remove_patch.py') 
    applyPatchPath=os.path.expandvars('$EACC_ROOT/scripts/utils/patch/patch_functions/apply_patch.py')
    command='sed -i \"s/^PRODUCT=.*/PRODUCT=\''+product+'\'/g\" '+patchFunctionsPath
    op=commands.getoutput(command)
    command='sed -i \"s/^PRODUCT=.*/PRODUCT=\''+product+'\'/g\" '+removePatchPath
    op=commands.getoutput(command)
    command='sed -i \"s/^PRODUCT=.*/PRODUCT=\''+product+'\'/g\" '+applyPatchPath
    op=commands.getoutput(command)

    #Parse and validate the config json file passed
    patchConfig=os.path.abspath(sys.argv[1])
    log.info('Patch configuration file='+patchConfig)
    createPatchObj=PatchFunctions(patchConfig)
    createPatchObj.ValidateSourceFiles()
    createPatchObj.CreatePatchBinary()


if __name__ == '__main__':
	main()
