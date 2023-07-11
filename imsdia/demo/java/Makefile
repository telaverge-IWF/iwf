############################################################################
#                                                                          #
#     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                          #
############################################################################
#
# ID: $Id: Makefile,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:42  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.1  2006/05/23 05:55:02  sumag
# LOG: This is version 1.0 of the tcpip based java diameter client and the test
# LOG: java server.
# LOG: The client and server applications in app directory are operational
# LOG: javafiles directory files - to be completed
# LOG:
# LOG: Revision 1.2  2006/04/10 22:42:41  brianhu
# LOG: Makefile updated to generate API document
# LOG:
# LOG: Revision 1.1  2006/04/03 22:22:55  brianhu
# LOG: Java VAL classes
# LOG:
#
############################################################################
#
# Makefile for IntelliNet Diameter Java API
#

#
# Java Packages
#
PACKAGES=app

#
# Jar
#
JARS=../lib/diaapp.jar

#
# Java Sources
#
SOURCES=$(wildcard $(patsubst %,%/*.java,$(subst .,/,$(PACKAGES))))

CLASSES=$(SOURCES:.java=.class)

#
# Native Method Signatures for C/C++
#
NATIVES=$(patsubst %.java,../native/prot/%.prot,$(patsubst com/intellinet/%,%,$(SOURCES)))

#
# Pattern Rules
#
%.class: %.java
	$(JAVAC) $<

../native/prot/%.prot: com/intellinet/%.class
	$(JAVAH) -o $@ $(subst /,.,$(patsubst %.class,%,$<))

#
# Targets
#
.PHONY: all doc clean report

all: $(JARS) $(NATIVES)

clean:
	rm -rf $(JARS) $(NATIVES) $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES))) ../../../docs/java/val

doc:
	$(MKDIR) -p ../../../docs/java/val
	$(JAVADOC) -d ../../../docs/java/val \
        -windowtitle 'Diameter Java Vendor Adaptation Layer' \
        -doctitle 'IntelliNet Diameter Java Vendor Adaptation Layer Specification' \
        -header '<b>Diameter Java Vendor Adaptation Layer</b>' \
        $(PACKAGES)

report:
	@echo PATTERN='$(patsubst %,%/*.class,$(subst .,/,$(PACKAGES)))'
	@echo NATIVES='$(wildcard $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES))))'
	@echo CLASSES='$(subst \$,\$\$,$(wildcard $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES)))))'

$(JARS): $(CLASSES)
	$(JAR) cf $(JARS) $(SOURCES:.java=*.class)

JAVAC=javac
JAVAH=javah -force
JAR=jar
JAVADOC=javadoc

#
# Dependency
#
#$(NATIVES): $(CLASSES)
