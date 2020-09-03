SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c, %, $(SRCS))
CC = gcc
CFLAGS = $(shell pkg-config --cflags glib-2.0)
LIBS = $(shell pkg-config --libs glib-2.0)

print-%: ; @echo $* = $($*)

all: $(PROGS)

%: %.c
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

