include ../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include -I$(EACC_ROOT)/mess/include \
		    -I$(EACC_ROOT)/cmapi/idl -I.

LIBS += -L${PROTOBUF_PATH}/.libs -L$(EACC_ROOT)/cmapi/idl/lib \
		-lavamgridl \
		-lmess -lblocks -lprotobuf -lprotoc

BINDIR := ./bin/$(DBGDIR)/

mdecode_BIN := mdecode
mdecode_OFILES := MeSSHeaderDecoder.o

TARGETS_BIN := mdecode

include ../../Makefile.rules



