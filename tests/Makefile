CFLAGS ?= -O2 -lcmocka
LFLAGS ?= -shared

OBJ := object

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(OBJ)/%.o, $(SOURCES))

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib

tests: $(OBJECTS)
	$(CC) ../$^ $^ -o $@ ${CFLAGS}

$(OBJ)/%.o: *.c
	$(CC) -I../src/include -c $< -o $@ ${CFLAGS}

clean:
	@rm -r ${OBJ}
	@mkdir ${OBJ}
	@rm tests
