
#for all interfaces except for BCGI
all:
	cd src && $(MAKE);
 
# all interfaces but only for BCGI build
BCGI:
	cd src && $(MAKE) clean;
	cd src && $(MAKE) TARGET=BCGI BCGI;

# clean all
clean:
	cd src && $(MAKE) clean;

#for all interfaces except for BCGI
cleanall:
	cd src && $(MAKE) clean;
	cd src && $(MAKE);
	cd src && rm -rf common_cc_decode.o;$(MAKE) TARGET=BCGI BCGI
 
