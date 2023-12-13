/*
Preamble:

This is the simplest parsing example. The grammar is as follows:
<PROG> ::= "BEGIN" <CODE>
<CODE> ::= "END" | <STATEMENT> <CODE>
<STATEMENT> ::= "ONE" | "NOUGHT"

Basically, the only valid setup is 
BEGIN
[series of NOUGHT and ONE]
END

The fact that the part of the grammar calls itself (CODE can be followed by CODE)
shows that parsing is recursive by nature. 

Before starting the CW, let's try and implement this simple parser.
*/

#include "specific.h"

int main(void){
    // Init space for the input script. 
    Program* prog = (Program*)calloc(1, sizeof(Program));
    int i = 0;
    // Clever little 1 line while loop, reads words in until it cant anymore
    while(scanf("%s", prog->words[i++]) == 1 && i<MAXTOKENS);

    printf("Parsed OK!");

    free(prog);
    return 0;
}
