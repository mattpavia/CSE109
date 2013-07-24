/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include <iostream>
using namespace std;

#include "tree.t"
#include "word.h"

//Creates a tokenizer for the PCalc and FPCalc languages
class Lex {
public:
  //token values
  static const int JUNK=-1, NUMBER = 0,IDENTIFIER = 1, PLUS=2, MINUS=3,TIMES=4,DIVIDE=5,CLEAR=6, GETSCREEN=7, ENTER=8, LBRACK=9, RBRACK=10, LPAR=11, RPAR=12, PUSH=13, POP=14, JUMP=15, JUMPL=16, JUMPG=17, JUMPLE=18, JUMPGE=19,JUMPE=20, JUMPNE=21,DOLLAR=22,END=23,STACK =24,COLON=26;
private:
  Tree<Word, int> keywords; //the list of keywords and their token values
  Tree<Word, int> symbols; //the list of symbols and their token values
  Word wd; //the full line of text that is read in
  Word str; //the current token
  int loc; //used for wd. initialize in no arg constructor
  int loc2; //used for str. initialize in no arg constructor
  //Precondition: none
  //Postcondition: loads all keywords into the keywords tree
  void loadKeyWords();
  //Precondition: none
  //Postcondition: loads all the symbols into the sumbols tree
  void loadSymbols();
  //Precondition: none
  //Postcondition: returns the token value of str if it is an identifier, symbol or keyword
  int getAlpha();
  //Precondition: none
  //Postcondition: returns the token value of str if it is a number
  int getNumber();
  //Precondition: none
  //Postcondition: returns the token value of str if it is a symbol, else return the token value of junk
  int getSymbol();
public:
  //Precondition: none
  //Postcondition: initializes this Lex object
  Lex();
  //Precondition: w is an initialized Word containing the string of text to be read in
  //Postcondition: wd is set to w and an $ is appended to the end
  void setString(Word w);
  //Precondition: none
  //Postcondition: returns the next token in wd
  int next();
  //Precondition: none
  //Postcondition: returns true if we are at the end of wd
  bool atEnd();
  //Precondition: p is either an int value or not present
  //Postcondition: resets the position of word to p, otherwise to 0 if p isnt supplied
  void reset(int p = 0);
  //Precondition: none
  //Postcondition: returns the current token in Word form
  Word word();
  //Precondition: none
  //Postcondition: returns the current position in wd
  int position();
  //Precondition: none
  //Postcondition: returns the next token in wd without changing wd or loc
  int peek();
};
