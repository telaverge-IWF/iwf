#
# get the vars
#
include $(ITS_ROOT)/config/config.vars

#
# objs
#

OBJS = main.o tim_send.o tim_encdec.o app_dbc.o
SHAREDOBJS = tim_api.o tim_recv.o

INCLS  := $(INCLS) \
	-I. \
	-I$(ITS_ROOT)/include \
	-I$(ITS_ROOT)/include/ansi \
	-I$(ITS_ROOT)/include/asn-cpp

CFLAGS := $(CFLAGS) $(INCLS)
CXXFLAGS := $(CFLAGS) $(INCLS)

DEFS := $(DEFS) -DANSI -D_REENTRANT -DUSING_FLEX -DHAVE_NAMESPACES
DEFS := $(DEFS) -DHAVE_STD_NAMESPACE -DHAVE_THROW_SPECS -DHAVE_STL  -DDEBUG -DUNIX
CFLAGS  = -g -c $(INCLS) $(DEFS)
LDFLAGS := $(LDFLAGS) -g


LIBS    := \
           -lENGINED -lDISPATCH++D -lDRIVER++D -lVFrameD -lANSI-VENDORD \
           -lDSM-STUBD -lASN++D -lANSI-VENDORD -lWIN++D

LIBS    := $(LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/lib \
           $(LIBS) -L/opt/nmstx/lib -L/opt/nms/lib

all: libtim.so tim

libtim.so: tim_recv.o tim_api.o
	$(SHAREDAR) $(SHAREDARFLAGS) $@ $(SHAREDOBJS)

tim: $(OBJS)
	$(LD) -o tim $(OBJS) $(LDFLAGS) -L. -ltim $(LIBS) 

clean:
	@$(RM) libtim.so tim $(OBJS) $(SHAREDOBJS) *.err .depend

#
# get the rules
#
include $(ITS_ROOT)/config/config.rules

