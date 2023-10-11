#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct user_input {int guess; int amount; bool valid;};
typedef struct user_input user_input;


int selection(){
    int val;
    val = (rand())%35;
    return val;
}

char user_guess(void){
    user_input input;
    printf("----------\n");
    printf("Enter a guess followed by the bet\n");
    printf("A guess can either odd or even (o or e) or a specific number (0-35)\n");
    printf("Example inputs:\n");
    printf("e 50\n");
    printf("21 50\n");
    printf("----------\n\n");

    scanf(

}



int main(){
    user_input input;
    char guess[GUESS_LEN];
    guess = user_guess();
    snprintf(guess, GUESS_LEN);
}
