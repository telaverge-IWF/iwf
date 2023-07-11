
# Set EACC_ROOT to this directory

ECHO=echo -e

ifdef TEST_MAKE
CXX := @echo g++
AR := @echo ar -r
CXXDEP := @echo g++ -MM
else
CXX := g++
AR := ar -r
CXXDEP := g++ -MM
CC := gcc
CCDEP := gcc -MM
endif

export DB_CONN=$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0

#
# version
ifeq ($(PRODUCT), iwf)
export DRE_VER_VERSION=0
export DRE_VER_RELEASE=0
export IWF_VER_VERSION=$(shell grep "Version:" $(IWF_ROOT)/package/iwf.spec | cut -d' ' -f 2)
export IWF_VER_RELEASE=$(shell grep "Release:" $(IWF_ROOT)/package/iwf.spec | cut -d' ' -f 2)
else
export DRE_VER_VERSION=$(shell grep "Version:" $(DRE_ROOT)/package/dre.spec | cut -d' ' -f 2)
export DRE_VER_RELEASE=$(shell grep "Release:" $(DRE_ROOT)/package/dre.spec | cut -d' ' -f 2)
endif

ifeq ($(PRODUCT), iwf)
CXXFLAGS += -DDRE_VER=\"v$(DRE_VER_VERSION)-$(DRE_VER_RELEASE)\" 
CFLAGS += -DDRE_VER=\"v$(DRE_VER_VERSION)-$(DRE_VER_RELEASE)\"
CXXFLAGS += -DIWF_VER=\"v$(IWF_VER_VERSION)-$(IWF_VER_RELEASE)\" -DFOR_IWF
CFLAGS += -DIWF_VER=\"v$(IWF_VER_VERSION)-$(IWF_VER_RELEASE)\" -DFOR_IWF
else
CXXFLAGS += -DDRE_VER=\"v$(DRE_VER_VERSION)-$(DRE_VER_RELEASE)\" 
CFLAGS += -DDRE_VER=\"v$(DRE_VER_VERSION)-$(DRE_VER_RELEASE)\"
endif


ifeq ($(DEBUG),NO)
    DBGDIR := release
	CXXFLAGS += -fPIC -g -O2 -fno-strict-aliasing
	#CXXFLAGS += -g -O2
	CFLAGS += -g -O2
else
    DBGDIR := debug
    CXXFLAGS += -fPIC -g -DDEBUG
	CFLAGS += -g -DDEBUG
endif

LIB_DIRS := -L$(EACC_ROOT)/lib/$(DBGDIR) -L${EACC_ROOT}/3rdparty/lib

CXXFLAGS += -Wall -D_REENTRANT
CXXFLAGS += -I./include -I${EACC_ROOT}/3rdparty/include
CXXFLAGS += -std=c++0x

LFLAGS += $(LIB_DIRS)
LIBS := -lpthread -lrt -ltcmalloc -lunwind

SO_LFLAGS += -shared $(LFLAGS)

SRCDIR = src/
OBJDIR = obj/$(DBGDIR)/
BINDIR = $(EACC_ROOT)/bin/$(DBGDIR)/
LIBDIR = $(EACC_ROOT)/lib/$(DBGDIR)/

CHK_FOR_ENV := @if [ "X$$EACC_ROOT" = "X" ];\
                then\
                    $(ECHO) "EACC_ROOT Environment not set";\
                    exit 1;\
                else\
                    exit 0;\
                fi 


PRINT_BIN_TARGETS = @for target in $(TARGETS_BIN); do \
	                    $(ECHO) -n " \$$(BINDIR)\$$($${target}_BIN)";\
                     done
PRINT_SO_TARGETS = @for target in $(TARGETS_SO); do \
	                    $(ECHO) -n " \$$(LIBDIR)\$$($${target}_SO)";\
                     done
PRINT_AR_TARGETS = @for target in $(TARGETS_AR); do \
	                    $(ECHO) -n " \$$(LIBDIR)\$$($${target}_AR)";\
                     done

