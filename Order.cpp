#include "Order.hpp"

Order::Order(){}

Order::Order(int id, char type, float price, int timestamp){
    this -> id = id;
    this -> type = type;
    this -> price = price;
    this -> timestamp = timestamp;
}

Order::~Order(){
    // Não há elementos que precisem ter seu espaço de memória liberado manualmente
}

int Order::getId(){
    return this -> id;
}

char Order::getType(){
    return this -> type;
}

float Order::getPrice(){
    return this -> price;
}

int Order::getTimestamp(){
    return this -> timestamp;
}

bool Order::compareOrder(Order order){
    if(this -> id == order.id){
        return true;
    } else {
        return false;
    }
}