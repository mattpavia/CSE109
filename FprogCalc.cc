/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "FprogCalc.h"

FProgCalc::FProgCalc():ProgCalc() {
}

FProgCalc::~FProgCalc() {
  delete []program;
}

void FProgCalc::doLine() {
  switch(tok){
  case Lex::ENTER: doEnter(); break;
  case Lex::PUSH: doPush(); break;
  case Lex::POP: doPop(); break;
  case Lex::CLEAR: doClear(); break;
  case Lex::PLUS:
  case Lex::MINUS:
  case Lex::TIMES:
  case Lex::DIVIDE: doArith(); break;
  case Lex::IDENTIFIER: doMemOp(); break;
  case Lex::JUMP:
  case Lex::JUMPL:
  case Lex::JUMPG:
  case Lex::JUMPLE:
  case Lex::JUMPGE:
  case Lex::JUMPE:
  case Lex::JUMPNE: doJumps(); break;
  case Lex::GETSCREEN: doGetScreen(); break;
  case Lex::STACK: doStack(); break;
  case Lex::DOLLAR: break;
  default: check(false,"(FProgCalc::doLine()) command expected");
  }
  endLine();
}

void FProgCalc::doJumps() {
  check(lex.peek() == Lex::IDENTIFIER, "FProgCalc::doJumps() invalid syntax");
  if (tok == Lex::JUMP) {
    tok = lex.next();
    pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPL) {
    tok = lex.next();
    if (screen < 0)
      pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPG) {
    tok = lex.next();
    if (screen > 0)
      pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPLE) {
    tok = lex.next();
    if (screen <= 0)
      pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPGE) {
    tok = lex.next();
    if (screen >= 0)
      pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPE) {
    tok = lex.next();
    if (screen == 0)
      pc = addrTab[lex.word()];
  }
  else if (tok == Lex::JUMPNE) {
    tok = lex.next();
    if (screen != 0)
      pc = addrTab[lex.word()];
  }
}

void FProgCalc::doPush() {
  if (lex.peek() != Lex::DOLLAR) {
    tok = lex.next();
    screen = doExpression();
  }
  push();
}

double FProgCalc::doExpression() {
  double result = doTerm();
  while (tok == Lex::PLUS || tok == Lex::MINUS) {
    if (tok == Lex::PLUS) {
      tok = lex.next();
      result += doTerm();
    } else if (tok == Lex::MINUS) {
      tok = lex.next();
      result -= doTerm();
    }
  }
  return result;
}

double FProgCalc::doTerm() {
  double result = doFactor();
  while (tok == Lex::TIMES || tok == Lex::DIVIDE) {
    if (tok == Lex::TIMES) {
      tok = lex.next();
      result *= doFactor();
    } else if (tok == Lex::DIVIDE) {
      tok = lex.next();
      double temp = doFactor();
      check (temp != 0, "FProgCalc::doTerm() division by zero");
      result /= temp;
    }
  }
  return result;
}

double FProgCalc::doFactor() {
  check(tok == Lex::LPAR || tok == Lex::IDENTIFIER || tok == Lex::NUMBER, "FProgCalc::doFactor() invalid syntax");
  double result = 0;
  if (tok == Lex::LPAR) {
    tok = lex.next();
    result = doExpression();
    check (tok == Lex::RPAR, "FProgCalc::doFactor() mismatched parentheses");
    tok = lex.next();
  } else if (tok == Lex::IDENTIFIER) {
	check(varTab.inTree(lex.word()), "FProgCalc::doFactor() invalid identifier");
    result = memory[varTab[lex.word()]];
    tok = lex.next();
  } else if (tok == Lex::NUMBER) {
    result = lex.word().asDouble();
    tok = lex.next();
  }
  return result;
}
