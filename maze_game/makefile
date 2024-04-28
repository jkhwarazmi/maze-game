CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

TARGET = maze

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
