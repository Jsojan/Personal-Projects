# Assignment 5 - RSA Encryption (README.md)

## Short description:
     This progam performs RSA encryption through the usage of number theoretic functions, public and private keys and mathematical encrypting and decrypting of messages using said number theoretic functions. Furthermore, this program implements gmp (Gnu multiple precision) values to ensure public and private keys are large enough primes for which encryption and decryption are secure for the sender of the message and the intended recipient. As such, this program consists of three main programs which are the RSA key generation (keygen.c), RSA encryption (encrypt.c) and RSA decryption (decrypt.c).

## Build
     To build this program manually, use "make" or "make all" using the provided make file.Alternatively, to manually build this program, first type "make keygen" with the provided Makefile. This will build the necessary keys for RSA encryption. Then, input "make encrypt" followed by "make decrypt" to build the rest of the required files for this program. To check if the RSA encrypting and decryption program truly works try (echo 'enter any text here' | ./encrypt | ./decrypt).

## Running
    ./keygen
    ./encrypt
    ./decrypt
    
    For all three of these files, the -h specifier when running this program will print the usage and synopsis of each respective function when called such as(./encrypt -h) as an example. For keygen, the options include -b for bits needed for public modulus, -i for iterations of Miller Rabin, -n for public keyfile,-d for private key file, -s for random seed, and -v for enabling verbose output. As for encrypt and decrypt.c, -i specifies the input file, -o specifies the output file, -n specifies the public key file to be used, and -v enables verbose output.


## Cleaning
    For cleaning the files, type "rm -f keygen *.o", "rm -f encrypt *.o", "rm -f decrypt *.o" on the command line. Another method is to type "make clean" in the command line with the provided Makefile.

