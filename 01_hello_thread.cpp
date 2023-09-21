#include <iostream>
#include <thread>

using namespace std;

void hello(){
    cout<< "Hello thread!"<<endl;
}

int main(){
    thread t(hello);

    t.join();

    return 0;
}