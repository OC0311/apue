#include "apue.h"
#include <setjmp.h>
#include <sys/signal.h>
#include <unistd.h>

static jmp_buf env_alrm;
static void sig_int(int);

static void sig_alrm(int signo){
    printf("sig_alrm!!!\n");
    // 防止因为系统繁忙第一次alarm 在调用pause 之前超时
    // 不过会同样调用信号处理函数就会跳转到setjmp 处并且返回1 直接return掉
    longjmp(env_alrm, 1);
}

static void sig_alrm1(int signo){
    printf("sig_alrm!!!\n");
  
}


unsigned int sleep1(unsigned int seconds){
    if (signal(SIGALRM, sig_alrm1) == SIG_ERR){
        return (seconds);
    }

    alarm(seconds);
    pause();
    return (alarm(0));
}
unsigned int sleep2(unsigned int seconds){
    
    if (signal(SIGALRM, sig_alrm) == SIG_ERR){
        return (seconds);
    }

    // 从longjmp跳转过来后setjmp 的返回值为 >0 所以会直接return
    if (setjmp(env_alrm) == 0){
        alarm(seconds);
        // 等待时钟闹铃的信号
        // 同时也会接受到其他的信号提前终止（手动触发）
        pause();
    }
    // 手动或有剩余时间
    // 所以都要取消闹铃并将剩余的秒数返回
    return (alarm(0));
}

static void sig_int(int signo){
    int i,j;
    // 防止编译器优化，告诉编译器这个值是不稳定的，
    // 每次都重新读取这个值
    volatile int k;
   
    printf("\n sig_int starting\n");
    for(i = 0; i<30000000;i++){
        for(j = 0;j<4000;j++){
            k+=i*j;
        }
    }

    printf("sig_int fished\n");

}
int main(void){
    unsigned int unslept;

    if(signal(SIGINT,sig_int) == SIG_ERR){
        err_sys("signalk  (SIGINT) error");

    }
    unslept = sleep1(5);
    printf("sleep2 returned: %u\n", unslept);
    exit(0);


}



