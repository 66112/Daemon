#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

using namespace std;
void handler(int signo)
{
    while(1){
        cout << "SIGCHLD " << endl;
        sleep(2);
    }
}
void Mydaemon()  //守护进程
{
    int fd0;
    pid_t pid = fork();
    if(pid > 0){
        exit(0);
    }
    setsid();       //新建会话,只能先fork(),再创建会话
    umask(0);       //将掩码设为0
    signal(SIGCHLD,handler);  //捕捉SIGCHLD信号
    if(chdir("/") < 0){  //将当前工作目录更改为根目录
        return;
    }
    close(0);  //关闭不需要的文件描述符
    fd0 = open("/dev/null",O_RDWR);  //重定向到垃圾桶中
    dup2(fd0,1);   //先关闭1号文件描述符,创建一个fd0文件描述符的副本为1,若输出，就输出到fd0中去了,类似重定向
    dup2(fd0,2);   //同上
}
int main()
{
    sleep(3);
    Mydaemon();
    while(1){
        sleep(1);
    }
}
