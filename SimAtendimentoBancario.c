#include "SimAtendimentoBancario.h"

// Criar um novo cliente
Cliente *criarCliente(int id, const char *nome, int idade)
{
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    novoCliente->id = id;
    strncpy(novoCliente->nome, nome, sizeof(novoCliente->nome) - 1);
    novoCliente->nome[sizeof(novoCliente->nome) - 1] = '\0';
    novoCliente->idade = idade;
    novoCliente->transacoes = NULL;
    novoCliente->tempoEntradaFila = time(NULL);
    novoCliente->tempoAtendimento = 0;
    novoCliente->tempoNaFila = 0;
    novoCliente->proximo = NULL;
    return novoCliente;
}

// Inicializar a fila
void inicializarFila(Fila *fila)
{
    fila->frente = NULL;
    fila->tras = NULL;
    fila->totalClientes = 0;
    fila->tempoTotalAtendimento = 0;
    fila->clientesAtendidos = NULL;
}

// Adicionar um cliente à fila
void enfileirar(Fila *fila, Cliente *cliente)
{
    if (fila->frente == NULL)
    {
        fila->frente = cliente;
        fila->tras = cliente;
    }

    // Implementação da fila de prioridade de idosos
    else if (cliente->idade >= 60)
    {
        Cliente *atual = fila->frente;
        Cliente *anterior = NULL;

        // Compara a idade do cliente a ser inserido na fila
        // com a idade dos já presentes nela e põe o cliente com maior idade na frente
        while (atual != NULL && atual->idade >= 60 && atual->idade > cliente->idade)
        {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL)
        {
            cliente->proximo = fila->frente;
            fila->frente = cliente;
        }
        else
        {
            anterior->proximo = cliente;
            cliente->proximo = atual;
        }
        if (atual == NULL)
        {
            fila->tras = cliente;
        }
    }
    else
    {
        fila->tras->proximo = cliente;
        fila->tras = cliente;
    }
    fila->totalClientes++;
}

// Remover um cliente da fila
Cliente *desenfileirar(Fila *fila)
{
    if (fila->frente == NULL)
    {
        return NULL;
    }
    Cliente *clienteRemovido = fila->frente;
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL)
    {
        fila->tras = NULL;
    }
    return clienteRemovido;
}

// Ler os dados de um cliente
Cliente *lerCliente(int id)
{
    char nome[50];
    char strIdade[10]; // Armazena a idade como uma string
    int idade;

    printf("\nNome: ");
    fgets(nome, sizeof(nome), stdin);
    // Remove o caractere de nova linha do buffer
    nome[strcspn(nome, "\n")] = 0;

    // Verificar se nome possui apenas letras e espaços
    int i;
    for (i = 0; i < strlen(nome); i++)
    {
        if (!((isalpha((unsigned char)nome[i])) || isspace((unsigned char)nome[i])))
        { // Se o caractere não for nem uma letra nem um espaço, marca a entrada como inválida
            printf("\nNome invalido. Digite apenas letras e espacos.\n");
            return NULL;
        }
    }

    printf("Idade: ");
    fgets(strIdade, sizeof(strIdade), stdin); // Lê a idade como uma string
    strIdade[strcspn(strIdade, "\n")] = 0;    // Remove o \n
    sscanf(strIdade, "%d", &idade);           // Converte a string para um inteiro
    // Verifica se a idade é um número inteiro válido
    for (i = 0; i < strlen(strIdade); i++)
    {
        if (!isdigit((unsigned char)strIdade[i]))
        {
            printf("\nIdade invalida. A idade deve ser um numero inteiro.\n");
            return NULL;
        }
    }

    if (idade < 13)
    {
        printf("\nMuito novo para movimentar contas bancarias. Va brincar. :)\n");
        return NULL;
    }

    return criarCliente(id, nome, idade);
}

