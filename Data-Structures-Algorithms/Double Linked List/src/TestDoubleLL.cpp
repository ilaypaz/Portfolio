#include "LinkedList.h"
#include <iostream>

using namespace std;

int main(){
    LinkedList list(5);

    list.ShowForward();
    list.ShowReverse();

    list.AddNode(2, 100);

    list.AddNode(4, 100);

    list.AddNodeFirst(100);
 list.AddNodeFirst(200);

    list.ShowForward();
    list.ShowReverse();

    cout << list.firstIndexOf(100) << endl;
    
    return 0;
}