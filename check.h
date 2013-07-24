/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef CHECK_H
#define CHECK_H

#include <iostream>
using namespace std;

//Precondition: good reduces to a boolean expression and msg
//contains desired error message
//Postcondition: if bool is false, msg is printed as an error and
//the program exits
void check(bool b, char *msg);

#endif
