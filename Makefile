CFLAGS = -g -Wall
CC=g++
TARGET=SpMM

all: $(TARGET)

debug:	CFLAGS += -DDEBUG
debug:	$(TARGET)

reader.o:	reader.cc
	$(CC) $(CFLAGS) -c reader.cc

matrix.o:	matrix.cc
	$(CC) $(CFLAGS) -c matrix.cc

main.o:	main.cc
	$(CC) $(CFLAGS) -c main.cc

$(TARGET):	main.o reader.o matrix.o
	$(CC) $(CFLAGS) -o SpMM reader.o main.o matrix.o

clean :
	rm -rf *.o $(TARGET)

.PHONY: all debug clean
