
ifndef EACC_ROOT
    export EACC_ROOT=$(shell pwd)
endif

export TPARTY_DIR=$(EACC_ROOT)/3rdparty/
export DB_CONN=$(EACC_ROOT)/3rdparty/mysql-connector-c++-1.1.0
#DIRS= blocks utils mess cmapi common avamgr/hacomponent cli cmgr repmgr avamgr
DIRS=${DB_CONN} ${TPARTY_DIR} blocks utils mess cmapi common avamgr/hacomponent cli cmgr repmgr avamgr
TESTDIRS=blocks mess avamgr

.PHONY: test clean testclean config

all: config
	@for dir in ${DIRS} ; \
	do \
		$(MAKE) -C $${dir}; \
		if [ $$? -ne 0 ] ; then \
			echo "$${dir} **failed** to compile"; \
			exit -1; \
		fi \
	done

test:
	@for dir in ${TESTDIRS} ; \
	do \
		$(MAKE) -C $${dir}/test; \
	done


clean:
	@for dir in ${DIRS} ; \
	do \
		$(MAKE) -C $${dir} clean; \
	done

testclean:
	@for dir in ${TESTDIRS} ; \
	do \
		$(MAKE) -C $${dir}/test clean; \
	done

config: $(DB_CONN)/CMakeCache.txt

$(DB_CONN)/CMakeCache.txt:
	cd $(TPARTY_DIR) && tar -xvf mysql-connector-c++-1.1.0.tar.gz; \
	cd $(DB_CONN) && cmake . && cd $(EACC_ROOT) 

