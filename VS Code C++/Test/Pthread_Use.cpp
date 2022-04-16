#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <future>
#include <atomic>
#include <string>
#include <iostream>
using namespace std;

template <class... Args> decltype(auto) sum(Args &&... args) {
    // C++17折叠表达式
    // "0 +"避免空参数包错误
    return (0 + ... + args);
}

int main() {
    future<int> val = async(launch::async, sum<int, int, int>, 1, 10, 100);
    // future::get() 阻塞等待线程结束并获得返回值
    cout << val.get() << endl;
    return 0;
}
