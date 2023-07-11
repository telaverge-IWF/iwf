include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) -DTRANSPORT_SS7

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL)\
	-I$(ITS_ROOT)/common/include	\
        -I$(VENDOR_ROOT)/nms/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include	\
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
	-I$(ITS_ROOT)/tools/include	\


CXXFLAGS:=$(CXXFLAGS) \
	-I$(ITS_ROOT)/common/include	\
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/ISUP/include/itu  \
	-I$(ITS_ROOT)/TCAP/include	\
	-I$(ITS_ROOT)/TCAP/include/itu	\
	-I$(ITS_ROOT)/SCCP/include	\
	-I$(ITS_ROOT)/tools/include	\
	-I$(ITS_ROOT)/MTP2/include	\
	-I$(ITS_ROOT)/MTP3/include	\
	-I$(VENDOR_ROOT)/nms/include

OBJS:= sendISUPMsg.o printISUPMsg.o readISUPMsg.o test.o

LIBS:=-L$(ITS_ROOT)/common/lib	\
        -L$(ITS_ROOT)/tools/lib \
	-L$(ITS_ROOT)/MTP3/lib	\
        -L$(ITS_ROOT)/ISUP/lib  \
        -L$(VENDOR_ROOT)/nms_v3_5/lib \
        -L$(VENDOR_ROOT)/nms/lib \
        -L/opt/nmstx/lib        \
	-L/opt/nms/lib          \
        -lVFrame$(DBGSUFFIX)    \
	-lSUPPORT$(DBGSUFFIX)	\
	-lCORE$(DBGSUFFIX)	\
        -lUNITTEST$(DBGSUFFIX)  \
	-l$(PROTOCOL)-MTP3$(DBGSUFFIX) \
        -l$(PROTOCOL)-ISUP$(DBGSUFFIX) \
	-l$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX)	\
	-lSUPPORT$(DBGSUFFIX)	\
	-lCORE$(DBGSUFFIX)	\
        -lUNITTEST$(DBGSUFFIX)  \
	-l$(PROTOCOL)-MTP3$(DBGSUFFIX)	\
	-l$(PROTOCOL)-ISUP$(DBGSUFFIX)	\
        -l$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX)     \
        -lcta -lctal -lctacl -lcpi -lisupapi -lmtp3api   \
	-lisupmgmt -lss7mapi -lhmiapi -lhmimgr -lthread -lnsl $(SYSLIBS)

all: isuptest$(PROTOCOL) 

clean:
	$(RM) $(OBJS) isuptest$(PROTOCOL)	
 
isuptest$(PROTOCOL): $(OBJS)
	$(CXX) $(CXXFLAGS) -o isuptest$(PROTOCOL) $(OBJS) \
	$(LIBS) $(SOCKLIBS) $(THREADLIBS) -ldl
#
#	get	the	rules
#
include	$(ITS_ROOT)/config.rules

