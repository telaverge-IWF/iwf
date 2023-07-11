#
# Java Packages
#
TESTPKGS=diameter.dcca diameter.gx diameter.gx.base diameter.sh diameter.rx diameter.rx.base diameter.tx diameter.tx.base diameter.ty diameter.ty.base diameter.wx diameter.wx.ietf diameter.base diameter.cxdx diameter.rfro diameter.rfro.ims diameter.rfro.ietf diameter.gqgqprime

PACKAGES=diameter $(TESTPKGS)

#
# Java Sources
#
SOURCES=$(wildcard $(patsubst %,%/*.java,$(subst .,/,$(PACKAGES))))

CLASSES=$(SOURCES:.java=.class)

JARS=

#
# Classpath
#
CLASSPATH=.:../../../val/java/lib/diameter.jar:../lib/diaapi.jar

#
# Targets
#
all: $(CLASSES)

clean:
	rm -rf $(JARS) $(patsubst %,%/*.class,$(subst .,/,$(PACKAGES)))
 
realclean: clean
	rm -rf $(wildcard $(patsubst %,%/*.java,$(subst .,/,$(TESTPKGS))))

#
# Pattern Rules
#
%.class: %.java
	$(JAVAC) $<

#
# Commands
#
JAVAC=javac -classpath $(CLASSPATH)
JAR=jar
