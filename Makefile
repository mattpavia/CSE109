/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

p8: p8.o progCalc.o FprogCalc.o lex.o calc.o stcalc.o word.o check.o
	g++ -o p8 p8.o progCalc.o FprogCalc.o lex.o calc.o stcalc.o word.o check.o

p8.o: p8.cc check.h calc.h stcalc.h FprogCalc.h word.h progCalc.h tree.t node.t
	g++ -c -Wall -Werror p8.cc

FprogCalc.o: FprogCalc.h FprogCalc.cc progCalc.h lex.h stcalc.h calc.h FileStream.t tree.t node.t check.h word.h
	g++ -c -Wall -Werror FprogCalc.cc

progCalc.o: progCalc.h progCalc.cc lex.h stcalc.h calc.h FileStream.t tree.t node.t check.h word.h
	g++ -c -Wall -Werror progCalc.cc

word.o: word.h word.cc check.h
	g++ -c -Wall -Werror word.cc

lex.o: lex.h lex.cc word.h
	g++ -c -Wall -Werror lex.cc

stcalc.o: stcalc.cc calc.h stcalc.h
	g++ -c -Wall -Werror stcalc.cc

calc.o: calc.cc check.h calc.h
	g++ -c -Wall -Werror calc.cc

check.o: check.cc check.h
	g++ -c -Wall -Werror check.cc

clean:
	rm -f *~ *.o p8