BIN_RULES = @for target in $(TARGETS_BIN); do \
                $(ECHO)  "$${target}_DEPENDS := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.d)";\
                $(ECHO)  "$${target}_OFILES := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.o)";\
                $(ECHO)  "$${target}_LFLAGS := \$$(LFLAGS) \$$($${target}_LFLAGS)";\
                $(ECHO)  "$${target}_LIBS := \$$(LIBS) \$$($${target}_LIBS)";\
		        $(ECHO)  "\$$(BINDIR)\$$($${target}_BIN): \$$($${target}_DEPENDS) \$$($${target}_OFILES)";\
        		$(ECHO)  "	\$$(CXX) \$$($${target}_LFLAGS) -o \$$@ \$$($${target}_OFILES) \$$($${target}_LIBS)";\
                $(ECHO)  "\n-include \$$($${target}_DEPENDS)\n";\
    		    $(ECHO) ;\
            done

SO_RULES = @for target in $(TARGETS_SO); do \
                $(ECHO)  "$${target}_DEPENDS := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.d)";\
                $(ECHO)  "$${target}_OFILES := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.o)";\
                $(ECHO)  "$${target}_LFLAGS := \$$(SO_LFLAGS) \$$($${target}_LFLAGS)";\
                $(ECHO)  "$${target}_LIBS := \$$(LIBS) \$$($${target}_LIBS)";\
		        $(ECHO)  "\$$(LIBDIR)\$$($${target}_SO): \$$($${target}_DEPENDS) \$$($${target}_OFILES)";\
        		$(ECHO)  "	\$$(CXX) \$$($${target}_LFLAGS) -o \$$@ \$$($${target}_OFILES) \$$($${target}_LIBS)";\
                $(ECHO)  "\n-include \$$($${target}_DEPENDS)\n";\
    		    $(ECHO) ;\
            done

AR_RULES = @for target in $(TARGETS_AR); do \
                $(ECHO)  "$${target}_DEPENDS := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.d)";\
                $(ECHO)  "$${target}_OFILES := \$$($${target}_OFILES:%.o=\$$(OBJDIR)%.o)";\
		        $(ECHO)  "\$$(LIBDIR)\$$($${target}_AR): \$$($${target}_DEPENDS) \$$($${target}_OFILES)";\
        		$(ECHO)  "	\$$(AR) \$$@ \$$($${target}_OFILES)";\
                $(ECHO)  "\n-include \$$($${target}_DEPENDS)\n";\
    		    $(ECHO) ;\
            done

DIR_RULES = @$(ECHO) "dirs:\n\t@for d in \$${TARGETS_DIR}; do \\\\\n\t\t\$$(MAKE) -C \$$\$${d}; \\\\\n\tdone\n"

PRINT_BIN_CLEAN = @for target in $(TARGETS_BIN); do \
	                    $(ECHO) -n " $${target}.clean";\
                  done
PRINT_SO_CLEAN = @for target in $(TARGETS_SO); do \
	                    $(ECHO) -n " $${target}.clean";\
                  done
PRINT_AR_CLEAN = @for target in $(TARGETS_AR); do \
	                    $(ECHO) -n " $${target}.clean";\
                  done

BIN_CLEAN = @for target in $(TARGETS_BIN); do \
		        $(ECHO)  "$${target}.clean:";\
        		$(ECHO)  "	-rm -f \$$(BINDIR)\$$($${target}_BIN) \$$($${target}_OFILES) \$$($${target}_DEPENDS)";\
    		    $(ECHO) ;\
            done
                  
SO_CLEAN = @for target in $(TARGETS_SO); do \
		        $(ECHO)  "$${target}.clean:";\
        		$(ECHO)  "	-rm -f \$$(LIBDIR)\$$($${target}_SO) \$$($${target}_OFILES) \$$($${target}_DEPENDS)";\
    		    $(ECHO) ;\
            done
                  
AR_CLEAN = @for target in $(TARGETS_AR); do \
		        $(ECHO)  "$${target}.clean:";\
        		$(ECHO)  "	-rm -f \$$(LIBDIR)\$$($${target}_AR) \$$($${target}_OFILES) \$$($${target}_DEPENDS)";\
    		    $(ECHO) ;\
            done
                  
DIR_CLEAN = @$(ECHO) "dirsclean:\n\t@for d in \$${TARGETS_DIR}; do \\\\\n\t\t\$$(MAKE) -C \$$\$${d} clean; \\\\\n\tdone\n"

.SUFFIXES: .o .cpp .c .cc

