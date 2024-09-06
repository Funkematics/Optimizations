PROG = Problem1
CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = -lm
SRCS = Problem1.c
OBJS = $(SRCS:.c=.o)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(PROG)

.PHONY: clean
