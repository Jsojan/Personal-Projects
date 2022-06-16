//-----------------------------------------------------------------------------//
// Joel Sojan, jsojan
// CSE101 Spring 2022 PA6
//
// Arithmetic.cpp
// Main file for PA6 implementation that uses BigInteger ADT.
//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>

#include "BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char *argv[]) {
    // Created needed variables here.
    string str;

    ifstream in;
    ofstream out;

    // Check that there are only three arguments in the function.
    if (argc != 3) {
        cerr << "Error: Too many or too little arguments given for Arithmetic program." << endl;
	exit(EXIT_FAILURE);
    }
    
    // Check the input file for Arithmetic program is valid.
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Error: Could not read input file" << argv[1] << " or input file is NULL." << endl;

	exit(EXIT_FAILURE);
    }

    // Check the output file for Arithmetic program is valid.
    out.open(argv[2]);
    if (!out.is_open()) {
	cerr << "Error: Could not read output file" << argv[2] << " or output file is NULL." << endl;

	exit(EXIT_FAILURE);
    }
    
    // Get the first line of input file and store in as A.
    getline(in, str);

    BigInteger A = BigInteger(str);
    
    // Read in empy second line.
    getline(in, str);
    
    // Get the second line of input file and store in as B.
    getline(in, str);

    BigInteger B = BigInteger(str);
    
    // Create copies of A and B to be used later.
    BigInteger C = A;
    BigInteger D = B;
    
    // Return A.
    out << A << endl;
    
    // Return B.
    out << B << endl;
    
    BigInteger E = A.add(B);
    
    // Return A + B.
    out << E << endl;

    BigInteger F = A.sub(B);
    
    // Return A -  B.
    out << F << endl;
    
    BigInteger G = A.sub(A);
    
    // Return A - A.
    out << G << endl;

    BigInteger H = BigInteger("3");
    BigInteger I = BigInteger("2");

    BigInteger Ho = H * A;
    BigInteger Io = I * B;
    
    BigInteger K = Ho.sub(Io);
    
    // Return 3A - 2B.
    out << K << endl;
    
    BigInteger L = A.mult(B);
    
    // Return A * B.
    out << L << endl;

    BigInteger M = A.mult(A);
    
    // Return A * A.
    out << M << endl;

    BigInteger N = B.mult(B);
    
    // Return B * B.
    out << N << endl;

    BigInteger O = BigInteger("9");
    BigInteger P = BigInteger("16");

    for (int x = 0; x < 3; x++) {
	C *= A;
    }

    for (int y = 0; y < 4; y++) {
	D *= B;
    }

    BigInteger On = O * C;
    BigInteger Pn = P * D;
    
    BigInteger Q = On + Pn;
    
    // Return 9(A^4) + 16(B^5)
    out << Q << endl;


    // close files
    in.close();
    out.close();

    return 0;
}
