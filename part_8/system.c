#include "apue.h"
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>

int systemV1(const char *cmdstring){
    pid_t pid;
    int status;

    // 判断是否为空串
    if (cmdstring ==NULL){
        return(1);
    }

    if((pid = fork()) < 0 ){
        status = -1;
    }else if(pid == 0){
        execl("/bin/sh","sh","-c", cmdstring, (char *)0);

        // 直接退出不会flush
        _exit(127);
    }else{
        // 等待某一个进程，并设置状态
        /// 这也是和wait 的区别
       
        // while(waitpid(pid, &status,0) <0){
        //     if(errno != EINTR){
        //         status = -1;
        //         break;
        //     }
        // }
        
        waitpid(pid, &status,0);
        
    }

    return (status);
}
void pr_exit(int status){
    if (WIFEXITED(status)){
        printf("normal treminatrion exit status = %d\n",WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        printf("abnormal termination signal number = %d%s\n",WTERMSIG(status),
    
#ifdef WCOREDUMP 
    WCOREDUMP(status) ? "core file generated" : "" );
    }
#else 
    "");
    }
#endif 
    else if (WIFSTOPPED(status)) {
        printf("child stopped signal number = %d\n",WSTOPSIG(status));
    }
    
}

// system 相对于直接调用exec 和fork 多了一些错误处理
int main(void){
    int status;

    if ((status = system("date")) < 0){
        err_sys("system() error");
    }
    pr_exit(status);

    if((status = system("unkown cmd")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    // 获取到了退出状态码
    if((status = systemV1("who; exit 44")) < 0 ){
        err_sys("system() error");
    }
    
    pr_exit(status);

    exit(0);
}