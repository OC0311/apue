#include "apue.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


void print_family(struct addrinfo  *aip){
    // TODO
}

void print_type(struct addrinfo *aip){
    // TODO
}

void print_protocol(struct addrinfo *aip){
    // TODO
}

void print_flags(struct addrinfo *aip){
    // TODO
}


int mian(int argc, char * argv[]){
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    const char *addr;
    int err;
    char abuf[INET_ADDRSTRLEN];

    if(argc != 3){
        err_quit("usage:%s nodename service", argv[0]);
    }

    // 过滤信息
    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 0;
    hint.ai_socktype = 0;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = 0;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if((err = getaddrinfo(argv[1], argv[2],&hint, &ailist))){
        err_quit("get addr info error:%s", gai_strerror(err));
    }

    // ailist 是一个链表
    for (aip = ailist; aip != NULL; aip=aip->ai_next){
        print_flags(aip);
        print_family(aip);
        print_type(aip);
        print_protocol(aip);
        printf("\n\thost %s",aip->ai_canonname ? aip->ai_canonname:"-");

        if(aip->ai_family == AF_INET){
            sinp = (struct sockadr_in *)aip->ai_addr;
            addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);

            printf("address %s", addr?addr:"unknow");
            printf("port %d", nhost(sinp->sin_port));
        }

        printf("\n");
    }

    exit(0);
}