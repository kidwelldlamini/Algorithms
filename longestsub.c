#include <stdio.h>

int main(){
    char arr[1000];
    int current_char[999]={0};// all elements are initiailized to zero.
    int high_count = 0;

    int H_rangeLow=0,H_rangeHigh=0; //prints out the position.

    int min_count = 0; //section piece of code.

    fgets(arr,1000,stdin);

    for(int j = 0;j<999;j++){
        current_char[j] = 0;
    }
/
    for(int i = 0; i<1000;i++){
		if(arr[i]=='\0'){
            if(i - min_count > high_count){
                H_rangeLow = min_count;
                H_rangeHigh = i;
            }
            break;
        }

        if(current_char[arr[i]]){
            for(int j = 0;j<999;j++){
                current_char[j] = 0;
            }
            for(int j = min_count;j<i;j++){ 

                if(arr[j]==arr[i]){

                    if(i-min_count>high_count){
                        high_count = i-min_count;
                        H_rangeLow=min_count;
                        H_rangeHigh=i;

                    }
                    min_count = j + 1;
                    i = j;
                    break;
                }
            }
        }else{
            current_char[arr[i]] = 1;
        }
    }
    for(int n = H_rangeLow;n< H_rangeHigh;n++){
        printf("%c",arr[n]);
    }
    return 0;
}