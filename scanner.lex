%{
/* Definitions section */
#include "tokens.hpp"
int handleSavedWords();
int handleSavedOperator();
%}
%x comment
%x string
%option yylineno
%option noyywrap

positiveDigit   ([1-9])
digit           ([0-9])
hexdigit        ([0-9A-F])
letter          ([a-zA-Z])
whitespace      ([\t\n\r ])
printable       ([\x20-\x7E]|whitespace)
escapeSequence  ((\[\"nrt0])|(\xdigitdigit))
savedWord (void|int|byte|b|bool|and|or|not|true|false|return|if|else|while|break|continue)
savedOperator (;|,|\(|\)|\{|\}|=)
relop (==|!=|<|>|<=|>=)
binop (\+|\-|\*|\/)


%%
 /* Rules section*/

{whitespace}                                                    ;
{savedWord}                                                     return handleSavedWords();
{savedOperator}                                                 return handleSavedOperator();
{relop}                                                         return RELOP;
{binop}                                                         return BINOP;
\/\/                                                            {
                                                                BEGIN(comment);
                                                                return COMMENT;
                                                                }
<comment>[^\n\r]                                                ; /* swallow rest of the line. */
<comment>[\n\r]                                                 BEGIN(INITIAL);
\"                                                              {
                                                                BEGIN(string);
                                                                }

<string>((\\\"))?(([^\\]\\\")|[(\x20-\x21\x23-\x7E)])*\"        {
                                                                BEGIN(INITIAL);
                                                                return STRING;
                                                                }
<string><<EOF>>                                                 return ERROR_UNCLOSED_STRING;
<string>[\n\r]                                                  return ERROR_UNCLOSED_STRING;
<string>.                                                       return ERROR_UNCLOSED_STRING;
{letter}+({digit}|{letter})*                                    return ID;
{positiveDigit}{digit}*|0                                       return NUM;
.                                                               return ERROR_INVALID_CHAR;

%%
 /* Code section*/

