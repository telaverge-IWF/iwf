
TPARTY_DIR := $(shell pwd)
PROTOBUF_DIR := protobuf-2.4.1
JSONCPP_DIR := jsoncpp_0.6.0-rc2
LIBMEMCACHED_DIR := libmemcached-0.34
NCURSES_DIR := ncurses-5.7
MYSQL_DIR := mysql-cluster-gpl-7.2.8
MEMCACHED_FUNCTIONS_MYSQL := memcached_functions_mysql-1.0
CLIPS_DIR := clips-src-6.24
INCRON_DIR := incron-0.5.10
LIBCOUCHBASE_DIR := libcouchbase-2.2.0
TCMALLOC_DIR := gperftools-2.0
LIB_UNWIND_DIR := libunwind-1.1

CMAKE := cmake

DIRS :=  ${PROTOBUF_DIR} ${JSONCPP_DIR} ${LIBMEMCACHED_DIR} ${NCURSES_DIR} ${MYSQL_DIR} ${MEMCACHED_FUNCTIONS_MYSQL} ${CLIPS_DIR} ${INCRON_DIR} ${LIBCOUCHBASE_DIR} ${TCMALLOC_DIR} ${LIB_UNWIND_DIR}

.PHONY: all config clean protobuf jsoncpp libmemcached ncurses mysql-cluster-gpl memcached_functions_mysql clips-src-6.24 incron-0.5.10

#all: protobuf jsoncpp libmemcached ncurses mysql-cluster-gpl memcached_functions_mysql clips-src-6.24 incron-0.5.10
all: protobuf jsoncpp libmemcached ncurses mysql-cluster-gpl memcached_functions_mysql clips-src-6.24 incron-0.5.10 libcouchbase tcmalloc libunwind
#all: libcouchbase

libcouchbase: 
	@echo "----------- Configuring LibCouchbase ------------"
	@tar -xvf $(LIBCOUCHBASE_DIR).tar.gz 
	@mkdir -p $(LIBCOUCHBASE_DIR)/tests/
	@cp CouchbaseMock.jar $(LIBCOUCHBASE_DIR)/tests/. 
	@cp gtest-1.7.0.zip $(LIBCOUCHBASE_DIR)/.
	@cd $(LIBCOUCHBASE_DIR) && ./configure --prefix=${TPARTY_DIR} --disable-plugins && cd -
	$(MAKE) -C ${LIBCOUCHBASE_DIR} install

tcmalloc: bin/tcmalloc

bin/tcmalloc: ${TCMALLOC_DIR}/config.h
	$(MAKE) LIBS=-lunwind -C ${TCMALLOC_DIR} install

${TCMALLOC_DIR}/config.h: libunwind
	@echo "----------- Configuring Google Perf TCMalloc ------------"
	-@cd ${TCMALLOC_DIR} && make distclean 2>&1 >/dev/null ; ./configure --prefix=${TPARTY_DIR}  CPPFLAGS=-I../libunwind-1.1/include LDFLAGS=-L../lib 2>&1 >/dev/null && cd -
	@cd ${TCMALLOC_DIR} && make distclean ; ./configure --prefix=${TPARTY_DIR}  CPPFLAGS=-I../libunwind-1.1/include LDFLAGS=-L../lib && cd -

# libmemcached related
libunwind: ${LIB_UNWIND_DIR}/config.h
	$(MAKE) -C ${LIB_UNWIND_DIR} install

${LIB_UNWIND_DIR}/config.h:
	@echo "----------- Configuring libunwind ------------"
	@cd ${LIB_UNWIND_DIR} && ./configure --prefix=${TPARTY_DIR} && sed -i 's/install: install-am/install:/g' doc/Makefile && cd -
# Protocol buffer related make rules
protobuf: bin/protoc

bin/protoc: ${PROTOBUF_DIR}/config.h
	$(MAKE) -C ${PROTOBUF_DIR} install

${PROTOBUF_DIR}/config.h:
	@echo "----------- Configuring Google Protocol Buffers ------------"
	@cd ${PROTOBUF_DIR} && ./configure --prefix=${TPARTY_DIR} && cd -

# JSON CPP related
jsoncpp:
	$(MAKE) -C ${JSONCPP_DIR}
	@cp -r ${JSONCPP_DIR}/json ${TPARTY_DIR}/include

# libmemcached related
libmemcached: ${LIBMEMCACHED_DIR}/config.h
	$(MAKE) -C ${LIBMEMCACHED_DIR} install

${LIBMEMCACHED_DIR}/config.h:
	@echo "----------- Configuring libmemcached ------------"
	@cd ${LIBMEMCACHED_DIR} && ./configure --prefix=${TPARTY_DIR} && cd -

# ncurses related
ncurses: ${NCURSES_DIR}/include/ncurses.h
	$(MAKE) -C ${NCURSES_DIR} install

${NCURSES_DIR}/include/ncurses.h:
	@echo "----------- Configuring ncurses ------------"
	@cd ${NCURSES_DIR} && ./configure --prefix=${TPARTY_DIR} && cd -

# mysql-cluster-gpl related
mysql-cluster-gpl: ${MYSQL_DIR}/include/my_config.h
	$(MAKE) -C ${MYSQL_DIR} install

${MYSQL_DIR}/include/my_config.h:
	@echo "----------- Configuring mysql-cluster-gpl ------------"
	@cd ${MYSQL_DIR} && $(CMAKE) -DCMAKE_INSTALL_PREFIX=${TPARTY_DIR}/mysql \
	-DCURSES_LIBRARY=${TPARTY_DIR}/lib/libncurses.a -DCURSES_INCLUDE_PATH=${TPARTY_DIR}/include/ncurses && cd -

# memcached_functions_mysql
memcached_functions_mysql: ${MEMCACHED_FUNCTIONS_MYSQL}/src/libmemcached_config.h
	$(MAKE) -C ${MEMCACHED_FUNCTIONS_MYSQL} install	

${MEMCACHED_FUNCTIONS_MYSQL}/src/libmemcached_config.h:
	@echo "----------- Configuring memcached_functions_mysql ------------"
	cd ${MEMCACHED_FUNCTIONS_MYSQL} && ./configure --prefix=${TPARTY_DIR} --with-mysql=${TPARTY_DIR}/mysql/bin/mysql_config \
		--with-libmemcached=${TPARTY_DIR} && cd -

clips-src-6.24:
	@echo "----------- Compiling Clips 3rdparty RulesEngine  ------------"
	$(MAKE) -C ${CLIPS_DIR}

incron-0.5.10:
	@echo "-----------Compiling incron-0.5.10-----------------"
	$(MAKE) -C ${INCRON_DIR}

clean:
	@for dir in ${DIRS} ; \
	do \
		$(MAKE) -C $${dir} clean; \
	done
	rm -rf bin lib include share man mysql
