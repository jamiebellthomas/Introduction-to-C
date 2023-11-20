#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define ALPHABET 26

int anagram(char s1[], char s2[]);


int main(void){
    assert(anagram("elvis","lives") == 1);
    assert(anagram("dreads","sadder") == 1);
    assert(anagram("replays","parsley") == 1);
    assert(anagram("listen","silent") == 1);
    assert(anagram("orchestra","carthorse") == 1);
    assert(anagram("elvis","elvis") == 0);
    assert(anagram("niell","neil") == 0);
    assert(anagram("short","horse") == 0);

}

int anagram(char s1[], char s2[]){
    int len1 = strlen(s1), len2 = strlen(s2);
    if(len1 != len2){
        return false;
    }
    if(!strcmp(s1,s2)){
        return false;
    }

    int hist1[ALPHABET], hist2[ALPHABET];
    for(int i = 0; i<ALPHABET; i++){
        hist1[i] = 0;
        hist2[i] = 0;
    }
    int int1, int2;
    for(int i = 0;i<len1 ;i++){
        int1 = s1[i] - 'a';
        int2 = s2[i] - 'a';
        (hist1[int1])++;
        (hist2[int2])++;
        
    }
    for(int i = 0; i<ALPHABET; i++){
        if(hist1[i] != hist2[i]){
            return false;
        }
    }
    
    return true;
}

