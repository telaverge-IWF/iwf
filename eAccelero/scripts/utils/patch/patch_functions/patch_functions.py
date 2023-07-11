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
import shutil
import stat
import commands

PRODUCT='iwf'

#for apply patch script
sys.path.append('.')
sys.path.append('../logger/')
sys.path.append('../json_parser/')

#for remove patch script
sys.path.append('.')
sys.path.append('/opt/diametriq/'+PRODUCT+'/scripts/patch/logger/')
sys.path.append('/opt/diametriq/'+PRODUCT+'/scripts/patch/json_parser/')


from logger import *
from JsonParser_class import *

DRE_BASE='/opt/diametriq/'+PRODUCT+'/'
PATCH_BASE=DRE_BASE+'patches/'
STATIC_PATCH_BASE=PATCH_BASE+'static/'
PLUGIN_PATCH_BASE=PATCH_BASE+'plugin/'
DICTIONARY_PATCH_BASE=PATCH_BASE+'dictionary/'
GENERIC_PATCH_BASE=STATIC_PATCH_BASE
PATCH_SCRIPTS_BASE=DRE_BASE+'scripts/patch/'
REMOVE_PATCH_SCRIPT=DRE_BASE+'bin/remove_patch.py'
ORIG='Orig'
BACKUP_DIR_NUM='00'
FIRST_PATCH_DIR='01'

PATCH_BINARY_BACKUP_BASE='/opt/diametriq/'+PRODUCT+'/.syscfg/patch_info/'

