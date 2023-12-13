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

Before starting the CW, let's try and implement this simple parser
*/

#include "specific.h"