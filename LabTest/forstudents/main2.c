#include "subseq.h"

// Returns the length of the longest sub-sequence that the 2 strings share
// e.g. for "qwedsccodingqwecx" and "nhjtoklcodingoj" the longest subsequence
// common to both is the 6 letter string "coding"

int subseq(const char s1[], const char s2[]);

int main(void)
{
   // We will use these, as well as other, similar examples to
   // test your code with.

   // dog
   assert(subseq("abdogba", "xydogyx")==3);
   // dog
   assert(subseq("abdobgadogc", "xzdogzx")==3);
   // dog different to DOG
   assert(subseq("abDOGba", "xydogyx")==0);
   // red
   assert(subseq("firedoor", "hundreds")==3);
   // whole
   assert(subseq("whole", "whole")==5);
   // empty string
   assert(subseq("abdogba", "")==0);
   // long one
   assert(subseq("itwasntthatatall", "--itwasntthatatal")==15);
   // above swapped argument order
   assert(subseq("--itwasntthatatal", "itwasntthatatall")==15);

   assert(subseq("wordabcwords","wordxyzwords") == 5);
   assert(subseq("thisisaword danotherword","thisisawordadanotherword") == 12);
   assert(subseq("abcdefghijklmnopqrstuvwxyz","zyxwvutsrqponmlkjihgfedcba") == 1);
}
