/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include <iostream>
#include <fstream>
using namespace std;
#include "check.h"

template<class T>
class FileStream{
private:
  ifstream in;
  int count;
  char * fileName;
public:
  FileStream(int ct, char **arg);
  int countValues();
  bool good();
  template <class TYPE>
  friend ifstream & operator >> (FileStream<TYPE> &inp, TYPE &input); 
};


template<class T>
bool FileStream<T>::good(){
    return in.good();
}
	    

template <class T>
FileStream<T>::FileStream(int ct, char **arg){
  check(ct == 2,"(main()::fileStream(3 arg) constructor file not found");
  cout << "Opening file: '"<<arg[1]<<"'\n";
  in.open(arg[1]);
  check(in.good(),"Failure to open input file");
  fileName = arg[1];
  count = 0;
}

template <class TYPE>
ifstream & operator >> (FileStream<TYPE> &inp, TYPE &input){
  inp.in >> input;
  return inp.in;
}

template <class T>
int FileStream<T>::countValues(){
  count = 0;
  in.clear();
  in.seekg(0, std::ios_base::beg);
  T temp;
  while(in >> temp){
    count++;
  }
  in.clear();
  in.seekg(0, std::ios_base::beg);      
  return count;
}
  
  
  
