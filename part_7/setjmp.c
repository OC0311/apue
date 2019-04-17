#include "apue.h"
#include <setjmp.h>

static void f1(int,int,int,int);
static void f2(void);

jmp_buf jmpbuffer;

static int globval;

// 使用gcc -O setjmp.c 可以进行全优化编译
// 自动变量和register变量都会变成原来的样子
int main(void){
   int autoval;
   register int regival;
   volatile int volaval;
   static int statval;
 
   globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;

    if (setjmp(jmpbuffer) != 0){
        printf("after longjmp :\n");
        printf("globval = %d; autoval = %d; regival = %d; volaval = %d; statval = %d;\n", globval,autoval,regival,volaval,statval);
        exit(0);
    }
    globval = 11; autoval = 22; regival = 33; volaval = 44; statval = 55;
    f1(autoval,regival,volaval,statval);
    return 0;
}

static void f1(int i,int j,int k,int l){
    printf("in f1():\n");
    printf("globval = %d; autoval = %d; regival = %d; volaval = %d; statval = %d;\n", globval,i,j,k,l);
    f2();
}

static void f2(void){
    longjmp(jmpbuffer,1);
}