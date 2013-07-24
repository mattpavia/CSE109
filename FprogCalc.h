/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef FPROGCALC_H
#define FPROGCALC_H

#include "progCalc.h"

class FProgCalc:public ProgCalc {
public:
  FProgCalc();
  ~FProgCalc();
private:
  void doLine();
  void doJumps();
  void doPush();
  double doExpression();
  double doTerm();
  double doFactor();
};

#endif
