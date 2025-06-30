#ifndef OCORRENCIAS_H
#define OCORRENCIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 15
#define TAM_MAX 50
//struct lista ENCADEADEADA DE OCORRENCIAS
typedef struct CelulaOcorrencias *ApontadorIndice;
typedef struct CelulaOcorrencias{
  int numeroOcorrencias;
  int idDoc;
  ApontadorIndice Prox;
}CelulaOcorrencias;

typedef struct {
  ApontadorIndice Primeiro, Ultimo;
} TipoLista;


void FLVaziaEncadeada(TipoLista *Lista);
int VerificaVaziaEncadeada(TipoLista Lista);
void InsereEncadeada(int idoc, TipoLista *Lista);
void ImprimeEncadeada(TipoLista Lista);


#endif