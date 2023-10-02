#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float diff_calc(float a, int b, int c){
    float calcd_value;
    calcd_value = a-((float)b / (float)c);
    calcd_value = fabs(calcd_value);
    // This function produces a float.
    // Whats the best way to write assertion tests to test float outputs 
    return calcd_value;

}

int main(void){
    int a, b, a_best, b_best;
    double lowest_diff = 100, value, diff;
    printf("Select a positive decimal and we'll find you the best matching fraction");
    scanf("%lf", &value);
    for(a = 1; a <= 100000; a++){
	for(b = 1; b <= 100000; b++){
	    diff = diff_calc(value,a,b);
	    if(diff < lowest_diff){
	        a_best = a;
		b_best = b;
		lowest_diff = diff;
	    }
	}
    }
    printf("Input Value: %lf\n", value);
    printf("Closest fraction was:\n");
    printf("%i / %i\n", a_best,b_best);
    printf("This is equal to: \r%.15g\n", ((float)a_best/(float)b_best));
    return 1;

}
