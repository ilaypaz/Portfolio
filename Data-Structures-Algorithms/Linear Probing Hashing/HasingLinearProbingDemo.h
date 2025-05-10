#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include <iostream>
#include <functional>
using namespace std;
class HashingLinearProbingDemo{
private:
    int *hashTable;
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold;

public:
    int* getHashTable() {
        return hashTable;
    }

    int getHashTableSize() {
        return hashTableSize;
    }
    HashingLinearProbingDemo()
    {
        hashTable = nullptr;
        hashTableSize = 0;
        numberOfKeys = 0;
        loadFactorThreshold = 1.0;
    }

    HashingLinearProbingDemo(int size, double lft)
    {
        hashTableSize = size;
        hashTable = new int[hashTableSize];
        for (int i = 0; i < hashTableSize; i++)
        {
            hashTable[i] = 0;
        }
        numberOfKeys = 0;
        loadFactorThreshold = lft;
    }
    void Insert(int value)
    {
        if (value == 0)
        {
            cout << "0 not allowed" << endl;
            return;
        }
        if (!Search(value))
        {                                                                          // if value is not a duplicate
            double currentLoadFactor = (double)(numberOfKeys + 1) / hashTableSize; // increase the the current load factor first and foremost
            if (currentLoadFactor > loadFactorThreshold)
            { // if its bigger than the load factor threshhold rehashing is necessary
            ReHash();
            }
            hash<int> builtInHashFunction; // initialize the hash function

            int hashCode = builtInHashFunction(value); // Generate a unique hash code for the value that will be used to determine the index in the hash table.

            int hashTableIndex = hashCode % hashTableSize; // he hash code is reduced to an index within the bounds of the hash table by taking the remainder when dividing by hashTableSize (using the modulus operator %).

            if (hashTable[hashTableIndex] == 0)
            { // this checks if the slot at the computed index hashTableIndex is empty
                // no collision
                hashTable[hashTableIndex] = value; // set the index to value
                numberOfKeys++;                    // increase key num
            }
            else
            {
                while (hashTable[hashTableIndex] != 0)                     // while there is no empty slot
                    hashTableIndex = (hashTableIndex + 1) % hashTableSize; // increase the position by 1 and modulus for when the reult becomes  larger than the size of the array
            }
        }
        else
        {
            cout << value << " already exists!" << endl;
        }
    }
    void Delete(int value)
    {
                hash<int> builtInHashFunction;             // initialize the hash function
        int hashCode = builtInHashFunction(value); // Generate a unique hash code for the value that will be used to determine the index in the hash table.
        int hindex = hashCode % hashTableSize;     // he hash code is reduced to an index within the bounds of the hash table by taking the remainder when dividing by hashTableSize (using the modulus operator %).
        int anchor = hindex;
        while (hashTable[hindex] != 0) // while there is no empty slot
            if (hashTable[hindex] == value)
            {
               hashTable[hindex]=0;
               numberOfKeys--;
               cout<<"value deleted and replaced with 0"<<endl;
    }
    if(hindex==anchor){
        cout<<"value does not exist"<<endl;
        return;
    }} 

void ReHash()
{
    int newSize = hashTableSize * 2;  // Double the size
    int *newTable = new int[newSize]; // Create a new hash table of double size
    for (int i = 0; i < newSize; i++)
    {
        newTable[i] = 0; // Initialize new table with 0s
    }

    for (int i = 0; i < hashTableSize; i++)
    { 
        if (hashTable[i] != 0 && hashTable[i] != -1) // Only rehash non-zero, non-deleted values
        {
            int value = hashTable[i];
            hash<int> builtInHashFunction; // initialize the hash function
            int hashCode = builtInHashFunction(value); // Generate unique hash code
            int newIndex = hashCode % newSize;         // Find new index

            while (newTable[newIndex] != 0)
            {                                        // Linear probing for the next free spot
                newIndex = (newIndex + 1) % newSize;
            }
            newTable[newIndex] = value; // Place the value in the new table
        }
    }

    delete[] hashTable; // Free old table memory
    hashTable = newTable;
    hashTableSize = newSize;
}


    bool Search(int value)
    {
        hash<int> builtInHashFunction;             // initialize the hash function
        int hashCode = builtInHashFunction(value); // Generate a unique hash code for the value that will be used to determine the index in the hash table.
        int hindex = hashCode % hashTableSize;     // he hash code is reduced to an index within the bounds of the hash table by taking the remainder when dividing by hashTableSize (using the modulus operator %).
        int anchor = hindex;
        while (hashTable[hindex] != 0) // while there is no empty slot
            if (hashTable[hindex] == value)
            {
                return true;
            }
        hindex = (hindex + 1) % hashTableSize; // increase the position by 1 and modulus for when the reult becomes  larger than the size of the array
        if (hindex == anchor)
        {
            return false;
        }

        return false;
    }
    void Display()
    {
        cout << "Table Contents and indices" << endl;
        for (int i = 0; i < hashTableSize; i++)
        {
            cout << "content in index" << i << "is" << hashTable[i] << endl;
        }
        cout << "current table size is" << hashTableSize << endl;
        cout << "There are " << numberOfKeys << "keys" << endl;
        cout << " load factor threshold is" << loadFactorThreshold << endl;
        cout << "currentload facror is" << (double)numberOfKeys / (double)hashTableSize << endl;
    }
};
#endif
