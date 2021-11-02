#include "tokens.hpp"
#include <iostream>
#include <string>
using namespace  std;


int main()
{
	int token;
	while(token = yylex()) {

	    cout << yylineno << " " << token << " value = " << yytext << endl;
	}
	return 0;
}