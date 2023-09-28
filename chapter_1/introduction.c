// This may by default this will then open that script in the default editor
// So 2 slashes is how you do comments.
// The plan is to create loads of heavily commented scripts based off the course notes and this is how we'll learn
// Each weeks exercise / worksheets will be in seperate scripts.

// Firstly to create scripts via the console, simply cd over to directory you want to make the script in and enter:
// gedit name.c
// This may by default open that script in the default editor. On this course is recommended to use Nano. To open a script in nano simply do:
// nano name.c
// ... in the relevant directory
// If you already have a script of that name when you run gedit, this will open instead.

// Once you have created your own script you need to compile it as C is a compiled language (whereas Python is an interpreted i.e reads it as it goes along)
// This is done by running:
// clang name.c -o name_2
// This will create a .bin file called name_2 (I chose name_2 to show what the executable file is called, usually they are called the same thing)
// If you run pwd in console at this point you should see a new .bin file has been created. This means your code has compiled successfully and is ready to run.
// To run the compiled script simply run:
// ./name_2
// (Make sure you don't name your executable after a unix command.)

// Now let's look at some of the basic Syntax that will be ussed alot:

// Firstly let's look at notation types:
// We've seen that // is for single line comments.
// Paragraph comments (""" text """ in Python) are done as such:
/*
Like
This
*/

// Lines that start with # are preprocessor directives. These are special instructions that are processed before compilation takes place.
// The preprocessor is a part of the C compiler that performs text manipulation tasks on your source code that does not contain the directives or comments before it is passed into the compiler.
// A common example I think we'll see alot is:
#include <stdio.h>
// This is a built in header file in C. It stands for "Standard Input and Output" This header file contains 3 variable types, several macros and various functions for performing input and output.
// I'm not sure what any of these are and there are multiple types of preprocessor directives, let's look at the different types including #include:
/*

#include
This includes header files (libraries) in your program. Header files contain declerations of functions, conistants and data types your program may use.
As far as I can see this is the same as from ... import ... in Python

#define
This is used to define macros which are effectively text substitutions. This is what is used for defining variables at the start of scripts
e.g
#define PI 3.141

#ifdef, #ifndefm, #else, #elif, #endif
These directives are used for conditional compliation. I'm not sure when you'd only want to compile specific sections of your code uet. Hopefully we'll see more of this later on

There are a few more but, as previously mentioned, #include <stdio.h> is the main one that'll be use for now.
*/
// Now let's look at some code:






// When you define a function, you start with the expected output, 
//then you define the name and the input. 
//If there is no input put void, and there are no colons. 
//The contents of the functino are wrapped in curved braces
// All statements must end in a semicolon (;)
int hello(void)
{

printf("Hello World!\n")
return 0
}

// This is the most basic example. Most of the ideas in chapter 1  are pretty simple so i'll skip the notes and just go straight to worksheets.






