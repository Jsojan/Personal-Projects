# Assignment 6 - Huffman Coding (README.md)

## Short description:
     This progam performs Huffman Coding which utilizes the concept of entropy to assign symbols and values less bits the more frequent they are in a message or text file and vise versa. As such, Huffman Coding's one significant advantage is its ability to compress data in a file dby utilizing entropy for encoding and decoding. Furthermore, the implementaion of Huffman Coding relies on the creation of a Priority Queue (this implementation was created based of Insertion Sort), Stack, bitwise shifts of Huffman Codes, and an implementation of a Huffman Tree.

## Build
     To build this program manually, use "make" or "make all" using the provided make file. Alternatively, to manually build this program, first type "make encode" with the provided Makefile. This will encode the contents of the input file. Then, input "make decode" to build the decoding process used for decoding Huffman encoding. To check if the Huffman encoding and decoding program truly works try (echo 'enter any text here' | ./encode | ./decode).

## Running
    ./encode
    ./decode

    For both of these files, the -h specifier when running this program prints out the programs usage and synopsis. Likwise, the command line option -i specifies the infile it will take in while the -o option specifies the output file to be used by either encode or decode. Lastly, the -v command line option for encode prints compression statistics to stderr while the -v option for decode prints the decompression statistics to sterr.

## Error Handling
    Note, scan build returns some errors regarding my implementation of huffman.c noting that it is dereferencing a null pointer in (*root)->left or (*root)->right. However, if my function is call correctly then this error shouldn't occur since it checks for a null left or right child.

## Cleaning
    For cleaning the files, type "rm -f encode *.o", "rm -f decode *.o", on the command line. Another method is to type "make clean" in the command line with the provided Makefile.


