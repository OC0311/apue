#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int);
static jmp_buf env_alrm;

static void sig_alrm(int signo){
    longjmp(env_alrm, 1);
}



int main(void){
    int n;
    char line[MAXLINE];
    if (signal(SIGALRM, sig_alrm) == SIG_ERR){
        err_sys("signal (SIGALRM) error");
    }

    if (setjmp(env_alrm) != 0){
        err_quit("read_timeout");
    
    }
    // 定时
    alarm(10);
    // 键盘十秒内不输入会导致超时
    // 触发sig_alrm信号 跳转到longjmp(）-> setjmp 第二次执行setjmp 返回1 立即退出执行
    if ((n = read(STDERR_FILENO, line,MAXLINE)) < 0){
        err_sys("read error");
    }

    alarm(0);
    write(STDOUT_FILENO, line, n);

    exit(0);

}