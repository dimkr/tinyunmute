CC ?= cc
CFLAGS ?= -Wall -pedantic
LDFLAGS ?=
LIBS = -ltinyalsa
DESTDIR ?= /
PREFIX ?= usr
BIN_DIR ?= $(PREFIX)/bin
DOC_DIR ?= $(PREFIX)/share/doc/tinyunmute

tinyunmute: tinyunmute.c
	$(CC) $(CFLAGS) tinyunmute.c $(LDFLAGS) $(LIBS) -o tinyunmute

clean:
	rm -f tinyunmute

install: tinyunmute
	install -D -m 755 tinyunmute $(DESTDIR)/$(BIN_DIR)/tinyunmute
	install -D -m 644 README $(DESTDIR)/$(DOC_DIR)/README
	install -m 644 AUTHORS $(DESTDIR)/$(DOC_DIR)/AUTHORS
	install -m 644 COPYING $(DESTDIR)/$(DOC_DIR)/COPYING