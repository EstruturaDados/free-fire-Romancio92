//inclusao de bibliotecas.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definição de constante.
#define TAM 10

//definição da struct item.
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade; 
    int prioridade;   
} item;

//declaração das funções.
/*O modificador const (abreviação de constant) é uma palavra-chave em C que tem um papel crucial: 
prometer que o valor da variável que está sendo apontada não será alterado dentro daquela função.*/
void menu(item *ptritens, int *opcao, int *cont_atual);
void submenu(int *opcao2);
void inicializaritem(int *cont_atual);
void inseriritens(item *ptritens, const char *texto, const char *tipo_item, int quantidade, int *cont_atual, int prioridade);
void limparBufferEntrada();
void liberarMemoria(item *ptritens);
void removeritens(item *ptritens, int *cont_atual, const char *texto);
void listaritens(item *ptritens, int *cont_atual);
int buscaritens (item *ptritens, int *cont_atual, const char *texto);
void imprimirResultado(const char *texto, item *ptritens, int *cont_atual);
void bubbleSort(item *ptritens, int * cont_atual);
void insertionSort(item *ptritens, int *cont_atual);
void trocar(item *a, item *b) ;
void selectionsort(item *ptritens, int *cont_atual);

//definição da função principal.
int main (void)
{

    //declaração de variáveis.
    //definição de um ponteiro que aponta para a struct item; ponto de acesso para a mochila.
    item *ptritens; 
    int cont_atual, opcao, opcao2, quantidade, prioridade;
    char texto[20], tipo_item[20];

    //alocação de memoria de forma dinâmica.
    ptritens = (item *) malloc(TAM * sizeof(item));
    //verificação de alocação de memoria.
    if (ptritens == NULL)
    {
        printf("Erro: Falha ao alocar memoria.");
        return 1;
    }

    inicializaritem(&cont_atual);
    
    do
    {
        //inserir função de exibir menu.
        menu(ptritens, &opcao, &cont_atual);            

        switch(opcao)
        {
            case 1: 
                printf("Insira um item: ");
                fgets(texto, 20, stdin); 
                texto[strcspn(texto, "\n")] = 0;
                printf("Indique o tipo do item adicionado: ");    
                fgets(tipo_item, 20, stdin); 
                tipo_item[strcspn(tipo_item, "\n")]= 0;  
                printf("Indique a quantidade: ");    
                scanf("%i", &quantidade);
                limparBufferEntrada();   
                printf("nível de prioridade (1-5): ");
                scanf("%i", &prioridade);
                limparBufferEntrada(); 
                /*Em C, quando você usa o nome de um array em uma expressão (como em uma chamada de função), 
                o compilador automaticamente o converte para um ponteiro para o primeiro elemento desse array. 
                Ou seja, texto (o array) é automaticamente interpretado como &texto[0] (o endereço do primeiro caractere).*/

                //Essa variável (quantidade) não usa o & porque ela é passada por valor.
                inseriritens(ptritens, texto, tipo_item, quantidade, &cont_atual, prioridade);

                break;
            case 2:                 
                printf("Remova um item: \n");
                fgets(texto, 20, stdin);
                texto[strcspn(texto, "\n")] = 0;
                removeritens(ptritens, &cont_atual, texto);
                break;
            case 3:
                listaritens(ptritens, &cont_atual);
                break;   
            case 4: 
                submenu(&opcao2);
                switch(opcao2)
                {
                    case 1: 
                        bubbleSort(ptritens, &cont_atual);
                        printf("--- Ordenado por nome ---");
                        listaritens(ptritens, &cont_atual);
                        break;
                    case 2: 
                        insertionSort(ptritens, &cont_atual);
                        printf("--- Ordenado por tipo ---");
                        listaritens(ptritens, &cont_atual);
                        break;
                    case 3:
                        selectionsort(ptritens, &cont_atual);
                        printf("--- Ordenado por prioridade ---");
                        listaritens(ptritens, &cont_atual);
                        break;
                    case 0: 
                        printf("Voltar para tela inicial...\n");
                        break;
                }
                break;                 
            case 5:
                printf("Qual item deseja buscar? \n");
                fgets(texto, 20, stdin);
                texto[strcspn(texto, "\n")] = 0;
                buscaritens (ptritens, &cont_atual, texto);
                imprimirResultado(texto, ptritens, &cont_atual);
                break;           
            case 0:            
                printf("\n\nFuga efetivada com sucesso! Sair do sistema...\n\n");         
                break;
            default:            
                printf("\n\nOpção inválida. Tente novamente!\n\n");            
                break;
        }
        
    } while (opcao != 0);
    

    liberarMemoria(ptritens);
    

    return 0;
}


