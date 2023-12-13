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

    Prog(prog);

    printf("Parsed OK!");

    free(prog);
    return 0;
}

// This is step 1 of the grammar, assert it starts with BEGIN (else error)
// If so proceed to Code function
void Prog(Program* p){
    if(strcmp("BEGIN", p->words[p->current_word])){
        fprintf(stderr, "No BEGIN statement!");
        exit(EXIT_FAILURE);
    }

    (p->current_word)++;
    Code(p);
}
// This is the general body of the code, refer to the grammar,
// Here the code either terminates or launches into a statement
void Code(Program* p){
    // First see if code is being terminated, if so return
    if(!strcmp("END", p->words[p->current_word])){
        return;
    }
    // If code doesn't terminate, then what follows must be a statement
    Statement(p);
    (p->current_word)++;
    // Then we recall Code (recursive) to see what happens next
    Code(p);

}

void Statement(Program* p){
    // See if statements are valid (bottom of the recurison)
    if(!strcmp("ONE", p->words[p->current_word])){
        return;
    }

    if(!strcmp("NOUGHT", p->words[p->current_word])){
        return;
    }

    fprintf(stderr, "Invalid Statement");
    exit(EXIT_FAILURE);
}
