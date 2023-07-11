#
# get the vars
#
include $(ITS_ROOT)/config/config.vars

#
# Don't build if not ANSI
#
ifeq ($(PROTOCOL),ANSI)

CXXOBJS=test_codec_main.o

CXXSRCS=test_codec_main.cpp

ITS_LIBS = -lENGINE$(DBGSUFFIX) -lASN++$(DBGSUFFIX) \
           -lASN$(DBGSUFFIX) \
           -lWIN++$(DBGSUFFIX) -ldl \
           -lDSM-STUBD

LINK_FLAG = -L$(ITS_ROOT)/lib -L$(ITS_ROOT)/lib

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/include \
          -I$(ITS_ROOT)/include/asn-cpp \
          -I$(ITS_ROOT)/include/ansi

all: test_codec$(DBGSUFFIX)

test_codec$(DBGSUFFIX): $(CXXOBJS)
	$(CXX) -g $(CXXFLAGS) $(LDFLAGS) \
        $(LINK_FLAG) -o test_codec$(DBGSUFFIX) $(CXXOBJS) \
        $(ITS_LIBS) $(SOCKLIBS) $(THREADLIBS)

clean:
	$(RM) $(CXXOBJS) test_codec$(DBGSUFFIX) *.err .depend

#
# get the rules
#
include $(ITS_ROOT)/config/config.rules
#
# Don't build if not ANSI
#
else

all:

clean:

endif
