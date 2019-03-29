#include "apue.h"

// ./a.out < seek.c
// cat < /etc/passwd | ./a.out

int main(){
    // SEEK_CUR当前offset 加上offset
     if (lseek(STDIN_FILENO,0,SEEK_CUR)){
         printf("no");
     }else{
         printf("yes");
     }
     printf("%s","test")
    return 0;
}