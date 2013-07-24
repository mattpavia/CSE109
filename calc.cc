/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "calc.h"

Calc::Calc() {
  screen = 0;
  for (int i = 0; i < 10; i++) {
    memory[i] = 0;
  }
}

Calc::Calc(const Calc &c) {
  screen = c.screen;
  for (int i = 0; i < 10; i++) { //loop through all memory locations
				 //and set them equal to c's memory
				 //location values
    memory[i] = c.memory[i];
  }
}

Calc& Calc::enter(double num) {
  screen = num;
  return *this;
}

void Calc::clear() {
  screen = 0;
}

double Calc::getScreen() const {
  return screen;
}

Calc& Calc::memClear(int loc) {
  check(loc < 10 && loc >= 0, "CALC::memClear(loc) memory location invalid");
  memory[loc] = 0;
  return *this;
}

Calc& Calc::memAdd(int loc) {
  check(loc < 10 && loc >= 0, "CALC::memAdd(loc) memory location invalid");
  memory[loc] = memory[loc]+screen;
  return *this;
}

Calc& Calc::memRem(int loc) {
  check(loc < 10 && loc >= 0, "CALC::memRem(loc) memory location invalid");
  screen = memory[loc];
  return *this;
}

Calc& Calc::opM(int type, int loc) {
  check(loc < 10 && loc >= 0, "CALC::opM(type, loc) memory location invalid");
  //go through each arithmetic type and do desired opperation if its
  //type is supplied
  if (type == ADD) {
    screen += memory[loc];
  } else if (type == SUB) {
    screen -= memory[loc];
  } else if (type == MUL) {
    screen *= memory[loc];
  } else if (type == DIV) {
    check(memory[loc] != 0, "Calc::opM(type, loc) division by zero");
    screen /= memory[loc];
  }
  return *this;
}

Calc& Calc::operator +(double num) {
  screen += num;
  return *this;
}

Calc& Calc::operator -(double num) {
  screen -= num;
  return *this;
}

Calc& Calc::operator *(double num) {
  screen *= num;
  return *this;
}

Calc& Calc::operator /(double num) {
  check(num!=0, "CALC::Operator /(num) Division by 0");
  screen /= num;
  return *this;
}

istream& operator >>(istream &in, Calc &c) {
  double num;
  in >> num;
  c.screen = num; //since this method is not a member function, we
		  //have to call screen through c.screen
  return in;
}

ostream& operator <<(ostream &out, const Calc &c) {
  out << "Calc(" << c.screen << ")";
  return out;
}
