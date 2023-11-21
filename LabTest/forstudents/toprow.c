#include "toprow.h"
#define LOWER "qwertyuiop"
#define UPPER "QWERTYUIOP"
#define TOP_ROW_LEN 10

bool toprow(const char s[]){
    int len = strlen(s);
    for(int i = 0;i<len;i++){
        bool top_row = false;
        for(int j = 0;j<TOP_ROW_LEN;j++){
            if(s[i] == LOWER[j]){
                top_row = true;
                break;
            }
        }
        if(!top_row){
            for(int k = 0; k<TOP_ROW_LEN;k++){
                if(s[i] == UPPER[k]){
                    top_row = true;
                    break;
                }
            }
        }

        if(!top_row){
            return false;
        }
    }
    return true;
}
