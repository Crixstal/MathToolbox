BIN=math
OBJS=main.o binary_detection.o range.o referential2.o vector2.o 

CC?=gcc

CFLAGS=-Wall -g -O0 -Wno-unused-variable
CPPFLAGS=-MMD -Iinclude

LDLIBS=-lmingw32

DEPS=$(OBJS:.o=.d)

.PHONY: all clean run

all: $(BIN)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

run: $(BIN)
	./$<

debug: $(BIN)
	./$<

clean:
	rm -f $(OBJS) $(DEPS) $(BIN)
