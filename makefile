# ===== Config =====
CC      := gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -pedantic
LDFLAGS :=
LDLIBS  := -lm

TARGET  := parcial1

# Todos los .c de la carpeta
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:.o=.d)

# ===== Rules =====
.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

# Incluye dependencias generadas por -MMD
-include $(DEP)
