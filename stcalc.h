/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef STCALC_H
#define STCALC_H

#include "calc.h"

/*
  Represents a subclass of calculator that uses a stack to represent
  the memory locations
*/
class StCalc:public Calc{
public:
  static const int STACKSIZE = 20; //maximum size of the stack
private:
  int index; //current index of the stack. it is incremented and
	     //decremented accordingly in StCalc's member functions
  double stack[STACKSIZE]; //the stack of STACKSIZE elements
public:
  //Precondition: none
  //Postcondition: index is initialized to 0, the stack's elements are
  //all set to 0 and the superclass's constructor is called
  StCalc();
  //Precondition: c contains an initialized StCalc class
  //Postcondition: index is set to c's index, all of this stack's
  //values are set to c's stack's values and the superclass's copy
  //constructor is called with c as the parameter
  StCalc(const StCalc &c);
  //Precondition: index is between -1 and 19 (inclusive) and screen
  //contains a double value
  //Postcondition: screen's value is pushed into stack[index] and this
  //object is returned for further use
  StCalc& push();
  //Precondition: index is between 0 and 19 (inclusive)
  //Postcondition: stack[index] is removed from the stack, stored
  //in screen and this object is returned for further use
  StCalc& pop();
  //Precondition: index is between 1 and 19 (inclusive)
  //Postcondition: the top two values are removed from the stack,
  //added together and the result is pushed onto the stack. this object is
  //returned for further use
  StCalc& add();
  //Precondition: index is between 1 and 19 (inclusive)
  //Postcondition: the top two values are removed from the stack,
  //the first value is subtracted from the second and the result is
  //pushed onto the stack. this object is returned for further use
  StCalc& sub();
  //Precondition: index is between 1 and 19 (inclusive)
  //Postcondition: the top two values are removed from the stack,
  //multiplied together and the result is pushed onto the stack. this
  //object is returned for further use
  StCalc& mul();
  //Precondition: index is between 1 and 19 (inclusive)
  //Postcondition: the top two values are removed from the stack, the
  //second is divided by the first, and the result is pushed onto the
  //stack. division by 0 error is returned if the first value is
  //0. this object is returned for further use
  StCalc& div();
  //Precondition: c is an initialized StCalc object and out is the
  //disired ostream object
  //Postcondition: outputs the screen value of StCalc object c to out
  friend ostream& operator <<(ostream &out, const StCalc &c);
private:
  //Precondition: index is between 0 and 19 (inclusive)
  //Postcondition: removes and returns the top value on the stack
  double removeTop();
};

#endif
