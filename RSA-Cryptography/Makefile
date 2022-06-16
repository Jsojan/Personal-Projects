CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)
HEADERS = $(wildcard *.h)
MODULES = numtheory randstate rsa 

all: keygen encrypt decrypt

keygen: keygen.o numtheory.o randstate.o rsa.o 
	$(CC) $^ -o $@ $(LFLAGS)

encrypt: encrypt.o numtheory.o randstate.o rsa.o 
	$(CC) $^ -o $@ $(LFLAGS)

decrypt: decrypt.o numtheory.o randstate.o rsa.o 
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f keygen *.o
	rm -f encrypt *.o
	rm -f decrypt *.o

format:
	clang-format -i -style=file *.[ch]


