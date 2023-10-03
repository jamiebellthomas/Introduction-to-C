#include <stdio.h>
#include <stdlib.h>

int main(void){
    // Initialise the vowels and consonants arrrays then we'll just do a triple nested for loop to get all combos
    char vowels[5] = {'a','e','i','o','u'};
    char consonants[21] =  {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
    int i1 ,i2 ,i3, i_total = 1;
    for(i1 = 0; i1 < 21; i1++){
	for(i2 = 0; i2 < 5; i2++){
	    for(i3 = 0; i3 < 21;i3++){
	        printf("%i %c%c%c\n",i_total++,consonants[i1],vowels[i2],consonants[i3]);
	    }
	}
    }
}
