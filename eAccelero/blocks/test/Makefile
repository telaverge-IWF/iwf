include ../../Makefile.inc

CXXFLAGS += -fPIC -I$(EACC_ROOT)/blocks/include
LIBS += -lblocks -ldl

BINDIR := ./bin/$(DBGDIR)/
LIBDIR := ./lib/$(DBGDIR)/

stats_BIN := statsTest
stats_OFILES := StatsTest.o

exception_BIN := exception
exception_OFILES := ExceptionTest.o

IndexTableTest_BIN := IndexTableTest
IndexTableTest_OFILES := IndexTableTest.o

component_BIN := component
component_OFILES := ComponentTest.o

sigtest_BIN := sigtest
sigtest_OFILES := SignalTest.o

timertest_BIN := timertest
timertest_OFILES := TimerTest.o

reftest_BIN := reftest
reftest_OFILES := RefTest.o

mempooltest_BIN := mempooltest
mempooltest_OFILES := MemPoolTest.o

threadtest_BIN := threadtest
threadtest_OFILES := ThreadTest.o

tqtest_BIN := tqtest
tqtest_OFILES := TQTest.o

tss_BIN := tss
tss_OFILES := TSS.o

loadplugin_BIN := loadplugin
loadplugin_OFILES := LoadPlugin.o

futextest_BIN := futextest
futextest_OFILES := FutexTest.o

socktest_BIN := socktest
socktest_OFILES := SockTest.o

sctpclient_BIN := sctpclient
sctpclient_OFILES := SctpClient.o

TARGETS_BIN := stats exception IndexTableTest component sigtest timertest reftest mempooltest tss loadplugin threadtest tqtest futextest socktest sctpclient

testplugin_SO := libTest.so
testplugin_OFILES := TestPlugin.o

TARGETS_SO := testplugin

TARGETS_DIR := sctp

include ../../Makefile.rules
