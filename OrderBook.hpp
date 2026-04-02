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

    // Outros métodos auxiliares, se necessário
};

#endif

// Coments para o relatório:

    // Ideia: criar uma lista com a estrutura de uma lista encadeada simples (assim, conseguimos gerenciar a ordem
    // das ordens de compra e de venda). E, para as transações um array simples talvez. Ponto negativo: tirar um elemento
    // do meio seria muito trabalhoso, e a possibilidade de acontecer em nosso sistema é grande.