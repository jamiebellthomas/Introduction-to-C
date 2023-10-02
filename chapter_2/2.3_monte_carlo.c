#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float rand_gen(void);
float dist_canc(float a, float b);

float rand_gen(void){
    float rand_p=2;
    // This randomly returns a value between 0 & 1
    // Below shows the mthod of converting an int to a float so you can do maths on them and return a float
    rand_p = (float)rand()/(float)RAND_MAX;
    return rand_p;
}


float dist_calc(float a, float b){
    float dist;
    // This simply calculates the distance between point and origin
    dist = pow((pow(a,2) + pow(b,2)),0.5);
    return dist;
}

int main(void){
    // initialise variables
    float point_x, point_y, pi_est,dist;
    int iterations = 0, circle_count = 0;
    // Iterations so amazingly quick on C!
    // Basically just loop round, get a new point each time and do the Monte Carlo equation...
    while(iterations < 10000000){
	++iterations;
	point_x = rand_gen();
	point_y = rand_gen();
	dist = dist_calc(point_x, point_y);
	if(dist <= 1.0){
	    ++circle_count;
	}
	pi_est = 4.0*((float)circle_count/(float)iterations);
	printf("\r%.15g",pi_est);
    }
    return 0;
}
