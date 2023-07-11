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
PRODUCT='iwf'
sys.path.append('.')
sys.path.append('../logger/')
from patch_functions import *
from logger import *


def ApplyPatch():
	#relative paths for this scripts
	Heading('PATCHING')
	payloadRoot='../../../patch'
	payloadDirs=payloadRoot+'/'+PRODUCT
	scripts=payloadRoot+'/scripts'
	log=GetLogger()
	log.info('Preparing to patch...')
	log.info('Parsing patch.json file...')
	patchObj=PatchFunctions('../../patch.json')
	#set relative paths for this script
	patchObj.SetRelativePaths(payloadRoot,payloadDirs,scripts)


	#if its not a valid patch exit
#	if not patchObj.ValidatePatch():
#		return False

	#apply the patch
	ret=patchObj.Patch()
	if ret == False:
	    sys.exit(1)
	else:
	    # Update Json file which contains information about patches applied on DRE
	    patchObj.updatePatchInformationJson()
	    # Afetr patch removal Run backup
	    #os.chdir('/opt/diametriq/dre/scripts')
        #    print('Taking backup..')
	    #commands.getoutput('./backup.py --force')
	    sys.exit(0)


if __name__ == '__main__':
	ApplyPatch()
