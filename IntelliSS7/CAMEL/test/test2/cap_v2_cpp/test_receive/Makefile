#
# get the vars
#
include $(ITS_ROOT)/config/config.vars


CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/include/itu \
	-I$(ITS_ROOT)/include/asn-cpp


LIBS = -lDRIVER++D -lDISPATCH++D \
     -lENGINED -lCAP-V2++D -lASN++D -lmtmalloc -lrt

all: app.o test


test: test.cpp app.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test test.cpp app.cpp $(LIBS) \
	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)
#
# get the rules
#
include $(ITS_ROOT)/config/config.rules

.PHONY: clean
clean:
	\rm -rf *.o test SunWS_cache core
