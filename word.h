/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#ifndef WORD_H
#define WORD_H

#include "check.h"

/*Grow words by increments of 10*/
class Word{
private:
  char *wd,*delimiters;
  int count,size;
public:
  static const int DEFAULT_SIZE=10;
  Word();
  Word(char *c,char *stoppers=" \t\n");
  Word(char c);
  Word(int x);
  Word(const Word&w);
  ~Word();
  int length()const;//return "count"
  int asInt()const;
  double asDouble()const;
  char * getStr()const;
  void setDelimiters(char *c);
  const Word& operator=(const Word &w);
  bool operator==(const Word&b)const;
  friend bool operator==(char * a, const Word &b);
  friend bool operator==(char a, const Word &b);
  bool operator!=(const Word &b)const;
  friend Word operator+(const Word &a, const Word &b);
  friend bool operator!=(char *a, const Word &b);
  friend bool operator!=(char a, const Word &b);
  friend bool operator<(const Word &a, const Word &b);
  friend bool operator<=(const Word &a, const Word &b);
  friend bool operator>(const Word &a, const Word &b);
  friend bool operator>=(const Word &a, const Word &b);
  friend ostream & operator<<(ostream &out,const Word &b);
  friend istream & operator>>(istream &in,Word &b);
  char operator[](int loc)const;
  char & operator[](int loc);
  Word & add(char ch);
private:
  void init(char *c,char *stoppers=" \t\n");
  void grow();
  bool stopCh(istream &in,char& ch);
};
  
#endif
