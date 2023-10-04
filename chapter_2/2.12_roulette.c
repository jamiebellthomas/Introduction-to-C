#include <stdlib.h>
#include <stdio.h>

int selection(){
    int val;
    val = RAND_MAX%35;
    return val;
}


int main(){
    int i, v;
    for(i=0;i<11,i++){
        v = selection();
	printf("%i",v);
    }
}
