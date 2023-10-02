#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

// These are prototypes. This let's the compiler look at all the functions individually in the script before they are called anywhere
float calc(float a);
float tolerance(float a);
void test();

float calc(float a){
    // First function calls the equation we are testing
    // As this is the test variable we cannot run assertions on
    float ans;
    ans = pow(sin(a),2) + pow(cos(a),2);
    return ans;
}

float tolerance(float a){
    // This tells the user the absolute difference between input float a and 1 and makes sure its is very very small
    float b = fabs(a-1.0);
    if(b < 0.0001){
	return true;
    }
    else{
	return false;
    }

}

void test(){
    /*
    You can't do this as you can't directly compare floats
    assert(calc(1.0) == 1.0)
    So we have to make seperate function that works out the diff and makes sure it is VERY small. 
    This will be tested here
    */
    assert(tolerance(1.0) == true);
    assert(tolerance(2.0) == false);

}

int main(){
    // Run all tests first
    test();
    // Input a value, run it through the calc function
    float x,y;
    printf("Input a value and we'll test the relationship:\n");
    printf("x^2 + y^2 = 1\n");
    scanf("%f",&x);
    y = calc(x);
    // run it through the toleranc function
    bool z = tolerance(y);
    // check it
    if(z == true){
	printf("Calculated value is: %f\n", y);
    }
    else{
	printf("Something has gone wrong");
    }
}
