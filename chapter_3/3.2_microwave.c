#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define NO_SETTINGS 3
/*
The question explains this question really badly. However what it wants is for us to use the pre-set time increments (10 seconds, 1 min & 10 mins)
And make the most efficient way of reading the desired cooking time (not the minimum number of presses)

So 6mins 25seconds would be 6x1min + 3x10seconds

*/
int next_value(int time_settings[NO_SETTINGS], int *t_pointer, int *cook_instructions);

int main(void){
    /*
    General strategy is to take in a time and keep taking off the denominations in the mist efficent way until time is less than zero
    */
    int time = 0, times[NO_SETTINGS] = {600,60,10}, cook_instructions[NO_SETTINGS] = {0,0,0};
    int *p_time = &time;
    printf("How long are you cooking for?\n");
    scanf("%i",&time);
    // There is no simple way to sort an array (need a sort algorithm) so for now we'll just assume increments are entered in descending order
    while(time > 0){
	printf("%i\n",time);
	next_value(times, p_time , cook_instructions);
    }
    printf("%i, %i, %i\n", cook_instructions[0], cook_instructions[1], cook_instructions[2]);
}

int next_value(int time_settings[NO_SETTINGS], int *t_pointer, int *cook_instructions){
    int i;
    for(i = 0; i < NO_SETTINGS; i++){
	if(time_settings[i] < *t_pointer){
	    // Pretty much this is how you do a pointer to a value inside an array. In this function
	    // cook_instructions is already a pointer as seen in the function defintion 
	    // This means it doesnt know it is an array (only an int) so you can't use standard array notation (x[i])
	    // However you can exploit the fact that we know that array values are stored in successive bytes of memory
	    // as we can work out that cook_instructions[0] == *cook_instructions & cook_instructions[i] == *(cook_instructions + i)
	    *(cook_instructions + i) += 1;
	    *t_pointer -= time_settings[i];
	    return 0;
	}
    }
    *(cook_instructions + (NO_SETTINGS-1)) += 1;
    *t_pointer -= time_settings[NO_SETTINGS-1];
    return 0;
}
