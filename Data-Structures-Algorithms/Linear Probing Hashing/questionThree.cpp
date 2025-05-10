#include <iostream>
#include "HashingLinearProbingDemo.h"

using namespace std;

void findPairWithSum(HashingLinearProbingDemo &hashTable, int targetSum)
{
    for (int i = 0; i < hashTable.getHashTableSize(); i++)//iterate through array that you created that way its already sortred then use hashing to find the number you need to complete the pair
    {
        if (hashTable.getHashTable()[i] != 0)
        { 
            int complement = targetSum - hashTable.getHashTable()[i];
            if (hashTable.Search(complement))
            {
                cout << "Pair found (" << hashTable.getHashTable()[i] << ", " << complement << ")" << endl;
                return;
            }
        }
    }
    cout << "No pairs found" << endl;
}

int main()
{
    int size;
    double loadFactorThreshold;

    cout << "Enter size of hash table: "<<endl;
    cin >> size;
    cout << "Enter load factor threshold: "<<endl;
    cin >> loadFactorThreshold;

    HashingLinearProbingDemo hashTable(size, loadFactorThreshold);

    int numElements;
    cout << "Enter number of elements to insert: "<<endl;
    cin >> numElements;

    cout << "Enter the elements: "<<endl;
    for (int i = 0; i < numElements; i++)
    {
        int value;
        cin >> value;
        hashTable.Insert(value);
    }

    int targetSum;
    cout << "Enter target sum:<<endl ";
    cin >> targetSum;

    findPairWithSum(hashTable, targetSum);

    return 0;
}
