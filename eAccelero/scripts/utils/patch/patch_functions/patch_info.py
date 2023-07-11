#!/usr/bin/python
#*******************************-*-PYTHON-*-*********************************
 #                                                                          *
 #          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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
DRE_BASE='/opt/diametriq/'+PRODUCT+'/'
PATCH_BASE=DRE_BASE+'patches/'

PATCH_FUNCTION='/opt/diametriq/'+PRODUCT+'/scripts/patch/patch_functions/'
ret = os.path.exists(PATCH_FUNCTION)
if ret == True:
    sys.path.append(PATCH_FUNCTION)
    from patch_functions import *


def PatchInfo():
    Heading('PATCH INFO')
    rmPatchObj = PatchFunctions()
    ret=rmPatchObj.patch_information()
    if ret == -1:
        exit(0)

if __name__ == '__main__':
    ret=len(sys.argv)
    if ret != 1:
        print "Usage: "+sys.argv[0]
    else:
        ret = os.path.exists(PATCH_BASE)
        if ret == False:
            print "No patch applied for this build.\n"
            exit(0)
        else:
            PatchInfo()
