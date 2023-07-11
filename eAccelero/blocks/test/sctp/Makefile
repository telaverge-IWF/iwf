
include ../../../Makefile.inc

CXXFLAGS += -I$(EACC_ROOT)/blocks/include
LIBS += -lblocks

SRCDIR := ./
BINDIR := ./bin/$(DBGDIR)/
LIBDIR := ./lib/$(DBGDIR)/

sctp_BIN := sctp_test
sctp_OFILES := SctpTest.o

sctpAssoc_BIN := sctp_assoc_test
sctpAssoc_OFILES := SctpAssocTest.o

TARGETS_BIN := sctp sctpAssoc

include ../../../Makefile.rules

