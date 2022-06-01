/* Integrantes 
Ana Helena Marcacini            RA: 20.01305-0
Ettore Padula Dalben            RA: 20.00387-0
Pedro Henrique Sant’Anna Hein   RA: 20.00134-7
*/


// Inclusão das bibliotecas
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição de valores estáveis
#define Tamanho_Lista 8 // tamanho da lista
#define Valores_Iniciais {{5,9,-1}, {2,16,7}, {3,4,5}, {-1,1,2}}    // matriz com os valores pré-definidos
#define L 7 // indice inicial da lista

// Criação do tipo arranjo, estrutura da lista duplamente ligada
typedef struct arranjo{
    int proximo;    // aponta para o endereço do próximo valor
    int chave;      // valor do endereço atual
    int anterior;   //aponta para o endereço anterior
}Arranjo;

// Estruturação das funções
Arranjo inserir(Arranjo arranjo[], Arranjo add);    // função para colocar valores à lista
Arranjo remover(Arranjo arranjo[], int chave);      // função para retirar valores na lista
void imprimir(Arranjo arranjo[]);   // função para mostrar o conteúdo da lista
int validar(char invalidado[], int valido); // função para validar os valores digitados pelo usuário

// Programa principal
int main(){
    // Declaração de variáveis
    int opcao , valor, validaNUM, ValInit[4][3] = Valores_Iniciais, auxint = L;
    /*  opcao - capta o item selecionado pelo usuário
        valor - valor a ser adicionado como chave do item da lista
        validaNUM - auxiliar para validar se o valor inserido é válido [funciona como um booleano]
        ValInit - matriz dos valore iniciais, predefinidos ou selecionados pelo usuário
        auxint - indice para percorrer a lista  */
    
    Arranjo lista[Tamanho_Lista], auxi;
    /*  lista - a própria lista duplamente ligada
        auxi - auxiliar para fazer inserção e remoção de variáveis  */

    char validaSTR[1]; // validaSTR - recepção dos valores digitados

    // Inserindo um valor inválido em todos os espaços da lista, para funcionamento as operações
    for(auxint = 0; auxint < Tamanho_Lista; auxint++){
        lista[auxint].proximo = -999999999;
        lista[auxint].chave = -999999999;
        lista[auxint].anterior = -999999999;
    }

    // loop principal de operação
    do{
        printf("\n(1) - Iniciar\n(2) - Inserir\n(3) - Remover\n(4) - Imprimir\n(5) - Sair\nOpção: ");   // menu para o usuário 
        scanf("%s", &validaSTR);            // pegar input
        opcao = validar(validaSTR, opcao);  // valida se tem uma string
        printf("\n");   // espaçamento para separação de ações
        auxint = L; // indice da lista aplicado a uma variável
        validaNUM = 0;  // supõem-se um valor inicial verdadeiro 

        // ação das opções
        switch(opcao){
            case 1:
                // para iniciar a lista
                while(validaNUM == 0){

                    // limpa a lista, para que seja reiniciada
                    for(int x = 0; x<Tamanho_Lista; x++){
                        lista[x].chave = -999999999;
                        lista[x].anterior = -999999999;
                        lista[x].proximo = -999999999;
                    }

                    // questionamento para valor predefinido ou nova série de valores
                    printf("Lista padrão? [s/n]\n");
                    scanf("%s", &validaSTR);

                    // inserção dos valores pré-definidos
                    if(validaSTR[0]=='s'){
                        for(int x = 0; x < 4; x++){
							auxi.proximo = ValInit[x][0];
							auxi.chave = ValInit[x][1];
							auxi.anterior = ValInit[x][2];
                            inserir(lista, auxi);
                        }

                        validaNUM = 1;  // fim do looping de iniciação

                    // inserção de valores selecionados pelo usuário
                    } else if(validaSTR[0]=='n'){
                        // 4 valores serão inseridos em série
                        for(int x=0; x < 4; x++){
                            printf("Digite um valor [%i/4]: ", (x+1));
                            scanf("%s", &validaSTR);
                            valor = validar(validaSTR, valor);

                        // verfica a validade do valor antes da inserção
                            if(valor != -999999999){
                                auxi.proximo = -1;
                                auxi.chave = valor;
                                auxi.anterior = -999999999;
                                inserir(lista, auxi);
                            } else{
                                x--;    // caso o valor seja inválido, para que sejam completados os 4 valores
                            }
                        }

                        validaNUM = 1; // segunda possibilidade de fim de looping

                    // se un valor não inteiro for inserido
                    } else{
                        printf("Resposta inválida!\n");
                    }
                }

                // retorno amigável ao usuário
                printf("\n");
                printf("Lista iniciada:\n");
                imprimir(lista);
                break; // fim da opção de iniciação
            
            // para inserir um valor
            case 2:
                // inserção de valor por digitação
                printf("Digite um valor: ");
                scanf("%s", &validaSTR);
                valor = validar(validaSTR, valor);  //validação do valor

                // verificação da validade do valor, seguido por um retorno da estrutura da lista ao usuário
                if(valor != -999999999){
                    // admite-se que o valor inserido será o último da lista
					auxi.proximo = -1;
					auxi.chave = valor;
					auxi.anterior = -999999999; // o valor de anterior será atribuído na função inserir

                    // chamada das funções
                    inserir(lista, auxi);
                    imprimir(lista);
                }

                printf("\n");
                break;  // fim da opção de inserção
            
            // para remover um valor
            case 3:
                // digitação do valor a ser removido
                printf("Digite um valor para a remoção: ");
                scanf("%s", &validaSTR);
                valor = validar(validaSTR, valor);  //validação do valor

                // chamada das funções
                remover(lista, valor);
                imprimir(lista);
                break; // fim da opção de remoção
            
            // para imprimir a lista
            case 4:
                // apenas chama a função para imprir a lista 
                imprimir(lista);
                break;  // fim da opção de impressão

            // para avisar o usuário sobre a validade do valor
            default:
                // verifica se a opção é 5 para encerrar o looping
                if(opcao != 5){
                    printf("Opção inválida!\n");
                }
        }
    }while(opcao != 5); // comparação com o valor 5 para térmmino de operações

    return 0;   // retorno padrão
}

