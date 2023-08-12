#include <stdio.h>
int getLongestSubString(char *s){

    int max = 0;
    int string[128] = {0};
    int *lo;
    int *hi;
    lo = s;
    hi = s;
    int low = 0, high = 0;

    while((hi) != '\0'){
        if(string[hi] == 0){
            string[hi] = 1;
            hi++;
        }
        else
            if(max < hi - lo){
                    max = hi - lo;
                    low = lo;
                    high = hi;
            }

            while(lo != hi){
                string[lo] = 0;
                lo++;
            }
            lo++;
            hi++;
            }
            return max < hi - low ? hi - low : max;
}

int main(){

    char in_string[200];

    scanf("%s", in_string);

    low = in_string;
    high = in_string;

    int a = getLongestSubString(in_string);

    for(int i = 1; i <= a; i++){
        printf("%c", *low);
        low++;
    }
    return 0;
}