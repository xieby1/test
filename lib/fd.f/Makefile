SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
CC = gcc
CFLAGS = -g

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<
