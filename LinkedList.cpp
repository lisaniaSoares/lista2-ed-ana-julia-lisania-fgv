#include "LinkedList.hpp"

Node::Node(Order order) : order(order), next(nullptr), prev(nullptr) {
    
}

Node::~Node(){

}

DoubleLinkedList::DoubleLinkedList(){
    this -> head = nullptr;
    this -> tail = nullptr;
    size = 0;
}

DoubleLinkedList::~DoubleLinkedList(){

    Node* current = head;
    Node* next = nullptr;

    while(current != nullptr){
        next = current -> next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
}

void DoubleLinkedList::insertEnd(Order order){
    Node* node = new Node(order);

    if (head == nullptr){
        head = tail = node;

    } else {
        tail -> next = node;
        node -> prev = tail;
        node -> next = nullptr;
        tail = node;
    }

    size ++;
    
}

void DoubleLinkedList::remove(Order order){
    Node* current = head;
    Node* prev = nullptr;

    while(current != nullptr && !order.compareOrder(current -> order)){
        current = current -> next;
    }

    if(current == nullptr) return;

    // Casos de contorno : current = head e current = tail
    if(current == head){
        removeFront();
        return;
    }

    if(current == tail){
        removeEnd();
        return;
    }

    // Se não for caso de contorno

    // prev: elemento anterior ao que queremos remover
    prev = current -> prev;
    prev -> next = current -> next;
    current -> next -> prev = prev;

    delete current;
    size--;
}

// Funções auxiliares para os casos de contorno

void DoubleLinkedList::removeFront(){
    if(head == nullptr) return;

    Node* temp = head;
    head = head -> next;

    if (head != nullptr){
        head -> prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete temp;
    size--;   
}

void DoubleLinkedList::removeEnd(){
    if(head == nullptr) return;
    
    Node* temp = tail;
    tail = tail -> prev;

    if (tail != nullptr){
        tail -> next = nullptr;
    } else {
        head = nullptr;
    }

    delete temp;
    size--;
}

Node* DoubleLinkedList::getHead(){
    return head;
}

Node* DoubleLinkedList::getTail(){
    return tail;
}

int DoubleLinkedList::getSize(){
    return size;
}