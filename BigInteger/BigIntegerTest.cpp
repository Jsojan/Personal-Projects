//-----------------------------------------------------------------------------
//  Joel Sojan, jsojan
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   // Create initial strings.
   string s1 = "+34290743209743934294190348239108740924239";
   string s3 = "-98327494701239312792317498237109849231439023819";
   

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger D = BigInteger("2913489038324");
   BigInteger E = BigInteger("9324048320942");
   BigInteger F = BigInteger("-6983209834921");

   BigInteger I;

   cout << endl;

   // Check default constructor;
   cout << "Default Constructor Test" << endl;

   cout << I << endl;
   
   // Print the Lists A and B.
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;

   // Test Copy Constructor 

   cout << "Set BigInteger H = A " << endl;

   BigInteger H = A;

   cout << "H = " << H << endl;

   // Check compare function returns correctly using the overriden operators.

   cout << "(A==H) = " << ((A==H)?"True":"False") << endl;
   
   cout << "(F<B)  = " << ((F<B)? "True":"False") << endl;
   
   cout << "(F<=I) = " << ((F<=I)?"True":"False") << endl;
   
   cout << "(E>D)  = " << ((E>D)? "True":"False") << endl;
   
   cout << "(A>=H) = " << ((A>=H)?"True":"False") << endl << endl;

   cout << endl;

   // Check that makeZero function works correctly.
   
   cout << "This is D before make zero function is called: " << endl;
   cout << D << endl;

   D.makeZero();

   cout << "This is D after make zero function was called: " << endl;
   cout << D << endl;

   // Check negate function works.

   cout << "This I before negate function was called: " << endl;

   cout << "I: " << I << endl;

   I.negate();

   cout << "I after negate: " << I << endl;

   cout << "E: " << E << endl;
   
   E.negate();
   
   cout << "E after negate: " << E << endl;

   E.negate();

   cout << "E after negate twice: " << E << endl;

   // Check add() function works using the overloaded + and += function.

   BigInteger C = A+B;

   cout << "A+B = " << C << endl;

   cout << "C.sign() " << C.sign() << endl;

   I += B;

   cout << "I = I + B: " << I << endl;

   cout << "I.sign(): " << I.sign() << endl;

   // Check sub() function works using the overloaded - and -= function.

   BigInteger J = A - B;

   cout << "A - B: " << J << endl;
   cout << "J.sign() " << J.sign() << endl;

   I -= F;

   cout << "I = I - F: " << I << endl;
   cout << "I.sign() " << I.sign() << endl;

   // Check mult() function works using the overloaded * and *= function.

   BigInteger G = A * B;

   cout << "A * B = " << G << endl;
   cout << "G.sign() " << G.sign() << endl;

   F *= B;

   cout << "F = F * B: " << F << endl;
   cout << "F.sign() " << F.sign() << endl;

   // Manually check to_string function works even though overloaded 
   // operator that use to_string functions also works.

   cout << "This is a check to print out F" << endl;

   cout << F.to_string() << endl;
   
   // Additioncal check to see if Lists C and D are equal in this case.

   if (!(C == D)) {
	cout << "C: " << C << endl;
	cout << "D: " << D << endl;
   }
   
   // Check if C and D are equal and print out
   // the signs of C and D.

   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;

   cout << "C Sign " << C.sign() << endl;

   cout << "D sign " << D.sign() << endl;

   // Multiply C by A and set C equal to the result..

   C *= A;
   
   cout << "C = " << C << endl;
   cout << "C sign: " << C.sign() << endl;
   cout << endl;

   // Multiply E by F and set E equal to the result.

   E *= F;

   cout << "E = " << E << endl;
   cout << "E sign: " << E.sign() << endl;
   cout << endl;

   // Add G and H together and G equal to the result.

   G += H;

   cout << "G = " << G << endl;
   cout << "G sign: " << G.sign() << endl;
   cout << endl;

   // Check that BigInteger constructor works for edge cases that are tested
   // in this case.

   try{
      BigInteger J = BigInteger("--00");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("9123090w1-9414973415$2902384204389");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("24098324984+09321499843248");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}

