EXEC = \
	main \
	test-file \
	test-cfg-parser \
	test-md5

OBJS = \
	file.o \
	apitrace.o \
	_time.o \
	category.o \
	context.o

CC = gcc

CFLAGS = -Wall -std=c99
LDFLAGS= -lssl -lcrypto

INC_PATH = -I include

ifeq ($(strip $(DEBUG)),1)
CFLAGS += -DDEBUG -g
endif

all: $(EXEC)

main: src/main.c $(OBJS)
	$(CC) $< -o $@ $(OBJS) $(CFLAGS) $(INC_PATH) $(LDFLAGS)

%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH) $(LDFLAGS)

test-%: test/test-%.c $(OBJS)
	$(CC) $< -o $@ $(OBJS) $(CFLAGS) $(INC_PATH) $(LDFLAGS)

clean:
	$(RM) $(EXEC) $(OBJS)
