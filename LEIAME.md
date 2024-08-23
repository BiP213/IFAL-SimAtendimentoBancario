### Simulação de Atendimento Bancário

Este tutorial explica o funcionamento do programa `SimAtendimentoBancario`, que simula o atendimento em um banco, gerenciando a fila de clientes e gerando um relatório ao final do expediente. O sistema é implementado em C e utiliza estruturas de dados como listas encadeadas e filas para gerenciar as operações de forma eficiente.

#### Estruturas de Dados Implementadas

1. **`struct Transacao`**:
   - Armazena o tipo de transação realizada pelo cliente (Saque, Depósito, Pagamento, Transferência).
   - Implementada como uma lista encadeada para permitir a adição dinâmica de transações enquanto o cliente está sendo atendido.

2. **`struct Cliente`**:
   - Armazena as informações do cliente, como ID, nome, idade, e uma lista de transações.
   - Possui ponteiros para o próximo cliente na fila e para as transações realizadas.
   - A lista de transações permite gerenciar múltiplas operações para cada cliente de forma organizada.

3. **`struct Fila`**:
   - Gerencia a fila de clientes utilizando uma lista encadeada, onde cada nó representa um cliente.
   - Mantém um ponteiro para o início (`frente`) e o final (`tras`) da fila, além de variáveis para controlar o número total de clientes e o tempo total de atendimento.
   - Inclui também uma lista de clientes atendidos, para fins de geração do relatório.

#### Justificativa para o Uso das Estruturas de Dados

- **Filas**: A estrutura de fila é essencial para o gerenciamento de clientes no atendimento bancário, pois segue o princípio FIFO (First In, First Out), onde os primeiros clientes a entrarem na fila são os primeiros a serem atendidos. Além disso, a fila implementa uma prioridade para idosos (clientes com 60 anos ou mais), que são posicionados na frente dos clientes mais jovens, respeitando as normas de prioridade em atendimentos.

- **Listas Encadeadas**: Tanto para os clientes quanto para as transações, as listas encadeadas permitem a adição dinâmica de elementos (clientes e transações) sem precisar redimensionar uma estrutura fixa. Isso é muito útil para gerenciar uma quantidade variável de operações de maneira eficiente e sem sobrecarga de memória.

#### Funcionamento do Programa

1. **Inicialização**:
   - A fila é inicializada, e o programa apresenta um menu de opções para o usuário.

2. **Adição de Clientes**:
   - O usuário pode adicionar clientes à fila. Clientes idosos (60 anos ou mais) são automaticamente priorizados na fila. O nome do cliente é validado para garantir que contenha apenas letras e espaços, e a idade é verificada para ser um número válido.

3. **Atendimento**:
   - Durante o atendimento, o usuário registra as transações realizadas pelo cliente. Cada tipo de transação tem um tempo associado que é acumulado para calcular o tempo total de atendimento do cliente. Após o atendimento, o cliente é movido para a lista de clientes atendidos, onde seus dados serão usados na geração do relatório.

4. **Geração do Relatório**:
   - O relatório final exibe o número total de clientes atendidos, o tempo total de atendimento, o número de transações realizadas e o tempo de atendimento de cada cliente individualmente, detalhando as transações realizadas. O relatório apresenta os clientes atendidos em ordem decrescente, ou seja, os primeiros foram os últimos a serem atendidos.

#### Como Compilar e Executar

- Certifique-se de ter um compilador C instalado.
- Descompacte o arquivo **`SimAtendimentoBancario.zip`** para um diretório.
- Certifique-se de que todos os arquivos (**`main.c`**, **`SimAtendimentoBancario.c`**, **`SimAtendimentoBancario.h`**) estão presentes no mesmo diretório.
- **Compilador GCC**:  
  Compile o programa utilizando o comando:
  ```bash
  gcc -o SimAtendimentoBancario main.c SimAtendimentoBancario.c
  ```
- Execute o programa com:
  ```bash
  ./SimAtendimentoBancario
  ```

#### Arquivos

- **main.c**: Contém a função **`main()`** e a lógica principal do programa.
- **SimAtendimentoBancario.c**: Contém as implementações das funções declaradas em **`SimAtendimentoBancario.h`**.
- **SimAtendimentoBancario.h**: Contém as declarações de funções e de estruturas utilizadas nos arquivos acima.