/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "stcalc.h"

StCalc::StCalc():Calc() {
  index = 0;
  for (int i = 0; i < STACKSIZE; i++) {
    stack[i] = 0; //initialize all stack elements to 0
  }
}

StCalc::StCalc(const StCalc &c):Calc(c) {
  index = c.index; //index is equal to c's index
  for (int i = 0; i < STACKSIZE; i++) {
    stack[i] = c.stack[i]; //set all stack elements to their
			   //corresponding elements in c
  }
}

double StCalc::removeTop() {
  check(index >= 0, "STCALC::removeTop() no elements left in the stack");
  screen = stack[index];
  index--; //decrement index since there is one less element in the stack
  return screen;
}

StCalc& StCalc::push() {
  check(index < STACKSIZE, "STCALC::push() no more room in the stack");
  index++; //increment index before adding screen to the stack since
	   //we want the screen to be in the next position on the stack
  stack[index] = screen;
  return *this;
}

StCalc& StCalc::pop() {
  removeTop();
  return *this;
}

StCalc& StCalc::add() {
  check(index >= 1, "STCALC::add() not enough elements left in the stack");
  double first = removeTop();
  double second = removeTop();
  index++;
  stack[index] = first+second;
  return *this;
}

StCalc& StCalc::sub() {
  check(index >= 1, "STCALC::sub() not enough elements left in the stack");
  double first = removeTop();
  double second = removeTop();
  index++;
  stack[index] = second-first;
  return *this;
}

StCalc& StCalc::mul() {
  check(index >= 1, "STCALC::mul() not enough elements left in the stack");
  double first = removeTop();
  double second = removeTop();
  index++;
  stack[index] = first*second;
  return *this;
}

StCalc& StCalc::div() {
  check(index >= 1, "STCALC::div() not enough elements left in the stack");
  double first = removeTop();
  double second = removeTop();
  check(first != 0, "STCALC::div() division by 0"); //if first == 0,
						    //exit program
						    //because of
						    //division by 0
  index++;
  stack[index] = second/first;
  return *this;
}

ostream& operator <<(ostream &out, const StCalc &c) {
  out << "StCalc(" << c.screen << ")";
  return out;
}
