PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man

#CDEBUGFLAGS = -std=c11 -O3 -pg -Wall -I/lib/modules/4.9.0-rc5-airtime-9/build/linux/include/uapi
CDEBUGFLAGS = -std=gnu99 -Wall -O3 -Wall -I/lib/modules/4.9.0-rc5-airtime-9/build/linux/include/uapi

# FIXME for cross compilation
ARCH=$(shell uname -m)
ifeq ($(ARCH),armv7l)
NEON=-DHAVE_NEON -mfpu=neon
endif

ifeq ($(ARCH),x86_64)
X8664=-DHAVE_64BIT_ARCH
endif

DEFINES = $(PLATFORM_DEFINES) $(NEON) $(X8664)

CFLAGS = $(CDEBUGFLAGS) $(DEFINES) $(EXTRA_DEFINES)

LDLIBS = -lrt

SRCS = babeld.c net.c kernel.c util.c interface.c source.c neighbour.c \
       route.c xroute.c message.c resend.c configuration.c local.c \
       disambiguation.c rule.c

HEADERS := $(patsubst %.c,%.h,$(SRCS))
#OBJS := $(patsubst %.c,%.o,$(SRCS)) 
OBJS = babeld.o net.o kernel.o util.o interface.o source.o neighbour.o \
       route.o xroute.o message.o resend.o configuration.o local.o \
       disambiguation.o rule.o

babeld: $(OBJS) $(HEADERS) version.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o babeld $(OBJS) $(LDLIBS)

babeld.o: babeld.c version.h

local.o: local.c version.h

kernel.o: kernel_netlink.c kernel_socket.c

version.h:
	./generate-version.sh > version.h

babeld-whole.c: $(SRCS) version.h
	cat $(SRCS) > babeld-whole.c

babeld-whole.s: babeld-whole.c
	$(CC) $(CFLAGS) $(LDFLAGS) -msse4.2 -fwhole-program -fverbose-asm babeld-whole.c -S -o babeld-whole.s $(LDLIBS)

babeld-whole: babeld-whole.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fwhole-program babeld-whole.c -o babeld-whole $(LDLIBS)

TAGS: $(SRCS) $(HEADERS)
	etags $(SRCS) $(HEADERS)

.SUFFIXES: .man .html

.man.html:
	mandoc -Thtml $< > $@

babeld.html: babeld.man

.PHONY: all install install.minimal uninstall clean

all: babeld babeld.man

install.minimal: babeld
	-rm -f $(TARGET)$(PREFIX)/bin/babeld
	mkdir -p $(TARGET)$(PREFIX)/bin
	cp -f babeld $(TARGET)$(PREFIX)/bin

install: install.minimal all
	mkdir -p $(TARGET)$(MANDIR)/man8
	cp -f babeld.man $(TARGET)$(MANDIR)/man8/babeld.8

uninstall:
	-rm -f $(TARGET)$(PREFIX)/bin/babeld
	-rm -f $(TARGET)$(MANDIR)/man8/babeld.8

clean:
	-rm -f babeld babeld-whole babeld.html version.h *.o *~ core TAGS gmon.out babeld-whole.c
