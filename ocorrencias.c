#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ocorrencias.h"


void FLVaziaEncadeada(TipoLista *Lista) {
    if (Lista->Primeiro != NULL) {
        printf("Lista ja inicializada\n");
        return;
    }
    Lista->Primeiro = (ApontadorIndice) malloc(sizeof(CelulaOcorrencias));
    if (Lista->Primeiro == NULL) {
        printf("Erro MALLOC\n");
        exit(1);
    }
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->idDoc = 0;
    Lista->Primeiro->numeroOcorrencias = 0;
    Lista->Primeiro->Prox = NULL;
}


int VerificaVaziaEncadeada(TipoLista Lista) {
    if(Lista.Primeiro->Prox == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

void InsereEncadeada(int idoc, TipoLista *Lista) {
    ApontadorIndice aux = Lista->Primeiro->Prox;

    // verifica se o idDoc já existe
    while (aux != NULL) {
        if (aux->idDoc == idoc) {
            aux->numeroOcorrencias += 1;
            return;
        }
        aux = aux->Prox;
    }
    // se nao cria novo nó
    Lista->Ultimo->Prox = (ApontadorIndice) malloc(sizeof(CelulaOcorrencias));
    if (Lista->Ultimo->Prox == NULL) {
        printf("Erro MALOC\n");
        exit(1);
    }
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->idDoc = idoc;
    Lista->Ultimo->numeroOcorrencias = 1;
    Lista->Ultimo->Prox = NULL;
}


void ImprimeEncadeada(TipoLista Lista) {
    if (Lista.Primeiro == NULL) {
        printf("Lista nao iniciada\n");
        return;
    }
    ApontadorIndice Aux = Lista.Primeiro->Prox;
    if (Aux == NULL) {
        printf("Lista indices vazia\n");
        return;
    }
    while (Aux != NULL) {
        printf("Id: %d // qntd: %d\n", Aux->idDoc, Aux->numeroOcorrencias);
        Aux = Aux->Prox;
    }
}
