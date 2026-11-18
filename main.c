#include <stdio.h>
#include "meuBanco.h"

/* Localiza um cliente pelo nome */
int localizarCliente(Banco banco, char nome[]) {

    int i;

    for (i = 0; i < banco.quantidadeClientes; i++) {

        if (strcmp(banco.clientes[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

/* Realiza deposito ou saque */
void movimentarConta(Banco *banco, int operacao) {

    char nome[100];

    int indice;
    int tipo;
    int posicao;

    double valor;

    printf("\nNome do cliente: ");
    scanf(" %99[^\n]", nome);

    indice = localizarCliente(*banco, nome);

    if (indice == -1) {
        printf("\nCliente nao encontrado!\n");
        return;
    }

    Cliente *cliente = &banco->clientes[indice];

    printf("\n01 - Conta corrente\n");
    printf("02 - Conta salario\n");
    printf("03 - Conta poupanca\n");

    printf("\nTipo de conta: ");
    scanf("%d", &tipo);

    posicao = buscarConta(*cliente, tipo);

    if (posicao == -1) {
        printf("\nCliente nao possui esse tipo de conta.\n");
        return;
    }

    printf("Valor: R$ ");
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("\nValor invalido!\n");
        return;
    }

    if (operacao == 1) {

        cliente->saldo[posicao] += valor;

        registrarOperacao(cliente, 3, valor);

        printf("\nDeposito realizado com sucesso!\n");
    }

    else {

        if (cliente->saldo[posicao] < valor) {
            printf("\nSaldo insuficiente!\n");
            return;
        }

        cliente->saldo[posicao] -= valor;

        registrarOperacao(cliente, 4, valor);

        printf("\nSaque realizado com sucesso!\n");
    }

    printf("Saldo atual: R$ %.2f\n",
           cliente->saldo[posicao]);
}

int main() {

    Banco banco;

    int opcao;
    int i;

    banco.quantidadeClientes = 0;
    banco.bancoAberto = 0;

    do {

        printf("\n========================================\n");
        printf("             BANCO DIGITAL\n");
        printf("========================================\n");

        printf("1 - Abrir banco\n");
        printf("2 - Consultar historico\n");
        printf("3 - Efetuar sorteio\n");
        printf("4 - Solicitar emprestimo\n");
        printf("5 - Comprar titulo de capitalizacao\n");
        printf("6 - Consultar clientes\n");
        printf("7 - Realizar deposito\n");
        printf("8 - Realizar saque\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        if (banco.bancoAberto) {

            for (i = 0; i < banco.quantidadeClientes; i++) {
                verificarSaldoNegativo(banco.clientes[i]);
            }
        }

        switch (opcao) {

            case 1:

                if (banco.bancoAberto) {
                    printf("\nO banco ja esta aberto!\n");
                }

                else {

                    printf("\nAbrindo banco...\n");

                    cadastrarClientes(&banco);

                    banco.bancoAberto = 1;

                    printf("\nBanco aberto com sucesso!\n");
                }

                break;

            case 2:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    consultarHistorico(banco);
                }

                break;

            case 3:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    realizarSorteio(&banco);
                }

                break;

            case 4:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    solicitarEmprestimo(&banco);
                }

                break;

            case 5:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    comprarTitulo(&banco);
                }

                break;

            case 6:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    mostrarClientes(banco);
                }

                break;

            case 7:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    movimentarConta(&banco, 1);
                }

                break;

            case 8:

                if (!banco.bancoAberto) {
                    printf("\nAbra o banco primeiro!\n");
                }

                else {
                    movimentarConta(&banco, 2);
                }

                break;

            case 0:

                printf("\nEncerrando o sistema...\n");
                printf("Obrigado por utilizar nosso banco!\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

