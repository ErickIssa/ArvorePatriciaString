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
    ApontadorIndice ant = Lista->Primeiro;
    ApontadorIndice atual = Lista->Primeiro->Prox;

    // Percorre até achar o ponto de inserção (id maior ou igual)
    while (atual != NULL && atual->idDoc < idoc) {
        ant = atual;
        atual = atual->Prox;
    }

    // Se já existe, incrementa
    if (atual != NULL && atual->idDoc == idoc) {
        atual->numeroOcorrencias += 1;
        return;
    }

    // Cria novo nó
    ApontadorIndice novo = (ApontadorIndice) malloc(sizeof(CelulaOcorrencias));
    if (novo == NULL) {
        printf("Erro MALLOC\n");
        exit(1);
    }
    novo->idDoc = idoc;
    novo->numeroOcorrencias = 1;
    novo->Prox = atual;

    // Insere na lista
    ant->Prox = novo;

    // Atualiza ponteiro de último se inseriu no final
    if (novo->Prox == NULL) {
        Lista->Ultimo = novo;
    }
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
        printf("<Id: %d // qntd: %d> ", Aux->idDoc, Aux->numeroOcorrencias);
        Aux = Aux->Prox;
    }
}
