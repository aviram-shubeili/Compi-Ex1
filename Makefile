
all: hw1.out

lex.yy.c: scanner.lex
	flex scanner.lex

hw1.out: lex.yy.c hw1.cpp tokens.hpp
	g++ -std=c++17 hw1.cpp lex.yy.c  -o hw1.out


clean:
	rm hw1.out lex.yy.c