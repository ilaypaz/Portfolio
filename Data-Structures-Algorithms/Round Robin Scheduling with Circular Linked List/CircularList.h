#include <iostream>
#include <fstream>
using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node
{
public:
    int data;
    Node *next;

    Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList
{
private:
    Node *last;

public:
    CircularLinkedList() : last(nullptr) {}

    // Insert a new node with data at the end of the circular linked list
    void insert(int data)
    {
        Node *new_node = new Node(data);
        if (!last)
        {
            last = new_node;
            last->next = last;
        }
        else
        {
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
        }
    }

    // Delete a node with the given data
    void deleteNode(int data)
    {
        if (!last)
            return;

        Node *current = last->next;
        Node *previous = nullptr;

        while (current->next != last->next)
        {
            if (current->data == data)
            {
                if (current == last->next)
                    last->next = last->next->next;
                if (current == last)
                    last = previous;
                if (previous)
                    previous->next = current->next;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }

        if (current->data == data)
        {
            if (current == last->next)
                last->next = last->next->next;
            if (current == last)
                last = previous;
            if (previous)
                previous->next = current->next;
            delete current;
        }
    }

    // Search for a node with the given data
    bool search(int data)
    {
        if (!last)
            return false;

        Node *current = last->next;

        do
        {
            if (current->data == data)
                return true;
            current = current->next;
        } while (current != last->next);

        return false;
    }
    int getSize()
    {
        if (!last)
            return 0;
        Node *current = last->next;
        int count = 0;
        do
        {
            count++;
            current = current->next;
        } while (current != last->next);
        return count;
    }

    // display all elements in the circular linked list
    void display()
    {
        if (!last)
            return;

        Node *current = last->next;

        do
        {
            cout << current->data << " ";
            current = current->next;
        } while (current != last->next);

        cout << endl;
    }
    bool isEmpty()
    {
        return last == nullptr;
    }
    int sumAllNodes()
    {
        if (!last)
            return 0;
        Node *current = last->next;
        int total = 0;
        do
        {
            total += current->data;
            current = current->next;
        } while (current != last->next);
        return total;
    }
    ~CircularLinkedList()
    { // destructor
        if (isEmpty())
        {
            return;
        }
        else
        {
            Node *current = last->next; // this is basically just head and make iterating through everything start at the head
            last->next = nullptr;       // make the circular list normal and also so that the loop below can work
            while (current != nullptr)
            {                            // so iterate through the whole circular linked list
                Node *temp = current;    // have a pointer start at "head"
                current = current->next; // move current
                delete temp;
            }
            last = nullptr; // since we already deleted last in the 2 lines above we can set it to nullptr here.
        }
    }
};
class RoundRobinProcessScheduler
{
public:
    int timeSlice;
    CircularLinkedList processTimes;
    void LoadFromFile(string fileName)
    {
        ifstream input("process.txt");

        input >> timeSlice; // first line in the txt file is 5
        int processTime;
        char comma;
        while (!input.eof())
        {
            input >> processTime;
            processTimes.insert(processTime);
            input >> comma; // Skip the comma's
        }

        input.close();
    }
    double Process()
    {
        int totalTurnaroundTime = processTimes.sumAllNodes();
        int processCount = processTimes.getSize();
        double averageTime = totalTurnaroundTime / processCount;
        return averageTime;
    }
    void ShowResults()
    {
        cout << "Turnaround times for each processes p1,p2 and p3 are  "<<endl;
        processTimes.display();
double a = Process();
        cout << "Average Turnaround Time is" << a << endl;
    }
};


#endif
