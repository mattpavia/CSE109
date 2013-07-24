/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "word.h"


Word::  Word(){
  init("");
}  
  

Word::Word(char *c,char *stoppers){
  init(c,stoppers);
}

Word::Word(const Word &w){
  init(w.wd,w.delimiters);
}

void Word::init(char *c,char *stoppers){
  char *temp="\0";
    if(c==NULL)
      c=temp;
    check(stoppers!=NULL,"(Word(char*, char*)) Null pointer");

    if(strlen(c)==0)
      size = DEFAULT_SIZE;
    else
      size = (strlen(c)+1+DEFAULT_SIZE)/DEFAULT_SIZE*DEFAULT_SIZE;
    /* size=strlen(c)==0 ? DEFAULT_SIZE :
       (strlen(c)+1+DEFAULT_SIZE)/DEFAULT_SIZE*DEFAULT_SIZE;*/

    wd=new char[size+1];
    check(wd!=NULL,"(Word(char*,char*)) heap overflow");
    delimiters=new char[strlen(stoppers)+1];
    check(delimiters!=NULL,"(Word(char*,char*)) heap overflow");
    strcpy(wd,c);
    strcpy(delimiters,stoppers);
    count=strlen(wd);

  }
  
  Word:: Word(char c){
    char temp[]={c,'\0'};
    init(temp);
  }

Word::Word(int x){
  int sz,temp;
  char *w;
  check(x>=0,"(Word(int)) Cannot have negative argument");
  temp=x;
  sz=0;
  if(temp==0)
    sz=1;
  while(temp>0){
    temp/=10;
    sz++;
  } 
  w=new char[sz+1];
  check(wd!=NULL,"(Word(int)) Heap overflow");
  w[sz]='\0';
  while(sz>0){
    sz--;
    w[sz]=x%10+'0';
    x/=10;
  }
  init(w);
}
    
Word::~Word(){
  //  cerr<<"delimiters: '"<<delimiters<<"'\n";
  //cerr<<int('@')<<endl;
  //cerr<<"NULL? "<<(wd==NULL)<<endl;
  //cerr<<"wd: "<<wd<<endl;
  delete [] wd;
  delete  []delimiters;
}

const Word &Word::operator=(const Word &w){
  if(this!=&w){
    delete []wd;
    wd=new char[w.size+1];
    check(wd!=NULL,"(Word::=) Heap overflow");
    size=w.size;
    count=w.count;
    strcpy(wd,w.wd);
  }
 return *this;  
}

int Word::asInt()const{
  int temp;
  check(wd!=NULL && count>0,"(Word::asInt()) Non integer string");
  temp=0;
  for(int j=0;j<count;j++){
    check(wd[j]>='0' && wd[j]<='9',"(Word::asInt()) Non integer string");
    temp=10*temp+wd[j]-'0';
  }
  return temp;
}

char * Word::getStr()const{
  char *temp;
  if(count==0)
    return "";
  temp=new char[count+1];
  check(temp!=NULL,"(getStr()) Heap overflow");
  for(int j=0;j<count;j++)
    temp[j]=wd[j];
  temp[count]='\0';
  return temp;
}

bool Word::operator==(const Word&b)const{
  return strcmp(wd,b.wd)==0;
}

bool Word::operator!=(const Word &b)const{
  return !(*this==b);
}

bool operator==(char * a, const Word &b){return Word(a)==b;}

bool operator==(char a, const Word &b){return Word(a)==b;}

bool operator!=(char *a, const Word &b){return Word(a)!=b;}

bool operator!=(char a, const Word &b){return Word(a)!=b;}

bool operator<(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)<0;
}

bool operator<=(const Word &a, const Word &b){
  return a<b || a==b;
}

bool operator>(const Word &a, const Word &b){
  return b<a;
}

bool operator>=(const Word &a, const Word &b){
  return !(a<b);
}

ostream & operator<<(ostream &out,const Word &b){
  out<<b.wd;
  return out;
}

istream & operator>>(istream &in,Word &b){
  char ch;
  b.count=0;
  while(!b.stopCh(in,ch))
    b.add(ch);

  return in;
}

Word & Word::add(char ch){
  if(count>size-1)
    grow();
  wd[count]=ch;
  count++;
  wd[count]='\0';
  return *this;
}

void Word::grow(){
  // cout<<"Growing: "<<wd<<", size="<<size<<endl;
  char *temp;
  size+=10;
  temp=new char[size+1];
  check(temp!=NULL,"(Word::grow()) heap overflow");
  //cout<<"'";
  // for(int j=0;j<10;j++)
  //cout<<(int)wd[j]<<" ";
  //cout<<"Growing: "<<wd<<endl;
  strcpy(temp,wd);
  //  cout<<":::"<<temp<<endl;
  delete [] wd;
  wd=temp;
  // cout<<"Leaving: "<<wd<<endl;
}

bool Word::stopCh(istream &in,char& ch){
  in.get(ch);
  if(!in.good())
    ch='\n';
  for(unsigned j=0;j<strlen(delimiters);j++)
    if(ch==delimiters[j])
      return true;
  return false;
}

char Word::operator[](int loc)const{
  check(loc>=0 && loc<count,"(Word::[]const) range error");
  return wd[loc];
}

char & Word::operator[](int loc){
    check(loc>=0 && loc<count,"(Word::[]) range error");
    return wd[loc];
}

void Word::setDelimiters(char *c){
  check(c!=NULL,"(Word::setDelimeters()) Null pointer");
  delete [] delimiters;
  delimiters=new char[strlen(c)+1];
  check(delimiters!=NULL,
	"(Word::setDelimeters()) Heap overflow");
  strcpy(delimiters,c);
}

int Word::length()const{
  return count;
}

double Word::asDouble()const{
  double fract,temp,divisor;
  int loc;

  check(wd!=NULL && count>0,"(Word::asDouble()) String is not a double");
  temp=0;
  loc=0;
  fract=0;

  check(wd[0]>='0' && wd[0]<='9',"(Word::asDouble()) String is not a double");
  while(loc<count && wd[loc]>='0' && wd[loc]<='9'){
    temp=10*temp+wd[loc]-'0';
    loc++;
  }
  check(loc>=count || wd[loc]=='.',
	"(Word::asDouble()) '.' or end of string expected");
  if(wd[loc]=='.'){
    loc++;
    check(loc<count && wd[loc]>='0' && wd[loc]<='9',
	  "(Word::asDouble()) digit expected");
    divisor=10;
    while(loc<count && wd[loc]>='0' && wd[loc]<='9'){
      fract+=(wd[loc]-'0')/divisor;
      divisor*=10;
      loc++;
    }
  check(loc>=count,"(Word::asDouble()) '.' or end of string expected");
  }
  return temp+fract;
}

Word operator+(const Word &a, const Word &b){
  Word temp("");
  temp.wd = new char[a.count + b.count + 1];
  strcpy(temp.wd,a.wd);
  strcat(temp.wd,b.wd);
  temp.count = a.count + b.count;
  return temp;
}