//definição de funções.
//definição de função de menu.
void menu(item *ptritens, int *opcao, int *cont_atual)
{
    printf("===========================================\n");
    printf("PLANO DE FUGA - CODIGO DA ILHA\n");
    printf("===========================================\n");
    printf("Itens na mochila: %i/%i\n\n", *cont_atual,TAM);    
    printf("1. Inserir item na mochila (loot).\n");
    printf("2. Remover item da mochila.\n");
    printf("3. Listar componentes (inventário).\n");
    printf("4. Organizar mochila (ordenar componentes).\n");
    printf("5. Busca binária por componente-chave (por nome).\n");
    printf("0. Ativar a torre de fuga.\n\n");
    printf("Escolha a opção que deseja executar: \n");
    //função scanf nao necessita do '&', pois a função ja estabelece que é um ponteiro.
    scanf("%i", opcao);
    limparBufferEntrada();
}

//definição de função para submenu do item 4.
void submenu(int *opcao2)
{
    printf("Como deseja ordenar os componentes?\n");
    printf("1. por nome (ordem alfabética)\n");
    printf("2. por tipo\n");
    printf("3. por prioridade de montagem\n");
    printf("0. voltar\n\n");
    printf("Escolha o critério: ");
    scanf("%i", opcao2);
    limparBufferEntrada();
}

//definição de função de limpar buffer de entrada.
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);           
}

//definição de função para inicializar contador em "0".
void inicializaritem(int *cont_atual)
{
    *cont_atual = 0;
}

//definição de função para inserir itens.
void inseriritens(item *ptritens, const char *texto, const char *tipo_item, int quantidade, int *cont_atual, int prioridade)
{
    int i;
    
    if (*cont_atual == TAM)
    {
        printf("\nErro: a lista está cheia! Não é possível inserir item.\n");
        return;
    }

    int indice = *cont_atual; 
    strcpy(ptritens[indice].nome, texto);
    strcpy(ptritens[indice].tipo, tipo_item);
    ptritens[indice].quantidade = quantidade;
    ptritens[indice].prioridade = prioridade;

    printf("\nitem %s (tipo: %s, qtd: %i, prioridade: %i) inserido com sucesso!\n", texto, tipo_item, quantidade, prioridade);
    (*cont_atual)++;

    printf("\n=====================================\n");  
    printf("INVENTÁRIO ATUALIZADO (1)\n");
    for(i = 0; i < *cont_atual; i++)
    {              
        printf("Item: %-10s       | Tipo: %-10s       | Qte: %-5i       | Prioridade: %i\n", ptritens[i].nome, ptritens[i].tipo, ptritens[i].quantidade, ptritens[i].prioridade);
    }
    printf("\n=====================================\n");
}

//definição de função para remover itens.
void removeritens(item *ptritens, int *cont_atual, const char *texto)
{
    int i, pos = -1;
    
    if (*cont_atual == 0)
    {
        printf("Não há itens na mochila!\n");
        return;
    }
    
    for(i = 0; i < *cont_atual; i++)
    {
    
        if(strcmp(ptritens[i].nome, texto) == 0)
        {
        pos = i;
        printf("item removido com sucesso!\n");
        break;
        }        
    }
        if(pos == -1)
        {
        printf("Erro: o item %s não foi encontrado!\n", texto);
        return;
        }
    // Desloca todos os itens uma posição para trás, cobrindo o item na posição 'pos'
    for(i = pos; i < *cont_atual - 1; i++)
    {
        // Copia o item da frente (i+1) para a posição atual (i)
        ptritens[i] = ptritens[i + 1];
    }
    
    // Diminui o contador de itens na mochila
    (*cont_atual)--;

    printf("Item '%s' removido com sucesso! Itens restantes: %i/%i\n", texto, *cont_atual, TAM);

    printf("\n=====================================\n");  
    printf("INVENTARIO ATUALIZADO (2)\n");
    for(i = 0; i < *cont_atual; i++)
    {              
         printf("Item: %-10s       | Tipo: %-10s       | Qte: %-5i       | Prioridade: %i\n", ptritens[i].nome, ptritens[i].tipo, ptritens[i].quantidade, ptritens[i].prioridade);
    }
    printf("\n=====================================\n");
}


