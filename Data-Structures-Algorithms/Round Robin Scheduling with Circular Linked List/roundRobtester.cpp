#include <iostream>
#include "CircularList.h" 
using namespace std;

int main() {
    RoundRobinProcessScheduler scheduler;

    scheduler.LoadFromFile("process.txt");

    scheduler.ShowResults();

    return 0; // Remove the unnecessary semicolon
}
