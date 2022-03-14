#include "Algorithm_in_Leetcode.h"
using namespace std;

struct Param{
    string name;
    int age;
};

void* param_test(void* p){
    Param* param = (Param*)p;
    cout<<"hello "<<param->name<<endl;
    cout<<"age = "<<param->age<<endl;
}

int main() {
    pthread_t tid;
    Param*ptr = new Param();
    ptr->name = "pthread";
    ptr->age = 20;
    pthread_create(&tid, NULL, param_test, ptr);
    pthread_join(tid, NULL);
}