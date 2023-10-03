#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool prime(int num){
    int div;
    if(num==1){
        return false;
    }
    for(div = 2;div<num;++div){
        if(num%div == 0){
        return false;
        }
    }
    return true;
}


int main(void){
    // Let's start with C-V-C combinations as this is the larger search space
    char vowels[5] = {'a','e','i','o','u'};
    char consonants[21] =  {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
    int i1 ,i2, i_total = 1, sum;
    for(i1 = 0; i1 < 21; i1++){
        for(i2 = 0; i2 < 5; i2++){
            // The -180 is the ASCII shift for 3 numbers
	    sum = consonants[i1] + vowels[i2] + consonants[i1] - 288;
	    if(prime(sum) == true){
	        printf("%i - %c%c%c - Sum = %i\n",i_total++,consonants[i1],vowels[i2],consonants[i1],sum);

            }
        }
    }
    i1 = 0; i2 = 0;
    // Now let's do the V-C-V search space
    for(i1 = 0; i1 < 5; i1++){
        for(i2 = 0; i2 < 21; i2++){
            // The -180 is the ASCII shift for 3 numbers
            sum = vowels[i1] + consonants[i2] + vowels[i1] - 288;
            if(prime(sum) == true){
                printf("%i - %c%c%c - Sum = %i\n",i_total++,vowels[i1],consonants[i2],vowels[i1],sum);
            }
        }
    }
}
