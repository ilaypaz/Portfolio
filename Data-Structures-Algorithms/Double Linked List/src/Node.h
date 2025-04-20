#include<iostream>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node
{
public:
    int element;
    Node* next;
    Node* prev;

    Node(){
      element = 0;
      next = nullptr;
      prev = nullptr;
    }

    Node(int e){
      element = e;
      next = nullptr;
      prev = nullptr;
    }
};

#endif

