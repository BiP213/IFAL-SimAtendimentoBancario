#include "SimAtendimentoBancario.h"

int main()
{
    // Inicializar fila de clientes
    Fila filaClientes;
    inicializarFila(&filaClientes);

    // Menu principal
    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1 - Adicionar cliente\n");
        printf("2 - Iniciar atendimento\n");
        printf("3 - Gerar relatorio\n");
        printf("0 - Finalizar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            // Ler dados dos clientes e adicionar à fila
            Cliente *cliente = lerCliente(filaClientes.totalClientes + 1);
            enfileirar(&filaClientes, cliente);
            break;
        case 2:
            // Atender os clientes
            Cliente *clienteAtendido;
            while ((clienteAtendido = desenfileirar(&filaClientes)) != NULL)
            {
                atenderCliente(&filaClientes, clienteAtendido);
            }
            printf("\nAtendimento concluido.\n");
            break;
        case 3:
            // Gerar relatório
            gerarRelatorio(&filaClientes);
            break;
        case 0:
            // Finalizar programa
            printf("\nFinalizando...\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    // Liberar a memória dos clientes atendidos
    Cliente *cliente = filaClientes.clientesAtendidos;
    while (cliente != NULL)
    {
        // Salvar o próximo cliente para não perder a referência
        Cliente *clienteProx = cliente->proximo;

        // Liberar a memória de todas as transações desse cliente
        Transacao *transacaoAtual = cliente->transacoes;
        while (transacaoAtual != NULL)
        {
            Transacao *transacaoProx = transacaoAtual->proxima;
            free(transacaoAtual);
            transacaoAtual = transacaoProx;
        }

        // Liberar a memória do cliente em si
        free(cliente);

        // Atualizar o ponteiro para o próximo cliente na fila
        cliente = clienteProx;
    }

    return 0;
}
