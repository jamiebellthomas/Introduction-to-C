#include "toprow.h"

// Checks whether a particular string can be typed
// using ONLY the keys on the top row of a keyboard
// i.e. qwertyuiopQWERTYUIOP 
bool toprow(const char s[]);

int main(void)
{

   // We will use these, as well as other, similar examples
   // to test your code with.

   // typewriter
   assert(toprow("typewriter")==true);
   // Torque
   assert(toprow("Torque")==true);
   // Equity
   assert(toprow("Equity")==true);
   // empty string
   assert(toprow("")==true);

   // FLASH
   assert(toprow("FLASH")==false);
   // typewriters
   assert(toprow("typewriters")==false);
   // tip-top
   assert(toprow("tip-top")==false);

   assert(toprow("qWeTRgyuIoP")==false);
   assert(toprow("QwErTyUiOp"));

}
