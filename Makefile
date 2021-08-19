CFLAGS ?= -g -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -luring
LFLAGS ?= -shared

SRC := src
OBJ := object

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

cnidus: $(OBJECTS)
	$(CC) $^ -o $@ ${CFLAGS}

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) -I$(SRC)/include -c $< -o $@ ${CFLAGS}

clean:
	@rm -r ${OBJ}
	@mkdir ${OBJ}
	@rm cnidus
