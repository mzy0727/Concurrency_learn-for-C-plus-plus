#include<iostream>
#include<thread>
#include<string>
using namespace std;

void hello(string name){
    cout<<"Welcome to "<<name<<endl;
}

int main(){
    thread t(hello,"Hang Zhou");
    t.join();

    return 0;

}