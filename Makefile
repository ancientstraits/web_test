CFLAGS = -g -ggdb -Iinclude -Wall -static -Llib
LFLAGS = -lhpdfs -lm -lz
OBJS := $(patsubst  src/%.c, obj/%.o, $(wildcard src/*.c))
DEPS := $(wildcard include/*.h)
EXEC = main

all: $(EXEC)

obj:
	mkdir obj

obj/%.o: src/%.c obj $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
