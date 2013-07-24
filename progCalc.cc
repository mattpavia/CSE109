/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "progCalc.h"

ProgCalc::ProgCalc():StCalc() {

}

ProgCalc::ProgCalc(const ProgCalc &p) {
  program = p.program;
  progSize = p.progSize;
  lex = p.lex;
	input = p.input;
  tok = p.tok;
	progSize = p.progSize;
	pc = p.pc;
	varCount = p.varCount;
	steps = p.steps;
	inp = p.inp;
	addrTab = p.addrTab;
	varTab = p.varTab;
}

ProgCalc::~ProgCalc() {
	delete []program;
}

void ProgCalc::load(FileStream<Word> &in){
  progSize=0;    //keeps track of where to put line in program array
  varCount=0;    // keeps track of how many variables have been used
		 // for memory number
  cout<<"Loading:\n";
  int size = MAXPROGRAM;   // this will set array to 100, do not use countValue
  program = new Word[size]; // initializes the dynamic array program
			    // to have a size
  while(in.good() && progSize< size){  // keep reading lines from file
				       // while you have room in the
				       // program array and not at end
				       // of file
    program[progSize].setDelimiters("\n");  //sets the word that will
					    //read from the file to
					    //stop at end of line
    in>>program[progSize];       //in is a FileStream, we overloaded
				 //<< in FileStream and will read a
				 //full line not just one word because
				 //of setting delimiter
    cout<<progSize<<": "<<program[progSize]<<endl; //prints out
						   //program to screen
    checkLabel(program[progSize]);    //method that will tokenize the
				      //one line just to see if there
				      //is a label on the line IDENT
				      //COLON and if there is it will
				      //put label in label tree
    progSize++;                    
  }
  check(!in.good(),"(ProgCalc::load()) Program too large");
  setInput();     // this takes care of the numbers after the end,
		  // remember you don't have to have numbers after the
		  // end. I created another lex object and kept
		  // calling the .next function for that object
		  // everytime I encountered the enter with a blank
		  // after it
  checkForEnd();
  cout<<"Program successfully loaded...\n------------------------------\n";
}

void ProgCalc::run(){
  pc=0;
  cout<<"Running......\n";
  while(pc < progSize && program[pc] != "end") {
    lex.setString(program[pc]);          //lex is an object of type
					 //Lex that calls setString
					 //and reads in one line
    tok=lex.next();                      //get the first token for the line
    skipLabel();                        // skip over if tok is IDENT
					// and peek at next tok for
					// COLON if it is an label do
					// a tok = lex.next() twice to
					// get the next value on the line
    
    doLine();                           //this will process the tok
    check(tok==Lex::DOLLAR,"(ProgCalc::run()) end of line expected");
    pc++;
  }
}

void ProgCalc::checkForEnd() {
  int i = progSize-1;
  lex.setString(program[i]);
  tok = lex.next();
  while (tok == Lex::DOLLAR && i > 0) {
    i--;
    lex.setString(program[i]);
    tok = lex.next();
  }
  int temp = tok;
  lex.setString(program[i-1]);
  tok = lex.next();
  check(temp == Lex::END || tok == Lex::END, "No \"end\" found and end of input file");
}

void ProgCalc::doLine(){
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
  case Lex::JUMPG: doJumps(); break;
  case Lex::GETSCREEN: doGetScreen(); break;
  case Lex::STACK: doStack(); break;
  case Lex::DOLLAR: break;
  default: check(false,"(ProgCalc::doLine()) command expected");
  }
  endLine();
}

void ProgCalc::checkLabel(const Word &w) {
	lex.setString(w);
	tok = lex.next();
	if (tok == Lex::IDENTIFIER && lex.peek() == Lex::COLON) {
	  addrTab[lex.word()] = progSize;
	  tok = lex.next();
	  check (lex.peek() == Lex::DOLLAR, "ProgCalc::checkLabel() invalid syntax");
	}
}

void ProgCalc::skipLabel() {
	//if (addrTab.inTree(lex.word()) && lex.peek() == Lex::COLON) {
	if (tok == Lex::IDENTIFIER && lex.peek() == Lex::COLON) {
		tok = lex.next();
		tok = lex.next();
	}
}

void ProgCalc::doPush() {
	check (lex.peek() == Lex::DOLLAR,"ProgCalc::doPush() invalid syntax");
	push();
}

void ProgCalc::doPop() {
	check (lex.peek() == Lex::DOLLAR, "ProgCalc::doPop() invalid syntax");
	pop();
}

