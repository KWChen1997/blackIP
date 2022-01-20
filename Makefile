CC = gcc
CFLAGS = -g -Wall
CLIBS = -lcurl
SRCS = $(wildcard *.c)
PROG = blackIP

all:$(PROG)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

clean:
	rm -f $(PROG)
