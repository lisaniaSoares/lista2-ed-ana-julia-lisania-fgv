#include "OrderBook.hpp"
#include "Transaction.hpp"

OrderBook::OrderBook(){
    this -> buy_order_list = DoubleLinkedList();
    this -> sell_order_list = DoubleLinkedList();
    this -> transactions = new Transaction[200];
    this -> transactions_count = 0;
    
}

OrderBook::~OrderBook(){
    delete[] transactions;
}


bool OrderBook::submit(Order order){
    if (order.getType() == 'B'){

        // Verifica na lista de vendas se existe order compatível
        Node* current_sell = sell_order_list.getHead();
        Node* choosed_sell = nullptr;
        float lowest_price = order.getPrice();

        while (current_sell != nullptr){

            if(current_sell -> order.getPrice() < lowest_price){
                choosed_sell = current_sell;
                lowest_price = current_sell -> order.getPrice();
                current_sell = current_sell -> next;

            } else if (current_sell -> order.getPrice() == lowest_price){

                if(choosed_sell != nullptr){

                    if(current_sell -> order.getTimestamp() < choosed_sell -> order.getTimestamp()){
                        choosed_sell = current_sell;
                        current_sell = current_sell -> next;

                    } else {
                        current_sell = current_sell -> next;
                    }

                } else {
                    choosed_sell = current_sell;
                    current_sell = current_sell -> next;
                }

            } else {
                current_sell = current_sell -> next;
            }
        }

        if (choosed_sell == nullptr){
            buy_order_list.insertEnd(order);

            return false;

        } else {
            Transaction buy_t = Transaction(order.getId(), choosed_sell -> order.getId(), lowest_price);
            this -> transactions[transactions_count] = buy_t;
            transactions_count++;

            sell_order_list.remove(choosed_sell -> order);
            return true;
        }


    } else if(order.getType() == 'S'){

        // Verifica na lista de compras se existe uma order compatível
        Node* current_buy = buy_order_list.getHead();
        Node* choosed_buy = nullptr;
        int highest_price = order.getPrice();

        while(current_buy != nullptr){

            if(current_buy -> order.getPrice() > highest_price){
                choosed_buy = current_buy;
                highest_price = current_buy -> order.getPrice();
                current_buy = current_buy -> next;

            } else if (current_buy -> order.getPrice() == highest_price){

                if(choosed_buy != nullptr){

                    if(current_buy -> order.getTimestamp() < choosed_buy -> order.getTimestamp()){
                        choosed_buy = current_buy;
                        current_buy = current_buy -> next;

                    } else {
                        current_buy = current_buy -> next;
                    }

                } else {
                    choosed_buy = current_buy;
                    current_buy = current_buy -> next;
                }
                
            } else {
                current_buy = current_buy -> next;
            }
        }

        if (choosed_buy == nullptr){
            sell_order_list.insertEnd(order);

            return false;

        } else {
            Transaction sell_t = Transaction(choosed_buy -> order.getId(), order.getId(), highest_price);
            this -> transactions[transactions_count] = sell_t;
            transactions_count++;

            buy_order_list.remove(choosed_buy -> order);
            return true;
        }
    }

    return false;
    
}


bool OrderBook::cancel(int id){

    // Procurando na lista de ordens de compra
    Node* current_buy = buy_order_list.getHead();

    while(current_buy != nullptr){
        if(current_buy -> order.getId() == id){
            buy_order_list.remove(current_buy -> order);
            return true;
        }
        current_buy = current_buy -> next;
    }

    // Procurando na lista de ordens de venda
    Node* current_sell = sell_order_list.getHead();

    while(current_sell != nullptr){
        if(current_sell -> order.getId() == id){
            sell_order_list.remove(current_sell -> order);
            return true;
        }
        current_sell = current_sell -> next;
    }

    // Se não encontramos em nenhuma das duas listas, retornamos false
    return false;
}


Order* OrderBook::getBuyOrders(int* n){

    if(buy_order_list.getSize() == 0){
        *n = 0;
        return nullptr;
    }

    *n = buy_order_list.getSize();
    Order* order_list = new Order[*n];
    int i = 0;

    Node* current = buy_order_list.getHead();
    while(current != nullptr && i < *n){
        order_list[i] = current -> order;
        current = current -> next;
        i++;
    }

    return order_list;
}


Order* OrderBook::getSellOrders(int* n){

    if(sell_order_list.getSize() == 0){
        *n = 0;
        return nullptr;
    }

    *n = sell_order_list.getSize();
    Order* order_list = new Order[*n];
    int i = 0;

    Node* current = sell_order_list.getHead();
    while(current != nullptr && i < *n){
        order_list[i] = current -> order;
        current = current -> next;
        i++;
    }

    return order_list;
}


Transaction* OrderBook::getTransactions(int *n){

    if(transactions_count == 0){
        *n = 0;
        return nullptr;
    }

    *n = transactions_count;
    Transaction* transactions_copy = new Transaction[*n];

    for (int i = 0; i < transactions_count; i++){
        transactions_copy[i] = transactions[i];
    }

    return transactions_copy;
}