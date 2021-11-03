#include "tokens.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

static vector<string> tokenNames;
vector<string> InitTokenNames();

void printToken(int token);

void handleString();

int main()
{
    tokenNames = InitTokenNames();
    int token;
    while(token = yylex()) {
        printToken(token);
    }
    return 0;
}

void printToken(int token) {
    if(token == STRING) {
        cout << yylineno << " " << tokenNames[token] << " " << yytext << endl;
//        handleString();
        return;
    }
    else {
        cout << yylineno << " " << tokenNames[token] << " " << yytext << endl;
    }
}

void handleString() {
    if(yyleng >= 2 and yytext[yyleng-2] == '\\') {
        // TODO: special case string ends with '\' :: handle error
    }
    string result;
    for (int i = 0; i <= yyleng - 2 /* last char is always the closing " */; ++i) {
        if (yytext[i] != '\\') {
            result += yytext[i];
        }
        else // i < yyleng - 2 because of the corner case taken care of at the start.
        {
            switch (yytext[i+1]) {
                case '\\':
                    break;
                case '"':
                    break;
                case 'n':
                case 'r':
                    break;
                case 't':
                    break;
                case '0':
                    break;
                case 'x':
                    break;
                default:
                    // TODO: error!!!
                    break;
            }
        }
    }
}
vector<string> InitTokenNames() {
    vector<string> result = vector<string>(30);
    result[VOID] = "VOID";
    result[INT] = "INT";
    result[BYTE] = "BYTE";
    result[B] = "B";
    result[BOOL] = "BOOL";
    result[AND] = "AND";
    result[OR] = "OR";
    result[NOT] = "NOT";
    result[TRUE] = "TRUE";
    result[FALSE] = "FALSE";
    result[RETURN] = "RETURN";
    result[IF] = "IF";
    result[ELSE] = "ELSE";
    result[WHILE] = "WHILE";
    result[BREAK] = "BREAK";
    result[CONTINUE] = "CONTINUE";
    result[SC] = "SC";
    result[COMMA] = "COMMA";
    result[LPAREN] = "LPAREN";
    result[RPAREN] = "RPAREN";
    result[LBRACE] = "LBRACE";
    result[RBRACE] = "RBRACE";
    result[ASSIGN] = "ASSIGN";
    result[RELOP] = "RELOP";
    result[BINOP] = "BINOP";
    result[COMMENT] = "COMMENT";
    result[ID] = "ID";
    result[NUM] = "NUM";
    result[STRING] = "STRING";
    return result;
}


int handleSavedWords() {
    if (strcmp(yytext,"void") == 0)     return VOID;
    if (strcmp(yytext,"int") == 0)      return INT;
    if (strcmp(yytext,"byte") == 0)     return BYTE;
    if (strcmp(yytext,"bool") == 0)     return BOOL;
    if (strcmp(yytext,"and") == 0)      return AND;
    if (strcmp(yytext,"or") == 0)       return OR;
    if (strcmp(yytext,"not") == 0)      return NOT;
    if (strcmp(yytext,"true") == 0)     return TRUE;
    if (strcmp(yytext,"false") == 0)    return FALSE;
    if (strcmp(yytext,"return") == 0)   return RETURN;
    if (strcmp(yytext,"if") == 0)       return IF;
    if (strcmp(yytext,"else") == 0)     return ELSE;
    if (strcmp(yytext,"while") == 0)    return WHILE;
    if (strcmp(yytext,"break") == 0)    return BREAK;
    if (strcmp(yytext,"continue") == 0) return CONTINUE;
    // should never get here.
    assert(false);

}
int handleSavedOperator() {
    if(strcmp(";",yytext) == 0) return SC;
    if(strcmp(",",yytext) == 0) return COMMA;
    if(strcmp("(",yytext) == 0) return LPAREN;
    if(strcmp(")",yytext) == 0) return RPAREN;
    if(strcmp("{",yytext) == 0) return LBRACE;
    if(strcmp("}",yytext)== 0) return RBRACE;
    if(strcmp("=",yytext)== 0) return ASSIGN;
    // should never get here.
    assert(false);
}
