#include "tokens.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
#include <sstream>

using namespace std;
std::vector<std::string> InitTokenNames();

static vector<string> tokenNames;

void printToken(int token);

void handleString();

string handleAsciiChar(char *escape_seq);

bool isError(int token);

void handleError(int token, char *cause_of_error);

bool stringEndsWithBackSlash(int yyleng, char *yytext);

int main()
{
    tokenNames = InitTokenNames();
    int token;
    while(token = yylex()) {
        if(isError(token)) {
            handleError(token, yytext);
        }
        printToken(token);
    }
    return 0;
}


bool isError(int token) {
    return token >= ERROR_UNCLOSED_STRING;
}

void handleError(int token, char *cause_of_error) {
    switch (token) {
        case ERROR_INVALID_CHAR:
            cout << "Error" << cause_of_error[0] << "\n";
            break;
        case ERROR_UNCLOSED_STRING:
            cout << "Error unclosed string\n";
            break;
        case ERROR_UNIDENTIFIED_ESCAPE_SEQUENCE:
            cout << "Error undefined escape sequence" << cause_of_error[0] << "\n";
            break;
        case ERROR_INVALID_ASCII_ESCAPE_SEQUENCE:
            cout << "Error undefined escape sequence " << cause_of_error[1] << cause_of_error[2];
            if(yyleng == 4) {
                cout << cause_of_error[3];
            }
            cout << "\n";
            break;
        default:
            //should never get here.
            assert(false);
            break;
    }
    exit(0);
}

void printToken(int token) {
    if(token == STRING) {
        handleString();
        return;
    }
    else {
        cout << yylineno << " " << tokenNames[token] << " " << yytext << endl;
    }
}


void handleString() {
    string result;
    for (int i = 0; i <= yyleng - 2 /* last char is always the closing " */; ++i) {
        if (yytext[i] != '\\') {
            result += yytext[i];
        }
        else if(i == yyleng - 2){
            handleError(ERROR_UNCLOSED_STRING, yytext);
        }
        else // start of escape sequence
        {
            switch (yytext[i+1]) {
                case '\\':
                    result += '\\';
                    break;
                case '"':
                    result += '\"';
                    break;
                case 'n':
                    result += '\n';
                case 'r':
                    result += '\r';
                    break;
                case 't':
                    result += '\t';
                    break;
                case '0':
                    result += '\0';
                    break;
                case 'x':
                    result += handleAsciiChar(yytext+i+1);
                    break;
                default:
                    handleError(ERROR_UNIDENTIFIED_ESCAPE_SEQUENCE, yytext + i + 1);
                    break;
            }
            i++;
        }
    }
}


string handleAsciiChar(char *ascii_chars) {
    /* right now we are dealing with invalid ascii sequence in the REGEX,
        i leave the handling in this function so if we will want to deal with invalid here
        it will be easier.
     */

    int ascii_value;
    char ascii_char[2];
    ascii_char[0] = ascii_chars[0];
    ascii_char[1] = ascii_chars[1];
    // this turn string of hex number to string of ascii representation.
    std::istringstream(ascii_char) >> std::hex >> ascii_value;
    string result;
    result += ((char)ascii_value);
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

std::vector<std::string> InitTokenNames() {
    std::vector<std::string> result = std::vector<std::string>(30);
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
