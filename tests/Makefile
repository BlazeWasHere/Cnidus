CFLAGS ?= -O2 -lcmocka
LFLAGS ?= -shared

SRC := src
OBJ := bin

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(OBJ)/%, $(SOURCES))

test: $(OBJECTS)
	chmod +x tests.sh
	./tests.sh

$(OBJ)/%: %.c
	@mkdir -p $(OBJ)
	$(CC) -I../src/include ../object/$(notdir $@).o $< -o $@ ${CFLAGS}

clean:
	@rm -r ${OBJ}
	@mkdir ${OBJ}