// Calcular o tempo total das transações
void calcularTempoTotalTransacoes(Cliente *cliente, int *tempoTotalTransacoes)
{
    Transacao *transacaoAtual = cliente->transacoes;
    while (transacaoAtual != NULL)
    {
        switch (transacaoAtual->tipo)
        {
        case 1: // Saque
            (*tempoTotalTransacoes) += 50;
            break;
        case 2: // Depósito
            (*tempoTotalTransacoes) += 70;
            break;
        case 3: // Pagamento
            (*tempoTotalTransacoes) += 100;
            break;
        case 4: // Transferência
            (*tempoTotalTransacoes) += 60;
            break;
        }
        transacaoAtual = transacaoAtual->proxima;
    }
}

// Atender um cliente
void atenderCliente(Fila *fila, Cliente *cliente)
{
    // Registrar o tempo para calcular o tempo de espera
    time_t tempoAtual = time(NULL);

    // Calcular o tempo de espera na fila
    cliente->tempoNaFila = difftime(tempoAtual, cliente->tempoEntradaFila);

    printf("\nAtendendo cliente %d - %s\n", cliente->id, cliente->nome);

    Transacao *ultimaTransacao = NULL;

    while (1)
    {
        printf("\nDigite o tipo de transacao (1-Saque, 2-Deposito, 3-Pagamento, 4-Transferencia, 0-Finalizar): ");
        int tipoTransacao;
        scanf("%d", &tipoTransacao);
        getchar();

        if (tipoTransacao == 0)
            break;

        if (tipoTransacao > 4)
        {
            printf("\nTipo de transacao invalido. Digite um valor entre 1 e 4 ou 0 para sair.\n");
            continue; // Retorna ao inicio do loop para tentar novamente
        }

        Transacao *novaTransacao = (Transacao *)malloc(sizeof(Transacao));
        novaTransacao->tipo = tipoTransacao;
        novaTransacao->proxima = NULL;

        if (cliente->transacoes == NULL)
        {
            cliente->transacoes = novaTransacao;
        }
        else
        {
            ultimaTransacao->proxima = novaTransacao;
        }
        ultimaTransacao = novaTransacao;
    }

    int tempoTotalTransacoes = 0;
    calcularTempoTotalTransacoes(cliente, &tempoTotalTransacoes);

    cliente->tempoAtendimento = tempoTotalTransacoes + cliente->tempoNaFila;

    fila->tempoTotalAtendimento += cliente->tempoAtendimento;

    cliente->proximo = fila->clientesAtendidos;
    fila->clientesAtendidos = cliente;
}

// Gerar relatório final
void gerarRelatorio(Fila *fila)
{
    printf("\n######################################################################################################################\n");
    printf("Relatorio do Atendimento:\n");

    Cliente *cliente = fila->clientesAtendidos;
    int totalTransacoes = 0;
    int totalClientesAtendidos = 0;

    while (cliente != NULL)
    {
        int quantTransacoes = 0;
        Transacao *transacaoAtual = cliente->transacoes;
        while (transacaoAtual != NULL)
        {
            quantTransacoes++;
            transacaoAtual = transacaoAtual->proxima;
        }

        printf("Cliente %d - Nome: %s, Idade: %d --> Quantidade de operacoes: %d, Tempo de atendimento: %d segundos,\n",
               cliente->id, cliente->nome, cliente->idade, quantTransacoes, cliente->tempoAtendimento);
        printf("Operacoes realizadas: ");
        transacaoAtual = cliente->transacoes;
        while (transacaoAtual != NULL)
        {
            printf("%d ", transacaoAtual->tipo);
            transacaoAtual = transacaoAtual->proxima;
        }
        printf("\n");
        cliente = cliente->proximo;
        totalClientesAtendidos++;           // Incrementa o contador de clientes atendidos
        totalTransacoes += quantTransacoes; // Adiciona o número de transações desse cliente ao total
    }
    printf("\nResumo:\n");
    printf("Tempo total de atendimento: %d segundos\n", fila->tempoTotalAtendimento);
    printf("Clientes atendidos: %d\n", totalClientesAtendidos);
    printf("Total de transacoees realizadas: %d\n", totalTransacoes);
    printf("######################################################################################################################\n");
}