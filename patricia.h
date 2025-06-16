#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 15
#define TAM_MAX 50

typedef char String[TAM_MAX];
typedef short boolean;

typedef enum { Interno, Externo } TipoDoNo;

typedef struct TipoPatNo* TipoArvore;
typedef struct TipoPatNo {
  TipoDoNo nt;
  union {
    struct {
      int Index;          // índice do caractere onde diverge
      char caractere;     // caractere armazenado no nó interno (maior)
      TipoArvore Esq, Dir;
    } NInterno;
    String Chave;         // palavra armazenada no nó externo
  } NO;
} TipoPatNo;

int PosicaoQueDifere(String s1, String s2);
char MaiorLetraEntreStrings(String s1, String s2);
short EExterno(TipoArvore p);
void InicializaPatricia(TipoArvore* arvoreInicial);
TipoArvore CriaNoInt(int indice,char caractereDif, TipoArvore *Esq,  TipoArvore *Dir);
TipoArvore Insere(String palavra, TipoArvore *t);
int Bit(int i, String k, char referencia);
TipoArvore InsereEntre(String k, TipoArvore *t, int i);



#endif
