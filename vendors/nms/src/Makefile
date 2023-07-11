#Work in Progress
#
# get the vars
#
include $(VENDOR_ROOT)/config.vars

#
# set this to the appropriate subdirectory (NMS release)
#
NMSVER=v4_0
#
# set this for the software part (major times 1000, minor
# times 10
#
NMS_VERSION=4000

DEFINES:=$(DEFINES) -D_Solaris64_
CFLAGS:=$(CFLAGS) -I../include -I../include/$(NMSVER) \
	-DNMS_VERSION=$(NMS_VERSION) -DUNIX \
       -I$(ITS_ROOT)/common/include \
       -I$(ITS_ROOT)/TCAP/include \
       -I$(ITS_ROOT)/SCCP/include \
       -I$(ITS_ROOT)/MTP2/include \
       -I$(ITS_ROOT)/MTP3/include \
       -I$(ITS_ROOT)/ISUP/include \
       -I$(VENDOR_ROOT)/IntelliNet/include

ifeq ($(PLATFORM),linux)
CFLAGS:=$(CFLAGS) -DLINUX
else
CFLAGS:=$(CFLAGS) -DSOLARIS
endif

OBJS:=hmi.o transport.o \
	mtp2.o mtp2_alarms.o mtp3.o isup.o isup_translate.o sccp.o tcap.o

all: ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).a \
     ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).so 

clean:
	$(RM) $(OBJS) ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).a \
                      ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).so

../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).a: $(OBJS)
	$(AR) $(ARFLAGS) ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).a $(OBJS)

../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).so: $(OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) ../lib/lib$(PROTOCOL)-NMSVENDOR$(DBGSUFFIX).so $(OBJS)

 
#
# get the rules
#
#include $(VENDOR_ROOT)/config.rules


