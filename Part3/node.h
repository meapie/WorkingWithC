#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please email me
// TODO your code for the Node class goes here:

template<typename T>
class Node{
    public:
        T data;
        Node<T>* next;
        Node<T>* previous;
    
    Node(T item): data(item), next(nullptr), previous(nullptr){}
    
};
// (Note the 'NodeIterator' class will report lots of errors until Node exists)

template<typename T>
class NodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here
    
    /**
     * Overriding the == operator
     * 
    */
    bool operator==(const NodeIterator & other)
    {
        return(current == other.current);
    }

    /**
     * Overriding the != operator
    */
    bool operator!=(const NodeIterator & other)
    {
        return(current != other.current);
    }

    /**
     * Overriding the ++ operator
    */
    NodeIterator operator++()
    {
        if (current) {
            current = current -> next;
        }

        return *this;
    }

    /**
     * Returns the current node pointer
    */
    Node<T>* getNodePtr() {
        return current;
    }
};

#endif
