#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int main()
{
    daemon(1,0);   
    //参数1若为0,守护进程将调用进程的当前工作目录为根目录；否则，当前工作目录将保持不变
    //参数2若为0,守护进程会将标准输入、标准输出、标准错误重定向至/dev/null;否则，这些文件描述符不变
    while(1)
    {
        sleep(2);
        cout << "123" <<endl;
    }
}
