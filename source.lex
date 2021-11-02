%{
/* Definitions section */
#include <string>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap

positiveDigit   ([1-9])
digit           ([0-9])
letter          ([a-zA-Z])
whitespace      ([\t\n\r ])
printable       ([\x20-\x7Ewhitespace])
escapeSequence  ((\[\"nrt0]) | (\xdigitdigit))

%%
 /* Rules section*/
{digit}+            return NUM;

%%
 /* Code section*/

