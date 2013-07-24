/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "FprogCalc.h"

int main(int ct,char **arg){
  FileStream<Word> program(ct, arg);
  FProgCalc p;
  p.load(program);
  p.run();
}
