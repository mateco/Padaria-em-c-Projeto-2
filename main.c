#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int retornar = 1; // Variavel global pra informar q o "retornar" sempre seja 1

struct produtos
{
    char nome[15];
    float valor;
    int cod;
    int Estoque;
    int Quantidade;
    float Subtotal;
    int vendas;
};
struct produtos prod[5] =
{
    {"Pao de forma  ", 7.50, 1, 0},
    {"Pao de centeio", 8.69, 2, 0},
    {"Broa de milho ", 5.00, 3, 0},
    {"Sonho         ", 4.50, 4, 0},
    {"Tubaina       ", 3.25, 5, 0}
};
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
int CadastrarEstoque()
{
    int i, opc, Qtd = -1;

    printf("\n| Posicao no vetor | Codigo do item |      Item      |\n\n"); // Tabela de cadastro de estoque
    for(i = 0; i < 5; i++) // Laço para construir a tabela
    {
        printf("|        %d         |       %d        | %s |\n", i, prod[i].cod, prod[i].nome); // Exibição da tabela
    }
    while(opc < 1 || opc > 5) // looping caso seja digitado algum numero que nao esteja entre 1 e 5
    {
        printf("\nDigite o codigo do item que deseja alterar o estoque: ");
        scanf("%d", &opc);

        if(opc < 1 || opc > 5)
        {
            printf("\n                  Código inválido\n");
        }
    }
    while(Qtd < 0) // looping caso seja digitado algum numero abaixo de 0
    {
        printf("\nDigite a quantidade do estoque do item selecionado: ");
        scanf("%d", &Qtd);

        if(Qtd < 0)
        {
            printf("\nQuantidade invalida, a mesma deve ser maior ou igual a zero. \n");
        }
    }
    prod[opc-1].Estoque += Qtd; // Armazenando a quantidade em um vetor de estoque

    printf("\nEstoque atualizado com sucesso.\n\n");
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
int VisualizarEstoque()
{
    int i;

    printf("\n| Item (Codigo) | Nome do item     | Valor (Unidade) | Estoque\n\n"); // Tabela da visualização de estoque
    for(i = 0; i < 5; i++) // Laço para construir a tabela
    {
        printf("| %d             | %s   | R$ %.2f         | %d\n",prod[i].cod, prod[i].nome, prod[i].valor, prod[i].Estoque); // Exibição da tabela
    }
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
int RealizarVenda()
{
    int i, j, opc_Troco, opc = 1, item, Qtd, opc_Pag, Num_parcelas;
    float troco, saldo, desconto, valor_parcelas, acrescimo, r = 0;

    while(opc == 1)
    {
        printf("\n| Item (Codigo) | Nome do item     | Valor (Unidade) |\n\n"); // Tabela de compras
        for(i = 0; i < 5; i++) // Laço para construir a tabela
        {
            printf("| %d             | %s   | R$ %.2f         |\n",prod[i].cod, prod[i].nome, prod[i].valor); // Exibição da tabela
        }
        printf("\nDigite o código do item que deseja: ");
        scanf("%d", &item);

        if(item < 1 || item > 5)  // Verificar se o código de produto está correto
        {
            printf("Codigo de produto invalido, selecione o produto novamente\n");
            continue;
        }
        printf("Digite a quantidade do produto: ");   // Selecao de quantidade do produto
        scanf("%d", &Qtd);

        if(Qtd <= 0 || Qtd > prod[item-1].Estoque)   // Verificar se a quantidade do produto está correto e repetircaso nao seja
        {
            printf("\nQuantidade invalida!! Deseja tentar realizar a compra novamente? 1-Sim / 2-Nao:  ");
            scanf("%d", &opc);
            if(opc != 1)
            {
                return 0;
            }
        }

        prod[item-1].Quantidade += Qtd;  // Adiciona a quantidade de itens ao struct de itens vendidos
        prod[item-1].Subtotal = prod[item-1].Quantidade * prod[item-1].valor;  // cálculo do total das compras
        prod[item-1].Estoque -= prod[item-1].Quantidade;  // Subtrai o estoque comprada pela quantidade

        r += prod[item-1].Subtotal;

        printf("\nDeseja fazer uma nova compra?\n1. Sim\n2. Nao\n");
        scanf("%d", &opc);

        struct produtos temp_prod[5];
        for (int i = 0; i < 5; i++)
        {
            temp_prod[i] = prod[i];
        }
    }
    // Ordenar os valores dos produtos do mais caro para o mais barato
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 4 - i; j++)
        {
            if(prod[j].Subtotal < prod[j+1].Subtotal)
            {
                struct produtos temp = prod[j];
                prod[j] = prod[j+1];
                prod[j+1] = temp;
            }
        }
    }
    // Nota fiscal
    printf("|Codigo         | Nome do item     | Valor (Unidade) | Quantidade | Subtotal\n");
    for(i = 0; i < 5; i++)
    {
        if(prod[i].Quantidade > 0)
        {
            printf("| %d             | %s   | R$ %.2f         | %d          | R$ %.2f\n",i+1, prod[i].nome, prod[i].valor, prod[i].Quantidade, prod[i].Subtotal);
        }
    }
    printf("---------------------------------------------------------------------------\n");
    printf("|                                                    |Total       | R$ %.2f\n",  r);
    printf("---------------------------------------------------------------------------");

    // Forma de pagamentos
    printf("\nForma de pagamento:\n");
    printf("1- À vista\n");
    printf("2- À prazo\n");
    scanf("%d", &opc_Pag);

    while(opc_Pag < 1 || opc_Pag > 2)  // Verificar se a opção digitada está correta
    {
        printf("\nOpção de pagamento invalida!! Digite novamente\n");
        scanf("%d", &opc_Pag);
    }

    //                  Pagamento a vista;
    if(opc_Pag == 1)
    {
        if(r <= 50)
        {
            desconto = r * 0.05; // 5% de desconto
            r -= desconto;
        }
        else if(r < 100)
        {
            desconto = r * 0.1; // 10% de desconto
            r -= desconto;
        }
        else
        {
            desconto = r * 0.18; // 18% de desconto
            r -= desconto;
        }

        printf("\nPagamento a vista selecionado, precisa de troco?\n1.Sim\n2.Nao\n");
        scanf("%d", &opc_Troco);

        if(opc_Troco == 1)
        {
            printf("Valor de seu saldo: ");
            scanf("%f", &saldo);

            while(saldo < r)  // Verifica se o saldo do cliente é suficiente para realizar a compra
            {
                printf("Saldo insuficiente!! Tente novamente\n");
                scanf("%f", &saldo);
            }
            troco = saldo - r;
            printf("Troco: R$ %.2f\n", troco);
            printf("Desconto de : R$ %.2f\n", desconto);
        }
    }
    //               Pagamento a prazo
    else if(opc_Pag == 2)
    {
        printf("\nValor total da compra: R$ %.2f\n", r);
        printf("Digite o numero de parcelas: ");
        scanf("%d", &Num_parcelas);

        while(Num_parcelas <= 0)   // Verificar se o numero de parcelas está correto (se não é igual ou menor que 0)
        {
            printf("“Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela.");
            scanf("%d", &Num_parcelas);
        }

        if(Num_parcelas > 3)                  // Se numero de parcelas maior que 3 = 8% de acréscimo
        {
            acrescimo = r * 0.08;
            r += acrescimo;
        }
        else
        {
            acrescimo = r * 0.05;    // Caso contrário, 5% de acréscimo
            r += acrescimo;
        }

        valor_parcelas = r / Num_parcelas;  // Calcular valor de cada parcela e apresentar numero de parcelas e acréscimos
        printf("\n%d parcelas de: R$ %.2f\n", Num_parcelas, valor_parcelas);    // Apresentar número de parcelas e seus respectivos valores
        printf("Acrescimo de: R$ %.2f\n", acrescimo);                           // Apresentar o acréscimo que foi incluido
    }
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
int main()
{
    setlocale(LC_ALL, "portuguese"); //cod para escrever com ç e acento
    int opc;

    while(retornar == 1)
    {
        // Apresentar menu inicial
        printf("\n1 - Cadastrar estoque\n");
        printf("2 - Visualizar estoque\n");
        printf("3 - Realizar venda\n");
        printf("4 - Sair\n");

        printf("\nDigite a opção: ");
        scanf("%d", &opc);

        switch(opc)   // caso seja digitado dentre as opções 1,2 e 3, vão ser levadas as suas respectivas funções
        {
        case 1:
            CadastrarEstoque();
            break;
        case 2:
            VisualizarEstoque();
            break;
        case 3:
            RealizarVenda();
            break;
        case 4:
            // Relatório de itens que foram vendidos
            printf("| Nome do item      | Itens vendidos\n");
            for(int i = 0; i < 5; i++)
            {
                printf("| %s    | %d\n", prod[i].nome, prod[i].Quantidade);
            }
            printf("\nSaindo do programa...\n");
            return 0;
        default:
            printf("\nOpção inválida\n");
            break;
        }
    }
    return 0;
}
