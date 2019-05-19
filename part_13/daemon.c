#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>
// 文件锁名称
#define LOCKFILE "/var/run/deamon.pid"
// 文件锁模式
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

sigset_t mask;

extern int lockfile(int);

void daemonize(const char *cmd){
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;

    // 清除之前可能设置的屏蔽字
    umask(0);

    // 检查最大打开文件数
    if (getrlimit(RLIMIT_NOFILE, &r1) < 0){
        err_quit("%s: can't fork", cmd);
    }else if (pid != 0){
        exit(0);
    }

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGHUP, &sa, NULL) <0 ){
        err_quit("%s: 忽略信号失败", cmd);
    }

    if((pid = fork()) < 0){
        err_quit("%s: 创建进程失败", cmd);
    }else if(pid != 0){
        // 父进程退出
        exit(0);
    }

    if(chdir("/") < 0){
        err_quit("%s: 切换目录失败");
    }

    if(r1.rlim_max == RLIM_INFINITY){
        r1.rlim_max = 1024;
    }

    // 关闭打开的文件描述符
    for (i = 0;i < r1.rlim_max; i++){
        close(i);
    }

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2){
        syslog(LOG_ERR, "错误的文件描述:%d,%d,%d",fd0,fd1,fd2);
        exit(1);
    }
}


// 只能运行一个副本
int already_running(void){
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if(fd <0){
        syslog(LOG_ERR, "无法打开文件%s:%s",LOCKFILE, string(errno));
        exit(1);
    }

    // 判断是否可以加锁成功
    if (lockfile(fd) < 0){
        if (errno == EACCES || errno == EAGAIN){
            close(fd);
            return (1);
        }
        syslog(LOG_ERR, "无法加锁:%s:%s",LOCKFILE, strerror(errno));
        exit(1);
    }
    // 截断文件
    ftruncate(fd,0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);
    return(0);
}


void reread(void){
    // TODO 重新读取文件
}


void * thr_fn(void *arg){
    int err ,signo;
    for(;;){
        // 就是等到信号没有别的意识
        err = sigwait(&mask, &signo);
        if (err != 0){
            err_exit(err, "sigwait failed");
        }

        switch(signo){
        // ctrl+c
        case SIGHUP:
            syslog(LOG_INFO, "重新加载配置文件");
            // 跳过该信号
            reread();
            break;
        // ctrl+\
    
        case SIGTERM:
            syslog(LOG_INFO, "收到 SIGERM 信号 exiting");
            exit(0);
        default:
            syslog(LOG_INFO, "不明信号：%d\n", signo);
        }

    }
}

int main(int argc,char *argv[]){
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa;

    if((cmd = strrchr(argv[0],'/'))){
        cmd = argv[0];
    }else{
        cmd ++;
    }

    daemonize(cmd);

    if (already_running()){
        syslog(LOG_ERR, "deamon already running");
        exit(1);
    }

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);

    sa.sa_flags = 0;
    if(sigaction(SIGHUP ,&sa, NULL)){
        err_quit("%s: 无法设置信号");
    }

    sigfillset(&mask);
    if((err = pthread_sigmask(SIG_BLOCK,&mask,NULL)) != 0){
        err_exit(err, "信号阻塞失败");
    }

    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0){
        err_exit(err, "无法创建线程");
    }

    exit(0);

}
