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
import logging
import logging.config
import os
import sys

sys.path.append('.')
#get the current directory of the config file
logConfPath=os.path.dirname(os.path.realpath(__file__))

def GetLogger(filename='patch',logConfigFile=(logConfPath+'/logger.conf')):
	#logging.config.fileConfig(logConfigFile)
	logging.config.fileConfig(logConfigFile, defaults=None, disable_existing_loggers=False)
	logger=logging.getLogger(filename)
#	logger.setLevel(logging.DEBUG)
	return logging.getLogger(filename)

def Heading(headingString):
	log=GetLogger()
	log.info('\n\n\n\n----------------------------------------------------------------------------')
	log.info('                      '+headingString+'                                     ')
	log.info('----------------------------------------------------------------------------\n')


#test code to test logger 
if __name__ == '__main__':
    log=GetLogger("sample")
    log.debug("test")
