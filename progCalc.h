/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef PROGCALC_H
#define PROGCALC_H

#include "stcalc.h"
#include "word.h"
#include "lex.h"
#include "FileStream.t"

class ProgCalc:public StCalc {
public:
  static const int MAXPROGRAM = 100;
  ProgCalc();
  ProgCalc(const ProgCalc &p);
  virtual ~ProgCalc();
  void load(FileStream<Word> &in);
  void run();
protected:
  Word* program;
  int progSize,pc,steps,tok,varCount,inp;
  //bool verbose;
  Tree<Word,int> addrTab,varTab; //addr = label tree, varTab = ident tree
									//when adding to varTab, make int = to index and
									//then increment index
  Lex lex,input;
  void checkLabel(const Word &w);
  void skipLabel();
  void checkForEnd();
  virtual void doLine();
  void endLine();
  void doEnter();
  virtual void doPush();
  void doPop();
  void doClear();
  void doArith();
  void doMemOp();
  void doJumps();
  void doGetScreen();
  void doStack();
  void setInput();
};
#endif
