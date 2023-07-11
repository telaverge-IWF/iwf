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
import os
import sys
PRODUCT='iwf'
sys.path.append('/opt/diametriq/'+PRODUCT+'/scripts/patch/patch_functions/')

from patch_functions import *
def RemovePatch():
	Heading('PATCH UNINSTALL')
	rmPatchObj = PatchFunctions()
	jsonPath=rmPatchObj.GetJsonFilePath()
	if "/00/" in jsonPath:
		print "No Patch present in the system to remove!"
		sys.exit()		

	rmPatchObj.ParseJson(rmPatchObj.GetJsonFilePath())
	rmPatchObj.RemovePatch()
	# Update Json file which contains information about patches applied on DRE
	rmPatchObj.updatePatchInformationJson()
	# Afetr patch removal Run backup
	#os.chdir('/opt/diametriq/dre/scripts')
	#print('Taking backup..')
	#commands.getoutput('./backup.py --force')



if __name__ == '__main__':
	RemovePatch()
