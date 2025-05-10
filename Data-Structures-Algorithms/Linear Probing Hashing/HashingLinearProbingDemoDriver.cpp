#include "HashingLinearProbingDemo.h"
using namespace std;
#include <iostream>
int main(){
HashingLinearProbingDemo hashTable(10, 1.0);
hashTable.Insert(1);
hashTable.Insert(13);
hashTable.Insert(31);
hashTable.Insert(19);
hashTable.Insert(17);hashTable.Insert(1);
hashTable.Insert(14);
hashTable.Insert(10);

hashTable.Display();
hashTable.Search(10);
hashTable.Delete(10);
hashTable.Display();
    return 0;

}