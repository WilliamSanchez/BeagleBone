CC  = gcc
DEPS = shm_com.h
OBJ =  shm1.o shm2.o
CFLAGS = -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: shm1 shm2 mmap

shm1: shm1.o
	$(CC) -o $@ $^ $(CFLAGS)

shm2: shm2.o
	$(CC) -o $@ $^ $(CFLAGS)

mmap: mmap.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o shm2 shm1 mmap *~

