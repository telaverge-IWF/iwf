############################################################################
#                                                                          #
#     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
#  ID: $Id: Makefile,v 9.2 2007/01/10 11:14:58 yranade Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 9.2  2007/01/10 11:14:58  yranade
# LOG: Merge changes from 6.5.3 and Lucent branches
# LOG:
# LOG: Revision 9.1  2005/03/23 12:51:20  cvsadmin
# LOG: Begin PR6.5
# LOG:
# LOG: Revision 8.2  2005/03/21 13:49:22  cvsadmin
# LOG: PR6.4.2 Source Propagated to Current
# LOG:
# LOG: Revision 7.1  2002/08/26 22:08:42  mmiers
# LOG: Begin PR6.2
# LOG:
# LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
# LOG: Begin PR7.
# LOG:
# LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
# LOG: Start PR6.
# LOG:
# LOG: Revision 1.2  2001/07/18 22:22:59  hdivoux
# LOG: Build on Solaris okay.
# LOG:
# LOG: Revision 1.1  2001/07/18 21:47:35  hdivoux
# LOG: Creation.
# LOG:
#
############################################################################

include $(ITS_ROOT)/config.vars

OBJS_GR1 = config_lexer.o   \
           config_parser.o  \
           configuration.o  \
           skiplist.o       \
           acm.o

OBJS_GR2 = arch.o           \
           alarm.o          \
           events.o         \
           memory.o         \
           membership.o     \
           data_link.o      \
           network.o        \
           status.o         \
           log.o            \
           flow_control.o   \
           message.o        \
           acp-permit.o     \
           auth-null.o      \
           auth-ip.o

OBJS_GR3 = arch.o           \
           alarm.o          \
           events.o         \
           memory.o         \
           sp.o

OBJS_GR4 = spread.o         \
           protocol.o       \
           session.o        \
		   its_nicmonitor.o \
           groups.o

OBJS_GR5 = monitor.o        \
           alarm.o          \
           events.o         \
           memory.o         \
           data_link.o

CFLAGS := $(CFLAGS) -I.

all: gcs_daemon$(DBGSUFFIX)         \
     gcs_monitor$(DBGSUFFIX)        \
     gcs_flooder$(DBGSUFFIX)        \
     gcs_simple_user$(DBGSUFFIX)    \
     gcs_user$(DBGSUFFIX) 

gcs_daemon$(DBGSUFFIX): $(OBJS_GR1) $(OBJS_GR2) $(OBJS_GR4)
	$(CC) $(LDFLAGS) -o ../bin/gcs_daemon$(DBGSUFFIX)		\
                    $(OBJS_GR1)                             \
                    $(OBJS_GR2)                             \
                    $(OBJS_GR4)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    
gcs_monitor$(DBGSUFFIX): $(OBJS_GR1) $(OBJS_GR5)
	$(CC) $(LDFLAGS) -o ../bin/gcs_monitor$(DBGSUFFIX)		\
                    $(OBJS_GR1)                             \
                    $(OBJS_GR5)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    
gcs_flooder$(DBGSUFFIX): $(OBJS_GR3) flooder.o
	$(CC) $(LDFLAGS) -o ../bin/gcs_flooder$(DBGSUFFIX)		\
                    $(OBJS_GR3)                             \
                    flooder.o                               \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    
gcs_simple_user$(DBGSUFFIX): $(OBJS_GR3) simple_user.o
	$(CC) $(LDFLAGS) -o ../bin/gcs_simple_user$(DBGSUFFIX)		\
                    $(OBJS_GR3)                             \
                    simple_user.o                           \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    
gcs_user$(DBGSUFFIX): $(OBJS_GR3) user.o
	$(CC) $(LDFLAGS) -o ../bin/gcs_user$(DBGSUFFIX)			\
                    $(OBJS_GR3)                             \
                    user.o                                  \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)             

config_parser.c config_parser.h: config_parse.y    \
                                 configuration.h    \
                                 alarm.h            \
                                 skiplist.h         \
                                 memory.h           \
                                 objects.h          \
                                 conf_body.h
	$(YACC) -d -o config_parser.c config_parse.y

config_lexer.c: config_gram.l config_parser.h conf_body.h arch.h
	$(LEX) -oconfig_lexer.c config_gram.l 

clean:
	$(RM)   ../bin/gcs_daemon$(DBGSUFFIX)    \
            ../bin/gcs_monitor$(DBGSUFFIX)       \
            ../bin/gcs_flooder$(DBGSUFFIX)       \
            ../bin/gcs_simple_user$(DBGSUFFIX)   \
            ../bin/gcs_user$(DBGSUFFIX)          \
            $(OBJS_GR1)                          \
            $(OBJS_GR2)                          \
            $(OBJS_GR3)                          \
            $(OBJS_GR4)                          \
            $(OBJS_GR5)                          \
            flooder.o                            \
            simple_user.o                        \
            user.o                               \
            config_parser.c                      \
            config_parser.h                      \
            config_lexer.c                       \
            .depend

include $(ITS_ROOT)/config.rules

