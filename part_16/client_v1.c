#include "apue.h"
#include <sys/socket.h>
#include <netdb.h>

#define MAXSLEEP 128
#define BUFLEN 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen){
    int numsec,fd;

    for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1){
        if ((fd = socket(domain, type ,protocol)) < 0){
            return -1;
        }

        if (connect(fd, addr, alen) == 0){
            return fd;
        }

        close(fd);

        if(numsec <= MAXSLEEP/2){
            sleep(numsec);
        }

    }

    return -1;
}

void print_uptime(int socketd){
    int n;
    char buf[BUFLEN];

    while ((n = recv(socketd, buf, BUFLEN,0)) > 0)
    {
        write(STDOUT_FILENO, buf, n);
    }

    if (n < 0){
        err_sys("recv error");
    }
    
}

int main(int argc, char * argv[]){
    struct addrinfo *ailist , *aip;
    struct addrinfo hint;
    int sockfd, err;

    if(argc != 2){
        err_quit("usage: ruptime hostname");
    }

    memset(&hint, 0, sizeof(hint));

    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    // 获取地址信息
    if((err = getaddrinfo(argv[1],"ruptime", &hint,&ailist)) != 0){
        err_quit("get addr info error:%s", gai_strerror(err));
    }

    for(aip = ailist; aip != NULL; aip = aip->ai_next){

        // 失败重试
        if((sockfd = connect_retry(aip->ai_family,0,SOCK_STREAM,aip->ai_addr, aip->ai_addrlen)) < 0){
            err = errno;
        }else{
            print_uptime(sockfd);
            exit(0); 
        }
    }

    err_exit(err, "can't connect to %s",argv[1]);
}