#this class contains all the functions to create,apply and remove/rollback patches
class PatchFunctions:

	def __init__(self,patchConf,loggerConf):
		self.log=GetLogger("PatchFunctions")
		self.PatchConf=patchConf
		self.log.debug("----------")
		print "---"

	def __init__(self):
		self.log=GetLogger("PatchFunctions")
		self.log.debug("----------")
		print "---"
	def __init__(self,patchConf=None):

		self.log=GetLogger("PatchFunctions")
		#relative paths which can change based on whether we are creating a patch or applying it
		self.payloadRoot=os.path.expandvars('$EACC_ROOT/scripts/utils/patch/')

		if PRODUCT == 'dre':
		    self.patchDir=os.path.expandvars('$DRE_ROOT/package/patches/')+'patch/'
		elif PRODUCT == 'iwf':
		    self.patchDir=os.path.expandvars('$IWF_ROOT/package/patches/')+'patch/'
		self.payloadDirs=self.patchDir+PRODUCT
		self.scripts=self.patchDir+'scripts'

	    	self.temp=self.payloadRoot+'temp'
		#to store the information of state of patch files which will be used for rollback/uninstall purposes
		self.patchRollbackInfo={}
		#self.patchRollbackInfo.add_section('PatchFiles')
		if patchConf is None:
			self.patchConf=patchConf
		else:
			if not os.path.isfile(patchConf):
				self.log.error("Invalid File:"+patchConf)
				sys.exit()
			#parse and validate the passed patch json configuration file
			self.m_JsonObj=JsonParser(patchConf)
			self.patchConf=patchConf

	def ParseJson(self,patchConf):
		self.m_JsonObj=JsonParser(patchConf)
		self.patchConf=patchConf

	def ValidatePrePostScripts(self):
		if not os.path.isfile(os.path.expandvars(self.m_JsonObj.GetPreScript())):
			self.log.error('Invalid pre-patch-script!')
			sys.exit()
		if not os.path.isfile(os.path.expandvars(self.m_JsonObj.GetPostScript())):
			self.log.error('Invalid post-patch-script!')
			sys.exit()

	#to be called only during creating package in dev environment
	def ValidateSourceFiles(self):
		if self.m_JsonObj.ValidateSourceFiles():
			self.log.info('Validating Source Files...')
		else:
			self.log.error('Invalid source files in passed configuration!')
			sys.exit()

	#to be called only during applying/removing patch (target machine)
	def ValidateTargetFiles(self):
		if self.m_JsonObj.ValidateTargetFiles():
			self.log.info('Validating Target Files...')
		else:
			self.log.error('Invalid Target files in passed configuration!')
			sys.exit()

	#find and return the path of file else return None
	def Find(self,base,filename):
		for r,d,f in os.walk(base):
			for files in f:
				if files == filename:
					return os.path.join(r,files)

		return None


	#function to execute shell commands and return output
	def Cmd(self,command):
		op=commands.getoutput(command)
		self.log.debug(op)
		return op

	#function to generate directory hierarchy list from dre Makefile
	def GenerateDirectoryList(self):
		#get the start line of directories in dre Makefile
		expandVar=""
		if PRODUCT == 'dre':
		    self.log.debug(os.path.expandvars('$DRE_ROOT/Makefile'))
		    expandVar=os.path.expandvars('$DRE_ROOT/Makefile')
		elif PRODUCT == 'iwf':
		    self.log.debug(os.path.expandvars('$IWF_ROOT/Makefile'))
		    expandVar=os.path.expandvars('$IWF_ROOT/Makefile')

		command='cat '+expandVar+'|grep -n \"install:.*all\"|cut -d\':\' -f1'
		self.log.debug("Command="+command)
		startLine=self.Cmd(command);
		self.log.debug("StartLine="+startLine)
		#get the end line of directories in dre Makefile
		command='cat '+expandVar+'|wc -l'
		endLine=self.Cmd(command)
		tailNum=(int(endLine))-(int(startLine))
		self.log.debug('tailNum=%d',tailNum)

		#get the list
		#prepare a command to get the list
		command='cat '+expandVar+'|tail -'+str(tailNum)+'|grep \"mkdir\"|cut -d\'/\' -f4-'
	        list=self.Cmd(command)
		self.log.debug('Directory List\n'+list)

		#create a file containing the list of directories
		#the same list can be reused while creating directory hierarchy
		f=open('directory_list.txt','w')
		f.write(list)

	#function to remove directories,files recursively
	def RemoveDirs(self,basePath):
		for root, self.payloadDirs, files in os.walk('.', topdown=False):
    				for name in files:
        				os.remove(os.path.join(root, name))
    				for name in self.payloadDirs:
        				os.rmdir(os.path.join(root, name))


	#function to create firectory hierarchy from the diractory_list.txt
	def CreateDirectoryStructure(self,basePath,directoryListFile='./directory_list.txt'):

           	#check if basePath exists
		if os.path.isdir(basePath):
			self.log.debug('directory exists')
		else:
			self.log.debug('base dir '+basePath+' does not exist')
			return False


		#read the directoryListFile
		try:
			f=open(directoryListFile)
			#create directories mentioned in directoryListFile
			rootDir=os.getcwd()
			#change dir to base path
			os.chdir(basePath)
			#remove all files,dirs under it
			#self.RemoveDirs('.')
			#create the directory structure recursively
  			for dir in f:
				if not os.path.isdir(dir.rstrip('\n')):
					self.log.debug('Dir='+dir.rstrip('\n'))
					os.makedirs(dir.rstrip('\n'))

			#change back the directory
			os.chdir(rootDir)
			self.log.debug('Root Dir='+rootDir)
		except IOError:
			self.log.exception('Invalid File:'+directoryListFile)
			return False
		except:
			self.log.exception('Unknown Error')




		return True

	#function to copy files in tag "source" to tmp directory structure
	def CopySourceFiles(self):
		sourceFiles=self.m_JsonObj.GetSourceFiles()
		targetFiles=self.m_JsonObj.GetTargetFiles()
		self.log.debug("SourceFiles="+str(sourceFiles))
		self.log.debug("TargetFiles="+str(targetFiles))

		for i,j in zip(sourceFiles,targetFiles):
			if not os.path.isfile(os.path.expandvars(i)):
				self.log.error('Invalid file: '+i)
				sys.exit()

			self.log.debug('Copying '+os.path.expandvars(i)+'...')
			#if the target file does not belong inside /opt/diametriq/
			if  self.isDreFile(j):
				dst=self.patchDir+'/'+os.path.dirname(j)+'/'
				dst=dst.replace('/opt/diametriq','')
				if not os.path.isdir(dst):
					#create dir
					os.makedirs(dst)

				dst=dst+os.path.basename(j)
				#copy file into newly created dir
				shutil.copyfile(os.path.expandvars(i),dst)
				shutil.copystat(os.path.expandvars(i),dst)
			else:
				#exit if its not a DRE related file
				#dst=self.temp+'/';
				dst=self.patchDir+'/temp/'
				os.makedirs(dst)
				if "/etc/rc.d/init.d/dre" in j:
					self.log.error('os.path.expandvars(i)='+os.path.expandvars(i)+' dst)='+dst)
					self.log.error("Copying dre service script")
					shutil.copyfile(os.path.expandvars(i),dst+'dre')

				elif "/etc/profile.d/dre.sh" in j:
					self.log.error("Copying dre.sh")
					shutil.copyfile(os.path.expandvars(i),dst+'dre.sh')


				else:
					self.log.error('Cannot copy non dre related file '+j)
					if os.path.isdir(self.payloadRoot):
						shutil.rmtree(self.payloadRoot)

					self.log.error('Could not create patch!')
					sys.exit()


	#function to create tar for the payload
	def CreateTarPayload(self,root):
		command='tar czvf ./patch.tar '+root
		print command
		self.Cmd(command)


	#function to create the patch binary
	def CreatePatchBinary(self):
		#generate directory hierarchy list from DRE Makefile
		numToAlpha={1:'a', 2:'b', 3:'c', 4:'d', 5:'e', 6:'f',7:'g', 8:'h', 9:'i', 10:'j',
	        11:'k', 12:'l', 13:'m', 14:'n', 15:'o', 16:'p', 17:'q', 18:'r', 19:'s',
	        20:'t', 21:'u', 22:'v', 23:'w', 24:'x', 25:'y', 26:'z'}

		self.ValidatePrePostScripts()
		self.GenerateDirectoryList()

		if not os.path.isdir(self.payloadDirs):
			os.makedirs(self.payloadDirs)


		if not os.path.isdir(self.patchDir):
			os.makedirs(self.patchDir)
		#creating temp dir
		if not os.path.isdir(self.temp):
			os.makedirs(self.temp)

		#Create the directory structure
		self.CreateDirectoryStructure(self.payloadDirs)
		if os.path.isdir(self.scripts):
			shutil.rmtree(self.scripts)
		shutil.copytree(os.path.expandvars('$EACC_ROOT/scripts/utils/patch'),self.scripts)
		#copy the file containing directory organization information
		shutil.move('./directory_list.txt',self.patchDir)
		#copy the configuration file passed into the payload root
		shutil.copyfile(self.patchConf,self.patchDir+'/patch.json')
		shutil.copystat(self.patchConf,self.patchDir)

		#copy pre-patch and post-patch scripts if any
		shutil.copy(self.m_JsonObj.GetPreScript(),self.scripts)
		shutil.copy(self.m_JsonObj.GetPostScript(),self.scripts)

		#copy pre-uninstall and post-uninstall scripts
		shutil.copy(self.m_JsonObj.GetPreUninstallScript(),self.scripts)
		shutil.copy(self.m_JsonObj.GetPostUninstallScript(),self.scripts)

		os.chdir(os.path.expandvars('$EACC_ROOT/scripts/utils/patch'))
		#copy the source files into it

		self.CopySourceFiles()

		#create tar of files,scripts
		if PRODUCT == 'dre':
		    os.chdir(os.path.expandvars('$DRE_ROOT/package/patches/'))
		elif PRODUCT == 'iwf':
		    os.chdir(os.path.expandvars('$IWF_ROOT/package/patches/'))
		self.CreateTarPayload('./patch')
		#create binary
		os.chdir(os.path.expandvars('$EACC_ROOT/scripts/utils/patch'))
		if PRODUCT == 'dre':
		    self.Cmd('./addpayload.sh '+os.path.expandvars('$DRE_ROOT/package/patches/patch.tar'))
		elif PRODUCT == 'iwf':
		    self.Cmd('./addpayload.sh '+os.path.expandvars('$IWF_ROOT/package/patches/patch.tar'))
		#copy the binary created to the $DRE_ROOT/utils/patching/bin directory
         	patchBinaryName=''
         	#patchBinaryName='patch0'+str(self.m_JsonObj.GetPatchNumber())+'_'+self.m_JsonObj.GetDreRelease()+'.bin'
		if PRODUCT == 'dre':
         	    patchBinaryName=self.m_JsonObj.GetDreRelease()+numToAlpha[self.m_JsonObj.GetPatchNumber()]+'.bin'
		    binTarget=os.path.expandvars('$DRE_ROOT/package/patches/')+patchBinaryName
		elif PRODUCT == 'iwf':
         	    patchBinaryName=self.m_JsonObj.GetDreRelease()+'_'+numToAlpha[self.m_JsonObj.GetPatchNumber()]+'.bin'
		    binTarget=os.path.expandvars('$IWF_ROOT/package/patches/')+patchBinaryName
		print binTarget
		print self.Cmd('pwd')
		os.rename('./install.sh',binTarget)
		os.chmod(binTarget,0777)
		#change back dir
		#os.chdir('../')
		#remove the directories after creating binary with tar payload
		#shutil.rmtree(self.payloadRoot)
		if PRODUCT == 'dre':
		    os.remove(os.path.expandvars('$DRE_ROOT/package/patches/')+'patch.tar')
		    shutil.rmtree(os.path.expandvars('$DRE_ROOT/package/patches/')+'patch')
		    self.log.info('Patch created successfully!')
		    self.log.info('Path: '+os.path.expandvars('$DRE_ROOT/package/patch/bin/'+patchBinaryName))
		elif PRODUCT == 'iwf':
		    os.remove(os.path.expandvars('$IWF_ROOT/package/patches/')+'patch.tar')
		    shutil.rmtree(os.path.expandvars('$IWF_ROOT/package/patches/')+'patch')
		    self.log.info('Patch created successfully!')
		    self.log.info('Path: '+os.path.expandvars('$IWF_ROOT/package/patch/bin/'+patchBinaryName))

      ############### functions used during patching #############
	def GetCurrentInstalledPatchNumber(self):
		if  not os.path.isdir(STATIC_PATCH_BASE):
			return '-1'
		curPatchNum=self.Cmd('ls '+STATIC_PATCH_BASE+'|sort -n|tail -1')
		return curPatchNum.rstrip('\n')

        def ValidatePatch(self):
		self.isStaticPatch=True
                #check if version of DRE installed and DRE version in patch are same
                dreVerInstalled=self.Cmd('rpm -q '+PRODUCT+'|tail -1')
                if  'is not installed' in dreVerInstalled:
                        self.log.error('DRE not found in this system')
                        return False

		if not self.m_JsonObj.GetDreRelease() in dreVerInstalled:
			self.log.error('Invalid Patch!')
			self.log.error('Patch can only be applied on '+self.m_JsonObj.GetDreRelease())
			return False

		if ( (self.m_JsonObj.GetPatchNumber() < 0) or (self.m_JsonObj.GetPatchNumber() > 99)):
			self.log.error('Invalid Patch Number:'+str(self.m_JsonObj.GetPatchNumber()))
			return False

		if self.FormatPatchNum() in self.GetCurrentInstalledPatchNumber():
			self.log.error('Patch number:'+self.FormatPatchNum()+' is already present in the system!')
			return False

		if  os.path.isdir(STATIC_PATCH_BASE):
			if os.path.isdir(STATIC_PATCH_BASE+FIRST_PATCH_DIR):
				if not (self.ConvertPatchNum(self.GetCurrentInstalledPatchNumber())+1) == self.m_JsonObj.GetPatchNumber():
					self.log.error('Invalid patch number:')
					self.log.error('Patch number : '+str(self.ConvertPatchNum(self.GetCurrentInstalledPatchNumber())+1)+' should be applied')
					return False
			else:
				if self.m_JsonObj.GetPatchNumber() != 1:
					self.log.error('Invalid patch number:')
                        		return False
		else:
			if self.m_JsonObj.GetPatchNumber() != 1:
				self.log.error('Invalid patch number:')
				return False

		#Get the patch type
		if self.m_JsonObj.GetPatchType() in ["plugin","dynamic"]:
			self.log.debug('plugin patch!')
			self.isStaticPatch=False
		else:
			self.log.debug('patch')
			self.isStaticPatch=True

		if self.isStaticPatch:
			#validation for static patch
			if not os.path.isdir(STATIC_PATCH_BASE):
				self.log.debug(STATIC_PATCH_BASE+' does not exist')
				return True


			#validate the target files present in the configuration json file passed
			#self.ValidateTargetFiles()

		else:
			################### TODO Validation block for dynamic patch #############
			self.log.debug('--plugin patch not supported yet!--')
			return False

		return True

	#sets the relative paths with respect to a script which is calling this function
	def SetRelativePaths(self,payloadRoot,payloadDirs,scripts):
		self.payloadRoot=payloadRoot
		self.payloadDirs=payloadDirs
		self.scripts=scripts



	def CheckAndCreatePatchDirs(self):
		if not os.path.isdir(STATIC_PATCH_BASE):
			os.makedirs(STATIC_PATCH_BASE)

		if not os.path.isdir(STATIC_PATCH_BASE+BACKUP_DIR_NUM+'/'+PRODUCT):
			os.makedirs(STATIC_PATCH_BASE+BACKUP_DIR_NUM+'/'+PRODUCT)

		if not os.path.isdir(PLUGIN_PATCH_BASE):
			os.makedirs(PLUGIN_PATCH_BASE)

		if not os.path.isdir(PATCH_SCRIPTS_BASE):
			os.makedirs(PATCH_SCRIPTS_BASE)

	def isDreFile(self,i):
		if DRE_BASE in i:
			return True
		else:
			return False

        def CheckAndBackupOriginalFiles(self):
		#if any target file is still present under '/opt/diametriq/dre' folder back it up in the 00 dir
		targetFiles=self.m_JsonObj.GetTargetFiles()
		for i in targetFiles:
			#if file exists and is not a symbolic link
			if os.path.isfile(i) and not os.path.islink(i):
				self.log.debug('Backing up File:'+i+'...')
				if not self.isDreFile(i):
					if "/etc/rc.d/init.d/dre" in i:
						self.log.debug("/etc/rc.d/init.d/dre")
					elif "/etc/profile.d/dre.sh" in i:
						self.log.debug("/etc/profile.d/dre.sh")
					else:
						self.log.error('Cannot patch '+i+' , its not a DRE related file!')
				else:
					dst=i.replace('/opt/diametriq/','')
					shutil.copyfile(i,STATIC_PATCH_BASE+BACKUP_DIR_NUM+'/'+dst)
					shutil.copystat(i,STATIC_PATCH_BASE+BACKUP_DIR_NUM+'/'+dst)
					#delete the original files
					self.log.debug('relinking '+i+'...')
					#self.patchRollbackInfo['patchFiles'][i]=[STATIC_PATCH_BASE+'00/'+dst]
					self.patchRollbackInfo[i]=os.path.realpath(STATIC_PATCH_BASE+BACKUP_DIR_NUM+'/'+dst)
					os.remove(i)
			else:
				if os.path.islink(i):
					self.log.debug('File is a symlink:'+i)
					#is already a softlink
					#save the softlink info for rollback purposes
					link=i
					self.patchRollbackInfo[i]=os.path.realpath(os.readlink(link))
				else:
					if  self.isDreFile(i):
					    #new file added as part of this patch
					    self.log.debug('File is a new file for this patch:'+i)
					    if not os.path.isdir(os.path.dirname(i)):
						self.log.debug('Creating Dir: '+os.path.dirname(i))
					        os.makedirs(os.path.dirname(i))
					    else:
						self.log.debug('Dir '+os.path.basename(i)+' already exists')
					    self.patchRollbackInfo[i]=None
					else:
					    self.log.error('Cannot patch '+i+' , its not a DRE related file!')


	#Prepends single digit numbers with 0
	def FormatPatchNum(self):
		patchNum=self.m_JsonObj.GetPatchNumber()
		if len(str(patchNum))  == 1:
			#prepend 0 to it
			patchNum='0'+str(patchNum)

		return str(patchNum)


	def ConvertPatchNum(self,patchNum):
		if type(patchNum) is str:
			#if it has preceding 0 remove and return int
			if patchNum[0] == '0':
				return int(patchNum[1])

		else:
			if type(patchNum) is int:
				#if it does not have preceding 0 , prepend and
				#return a string
				if len(str(patchNum)) == 1:
					#prepend 0
					patchNum='0'+str(patchNum)
					return str(patchNum)

	#create soft links to the new files,libraries copied
	def CreateSoftLinks(self):
		targetFiles=self.m_JsonObj.GetTargetFiles()
		for i in targetFiles:
			link=i
			patchNum=self.FormatPatchNum()
			if self.isDreFile(i):
				src=i.replace('/opt/diametriq/','')
				src=STATIC_PATCH_BASE+patchNum+'/'+src
				self.log.debug(link+'--->'+src)
				if os.path.islink(link):
					os.unlink(link)
				self.log.info('Patching '+link+' ...')
				os.symlink(os.path.realpath(src),link)
			else:
				#special case for patch 02 dre-3.0.0-06
				if "/etc/rc.d/init.d/dre" in i:
					self.log.debug('/etc/rc.d/init.d/dre')
					self.log.info('Patching /etc/rc.d/init.d/dre')
				 	shutil.copyfile(self.payloadRoot+'/temp/dre','/etc/rc.d/init.d/dre')
				 	shutil.copystat(self.payloadRoot+'/temp/dre','/etc/rc.d/init.d/dre')
					self.Cmd('chmod +x /etc/rc.d/init.d/dre')
				elif "/etc/profile.d/dre.sh" in i:
					self.log.debug('/etc/profile.d/dre.sh')
				else:
					self.log.error('Cannot patch Non Dre File:'+i)

		patchRollbackInfoFile=STATIC_PATCH_BASE+patchNum+'/rollback_info.json'
		json.dump(self.patchRollbackInfo,open(patchRollbackInfoFile,'w'))

	#Pre patch script to be executed
	def PrePatchScript(self):
		self.Cmd(self.scripts+'/pre_patch.sh')
	#Post patch script to be executed
	def PostPatchScript(self):
		self.log.debug('--')
		self.Cmd(self.scripts+'/post_patch.sh')



	def Patch(self):
		patchDirNum=STATIC_PATCH_BASE+FIRST_PATCH_DIR
		#validate the patch
		if not self.ValidatePatch():
			if os.path.isdir(self.payloadRoot):
			    shutil.rmtree(self.payloadRoot)
			return False

		#execute the PrePatch script
		self.PrePatchScript()

		self.CheckAndCreatePatchDirs()
		#check if all the necessary folders are present, if not create them
		#if its first patch
			#create 00 folder under STATIC_PATCH_BASE and move all the files
			#mentioned in target tag of json to the 00 folder created.
		op=self.Cmd('ls '+STATIC_PATCH_BASE+'|grep '+FIRST_PATCH_DIR)
		#if op does not cantain 01
		if not op:
			#if block for first patch to be applied
			self.log.debug('This is the first patch to be applied')

			self.log.debug('Payload Root='+self.payloadRoot)
			baseDir=STATIC_PATCH_BASE+'/'+BACKUP_DIR_NUM+'/'+PRODUCT
			self.CreateDirectoryStructure(baseDir,self.payloadRoot+'/directory_list.txt')
			os.makedirs(patchDirNum)
			#copy the json configuration file of this particular patch
			shutil.copyfile(self.payloadRoot+'/patch.json',patchDirNum+'/patch.json')
			shutil.copystat(self.payloadRoot+'/patch.json',patchDirNum+'/patch.json')
			#also copy the directory_list.txt
			shutil.copyfile(self.payloadRoot+'/directory_list.txt',patchDirNum+'/directory_list.txt')
			shutil.copystat(self.payloadRoot+'/directory_list.txt',patchDirNum+'/directory_list.txt')


			self.CheckAndBackupOriginalFiles()
			dst=patchDirNum+'/'+PRODUCT

		else:
			self.log.debug('Not the first patch')
			#create soft links to the newly copied  patch files

			newPatchNumber=self.FormatPatchNum()
			patchDirNum=STATIC_PATCH_BASE+newPatchNumber
			os.makedirs(patchDirNum)
			#copy the json configuration file of this particular patch
			shutil.copyfile(self.payloadRoot+'/patch.json',patchDirNum+'/patch.json')
			shutil.copystat(self.payloadRoot+'/patch.json',patchDirNum+'/patch.json')
			#also copy the directory_list.txt
			shutil.copyfile(self.payloadRoot+'/directory_list.txt',patchDirNum+'/directory_list.txt')
			shutil.copystat(self.payloadRoot+'/directory_list.txt',patchDirNum+'/directory_list.txt')
			self.CheckAndBackupOriginalFiles()
			dst=patchDirNum+'/'+PRODUCT

			#special case for patch 2 dre-3.0.0-06
			#self.temp=self.payloadRoot+'/temp'
			#shutil.copytree(self.temp,patchDirNum+'/temp')

		shutil.copytree(self.payloadDirs,dst)

		#copy the pre uninstall and post uninstall scripts to patchDirNum
		preUninstallScript=self.m_JsonObj.GetPreUninstallScript()
		postUninstallScript=self.m_JsonObj.GetPostUninstallScript()
		if preUninstallScript and postUninstallScript != None:
			#get the path  of the pre and post uninstall scripts
			preUninstallScript=self.Find(self.payloadRoot,os.path.basename(preUninstallScript))
			postUninstallScript=self.Find(self.payloadRoot,os.path.basename(postUninstallScript))
			if preUninstallScript and postUninstallScript != None:
				#copy the pre and post uninstall scripts to patchDirNum
				shutil.copy(preUninstallScript,patchDirNum)
				shutil.copy(postUninstallScript,patchDirNum)

		#copy all the patching related scripts to /opt/diametriq/dre/scripts/patch

		patchScriptsPath='/opt/diametriq/'+PRODUCT+'/scripts/patch'
		shutil.rmtree(patchScriptsPath)
		shutil.copytree(self.scripts,patchScriptsPath)
		if os.path.isfile(REMOVE_PATCH_SCRIPT):
			os.remove(REMOVE_PATCH_SCRIPT)
		shutil.copyfile('./remove_patch.py',REMOVE_PATCH_SCRIPT)
		shutil.copystat('./remove_patch.py',REMOVE_PATCH_SCRIPT)
		self.CreateSoftLinks()

		#execute the PostPatch script
		self.PostPatchScript()
		self.log.info('Successfully applied patch '+self.FormatPatchNum()+' for '+str(self.m_JsonObj.GetDreRelease()))
		if os.path.isdir(self.payloadRoot):
			shutil.rmtree(self.payloadRoot)
	####################Functions used by remove_patch.py script ##########################



	#returns the Json configuration file path , if patchNum is is passed it will return json
	#config file which belongs to the patchNum passed, else it will return the json file of latest
	# patch num installed in the system
	def GetJsonFilePath(self,patchNum=None):
		if patchNum is None:
			#return the json path for latest patch applied
			jsonPath=STATIC_PATCH_BASE+self.GetCurrentInstalledPatchNumber()+'/patch.json'
			return jsonPath
		else:
			#return the json path for the patchNum passed
			jsonPath=STATIC_PATCH_BASE+patchNum+'/patch.json'
			return jsonPath


	def PreUninstall(self):
		uninstallScript=self.m_JsonObj.GetPreUninstallScript()
		if uninstallScript == None:
			return False

		uninstallScript=os.path.basename(uninstallScript)
		patchNum=self.FormatPatchNum()
		basePath=STATIC_PATCH_BASE+patchNum+'/'
		uninstallScriptPath=self.Find(basePath,uninstallScript)
		if uninstallScriptPath == None:
			self.log.error(uninstallScript+' not found!')
			return False

		uninstallScriptPath=os.path.abspath(uninstallScriptPath)
		#execute the script

		self.Cmd(uninstallScriptPath)

	def PostUninstall(self):
		uninstallScript=self.m_JsonObj.GetPostUninstallScript()
		if uninstallScript == None:
			return False

		uninstallScript=os.path.basename(uninstallScript)
		patchNum=self.FormatPatchNum()
		basePath=STATIC_PATCH_BASE+patchNum+'/'
		uninstallScriptPath=self.Find(basePath,uninstallScript)
		if uninstallScriptPath == None:
			self.log.error(uninstallScript+' not found!')
			return False

		uninstallScriptPath=os.path.abspath(uninstallScriptPath)
		#execute the script

		self.Cmd(uninstallScriptPath)


	def RemovePatch(self):
		patchNum=self.GetCurrentInstalledPatchNumber()

		if patchNum == "00":
			os.remove(REMOVE_PATCH_SCRIPT)
			self.log.error('No Patch available to remove!')
			return
		#execute the pre uninstall function
		self.PreUninstall()
		#get the prev patch info/state
 		rollbackInfoFile=STATIC_PATCH_BASE+patchNum+'/rollback_info.json'
		rollbackInfoParser = json.load(open(rollbackInfoFile))
		#destroy and recreate softlinks as per the prev patch info
		for link,src in rollbackInfoParser.iteritems():
			self.log.debug('link='+link)
			self.log.debug('src ='+str(src))
			os.unlink(link)
			#if src is None then the file was added newly as part of current patch
			# so while removing we need to delete that file and link associated with it
			if src != None:
				os.symlink(src,link)

		#execute the post uninstall function
		self.PostUninstall()

		#remove the current patch dir
		shutil.rmtree(STATIC_PATCH_BASE+patchNum)
		self.log.info('Successfully removed patch '+str(patchNum)+' of '+str(self.m_JsonObj.GetDreRelease()))

	# Print List of applied patches
    	def list_available_patches(self):
            ret = os.path.exists(PATCH_BASE)
            if ret == False:
               	print "No patch applied for this build.\n"
		self.log.debug('No Patch present in the system to remove!')
            	return -1
            else:
               	patchList = os.listdir(PATCH_BASE)
		revisedPatchList = []

            	count = 1
            	for patch in patchList:
		    items=os.listdir(PATCH_BASE+"/"+patch)
		    if len(items) > 1:
               		print str(count)+". "+patch
		    	print "\tPatch "+max(items)
			revisedPatchList.append(patch)
               		count=count+1

		if count < 2:
		    print "No Patch present in the system to remove!\n"
		    self.log.debug('No Patch present in the system to remove!')
		    exit(0)

		print "\n0. Exit"
            	print "\n"

		choice=input("Enter your choice: ")
		if choice == 0:
		    exit(0)

		if choice in range(1,count):
               	    return revisedPatchList[choice-1]
            	else:
               	    print "\nInvalid choice!\n"
               	    return -1

	def patch_information(self):
	    ret = os.path.exists(PATCH_BASE)
	    patchFlag = 0
            if ret == False:
               	print "No patch applied for this build.\n"
               	self.log.debug('No patch applied for this build.')
               	return -1
	    else:
               	patchList = os.listdir(PATCH_BASE)

		count=1
		if len(patchList) != 0:
            	    for patch in patchList:
		    	items=os.listdir(PATCH_BASE+"/"+patch)

			for i in items:
			    if i== "00":
				items.remove('00')
			if len(items) != 0:
			    patchFlag = 1
               		    print str(count)+". "+patch
		    	    for index in items:
		    	    	print "\t"+str(index)
		    	count=count+1
		    print "\n"

		    if patchFlag == 0:
			print "No patch applied for this build.\n"
               		self.log.debug('No patch applied for this build.')
		    return 0
		else:
		    return -1
	# Generate/update Json which will tell about patches applied on build
	def updatePatchInformationJson(self):
	    self.log.debug(' >>> updatePatchInformationJson >>>')
    	    if os.path.exists(PATCH_BASE):
	        static=[]
	        plugin=[]
	        dictionary=[]
	        patchList = os.listdir(PATCH_BASE)
	        if len(patchList) != 0:
	            for patch in patchList:
	    	        items=os.listdir(PATCH_BASE+"/"+patch)
 	    	        patch_list=[]
	    	        for i in items:
                            if i != "00" :
		    	        patch_entry={
					    'patch' : i
			  		}
		    	        patch_list.append(patch_entry)
		        if patch == "static":
		    	    static = patch_list
		        elif patch == "plugin":
		    	    plugin=patch_list
		        elif patch == "dictionary":
		    	    dictionary=patch_list
	            patch_detail=[{
				"static" : static,
				"plugin" : plugin,
				"dictionary" : dictionary
			     }]
	            dump=json.dumps({'patch_info': patch_detail}, sort_keys=True, indent=4)
	            self.log.debug(' JsonDump : %s'%dump)
		    if os.path.exists(PATCH_BINARY_BACKUP_BASE) == False:
			os.mkdir(PATCH_BINARY_BACKUP_BASE)
	            fd=open(PATCH_BINARY_BACKUP_BASE+'/patch_info.json','w')
	            fd.write(dump)
	            fd.close()
	            self.log.debug(' <<< updatePatchInformationJson <<<<')


#test code to test the patchFunctions class functions
if __name__ == '__main__':
	print "main"
	pf= PatchFunctions()
	pf.Cmd("ls")
	pf.GenerateDirectoryList()
	if pf.CreateDirectoryStructure('./test'):
		print 'success'
	else:
		print 'failure'
	print 'test'
