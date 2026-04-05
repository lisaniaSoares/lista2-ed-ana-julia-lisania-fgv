Repositório destinado a entrega da lista 2 da disciplina de Estrutura de Dados.

# Descrição do Sistema

O repositório implementa e simula um sistema de livro de ofertas (Order Book), estrutura fundamental em mercados financeiros. No contexto do sistema, usuários podem submeter ordens de compra ('B') ou de venda ('S') com um preço e um timestamp associados. O sistema então tenta realizar o pareamento (matching) entre ordens compatíveis, gerando transações quando possível. Caso o pareamento não ocorra a ordem então é armazenada na estrutura de dados adequada (lista de compra ou de venda).

Cada ordem possui um identificador único, um tipo (compra ou venda), um preço e um timestamp que indica o momento em que foi criada. Quando uma ordem de compra é submetida, o sistema busca a ordem de venda com o menor preço disponível que seja igual ou inferior ao preço ofertado pelo comprador. De forma análoga, quando uma ordem de venda é submetida, o sistema busca a ordem de compra com o maior preço disponível que seja igual ou superior ao preço pedido pelo vendedor. Em caso de empate no preço, a prioridade é dada à ordem com o menor timestamp (ou seja, a mais antiga).

Existem três classes principais no sistema:

1. **Order**: representa uma ordem individual com seus atributos (id, tipo, preço e timestamp).

```cpp
Order order(id, tipo, preco, timestamp);
```

2. **Transaction**: representa uma transação realizada com sucesso entre uma ordem de compra e uma de venda, registrando os IDs das ordens envolvidas e o preço de execução.
 
```cpp
Transaction t(buy_order_id, sell_order_id, execution_price);
```

3. **OrderBook**: classe central do sistema, responsável por gerenciar as listas de ordens de compra e venda e o histórico de transações. Permite submeter ordens, cancelá-las e consultar o estado atual do livro.

```cpp
OrderBook book;
book.submit(order);   // Submete uma ordem
book.cancel(id);      // Cancela uma ordem pendente pelo ID
```

# Instruções de Compilação

O repositório foi inteiramente programado em **C++**, portanto, é necessário compilar os arquivos antes de executar o programa. As instruções abaixo compilam todos os arquivos `.cpp` de uma vez:

1. Certifique-se de que todos os arquivos `.hpp` e `.cpp` estejam na mesma pasta.
2. Certifique-se de ter o `g++` instalado na sua máquina.
3. Em seu terminal, dentro da pasta onde estão os arquivos, execute:

```bash
g++ main.cpp LinkedList.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book
```

Após o comando, um arquivo executável será criado na mesma pasta.

# Instruções de Execução

Após compilar, execute o programa de acordo com o seu sistema operacional:
 
- **Windows**
 
```bash
.\order_book.exe
```
 
- **Linux / macOS**
 
```bash
./order_book
```

# Estrutura de Dados do Sistema

Internamente, o sistema mantém duas **listas duplamente encadeadas** (`DoubleLinkedList`), uma para ordens de compra pendentes e outra para ordens de venda pendentes. Cada nó da lista (`Node`) armazena um objeto `Order` e ponteiros para o nó anterior e para o próximo, permitindo inserções ao final e remoções de qualquer posição com eficiência.

Quando uma nova ordem é submetida via `submit()`, o sistema percorre a lista oposta em busca de uma ordem compatível. Se encontrada, uma transação é gerada e ambas as ordens são removidas das listas. Caso contrário, a ordem submetida é inserida ao final da sua respectiva lista, aguardando um pareamento futuro.

As transações realizadas são armazenadas em um **array dinâmico** de objetos `Transaction`, alocado com capacidade inicial para 200 transações. Um contador interno (`transactions_count`) rastreia quantas transações já foram registradas, permitindo o acesso e a cópia do histórico a qualquer momento por meio do método `getTransactions()`. Caso o número de transações ultrapasse a capacidade inicial de 200 transações um novo **array dinâmico** é criado com capacidade duplicada e então os dados do array antigo são copiados para o novo array. Após essa cópia, o array antigo é desalocado para evitar vazamento de memória, e o ponteiro passa a referenciar o novo espaço maior.
 
O cancelamento de uma ordem (`cancel()`) percorre ambas as listas encadeadas em busca do ID fornecido e, ao encontrá-la, remove o nó correspondente com atualização correta dos ponteiros vizinhos, tratando os casos especiais de remoção no início (`head`) ou no final (`tail`) da lista.