#ifndef NODE_H
#define NODE_H

#include <vector>//including the vector class......ew 

using namespace std;

// the node
class Node{
public:
    int value;
    // Array of pointers to the next nodes (which may be located at various levels)
    // next[i] is the next link for level i
    // the size of this vector determines the number of levels that the current node is part of
    vector<Node*> next; //think of this as an array of sorts , the vector must have a length of 1, maximum length of vector can be the MAXIMUM_ALLOWED_LEVEL_INDEX+1
    Node(int val, int level){
        value = val;
        next = vector<Node*>(level+1, nullptr); // initialize array of pointers to nulls
    };
};

#endif