//definição de função para listar itens.
void listaritens(item *ptritens, int *cont_atual)
{
    int i;
    if (*cont_atual == 0)
    {
        printf("Não há itens na mochila!\n");
    }
    else
    {
    printf("\n=====================================\n"); 
    printf("INVENTÁRIO ATUALIZADO (3)\n");
    for(i = 0; i < *cont_atual; i++)
    {              
         printf("Item: %-10s       | Tipo: %-10s       | Qte: %-5i       | Prioridade: %i\n", ptritens[i].nome, ptritens[i].tipo, ptritens[i].quantidade, ptritens[i].prioridade);
    }
    printf("\n=====================================\n");
    }
}

//definição de função para liberar memoria.
void liberarMemoria(item *ptritens)
{
    free(ptritens);
    printf("memoria liberada com sucesso.");
}

//definição de função para buscar itens de forma binária.

int buscaritens (item *ptritens, int *cont_atual, const char *texto)
{
    int inicio = 0, fim = *cont_atual - 1;

    while(inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        if(strcmp(ptritens[meio].nome, texto) == 0)
        {
            return meio;
        }
        else if(strcmp(ptritens[meio].nome, texto) > 0)
        {
            inicio = meio +1;
        }
        else
        {
            fim = meio - 1;
        }
        
    }
    return -1;
}

void imprimirResultado(const char *texto, item *ptritens, int *cont_atual)
{
    int i;

    for(i = 0; i < *cont_atual; i++)
    {
        if (strcmp(texto, ptritens[i].nome) == 0)
        {
            printf("\n-----------------------------\n");
            printf("\nDESCRIÇÃO DO ITEM BUSCADO\n");
            printf("item: %s\n", ptritens[i].nome);
            printf("Tipo: %s\n", ptritens[i].tipo);
            printf("Qte: %i\n", ptritens[i].quantidade);
            break;
        }        
        else
        {
            printf("\nitem não encontrado!\n");
        }

    }
   
}



//definição de função de trocar.
void trocar(item *a, item *b) 
{
    item temp = *a;
    *a = *b;
    *b = temp;
}
//definição de função para ordenação dos itens por nome.
void bubbleSort(item *ptritens, int *cont_atual)
{
    int i, j;
    int trocou;

    for(int i = 0; i < *cont_atual - 1; i++)
    {
        trocou = 0;

        for(j = 0; j < *cont_atual - 1 - i; j++)
        {
            if (strcmp(ptritens[j].nome, ptritens[j+1].nome) > 0)
            {
                trocar(&ptritens[j], &ptritens[j + 1]);
                trocou = 1;
            }            
        }
        if (trocou == 0)
        {
            break;
        }
    }

}

//definição de função ordenação dos itens por tipo.
void insertionSort(item *ptritens, int *cont_atual)
{
    for (int i = 1; i < *cont_atual; i++) 
    {
        item chave = ptritens[i];
        int j = i - 1;

        // Move os elementos maiores que a chave uma posição à frente
        while (j >= 0 && strcmp(ptritens[j].tipo, chave.tipo) > 0) 
        {
            ptritens[j + 1] = ptritens[j];
            j--;
        }

        ptritens[j + 1] = chave;
    }
} 

//definição de função ordenação dos itens por prioridade.
void selectionsort(item *ptritens, int *cont_atual)
{
    for (int i = 0; i < *cont_atual - 1; i++) 
    {
        int indiceMenor = i;
        for (int j = i + 1; j < *cont_atual; j++) 
        {
            if (ptritens[j].prioridade < ptritens[indiceMenor].prioridade)
            {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            trocar(&ptritens[i], &ptritens[indiceMenor]);
        }
    }
} 