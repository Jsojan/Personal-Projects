CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic 
HEADERS = $(wildcard *.h)
MODULES = node pq code io stack huffman

all: encode decode

encode: encode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) $^ -o $@

decode: decode.o node.o pq.o code.o io.o stack.o huffman.o
	$(CC) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode *.o
	rm -f decode *.o

format:
	clang-format -i -style=file *.[ch]

