#include "apue.h"

void pr_stdio(const char *,FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);


int main(void){
    FILE *fp;

    fputs("请输入一些字符\n",stdout);

    if (getchar() == EOF){
        err_sys("get char error");
    }

    fputs("一行标准错误\n",stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr",stderr);

    if ((fp =fopen("./a.tx","r")) == NULL){
        err_sys("fopen error");
    }

    if (getc(fp) ==EOF){
        err_sys("getc error");
    }

    pr_stdio("./a.out",fp);
    exit(0);
}


void pr_stdio(const char *name, FILE *fp){
    printf("stream = %s",name);

    if(is_unbuffered(fp)){
        printf("unbuffered");
    }else if(is_linebuffered(fp)){
        printf("line buffered");
    }else{
        printf("fully buffered");
    }

    printf(", buffered size = %d \n",buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)
int is_unbuffered(FILE *fp){
    return (fp->_flags & _IO_UNBUFFERED );
}

int is_linebuffered(FILE *fp){
    return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp){
    return (fp->_IO_buf_end - fp->_IO_buf_base );
}

#elif defined(_SNBF)
int is_unbuffered(FILE *fp){
    return (fp->_flags & _SNBF );
}

int is_linebuffered(FILE *fp){
    return (fp->_flags & _SNBF);
}

int buffer_size(FILE *fp){
   return (fp->_bf._size);
}

#elif defined(_IONBUF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _bvase __pad[2]
#endif

int is_unbuffered(FILE *fp){
    return (fp->_flags & _IONBUF );
}

int is_linebuffered(FILE *fp){
    return (fp->_flags & _IONBUF);
}

int buffer_size(FILE *fp){
#ifdef _LP64
    return (fp->_base - fp->_ptr);
#else
    return (BUFSIZ) ;
#endif
}

#else

//#error unknow stdio impl

#endif

