#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

enum triangle {equilateral,isosceles,scalene};
typedef enum triangle triangle;

// PROTOTYPES so the compiler can examine each of the functions seperately at the start 
triangle type(int a, int b, int c);
bool h_calc(int h, int o, int a);
bool r_angle(int a, int b, int c);

triangle type(int a, int b, int c){
    if(a == b && b == c){
	return equilateral;
    }
    if(a == b || a == c || b == c){
	return isosceles;
    }
    else{
	return scalene;
    }
}

bool h_calc(int h, int o, int a){
    float h_r = pow((pow(a,2) + pow(o,2)),0.5);
    if(h_r == (float)h){
        return true;
    }
    return false;
}



bool r_angle(int a, int b, int c){
    if(a > b && a > c){
	return h_calc(a, b, c);
    }
    if(b > a && b > c){
	return h_calc(b, a, c);
    }
    else{
	return h_calc(c, b, a);
    }
}


void test(){
    assert(type(3,3,3) == equilateral);
    assert(type(3,3,4) == isosceles);
    assert(type(3,4,5) == scalene);
    assert(h_calc(5,4,3) == true);
    assert(h_calc(3,4,5) == false);
    assert(r_angle(4,3,5) == true);

}

int main(){
    test();
    int a,b,c;
    printf("Enter the side lengths of your triangle");
    scanf("%i %i %i",&a,&b,&c);

    triangle t_type = type(a,b,c);
    bool right_angled = r_angle(a,b,c);

    printf("Triangle types:\n");
    printf("Equilateral = 0\n");
    printf("Isosceles = 1\n");
    printf("Scalene = 2\n\n");
    printf("Triangle type: %i\n",t_type);
    printf("Right Angled?\n");
    printf("%s\n", right_angled ? "true" : "false");



}


