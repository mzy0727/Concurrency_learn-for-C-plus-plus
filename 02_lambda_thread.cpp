#include <iostream>
#include <thread>

using namespace std;

int main(){
    thread t([] {
        cout << "hello lambda thread!"<<endl;
    }

    );
    t.join();

    return 0;
}