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
import json
sys.path.append('.')
sys.path.append('../logger/')
from logger import *


class JsonParser:
	def __init__(self,filename):
		self.log=GetLogger("JsonParser")
		self.f=open(filename , 'r' ).read() 
		self.config=json.loads(self.f)
		self.patch_details=self.config['patch-details'][0]
                self.patch_number=self.patch_details['patch-number']
                self.patch_release=self.patch_details['dre-release']
		self.patch_type=self.patch_details['patch-type']
		self.files=self.patch_details['files']
		#if pre-patch script is present
		if 'pre-patch-script' in self.patch_details.keys():
			self.pre_patch_script=os.path.expandvars(self.patch_details['pre-patch-script'])
		else:
			self.pre_patch_script=None

		if 'post-patch-script' in self.patch_details.keys():
			self.post_patch_script=os.path.expandvars(self.patch_details['post-patch-script'])
		else:
			self.post_patch_script=None	


		if 'pre-uninstall-script' in self.patch_details.keys():
			self.pre_uninstall_script=os.path.expandvars(self.patch_details['pre-uninstall-script'])
		else:
			self.pre_uninstall_script=None

		if 'post-uninstall-script' in self.patch_details.keys():
			self.post_uninstall_script=os.path.expandvars(self.patch_details['post-uninstall-script'])
		else:
			self.post_uninstall_script=None	


		self.sourceFiles=[]
		self.targetFiles=[]
		for i in range(len(self.files)):
			self.sourceFiles.append(self.files[i]['source'])
			self.targetFiles.append(self.files[i]['target'])
				
	def PrintFiles(self):
		for i in range(len(self.files)):
			self.log.debug( "source="+self.files[i]['source'])
			self.log.debug("target="+self.files[i]['target'])

	def PrintPatchDetails(self):
		print self.patch_details

	#function to validate source files from the json passed
	def ValidateSourceFiles(self):
		ret=True
		for i in range(len(self.files)):
			expand_path=os.path.expandvars(self.files[i]['source'])
			if os.path.isfile(expand_path) == True:
				self.log.debug("File exists")
			else:
				self.log.error("File "+self.files[i]['source']+" does not exist!")	
				ret=False
		return ret

	#function to validate target files from the json passed	
	def ValidateTargetFiles(self):
		ret=True
		for i in range(len(self.files)):
			expand_path=os.path.expandvars(self.files[i]['target'])
			if os.path.isfile(expand_path) == True:
				self.log.debug("File exists")
			else:
				self.log.error("File "+self.files[i]['target']+" does not exist!")	
				ret=False
		return ret

	def GetPatchNumber(self):
		return self.patch_number

	def GetDreRelease(self):
		return self.patch_release	
	
	def GetPatchType(self):
		return self.patch_type

	def GetSourceFiles(self):
		return self.sourceFiles
	
	def GetTargetFiles(self):
		return self.targetFiles	
		
	def GetPreScript(self):
		return self.pre_patch_script

	def GetPostScript(self):
		return self.post_patch_script

	def GetPreUninstallScript(self):	
		return self.pre_uninstall_script

	def GetPostUninstallScript(self):
		return self.post_uninstall_script


#test code to test json class
if __name__ == '__main__':
	log=GetLogger("JsonParser")
	log.debug( "execute main")
        patchJson=JsonParser('./patch.json')
#	patchJson.PrintPatchDetails() 
	patchJson.PrintFiles()
        if patchJson.ValidateSourceFiles():
		log.debug("Success")
	else:
		log.error("Invalid files")
