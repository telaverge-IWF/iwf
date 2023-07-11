
#.PHONY: all clean
CMAPIDIRS= idl configfetch alarms drestats iwfconfig dreconfig components usrmgt
all:	
	@for dir in ${CMAPIDIRS} ; \
	do \
	$(MAKE) -C $${dir}; \
	done
test:
	@for dir in ${CMAPIDIRS} ; \
	do \
	$(MAKE) -C $${dir}/test; \
	done
clean:
	@for dir in ${CMAPIDIRS} ; \
	do \
	$(MAKE) -C $${dir} $@; \
	done
