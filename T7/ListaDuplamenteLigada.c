#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Tamanho_Lista 10

typedef struct arranjo{
    int chave;
    struct arranjo *proximo;
    struct arranjo *anterior;
}Arranjo;

void inserir(Arranjo **lista, int chave);
Arranjo* remover(Arranjo **lista, int chave);
void imprimir(Arranjo *arranjo);
int validar(char *sus, int valido);

int main(){
    //Declaração de variáveis
    int opcao, valor, anterior, validaNUM, valores_iniciais[4] = {9, 16, 4, 1}, valido;
    Arranjo *removido, *lista = NULL;
    char validaSTR[Tamanho_Lista]; //O valor entre [] no validarSTR é o tamanho max da ListaDLigada em si

    do{
        printf("\n(1) - Iniciar\n(2) - Inserir\n(3) - Remover\n(4) - Imprimir\n(5) - Sair\nOpção: ");
        scanf("%s", &validaSTR[0]);
        opcao = validar(validaSTR, valido);
        printf("\n");

        switch(opcao){
            case 1:
                lista = NULL;
                validaNUM = 0;
                while(validaNUM == 0){
                    printf("Lista padrão? [s/n]\n");
                    scanf("%s", &validaSTR[0]);
                    if(validaSTR[0]=='s'){
                        for(int x=0; x < 4; x++){
                            inserir(&lista, valores_iniciais[x]);
                        }
                        validaNUM = 1;
                    } else if(validaSTR[0]=='n'){
                        for(int x=0; x < 4; x++){
                            printf("Digite um valor [%i/4]: ", (x+1));
                            scanf("%s", &validaSTR[0]);
                            valor = validar(validaSTR, valido);
                            if(valor != -999999999){
                                inserir(&lista, valor);
                            } else{
                                x--;
                            }
                        }
                        validaNUM = 1;
                    }  else{
                        printf("Resposta inválida!\n");
                    }
                }
                printf("\n");
                printf("Lista iniciada:\n");
                imprimir(lista);
                break;
            case 2:
                printf("Digite um valor: ");
                scanf("%s", &validaSTR[0]);
                valor = validar(validaSTR, valido);
                if(valor != -999999999){
                    inserir(&lista, valor);
                    imprimir(lista);
                }
                printf("\n");
                break;
            case 3:
                printf("Digite um valor para a remoção: ");
                scanf("%s", &validaSTR[0]);
                valor = validar(validaSTR, valido);
                validaNUM = 0;

                for(int x=0; x<Tamanho_Lista; x++){
                    removido = remover(&lista, valor);
                    if(removido){
                        validaNUM++;
                    }
                }

                printf("\n");
                if(validaNUM){
                    printf("Elemento removido: %i\nAgora a lista se apresenta assim:\n", valor);
                    free(removido);
                    imprimir(lista);
                } else{
                    printf("Elemento não encontrado!\n");
                }
                break;
            case 4:
                imprimir(lista);
                break;
            default:
                if(opcao != 5){
                    printf("Opção inválida!\n");
                }
        }
    }while(opcao != 5);

    return 0;
}

void inserir(Arranjo **lista, int chave){
    Arranjo *aux, *novo = malloc(sizeof(Arranjo));

    if(novo){
        novo->chave = chave;
        novo->proximo = NULL;

        if(*lista == NULL){
            *lista = novo;
            novo->anterior = NULL;
        } else{
            aux = *lista;
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
            novo->anterior = aux;
        }
    } else{
        printf("Erro ao alocar memoria!\n");
    }
}

Arranjo* remover(Arranjo **lista, int chave){
    Arranjo *aux, *remover = NULL;

    if(*lista){

        if((*lista)->chave == chave){
            remover = *lista;
            *lista = remover->proximo;

            if(*lista){
                (*lista)->anterior = NULL;
            }
        } else{
            aux = *lista;

            while(aux->proximo && aux->proximo->chave != chave){
                aux = aux->proximo;
            }

            if(aux->proximo){
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                if(aux->proximo){
                    aux->proximo->anterior = aux;
                }
            }
        }
    }
       
    return remover;
}

void imprimir(Arranjo *arranjo){
    printf("\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n§Lista: ");
    while(arranjo){
        printf("%i ", arranjo->chave);
        arranjo = arranjo->proximo;
    }
    printf("\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n");
}

int validar(char *invalidado, int valido){
    char *fim = NULL;
    if(strlen(invalidado)>9){
        printf("Valor muito grande!");
        return -999999999;
    }

    valido = strtol(invalidado, &fim, 10);

    if(fim == invalidado || *fim != '\0'){
        printf("Valor inválido!\n");
        return -999999999;
    } else{
        return valido;
    }
}