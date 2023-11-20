#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define ALPHABET 26

int isogram(char* s);

int main(void){
    assert(isogram("programming") == 0);
    assert(isogram("housewarmings") == 0);
    assert(isogram("abductions") == 1);
    assert(isogram("housewarming") == 1);
    assert(isogram("hydromagnetics") == 1);
    assert(isogram("uncopyrightable") == 1);

}


int isogram(char* s){
    int hist[ALPHABET], len = strlen(s),index;
    for(int i = 0;i<ALPHABET;i++){
        hist[i] = 0;
    }
    for(int i = 0;i<len;i++){
        index = s[i] - 'a';
        (hist[index])++;
    }

    for(int i = 0;i<ALPHABET;i++){
        if(hist[i]>1){
            return 0;
        }
    }
    return 1;

}
