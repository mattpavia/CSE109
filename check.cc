/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "check.h"

void check(bool b, char *msg){
  if(!b){
    cerr<<"ERROR: "<<msg<<endl;
    exit(1);
  }
}
