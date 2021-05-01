CFLAGS ?= -O2 -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -luring
LFLAGS ?= -shared

SRC := src
OBJ := object

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib

cnidus: $(OBJECTS)
	$(CC) $^ -o $@ ${CFLAGS}

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC)/include -c $< -o $@ ${CFLAGS}

clean:
	@rm -r ${OBJ}
	@mkdir ${OBJ}
	@rm cnidus