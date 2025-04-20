#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
//#include <cstring>
//#include <climits>
#include "Node.h"

#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList
{
public:
    // Maximum allowed level index
    int MAXIMUM_ALLOWED_LEVEL_INDEX; // maximum you will allow the skip list to grow to

    // current maximum level amongst the inserted nodes
    int currentHighestLevelIndex; // traces how many levels you have created and what within the skip list is the highest level

    // the head node's next links are connected to the first node at every level
    Node *head;

    SkipList(int maxLevels)
    {
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels; // how high up can you tolerate the coin flipping

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;

        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS), number of next links is important (initially this node is the first node at every level)
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
    }

    int RandomLevel()
    {
        float probablity = (float)rand() / RAND_MAX; // flip a coin in a perfect world you'll land head one time and tail the next time So you flip a coin to see which nodes are going up to the next level
        int lvl = 0;
        while (probablity < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX)
        {
            lvl++;                                 // landed heads so increase level by 1
            probablity = (float)rand() / RAND_MAX; // flip a coin again
        }
        return lvl;
    }

    Node *CreateNode(int value, int level)
    {
        // create a new node with next links for every level that this node will be part of
        // it will use these links to connect to the next node at each level
        return new Node(value, level);
    }

    void InsertElement(int value)//this is the insert method
    {                                                                    // value is 20
        Node *current = head;                                            // start at head node
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr); // this will hold the nodes that need updating at every level after the insert takes place, needed to keep track
        /*Olog(n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--)
        { // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible
            update[i] = current;
        }

        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to where the value is to be inserted to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0];

        if (current == nullptr || current->value != value)
        {                                 // eliminate duplicate or cvheck if  it is empty
            int ranLevel = RandomLevel(); // choose a random level upto where the new node will be placed

            if (ranLevel > currentHighestLevelIndex)
            {
                // if random level for current node is higher than the current maximum level for existing nodes; then set head as the node after which the new value is to be inserted for each level over current maximum to the level chosen for new value to be inserted (update currently contains nulls for these level(s)).
                for (int i = currentHighestLevelIndex + 1; i <= ranLevel; i++)
                {
                    update[i] = head; // put head on existing currebnt levels
                }

                // also change the current maximum level for the existing nodes
                currentHighestLevelIndex = ranLevel;
            }

            // create new node with next links for every level from ranLevel to zero
            Node *n = CreateNode(value, ranLevel);

            // placing new node in the correct place at every level
            for (int i = 0; i <= ranLevel; i++)
            {                                    // insert loop factoring in the level , makes a node be placed on ALL levels it was assigned from rand level
                n->next[i] = update[i]->next[i]; // nodes next is null
                update[i]->next[i] = n;          // previous  will point to the thing we are adding
            }
        }
    }

    void Delete(int value)
    {
        Node *current = head;                                            // start at head node
        vector<Node *> update(MAXIMUM_ALLOWED_LEVEL_INDEX + 1, nullptr); // this will hold the nodes that need updating at every level after the insert takes place, needed to keep track
        /*Olog(n)*/ for (int i = currentHighestLevelIndex; i >= 0; i--)
        { // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be deleted here then find out where (the node before ther node we want)
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            // found the node after which the value is to be placed at level i, move down a level, if possible
            update[i] = current;
        }
        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to where the value is to be inserted to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0];
        if (current != nullptr || current->value == value)
        { // eliminate duplicate or cvheck if  it is empty
            for (int i = 0; i <= currentHighestLevelIndex; i++)
            {
                if (update[i]->next[i] != current)
                {          // iterate through the level for node you want to delete
                    break; // Stop if node doesn't exist on this level
                }
                update[i]->next[i] = current->next[i]; // iterate by changing the pointer
            }

            while (currentHighestLevelIndex > 0 && head->next[currentHighestLevelIndex] == nullptr)//checking the higher levels 
            {
                currentHighestLevelIndex--;
            }

            delete current;
            current=nullptr;
        }
        else
        {
            cout << value << " is not found in the skip list." << endl;
        }
    }

    bool Search(int value)
    {
        Node *current = head;

        for (int i = currentHighestLevelIndex; i >= 0; i--)
        { // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be searched here then find out where (i.e. after which node)
            while (current->next[i] != nullptr && current->next[i]->value < value)
            { // while there is room to iterate iterate
                current = current->next[i];
            }
        }
        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to where the value is to be searched to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0]; // eliminate duplicate or cvheck if  it is empty

        // Check if the value exists.
        return current != nullptr && current->value == value; // return true if current has a value and the value in current is equal to the one you inputted
    }

    void Rescale(int newMaxLevelIndex)
    {
        if (newMaxLevelIndex < 0)
        {
            cout << "Invalid new maximum level index." << endl;// can't have negative levels now can you
            return;
        }

        vector<int> skipListValues;    // creating a vector
        Node *current = head->next[0]; // Start from the start of the list 
        while (current != nullptr)//while there are nodes
        {                                             
            skipListValues.push_back(current->value); // this vector method adds an item to the vector, so we are adding the node to the vector
            current = current->next[0];               // iterating through skiplist
        }
        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {                            // clear the current skip list
            head->next[i] = nullptr; // by setting everything to nullptr
        }
        currentHighestLevelIndex = 0;                   // cuz the list don't exist
        MAXIMUM_ALLOWED_LEVEL_INDEX = newMaxLevelIndex; // pretty self explanatory
        for (int i = 0; i < skipListValues.size(); i++)
        { // for loop iterating through the vector of all the elememnts of the skip list
            int value;
            value = skipListValues[i];
            InsertElement(value); // inserting the items from the vector using the insert method
        }
    }

    void Show()
    {
        for (int i = 0; i <= currentHighestLevelIndex; i++)
        {
            Node *node = head->next[i];
            cout << "Level " << i << ": ";
            while (node != nullptr && node->next[i] != nullptr)
            {
                cout << node->value << " -> ";
                node = node->next[i];
            }
            cout << node->value << " .\n";
        }
    }
};

#endif
