
include $(ITS_ROOT)/config.vars
include $(IMS_ROOT)/make.dirs

IDLDIR:= $(DRE_ROOT)/idl
IWFCMAPIDIR:=$(IWF_ROOT)/cmapi

DEFINES:=$(DEFINES) $(ITS_DEFINES)

CXXFLAGS+= -std=c++0x

CXXFLAGS += -I.
LIBS += -lblocks -lmess -lprotobuf -lprotoc -liwfidl

INCLS:=$(INCLS) $(ITS_INCLS) \
	-I../include \
	-I../../common \
	-I../../controller/include \
	-I$(IMS_ROOT)/apps/include \
	-I$(EACC_ROOT)/mess/include \
	-I$(EACC_ROOT)/blocks/include \
	-I$(EACC_ROOT)/common/include \
	-I$(EACC_ROOT)/3rdparty/include \
	-I$(IMS_ROOT)/include \
	-I$(ITS_ROOT)/include \
	-I$(IMS_ROOT)/api/c++/include \
	-I$(IMS_ROOT)/api/include \
	-I$(IMS_ROOT)/common/include \
	-I$(IMS_ROOT)/dframe/include \
	-I$(IMS_ROOT)/vendors/IntelliNet/include \
	-I$(IDLDIR)/include \
	-I$(IWFCMAPIDIR)/include 

OBJS:= CMApiIwf.o

.PHONY: all clean realclean test

all: ../lib/libiwfcmapi$(DBGSUFFIX).a

../lib/libiwfcmapi$(DBGSUFFIX).a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	-rm -f *.o
	-rm -f ../lib/libiwfcmapi*

include $(ITS_ROOT)/config.rules

