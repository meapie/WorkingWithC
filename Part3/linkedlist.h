#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <iostream>

#include <utility>

#include <initializer_list>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:


template <typename T>
class LinkedList{
    public:

    size_t count = 0;
    Node<T>* head;
    Node<T>* tail;

    LinkedList(): count(0), head(nullptr), tail(nullptr){}

    LinkedList(std::initializer_list<T> items) :count(0), head(nullptr), tail(nullptr){
        for(const auto & item: items){
            push_back(item);
            count += 1;
        }
    }

    /**
     * Push item to the front of the linked list
     * 
    */
    void push_front(const T & item){

        Node<T>* newNode = new Node<T>(item);

        if(head == nullptr){
            head = tail = newNode;
        }else{
            newNode->next = head;
            head -> previous = newNode;
            head = newNode;
        }
        count += 1;
    }

    /**
     * Return item that is at the front
    */
    T & front(){
        return head->data;
    }

    /**
     * Push item to the end of the linked list
    */
    void push_back(const T & item){

        Node<T>* newNode = new Node<T>(item);

        if (tail == nullptr) {
            tail = head = newNode;
        } else {
            tail->next = newNode;
            newNode -> previous = tail;
            tail = newNode;
        }

        count += 1;
    }

    /**
     * Return item that is at the back
    */
    T & back(){
        return tail->data;
    }

    /**
     * Return the size of the linked list
    */
    size_t size(){
        return count;
    }

    /**
     *Return a NodeIterator pointing to the head 
    */
    NodeIterator<T> begin() const{
        return NodeIterator<T>(head);
    }

    /**
     * Return NodeIterator pointing to nullptr (off the list)
    */
    NodeIterator<T> end() const{
        return NodeIterator<T>(nullptr);
    }

    /**
     * Inserting an element into a specific location 
     * Returns a NodeIterator point to the newNode
    */
    NodeIterator<T>  insert(NodeIterator<T> & where, T element){
        Node<T>* current = where.getNodePtr();
        Node<T>* prev = current -> previous;

        //inserting at the head
        if(current == head){
            push_front(element);
            return NodeIterator<T>(head);
        }
        //inserting at the tail
        else if(current == tail){
            push_back(element);
            return NodeIterator<T>(tail);
        }
        //Inserting into empty list
        else if(current == nullptr && prev == nullptr){
            push_front(element);
            return NodeIterator<T>(head);
        }
        else{
            Node<T>* newNode = new Node<T>(element);
            newNode -> previous = prev;
            newNode -> next = current;

            prev -> next = newNode;
            current -> previous = newNode;

            count++;

            return NodeIterator<T>(newNode);
        }
    }

    /**
     * Erasing a node from a specifc location
     * Return NodeIterator pointing to the nextNode
    */
    NodeIterator<T> erase(NodeIterator<T> where){
        Node<T>* current = where.getNodePtr();
        Node<T>* nextNode = current -> next;
        Node<T>* prev = current -> previous;

        //deleting at the head
        if(current == head){
            current -> next = nullptr;
            nextNode -> previous = nullptr;
            delete current;
            head = nextNode;
            count--;
            return NodeIterator<T>(head);
        }//deleting at the tail
        else if(current == tail){
            current -> previous = nullptr;
            prev -> next = nullptr;
            delete current;
            tail = prev;
            count--;
            return NodeIterator<T>(nullptr);
        }else{
            nextNode -> previous = prev;
            prev -> next = nextNode;

            current -> next = nullptr;
            current -> previous = nullptr;

            delete current;
            count--;

            return NodeIterator<T>(nextNode);
        }
        
    }

    /**
     * Reverses the list
    */
    void reverse(){

        //starting with the head
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        Node<T>* next = nullptr;

        while(current != nullptr){
            next = current -> next;
            current -> next = previous;
            previous = current;
            current = next;
        }


        head = previous;
    }

    
    /**
     * Deconstructor
    */
    ~LinkedList() {
        Node<T>* current = head;
        while(current != nullptr){
            Node<T>* next = current -> next;
            delete current;
            current = next;
        }
    }

};


// do not edit below this line

#endif