// Função de inserção
Arranjo inserir(Arranjo arranjo[], Arranjo add){
    // Definição de variáveis
    int auxint = L; // auxiliar de indice para obtenção dos valore das listas
    
    // para identificar se a lista está cheia
    for(int x = 0; x<Tamanho_Lista; x++){
        if(arranjo[x].chave==-999999999){
            break; // saída averiguando que a lista tem espaços para inserção
        } else{
            printf("A lista está cheia!\n");    // mensagem ao usuário
            return arranjo[auxint]; // término da função sem alteração na lista
        }
    }
    
    // inserção do valor caso seja o primeiro valor (funciona apenas para o primeiro valor pré-definido) 
    if(add.anterior == -1){
        // atribuições dos valores à lista
		arranjo[auxint].chave = add.chave;
		arranjo[auxint].anterior = add.anterior;
		arranjo[auxint].proximo = add.proximo;

    // inserção para os demais valores iniciais pré-definido
    } else if(add.anterior < 8 && add.anterior >= 0){
        auxint = arranjo[add.anterior].proximo; //obtenção do indice do valor a ser inserido

        // verifica se o indice condiz com o valor indice próximo do valor anterior
        if(arranjo[add.anterior].proximo != -1){
            // atribuições dos valores à lista
            arranjo[auxint].chave = add.chave;
            arranjo[auxint].anterior = add.anterior;
            arranjo[auxint].proximo = add.proximo;
        }
    // inserção dos valores não pré-definidos
    } else if(add.proximo == -1){
        auxint = rand() % 8;    // valor aleatório de 0 a 7 que será o índice do novo valor

        // looping caso o indice sorteado já esteja ocupado
        while(arranjo[auxint].chave != -999999999){
            auxint = rand() % 8;
        }

        // busca do antigo valor final da lista
        for(int x = 0; x<Tamanho_Lista; x++){
            if(arranjo[x].proximo == -1){
                arranjo[x].proximo = auxint;    // novo próximo endereço do até então valor final da lista
                // atribuições dos valores à lista
                arranjo[auxint].chave = add.chave;
                arranjo[auxint].anterior = x;
                arranjo[auxint].proximo = add.proximo;
                break;  // quebra da condicional
            
            // caso o valor inserido seja o primeiro valor
            } else if(x==(Tamanho_Lista-1)){
                // atribuições dos valores à lista
                arranjo[auxint].chave = add.chave;
                arranjo[auxint].anterior = -1;
                arranjo[auxint].proximo = add.proximo;
            }
        }
      
    // para casos não previstos
    } else{
        printf("Valor inválido!\n");
        return arranjo[-1]; // retorna a lista sem alterações 
    }

    return arranjo[-1]; // retorno de segurança
}

