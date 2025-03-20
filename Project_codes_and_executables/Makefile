# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Executable name
EXEC = scheduler

# Source files
SRCS = main.c fcfs.c rr.c sjf.c srtn.c hrrn.c edf.c priority.c lottery.c every.c

# Object files
OBJS = $(SRCS:.c=.o)

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c simulator.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)

