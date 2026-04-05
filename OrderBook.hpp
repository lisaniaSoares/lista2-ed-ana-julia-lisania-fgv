#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"
#include "LinkedList.hpp"

class OrderBook {

private:

    DoubleLinkedList buy_order_list;
    DoubleLinkedList sell_order_list;
    Transaction* transactions;
    int transactions_count;
    int transaction_capacity;

public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

};

#endif
