/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef CALC_H
#define CALC_H

#include "check.h"

/*
  Represents a calculator with 10 memory locations to store partial
  calculations and a screen
*/
class Calc {
public:
  static const char ADD = 1;
  static const char MUL = 2;
  static const char SUB = 3;
  static const char DIV = 4;
protected:
  double screen; //the value on the screen
  double memory[10]; //the ten memory locations
public:
  //Precondition: none
  //Postcondition: A calculator is created with its screen set to 0
  //and 0s in all memory locations.
  Calc();
  //Precondition: c contains a Calc object with initialized fields
  //Postcondition: the memory locations of c and the screen of c are
  //coppied into this current object
  Calc(const Calc &c);
  //Precondition: num is a double to be entered onto the screen
  //Postcondition: the screen is replaced with num and the current
  //object is returned for further use
  Calc& enter(double num);
  //Precondition: none
  //Postcondition: screen is reset to 0
  void clear();
  //Precondition: none
  //Postcondition: returns the current value in the screen
  double getScreen() const;
  //Precondition: loc is between 0 and 9 (inclusive) and is the memory
  //location that is to be cleared
  //Postcondition: the supplied memory location is reset to 0 and the
  //current object is returned for further use
  Calc& memClear(int loc);
  //Precondition: loc is between 0 and 9 (inclusive) and is the memory
  //location to be added with the screen
  //Postcondition: the screen is added with the supplied memory
  //location and then stored back into the supplied memory location
  Calc& memAdd(int loc);
  //Precondition: loc is between 0 and 9 (inclusive) and is the memory
  //location to be moved to the screen
  //Postcondition: supplied memory location is stored on the screen
  Calc& memRem(int loc);
  //Precondition: type is between 1 and 4 (inclusive) and loc is the
  //memory location to manipulate with the screen (between 0 and 9 inclusive)
  //Postcondition: screen is changed based on the supplied
  //athrithmetic type and the given memory location
  Calc& opM(int type, int loc);
  //Precondition: num is a double
  //Postcondition: the supplied num is added to screen
  Calc& operator +(double num);
  //Precondition: num is a double
  //Postcondition: the supplied num is subracted from the screen
  Calc& operator -(double num);
  //Precondition: num is a double
  //Postcondition: the supplied num is multiplied with the screen
  Calc& operator *(double num);
  //Precondition: num is a non-zero double
  //Postcondition: the supplied num is divided with the screen
  Calc& operator /(double num);
  //Precondition: c is an initialized Calc object and in is the
  //desired istream object
  //Postcondition: reads in a double a stores it to the screen
  friend istream& operator >>(istream &in, Calc &c);
  //Precondition: c is an initialized Calc object and out is the
  //disired ostream object
  //Postcondition: outputs the screen value of Calc object c to out
  friend ostream& operator <<(ostream &out, const Calc &c);
};

#endif