void ProgCalc::doGetScreen() {
	check (lex.peek() == Lex::DOLLAR, "ProgCalc::doGetScreen() invalid syntax");
	cout << getScreen() << endl;
}

void ProgCalc::doEnter() {
	if (lex.peek() == Lex::DOLLAR) {
		check (input.peek() != Lex::JUNK, "ProgCalc::doEnter() invalid input line");
		check (input.peek() != Lex::DOLLAR, "ProgCalc::doEnter() not enough input values");
		if (input.peek() == Lex::MINUS) {
			input.next();
			input.next();
			enter((-1)*(input.word().asDouble()));
		} else {
			input.next();
			enter(input.word().asDouble());
		}
	} else if (lex.peek() == Lex::IDENTIFIER) {
	  tok = lex.next();
	  check(varTab.inTree(lex.word()), "ProgCalc::doEnter() invalid identifier");
	  enter(memory[varTab[lex.word()]]);
	} else if (lex.peek() == Lex::MINUS) {
	  tok = lex.next();
	  check(lex.peek() == Lex::NUMBER, "ProgCalc::doEnter() invalid syntax");
	  tok = lex.next();
	  enter((-1)*(lex.word().asDouble()));
	} else if (lex.peek() == Lex::NUMBER) {
	  tok = lex.next();
	  enter(lex.word().asDouble());
	} else {
	  check (false, "ProgCalc::doEnter() invalid syntax");
	}
}

void ProgCalc::doClear() {
	check(lex.peek() == Lex::IDENTIFIER || lex.peek() == Lex::DOLLAR, "ProgCalc::doClear() invalid syntax");
	if (lex.peek() == Lex::DOLLAR) {
	  clear();
	} else {
	  tok = lex.next();
	  if (!varTab.inTree(lex.word())) {
	    varTab[lex.word()] = varCount;
	    varCount++;
	    check(varCount < 10, "Memory limit exceeded");
	  }
	  memory[varTab[lex.word()]] = 0;
	}
}

void ProgCalc::doStack() {
	check(lex.peek() == Lex::PLUS || lex.peek() == Lex::MINUS || lex.peek() == Lex::TIMES || lex.peek() == Lex::DIVIDE, "ProgCalc:doStack() invalid syntax");
	tok = lex.next();
	if (tok == Lex::PLUS) {
		add();
	} else if (tok == Lex::MINUS) {
		sub();
	} else if (tok == Lex::TIMES) {
		mul();
	} else {
		div();
	}
}

void ProgCalc::doArith() {
	check(lex.peek() == Lex::IDENTIFIER || lex.peek() == Lex::NUMBER, "ProgCalc::doArith() invalid syntax");
	if (tok == Lex::PLUS) {
		tok = lex.next();
		if (tok == Lex::IDENTIFIER) {
			screen += memory[varTab[lex.word()]];
		} else {
			screen += lex.word().asDouble();
		}
	}
	else if (tok == Lex::MINUS) {
		tok = lex.next();
		if (tok == Lex::IDENTIFIER) {
			screen -= memory[varTab[lex.word()]];
		} else {
			screen -= lex.word().asDouble();
		}
	}
	else if (tok == Lex::TIMES) {
		tok = lex.next();
		if (tok == Lex::IDENTIFIER) {
			screen *= memory[varTab[lex.word()]];
		} else {
			screen *= lex.word().asDouble();
		}
	}
	else if (tok == Lex::DIVIDE) {
		tok = lex.next();
		if (tok == Lex::IDENTIFIER) {
			screen /= memory[varTab[lex.word()]];
		} else {
			screen /= lex.word().asDouble();
		}
	}
}

void ProgCalc::doMemOp() {
	check(lex.peek() == Lex::PLUS, "ProgCalc::doMemOp() invalid syntax");
	if (!varTab.inTree(lex.word())) {
	  varTab[lex.word()] = varCount;
	  memory[varTab[lex.word()]] = 0;
	  varCount++;
	  check(varCount < 10, "Memory limit exceeded");
	}
	memory[varTab[lex.word()]] += screen;
	tok = lex.next();
}

void ProgCalc::doJumps() {
	check(lex.peek() == Lex::IDENTIFIER, "ProgCalc::doJumps() invalid syntax");
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
}

void ProgCalc::endLine() {
	if (tok != Lex::DOLLAR)
		tok = lex.next();	
}

void ProgCalc::setInput() {
  int i = 0;
  lex.setString(program[i]);
  tok = lex.next();
  while (tok != Lex::END && i < progSize) {
    i++;
    lex.setString(program[i]);
    tok = lex.next();
  }
  input.setString(program[i+1]);
}
