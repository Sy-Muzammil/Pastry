#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <unistd.h>
using namespace std;
void independentThread(string str) 
{
    std::cout << "Starting concurrent thread.\n";
    cout << str << endl;
    std::cout << "Exiting concurrent thread.\n";
}
 
void threadCaller() 
{
    std::cout << "Starting thread caller.\n";
    string str = "Hello";  
    thread t(independentThread,str);
    t.detach();
    std::cout << "Exiting thread caller.\n";
}
 
int main() 
{
    threadCaller();
    usleep(10000);
}