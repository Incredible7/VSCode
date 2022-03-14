#include <pthread.h>
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;

/*
    pthread_create是UNIX环境创建线程函数，共四个参数：
    第一个参数为指向线程标识符的指针，type：pthread_t *
    第二个参数用来设置线程属性
    第三个参数是线程运行函数的起始地址，type：(void *)(*)(void *)
    第四个参数是运行函数的参数，type：void *
*/

pthread_once_t once = PTHREAD_ONCE_INIT;

void once_run(void) {
    cout << "once_run in thread " << (unsigned int)pthread_self() << endl;
}

void *child1(void *arg) {
    pthread_t tid = pthread_self();
    cout << "thread " << (unsigned int)tid << " enter" << endl;
    pthread_once(&once, once_run);
    cout << "thread " << tid << " return" << endl;
}

void *child2(void *arg) {
    pthread_t tid = pthread_self();
    cout << "thread " << (unsigned int)tid << " enter" << endl;
    pthread_once(&once, once_run);
    cout << "thread " << tid << " return" << endl;
}

int main() {
    cout << "main thread: " << pthread_self() << endl;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, child1, NULL);
    sleep(3);
    pthread_join(tid1, NULL);
    pthread_create(&tid2, NULL, child2, NULL);
    sleep(3);
    cout << "main thread exit." << endl;
}