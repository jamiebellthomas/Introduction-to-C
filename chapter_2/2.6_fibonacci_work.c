#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define PHI 1.61803398875
int floor_func(float a);

void test(void){
    assert(floor_func(2.89) == 2);
    assert(floor_func(-1.78) == -1);

}

int floor_func(float a){
    // This is a safe way to convery a float to an integer while saving the original variable
    // (It will always round down)
    int a_int = a;
    return a_int;
}

int calculator(int b){
    // This simply does the calcs
    printf("%f\n",PHI);
    int out = 2 + floor_func((float)b * PHI) - floor_func((float)(b+1) * PHI);
    return out;
}

int main(void){
    int val, out;
    // This takes in the input and runs it through the respective functions
    printf("Pick an number (int) and we'll return that digit of the Fibonnaci Alphabet sequence\n");
    scanf("%i", &val);
    out = calculator(val);
    printf("%i\n",out);
}
