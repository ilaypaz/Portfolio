#ifndef CHAINING_H
#define CHAINING_H
#include "Node.h"
#include "SkipList.h"
#include "functional"
using namespace std;
#include <iostream>
class Chaining
{
private:
    vector<SkipList> hashTable;
    int hashTableSize;
    double loadFactorThreshold;
    int numberOfKeys;

    int HashFunction(int value)
    {
        hash<int> builtInHashFunction; // initialize the hash function

        int hashCode = builtInHashFunction(value); // Generate a unique hash code for the value
        int hindex = hashCode % hashTableSize;     // Calculate the index using mod operation
        return hindex;
    }

public:
    Chaining(int size, double threshold)
    {
        hashTableSize = size;
        loadFactorThreshold = threshold;
        numberOfKeys = 0;
        hashTable.resize(hashTableSize, SkipList(3));
    }

    void Insert(int value) // insert a value into the hash table
{
    if (value == 0) // if user tries 0, give an error
    {
        cout << "0 not allowed" << endl;
        return;
    }

    // Check if the load factor threshold is exceeded
    if ((numberOfKeys + 1) / (double)hashTableSize > loadFactorThreshold) // rehash vector if needed
    {
        ReHash();
    }

    int index = HashFunction(value); // find where to place the int

    // Only insert if the value does not already exist at the calculated index
    if (!hashTable[index].Search(value)) 
    {
        hashTable[index].InsertElement(value); // Insert into the correct index's skip list
        numberOfKeys++; // Increase the number of keys 
    }
    else
    {
        cout << value << " already exists in the hash table." << endl; // Notify if value already exists
    }
}


    void Delete(int value)
    {
        int index = HashFunction(value); // tell you where to start looking for the item you want to delete
        hashTable[index].Delete(value);
        numberOfKeys--;
    }

    bool Search(int value)
    {
        int index = HashFunction(value);
        return hashTable[index].Search(value);
    }

    void ReHash()
    {
        int newSize = hashTableSize * 2;
        vector<SkipList> newHashTable(newSize, SkipList(3));

        for (int i = 0; i < hashTableSize; i++)
        {
            Node *current = hashTable[i].head->next[0]; // add the old nodes back to
            while (current != nullptr)
                ;
            {
                int newIndex = current->value % newSize;
                newHashTable[newIndex].InsertElement(current->value);
                current = current->next[0];
            }
        }

        hashTable = newHashTable;

        hashTableSize = newSize;
    }

    void Display()
    {
        for (int i = 0; i < hashTableSize; i++)
        {
            cout << "Index " << i << ": " << endl;
            hashTable[i].Show();
        }
        cout << "Current Table Size: " << hashTableSize << endl;
        cout << "Number of Keys: " << numberOfKeys << endl;
        cout << "Current Load Factor: " << (double)numberOfKeys / hashTableSize << endl;
        cout << "Load Factor Threshold: " << loadFactorThreshold << endl;
    }
};
#endif
