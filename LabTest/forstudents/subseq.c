#include "subseq.h"

int subseq(const char s1[], const char s2[]){
    int longest = 0, len1 = strlen(s1), len2 = strlen(s2);
    printf("%i %i\n",len1,len2);
    for(int i = 0; i<len1;i++){
        for(int j = 0;j<len2;j++){
            if(s1[i] == s2[j]){
                int len = 1;
                bool matching = true;
                int index1 = i, index2 = j;
                if((index1 == (len1-1)) || (index2 == (len2-1))){
                    matching = false;
                }
                while(matching){
                    index1++;
                    index2++;
                    matching = (s1[index1] == s2[index2]);
                    
                    if(matching){
                        len++;
                    }
                    if((index1 == (len1-1)) || (index2 == (len2-1))){
                        matching = false;
                    }
                }
                if(len>longest){
                    longest = len;
                }

            }
        }
    }
    printf("%i\n", longest);
    return longest;
}


