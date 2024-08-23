#ifndef SIMATENDIMENTOBANCARIO_H
#define SIMATENDIMENTOBANCARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Estruturas de Dados
typedef struct Transacao
{
    int tipo; // 1-Saque, 2-Depósito, 3-Pagamento, 4-Transferência
    struct Transacao *proxima;
} Transacao;

typedef struct Cliente
{
    int id;
    char nome[50];
    int idade;
    Transacao *transacoes; // Ponteiro para a primeira transação
    time_t tempoEntradaFila;
    int tempoAtendimento;
    double tempoNaFila;
    struct Cliente *proximo;
} Cliente;

typedef struct Fila
{
    Cliente *frente;
    Cliente *tras;
    int totalClientes;
    int tempoTotalAtendimento;
    Cliente *clientesAtendidos;
} Fila;

// Funções

// Função para a criação de novos clientes
Cliente *criarCliente(int id, const char *nome, int idade);

// Função para inicializar a fila
void inicializarFila(Fila *fila);

// Função para enfileirar novos clientes
void enfileirar(Fila *fila, Cliente *cliente);

// Função para remover clientes após o atendimento
Cliente *desenfileirar(Fila *fila);

// Função para atender clientes da fila
void atenderCliente(Fila *fila, Cliente *cliente);

// Função para ler os dados nome e idade do cliente para então criar um novo cliente
Cliente *lerCliente(int id);

// Função para gerar o relatório final
void gerarRelatorio(Fila *fila);

#endif
