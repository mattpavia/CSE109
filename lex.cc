/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "lex.h"

Lex::Lex() {
  loc = 0;
  loadSymbols();
  loadKeyWords();
}

void Lex::loadSymbols() {
  //sets all the symbols to their token values
  symbols["+"] = 2;
  symbols["-"] = 3;
  symbols["*"] = 4;
  symbols["/"] = 5;
  symbols["["] = 9;
  symbols["]"] = 10;
  symbols["("] = 11;
  symbols[")"] = 12;
  symbols["$"] = 22;
  symbols[":"] = 26;
}

void Lex::loadKeyWords() {
  //sets all keywords to their token values
  keywords["clear"] = 6;
  keywords["getScreen"] = 7;
  keywords["enter"] = 8;
  keywords["push"] = 13;
  keywords["pop"] = 14;
  keywords["jump"] = 15;
  keywords["jumpL"] = 16;
  keywords["jumpG"] = 17;
  keywords["jumpLE"] = 18;
  keywords["jumpGE"] = 19;
  keywords["jumpE"] = 20;
  keywords["jumpNE"] = 21;
  keywords["end"] = 23;
  keywords["stack"] = 24;
}

void Lex::setString(Word w) {
  wd = w;
  wd.add('$'); //append a $ to the end to indicate the end of the input
  loc = 0; //reset the location back to 0
}

int Lex::next() {
  if (wd[loc] == '$')
    return Lex::DOLLAR;

  //ignore whitespace
  while(wd[loc] == ' ' || wd[loc] == '\t' || wd[loc] == '\n') {
    loc++;
  }
  str = "";
  
  //if the first character is a letter, go into getAlpha()
  if ((wd[loc] >= 'a' && wd[loc] <= 'z') || (wd[loc] >= 'A' && wd[loc] <= 'Z')) {
    return getAlpha();
  }
  //if the first character is a number, go into getNumber()
  else if ((wd[loc] >= '0' && wd[loc] <= '9') ) {
    return getNumber();
  }
  //else, go into getSymbol()
  else {
    return getSymbol();
  }
}

int Lex::getAlpha() {
  str.add(wd[loc]);
  loc++;
  while ((wd[loc] >= 'a' && wd[loc] <= 'z') || (wd[loc] >= 'A' && wd[loc] <= 'Z') || (wd[loc] >= '0' && wd[loc] <= '9')) {
    str.add(wd[loc]);
    loc++;
  }
  if (keywords.inTree(str)) {
    return keywords[str];
  } else {
    return Lex::IDENTIFIER;
  }
}

int Lex::getNumber() {
  str.add(wd[loc]);
  loc++;
  while ((wd[loc] >= '0' && wd[loc] <= '9')) {
    str.add(wd[loc]);
    loc++;
  }

  //if we exited the while loop, check to see if the next char is a ., then continue getting numbers
  if(wd[loc] == '.') {
    str.add(wd[loc]);
    loc++;
  }
  while ((wd[loc] >= '0' && wd[loc] <= '9')) {
    str.add(wd[loc]);
    loc++;
  }
  return Lex::NUMBER;
}

int Lex::getSymbol() {
  str = wd[loc];
  loc++; 
  if (symbols.inTree(str)) {
    return symbols[str];
  } else {
    return Lex::JUNK;
  }
}

int Lex::position() {
  return loc;
}

void Lex::reset(int p) {
  loc = p;
}

bool Lex::atEnd() {
  //if were at a $, were at the end of the input text
  if (wd[loc] == '$')
    return true;
  else
    return false;
}

Word Lex::word() {
  return str;
}

int Lex::peek() {
  //return next token but make sure to not change str or loc
  int tmp1 = loc;
  Word temp = str;
  int result = next();
  loc = tmp1;
  str = temp;
  return result;
}







