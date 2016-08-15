EXEC = \
	main \
	test-file \
	test-dump-stdout

OBJS = \
	file.o \
	apitrace.o

CC = gcc

CFLAGS = -Wall -std=c99
LDFLAGS=

INC_PATH = -I include

ifeq ($(strip $(DEBUG)),1)
CFLAGS += -DDEBUG -g
endif

all: $(EXEC)

main: src/main.c $(OBJS)
	$(CC) $< -o $@ $(OBJS) $(CFLAGS) $(INC_PATH)

%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

test-%: test/test-%.c $(OBJS)
	$(CC) $< -o $@ $(OBJS) $(CFLAGS) $(INC_PATH)

clean:
	$(RM) $(EXEC) $(OBJS)
