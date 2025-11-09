CFLAGS = -g -Wall
CC=gcc
TARGET=SpMM

all: $(TARGET)

debug:	CFLAGS += -DDEBUG
debug:	$(TARGET)

reader.o:	reader.c
	$(CC) $(CFLAGS) -c reader.c

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

$(TARGET):	main.o reader.o
	$(CC) $(CFLAGS) -o SpMM reader.o main.o

clean :
	rm -rf *.o $(TARGET)

.PHONY: all debug clean
