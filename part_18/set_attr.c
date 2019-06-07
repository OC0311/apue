#include "apue.h"
#include <termios.h>

int main(void){
    struct termios term;
    long vdisable;

    if (isatty(STDIN_FILENO) == 0){
        err_quit("未知的终端类型");
    }

    if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)) <0 ){
        err_quit("路径错误");
    }

    // 获取终端属性
    if (tcgetattr(STDIN_FILENO, &term) <0 ){
        err_sys("获取属性错误");
    }

    term.c_cc[VINTR] = vdisable;
    term.c_cc[VEOF] = 2;

    // 设置终端属性
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) <0 ){
        err_sys("设置属性错误");
    }

    // 尝试再次获取属性，与之前的对比来判断是否已经改变
}