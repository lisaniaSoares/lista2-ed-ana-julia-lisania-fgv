#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Order.hpp"

class Node {

public:

    Order order;
    Node* next;
    Node* prev;

    Node(Order order);
    ~Node();
};

class DoubleLinkedList {
    
private:

    Node* head;
    Node* tail;
    int size;

public:

    DoubleLinkedList();
    ~DoubleLinkedList();

    void insertEnd(Order order);
    void remove(Order order);
    void removeFront();
    void removeEnd();

    Node* getHead();
    Node* getTail();
    int getSize();

};

#endif