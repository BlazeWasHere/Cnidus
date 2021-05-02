CFLAGS ?= -O2 -lcmocka
LFLAGS ?= -shared

BIN := bin

SOURCES := $(wildcard *.c)
BINS := $(patsubst %.c, %, $(SOURCES))

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib

$(BINS)/: *.c
	$(CC) -I../src/include ../object/$@.o $< -o $(BIN)/$@ ${CFLAGS}

clean:
	@rm -r ${BIN}
	@mkdir ${BIN}
	@rm bin
