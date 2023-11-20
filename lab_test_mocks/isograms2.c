#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

#define ALPHABET 26
#define MAX_LEN 50

int isogram(char* s);

int main(int argc, char* argv[]){
    assert(isogram("programming") == 0);
    assert(isogram("housewarmings") == 0);
    assert(isogram("abductions") == 10);
    assert(isogram("housewarming") == 12);
    assert(isogram("hydromagnetics") == 14);
    assert(isogram("uncopyrightable") == 15);
    if(argc!=2){
        fprintf(stderr,"Invalid Usage\n");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen(argv[1], "r");
    if(file == NULL){
        fprintf(stderr,"Invalid file name\n");
        exit(EXIT_FAILURE);
    }
    char string[MAX_LEN], longest_string[MAX_LEN];
    int high_len = 0, temp_len = 0;

    while(fscanf(file, "%s", string) != EOF){
        temp_len = isogram(string);
        if(temp_len>high_len){
            strcpy(longest_string, string);
            high_len =  temp_len;
        }
    }
    printf("%s, (%i)\n", longest_string, high_len);
    


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
    bool isogram = true;
    for(int i = 0;i<ALPHABET;i++){
        if(hist[i]>1){
            isogram = false;
            break;
        }
    }
    if(isogram){
        return(len);
    }
    return 0;
    

}
