include $(ITS_ROOT)/config/config.vars

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/include/itu -I$(ITS_ROOT)/include/asn-cpp 

LIBS = -lENGINED -lCAP-V2++D -lDISPATCH++D -lDRIVER++D \
     -lASN++D -lCAP-V2++D -lmtmalloc -lrt

all : test appitu.o app.o

test: test.cpp appitu.cpp app.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test appitu.cpp app.cpp test.cpp $(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

#
# get the rules
#
include $(ITS_ROOT)/config/config.rules

.PHONY: clean
clean:
	rm -rf *.o *.so test SunWS_cache core
