#include "tokens.hpp"
#include <iostream>
#include <string>
using namespace  std;
int handleSavedWords() {
    return 12;
}
int handleSavedOperator() {
    return 23;
}

int main()
{

	int token;
	while(token = yylex()) {

	    cout << yylineno << " " << token << " value = " << yytext << endl;
	}
	return 0;
}