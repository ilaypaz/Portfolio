#include "Node.h"
#include <iostream>

using namespace std;

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

class LinkedList
{
public:
    Node *head;
    Node *tail;

    LinkedList()
    {
        // empty list
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(int n)
    {
        head = tail = nullptr;
        for (int i = 0; i < n; i++)
        {
            AddNodeLast(i + 1);
        }
    }

    LinkedList(const LinkedList &source)
    {
        head = tail = nullptr;

        Node *temp = source.head;
        while (temp != nullptr)
        {
            AddNodeLast(temp->element);
            temp = temp->next;
        }
    }

    ~LinkedList()
    {

        Node *temp;
        Node *nextNode = nullptr;

        for (temp = head; temp != tail; temp = nextNode)
        {

            if (temp != nullptr)
            {
                nextNode = temp->next;
                delete temp;
            }
        }

        delete tail;
        head = tail = nullptr;
    }

    bool IsEmpty()
    {
        return tail == nullptr;
    }

    int Size() const
    {
        int count = 0;
        Node *temp = tail;

        while (temp != nullptr)
        {
            count++;
            temp = temp->prev;
        }

        return count;
    }

    void AddNodeLast(int value = 0)
    {
        // add a new node to the end to the end of the list
        if (IsEmpty())
        {
            head = new Node(value);
            tail = head;
        }
        else
        {
            Node *temp = new Node(value);

            tail->next = temp;
            temp->prev = tail;

            tail = temp;
        }
    }

    void ShowReverse()
    {
        Node *temp = tail;

        while (temp != nullptr)
        {
            cout << temp->element << " - ";
            temp = temp->prev;
        }
        cout << endl;
    }

    void ShowForward()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->element << " - ";
            temp = temp->next;
        }
        cout << endl;
    }

    void AddNodeFirst(int value = 0)
    {
        // add a new node at the beginning of the list i.e. new node will become the new head
        if (IsEmpty())
        {
            head = new Node(value);
            tail = head;
        }
        else
        {
            head->prev = new Node(value);
            head->prev->next = head;
            head = head->prev;
        }
    }

    void AddNode(int index, int nodeValue)
    {
        int size = Size();
        if (index == 0)
        {
            AddNodeFirst(nodeValue); // add to the beginnningif the conditions match
        }
        else if (index == size - 1)
        { // add to end if conditions allow
            AddNodeLast(nodeValue);
        }
        else if (index < size && !(index < 0))
        { // some other position within the linked list
            // find the item currently at index first
            Node *temp = head; // temp is a just pointer startging from the start you are just moving along
            for (int i = 0; i < index; i++)
            { // index is the value where you want to add the value
                temp = temp->next;
            } // created pointer that points to the index where we wanbt to add new node

            // cout << temp->element << endl;
            Node *oldPrev = temp->prev;          // pointer to nodes new positions previous node
            Node *newNode = new Node(nodeValue); // create the new node in memory
            temp->prev->next = newNode;          // no longer pointing to old value rather the new value
            temp->prev = newNode;                // connecting old values previous to the new node
            newNode->next = temp;                // dealing with the other directions in these two lines
            newNode->prev = oldPrev;
        }
        else
        {
            cout << "Index out of bounds" << endl;
        }
    }

    void RemoveFirst()
    {
        if (!IsEmpty())
        {
            if (head == tail)
            {
                delete head;
                head = tail = nullptr;
            }
            else
            {
                Node *temp = head->next;
                head->next = nullptr;
                temp->prev = nullptr;
                delete head;
                head = temp;
            }
        }
    }

    void RemoveLast()
    {
        if (!IsEmpty())
        {
            if (head == tail)
            {
                delete head;
                head = tail = nullptr;
            }
            else
            {
                Node *temp = tail->prev;
                delete tail;
                tail = temp;
                tail->next = nullptr;
            }
        }
    }

    int Remove(int index)
    {
        if (IsEmpty())
        {
            if (head == tail)
            {
                delete head;
                head = tail = nullptr;
            }
        }
        else
        {
            Node *temp = head;
            int i=0;
            while(i<index){
                temp->next;
                i++;
            }
        }
    }

    void Swap(int index1, int index2)
    {
        // validate indices first
        // swap nodes at indices index1 and index2
        // Rewire connections (prev and next links) to swap
        // do NOT swap content of nodes i.e. this will be a data independent swap
        if (index1 < 0 || index2 < 0 || index1 >= CountNodes() || index2 >= CountNodes())
        {
            cout << "Please enter valid indices for swapping" << endl;
            return;
        }

        if (index1 == index2)
        { // don't swap if they're the same
            return;
        }

        Node *node1 = nullptr; // node 1
        Node *node2 = nullptr; // node 2
        Node *prev1 = nullptr; // previous node1
        Node *prev2 = nullptr; // previous node2
        Node *iteration1 = head;
        Node *iteration2 = head;

        for (int i = 0; i < index1; ++i)//setting node 1  to their correct swapping positions
        {
            prev1 = iteration1;            // Set prev1 to the node before node iteration is on
            iteration1 = iteration1->next; // Move to the next node
        }
        node1 = iteration1; // Set node1 to the node at index1 after loop is done

        for (int i = 0; i < index2; ++i)//setting node 2 to the correct swapping position
        {
            prev2 = iteration2;            // Set prev2 to the node before node iteration is on
            iteration2 = iteration2->next; // Move to the next node
        }
        node2 = iteration2; // Set node2 to the node at index2 after loop is done

        // Swap nodes at index1 and index2
        // Rewire previous nodes
        if (prev1 != nullptr) // if there is no value before node1
        {
            prev1->next = node2; // Set the previous node of node1 to point to node2
        }
        else
        {
            head = node2; // Set new head if node1 was at the head
        }

        if (prev2 != nullptr) // if there is no value before node2
        {
            prev2->next = node1; // Set the previous node of node2 to point to node1
        }
        else
        {
            head = node1; // Set new head if node2 was at the head
        }

        Node *temp = node2->next;  // Temporarily store node2's next
        node2->next = node1->next; // Point node2 to node1's next
        node1->next = temp;        // Point node1 to node2's next

        if (index1 == CountNodes() - 1)
        {
            tail = node2; // Set new tail if node1 was at the tail
        }
        if (index2 == CountNodes() - 1)
        {
            tail = node1; // Set new tail if node2 was at the tail
        }
    }
        int CountNodes()
    {
        // returns the total number of nodes in the linked list
        int c = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            c++;
            temp = temp->next;
        }
        return c;
    }
    

    int firstIndexOf(int item)
    {
        return firstIndexOf(item, head, 0);
    }

    int firstIndexOf(int item, Node *temp, int index)
    {
        if (IsEmpty())
        {
            cout << "The list is empty" << endl;
            return -1;
        }
        else if (temp != nullptr)
        {
            if (temp->element == item)
            {
                return index;
            }
            else
            {
                temp = temp->next;
                return firstIndexOf(item, temp, index + 1);
            }
        }
        else
        {
            cout << "The item is not in the list" << endl;
            return -1;
        }
    }

    LinkedList &operator=(const LinkedList &source)
    {
        // overload the assignment operator
        // check for self assignment
        // delete the existing list
        // create a new list
        // copy the source list
        // return the new list
    }

    void Reverse()
    {
        // reverse the list
        // do not create new nodes
        // only change the links
    }

    void Sort()
    {
        // sort the list in ascending order
        // do not create new nodes
        // only change the links
    }

    // overload the << operator to display the list as a friend function
    friend ostream &operator<<(ostream &os, const LinkedList &list);
};

#endif
