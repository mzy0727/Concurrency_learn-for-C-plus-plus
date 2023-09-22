#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex> // 添加互斥锁头文件

using namespace std;

static const int MAX = 10e8;
static double sum = 0;
static mutex sum_mutex; // 声明一个互斥锁

void worker(int min, int max) {
    for (int i = min; i <= max; i++) {
        double sqrt_i = sqrt(i);
        // 使用互斥锁保护对 sum 的访问
        lock_guard<mutex> lock(sum_mutex);
        sum += sqrt_i;
    }
}

void serial_task(int min,int max){
    auto start_time = chrono::steady_clock::now();
    sum = 0;
    worker(0,MAX);
    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
    cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

void concurrent_task(int min, int max){
    auto start_time = chrono::steady_clock::now();
    
    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;
    min = 0;
    sum = 0;
    for(int t = 0; t < concurrent_count; t++){
        int range = max / concurrent_count * (t + 1);
        threads.push_back(thread(worker,min,range));
        min = range + 1;
    }
    for(int i = 0; i < threads.size(); i++){
        threads[i].join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;

}


int main(){

    serial_task(0, MAX);
    concurrent_task(0, MAX);


    return 0;
}
