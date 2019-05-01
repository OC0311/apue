#include "apue.h"

int f1 (int val ){
    int num = 0;
    int *ptr = &num;

    return *ptr+1;
}
int main(void){
    printf("%d",f1(1));
}