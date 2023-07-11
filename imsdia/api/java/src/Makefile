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
# ID: $Id: Makefile,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.7  2008/03/27 11:38:02  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:41  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.10  2006/07/27 13:27:57  sumag
# LOG: Modified to add diameter.rfro.ietf diameter.rfro.ims
# LOG:
# LOG: Revision 1.9  2006/06/13 16:31:29  brianhu
# LOG: "realclean" target removes generated test sources also
# LOG:
# LOG: Revision 1.8  2006/06/07 22:41:52  brianhu
# LOG: Fixed "realclean" target.
# LOG:
# LOG: Revision 1.7  2006/06/06 01:26:43  brianhu
# LOG: Added "realclean" target
# LOG:
# LOG: Revision 1.6  2006/06/06 01:23:25  brianhu
# LOG: Package specification for JavaDoc
# LOG:
# LOG: Revision 1.5  2006/06/06 01:18:17  brianhu
# LOG: Fixing classpath
# LOG:
# LOG: Revision 1.4  2006/05/23 06:08:53  sumag
# LOG: Additional paths included for java compilation
# LOG:
# LOG: Revision 1.3  2006/04/14 20:13:03  brianhu
# LOG: Skip all package-info.java
# LOG:
# LOG: Revision 1.2  2006/04/10 22:43:47  brianhu
# LOG: Makefile updated to generate API documents
# LOG:
# LOG: Revision 1.1  2006/04/04 14:20:08  brianhu
# LOG: Makefile to build generated Java API classes
# LOG:
#
############################################################################
#
# Makefile for IntelliNet Diameter Java API
#

#
# Java Packages
#
PACKAGES=diameter.base diameter.cxdx diameter.gqgqprime diameter.rfro diameter.sh diameter.rfro.ietf diameter.rfro.ims

#
# Jar
#
JARS=../lib/diaapi.jar

#
# Java Sources
#
ALLJAVA=$(wildcard $(patsubst %,%/*.java,$(subst .,/,$(PACKAGES))))

ALLTEST=$(wildcard $(patsubst %,../test/%/*.java,$(subst .,/,$(PACKAGES))))

SOURCES=$(filter-out %/package-info.java,$(ALLJAVA))

CLASSES=$(SOURCES:.java=.class)

#
# Depended
#
CLASSPATH=.:../../../val/java/lib/diameter.jar

#
# Pattern Rules
#
%.class: %.java
	$(JAVAC) $<

#
# Targets
#
.PHONY: all clean doc report

all: $(JARS)

clean:
	rm -rf $(JARS) $(NATIVES) $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES))) ../../../docs/java/api

realclean: clean
	rm -rf $(ALLJAVA) $(ALLTEST)


doc:
	$(MKDIR) -p ../../../docs/java/api
	$(JAVADOC) -d ../../../docs/java/api \
	-classpath $(CLASSPATH) \
        -windowtitle 'Diameter Java API' \
        -doctitle 'IntelliNet Diameter Java API Specification' \
        -header '<b>Diameter Java API</b>' \
        $(PACKAGES)

report:
	@echo PATTERN='$(patsubst %,%/*.class,$(subst .,/,$(PACKAGES)))'
	@echo CLASSES='$(subst \$,\$\$,$(wildcard $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES)))))'

$(JARS): $(CLASSES)
	$(JAR) cf $(JARS) $(SOURCES:.java=*.class)

JAVAC=javac -classpath $(CLASSPATH)
JAR=jar
JAVADOC=javadoc
