// Ok let's try our first proper exercise
// Take in a user input of 3 intergers, double the sum then add the final entry
#include <stdio.h>

int main(void){
    //Firstly let's initialise our variables a,b&c
    int a,b,c;
    printf("Intput 3 integers:");
    //scanf reads in 3 integers and allocates them to a,b &c respectively
    scanf("%d %d  %d", &a, &b, &c);
    // a,b&c are then printed using formatted printing
    printf("\n%s %i %i %i", "Integers are:",a,b,c);
    // Do the relevant maths
    int sum = (2*(a+b+c))+c;
    // Print relevant information
    printf("\n%s %i %s %i\n","The sum of the integers plus",c,"is",sum);
    return 0;
}
