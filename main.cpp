#include <iostream>
using namespace std;
#include <algorithm> // por que tem essa inclusão?
#include "OrderBook.hpp"


void printSeparator(const string& title) {
    cout << "\n========================================" << endl;
    cout << " " << title << endl;
    cout << "========================================\n" << endl;
}


int main(void){
    cout << "Executando!" << endl;

    OrderBook book;

    // 1. Inserção de ordens sem transações
    printSeparator("CASO 1: Insercao sem match");

    Order b1(1, 'B', 100.0, 1);
    Order b2(2, 'B',  95.0, 2);
    Order s1(3, 'S', 110.0, 3);
    Order s2(4, 'S', 120.0, 4);

    bool r1 = book.submit(b1);
    bool r2 = book.submit(b2);
    bool r3 = book.submit(s1);
    bool r4 = book.submit(s2);
    
    cout << "submit(b1, id: 1, compra: 100) -> " << (r1 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "submit(b2, id: 2, compra: 95)  -> " << (r2 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "submit(s1, id: 3, venda: 110)  -> " << (r3 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "submit(s2, id: 4, venda: 120)  -> " << (r4 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "\n";

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // 2. Execuções bem sucedidas

    // 2.2 Nova compra cruza com venda existente
    printSeparator("CASO 2: Execucao bem-sucedida -  compra cruza com venda existente");

    Order b3(5, 'B', 115.0, 5);
    bool r5 = book.submit(b3);

    cout << "submit(b3, id: 5, compra: 115) -> " << (r5 ? "EXECUTADO" : "NA FILA") << " (Status esperado: EXECUTADO)" << endl;
    cout << "\n";
    
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // 2.2 Nova venda cruza com compra existente
    printSeparator("CASO 3: Execucao bem-sucedida - venda cruza com compra existente");
    
    Order s3(6, 'S', 90.0f, 6);
    bool r6 = book.submit(s3);

    cout << "submit(s3, id: 6, venda: 90)   -> " << (r6 ? "EXECUTADO" : "NA FILA") << " (esperado: EXECUTADO)" << endl;
    cout << "\n";

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // 3. Desempate por timestamp
    printSeparator("CASO 4: Desempate por timestamp");

    Order s4(7, 'S', 100.0, 7); // chegou antes, deve ter prioridade
    Order s5(8, 'S', 100.0,  8); // chegou depois

    bool r7 = book.submit(s4);
    bool r8 = book.submit(s5);

    cout << "submit(bs, id: 7, venda: 100)  -> " << (r7 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "submit(bs, id: 8, venda: 100)  -> " << (r8 ? "EXECUTADO" : "NA FILA") << " (Status esperado: NA FILA)" << endl;
    cout << "\n";

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // Entre s4 e s5 (mesmo preço 100), s4 tem timestamp menor, prioridade
    Order b4(9, 'B', 105.0, 9);
    bool r9 = book.submit(b4);

    cout << "\n";
    cout << "submit(b4, id: 9, compra: 105)  -> " << (r9 ? "EXECUTADO" : "NA FILA") << " (Status esperado: EXECUTADO)" << endl;
    cout << "\n";

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // 4. Cancelamento
    printSeparator("CASO 5: Cancelamento de ordens");

    bool c1 = book.cancel(4);  // cancela s2 (id=4), existe
    bool c2 = book.cancel(99); // tenta cancelar id inexistente

    cout << "cancel(id=4)  -> " << (c1 ? "CANCELADO" : "NAO ENCONTRADO") << " (Status esperado: CANCELADO)" << endl;
    cout << "cancel(id=99) -> " << (c2 ? "CANCELADO" : "NAO ENCONTRADO") << " (Status esperado: NAO ENCONTRADO)" << endl;
    cout << "\n";

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    printSeparator("CASO 6: Recuperacao via get");

    int nBuy;
    Order* buyOrders = book.getBuyOrders(&nBuy);

    cout << "getBuyOrders(&n)" << "\n";
    // devo imprimir a parte do retorna nullptr??
    cout << "-> n = " << nBuy << endl << "\n";

    int nSell;
    Order* sellOrders = book.getSellOrders(&nSell);
    
    cout << "getSellOrders(&n)" << "\n";
    cout << "-> n = " << nSell << endl << "\n";

    int nTransactions;
    Transaction* transactions = book.getTransactions(&nTransactions);

    cout << "getTransactions(&n)" << "\n";
    cout << "-> n = " << nTransactions << endl;

    printSeparator("CASO 7: Estado atual do sistema");

    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions(); 
}