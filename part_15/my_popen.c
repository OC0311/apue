#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


// 保存子进程和文件描述符的关系
static pid_t *childpid = NULL;

static int maxfd;

FILE * popen(const char *cmdstring,const char *type){
    int i;
    int pfd[2];
    pid_t pid;
    FILE *fp;
    int index;
    char t;

    // 检查参数
    if ((type[0] != 'r' && type[1] != 'w' ) || type[1] !=0){
        errno = EINVAL;
        return (NULL);
    }

    // 
    if (childpid == NULL){
        maxfd = open_max();
        // 申请内存失败
        if((childpid = calloc(maxfd, sizeof(pid_t))) == NULL){
            return (NULL);
        }
    }

    if (pipe((pfd)) <0 ){
        retrn (NULL);
    }

    if (pfd[0] > maxfd || pfd[1] >= maxfd){
        close(pfd[0]);
        close(pfd[1]);
        errno = EMFILE;
        return (NULL);
    }

    if((pid = fork()) < 0){
        return (NULL);
    }else if(pid == 0){ // 子进程
        if (*type == 'r'){
            // 只读模式为输出
            close(pfd[0]);
            if(pfd[1] != STDOUT_FILENO){
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        }else{
            close(pfd[1]);
            // 写入模式则写入到标准输出中
            if(pfd[0] != STDIN_FILENO){
                dup2(pfd[0],STDIN_FILENO);
                close(pfd[0]);
            }
        }

    
        for (i = 0; i<maxfd;i++){
            if(childpid[i] > 0){
                close(i);
            }
        }

        // 子进程执行程序
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
    }

    if(*type == 'r'){
        close(pfd[1]);
        if ((fp = fdopen(pfd[0], type )) == NULL){
            return (NULL);
        }
    }else{
        close(pfd[1]);
        if ((fp = fdopen(pfd[1], type )) == NULL){
            return (NULL);
        }
    }

    childpid[fileno(fp)] = pid;
    return (fp);
}

int pclose(FILE *fp){
    int fd,stat;
    pid_t pid;

    if (childpid == NULL){
        errno = EINVAL;
        return (-1);
    }

    fd = fileno(fp);
    if (fd > maxfd){
        errno = EINVAL;
        return (-1);
    }

    if ((pid = childpid[fd]) == 0){
        errno = EINVAL;
        return (-1);
    }

    childpid[fd] = 0;
    if (fclose(fp) ==EOF){
        return (-1);
    }

    // 等到父进程结束
    // 使用while 循环只是为了避免受到信号
    // 如果受到信号只是再次调用waitpid
    while(waitpid(pid, &stat, 0) < 0){
        if (errno != EINVAL){
            return (-1);
        }
    }

    return (stat);

}
