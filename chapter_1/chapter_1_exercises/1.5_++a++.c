// Read the code on the exercise sheet and determine what the values will be at the end of script 
// I think at the end:
// a = 5
// b = 2
// c = 2

#include <stdio.h>
int main(void){
	// Initialise a,b & c
	int a,b=0,c=0;
	// Here a = incremented b + incremented c = 1 + 1 = 2
	//a = 2, b = 1, c = 1
	a = ++b + ++c;
	printf("%s %i %i %i\n", "a,b,c=",a,b,c);
	// Here b & c are considered and then incremented
	// So a = 1+1 = 2
	// But now b = c = 2
	a = b++ + c++;
	printf("%s %i %i %i\n", "a,b,c=",a,b,c);
	// Here we increment b, add it to c and then increment c
	// a = 3 + 2 = 5
	// b = c = 3
	a = ++b + c++;
	printf("%s %i %i %i\n", "a,b,c=",a,b,c);
	// Here b is added to the decrement of c, b is then decremented itself
	// a = 3 + 2 = 5
	// b = c = 2
	a = b-- + --c;
	printf("%s %i %i %i\n","a,b,c=",a,b,c);
	return 0;
}

