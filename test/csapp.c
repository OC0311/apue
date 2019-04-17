#include <stdio.h>

typedef struct 
{
    int a[2];
    double d;

}struct_t;

double fun(int i){
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 2147477732;
    return s.d;

}
int
main(void){
    printf("∂%f",fun(0));
    printf("∂%f",fun(1));
    printf("∂%f",fun(2));
    printf("∂%f",fun(3));
    printf("∂%f",fun(4));
    printf("∂%f",fun(5));
    printf("∂%f",fun(6));
}

#include <stdio.h>

int
main(void){
    printf("%d",1<<1);
    return 0;
}