// Função de remoção
Arranjo remover(Arranjo arranjo[], int chave){
    // Percorre toda a lista procurando o(s) valor(es) para retirá-lo(s)
    for(int x = 0; x<Tamanho_Lista; x++){
        // verifica se o valor do endereço é o procurado
        if(arranjo[x].chave==chave){
            // reatribui os endereços anterior e próximo dos elementos ligados ao removido
            arranjo[arranjo[x].anterior].proximo = arranjo[x].proximo;
            arranjo[arranjo[x].proximo].anterior = arranjo[x].anterior;

            // limpa o endereço removido
            arranjo[x].proximo = -999999999;
            arranjo[x].chave = -999999999;
            arranjo[x].anterior = -999999999;
        }
    }
    return arranjo[Tamanho_Lista];  //retorno da função
}

// Função de impressão
void imprimir(Arranjo arranjo[]){
    int init = 0;   // endereço inicial para a impressão, não pode ser alterado durante as operações

    // percorre a lista procurando o endereço inicial
	for(int x = 0; x<Tamanho_Lista; x++){
        // verifica se o valor anterior é -1, o que marca o início da lista
        if(arranjo[x].anterior==-1){
            init = x;   // variável externa obtem o índice inicial
            break;  // saída cado o endereço seja encontrado
        }
    }

    int auxint = init;  // pode ser alterada para a impressão dos outros valores
    Arranjo aux = arranjo[init];    // auxilia na obtenção dos próximos valores a serem impressos

    // verifica se a lista não está vazia
    if(aux.proximo != -999999999){
        // decoração
        printf("\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n");
        printf("§Próximo:\t");  // título da cadeia de inpressão

        // percorre todos os valores de próximo endereço
        for(int x = init; aux.proximo != -1; x = aux.proximo){
            printf("%i\t", aux.proximo); // exibição do "próximo"
            aux = arranjo[aux.proximo]; // obtenção do próximo endereço
        }

        auxint = aux.proximo; // valor final a ser exibido
        printf("%i\t", auxint); // exibição do "próximo" final, espera-se (-1)
        printf("\n§Chave:\t\t");    // título da próxima cadeia de inpressão

        // percorre todos os valores das chaves
        for(int x = init; arranjo[x].proximo != -1; x = arranjo[x].proximo){
            printf("%i\t", arranjo[x].chave);   // exibição da "chave"
        }

        printf("%i\t", aux.chave);   // exibição da "chave" final
        printf("\n§Anterior:\t");   // título da próxima cadeia de inpressão

        // percorre todos os valores de endereço anterior
        for(int x = init; arranjo[x].proximo != -1; x = arranjo[x].proximo){
            printf("%i\t", arranjo[x].anterior);    // exibição do "anterior"
        }
        
        printf("%i\t", aux.anterior);   // exibição do "anterior" final
        // decoração
        printf("\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n");
   
    // aviso de lista vazia
    } else{
        printf("A lista está vazia");
    }
}

// Função validador
int validar(char invalidado[], int valido){
    char *fim = NULL; // ponteiro para validação
	
    // verifica o tamanho do valor inserido
    if(strlen(invalidado)>9){
        // valor máximo suportdo por variáveis int é 9 digitos + sinal
        printf("Valor muito grande!");
        return -999999999;  //valor padrão de vazio
    }

    valido = strtol(invalidado, &fim, 10); // transforma a string em long int 

    // verifica se o valor está vazio ou com character nulo
    if(fim == invalidado || *fim != '\0'){
        printf("Valor inválido!\n");
        return -999999999;  //valor padrão de vazio
    } else{
        return valido;  // retorna o valor quando válido
    }
}