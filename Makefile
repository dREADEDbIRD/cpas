CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = auth
SRCS = auth.c
OBJS = $(SRCS:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -vf $(OBJS) $(TARGET)
rebuild: clean all