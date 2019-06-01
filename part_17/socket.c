#include "apue.h"
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>

#define NQ 3
#define MAXMSZ 512
#define KEY 0x123

struct threadinfo{

    int qid;
    int fd;
};

struct mymesg {
    long mtype;
    char mtext[MAXMSZ];

};

void * helper(void *arg){
    int n;
    struct mymesg m;
    struct threadinfo *tip = arg;

    for(;;){
        // memset 将一块内存设置为一个指定的值
        memset(&m, 0, sizeof(m));
        // 需要注意文件描述符的权限问题
        // 可以用msgctl 等函数修改所有者

        // 接受消息
        if((n = msgrcv(tip->qid,&m,MAXMSZ,0,MSG_NOERROR)) <0){
            err_sys("msgrcv error");
        }

        // 将消息写入文件描述符
        if(write(tip->fd,m.mtext,n) < 0 ){
            err_sys("write error");
        }

    }
}


int main(){
    int i,n,err;
    int fd[2];
    int qid[NQ];
    struct pollfd pfd[NQ];
    struct threadinfo ti[NQ];
    pthread_t tid[NQ];
    char buf[MAXMSZ];

    // 每个队列对应一个POOL 处理
    for (i = 0; i < NQ; i++){
        // 创建一个消息队列的key
        if((qid[i] = msgget((KEY+1),IPC_CREAT|0666)) <0 ){
            err_sys("msgget error");
        }

        printf("queue ID %d is %d\n",i ,qid[i]);

        // 创建无命名的unix域套接字
        if(socketpair(AF_UNIX, SOCK_DGRAM,0,fd) <0 ){
            err_sys("sockpair error");
        }

        // 注册文件描述符和事件
        pfd[i].fd = fd[0];
        // 关心POLLIN事件
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];

        //  每个队列对应一个线程
        // 将参数用ti传到线程函数中
        // 
        if((err = pthread_create(&tid[i], NULL, helper, &ti[i])) != 0){
            err_exit(err, "pthread_create error");
        }

    }

    for(;;){
        // 初始化poll
        if(poll(pfd,NQ,-1) <0 ){
            err_sys("poll error");
        }

        for(i=0; i<NQ; i++){
            // revents 的作用是描述发生了那些事件
            if(pfd[i].revents & POLLIN){
                if((n = read(pfd[i].fd, buf, sizeof(buf))) < 0){
                    err_sys("read error");
                }

                // 标志结束
                buf[n] = 0;
                printf("queue id %d , message %s\n", qid[i], buf);
            }
        }
    }

    exit(0);
}