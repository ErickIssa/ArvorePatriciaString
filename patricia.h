
 // Adaptado de: Arvore-Patricia - GitHub/FurlanV (https://github.com/FurlanV/Arvore-Patricia/blob/master/Patricia.c)

#ifndef TIPOPAT_H
#define TIPOPAT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define D 8   /* depende de TipoChave */
#define TRUE 1
#define FALSE !TRUE

typedef char *String;      /* a definir, dependendo da aplicacao */
typedef  short boolean;


typedef enum {
  Interno, Externo
} TipoDoNo;

typedef struct TipoPatNo* TipoArvore;

typedef struct TipoPatNo {
  TipoDoNo nt;
    union {
      struct {
        short Index;
        char caractere; // caractete a ser comparado
        TipoArvore Esq, Dir;
      } NInterno;
    String Chave;
  } NO;
} TipoPatNo;


void InicializaPatricia(TipoArvore *arvoreInicial);
char Caractere(short i, String k);
short EExterno(TipoArvore p);
TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char CaractereRecebido);
TipoArvore CriaNoExt(String k);
void Pesquisa(String k, TipoArvore t);
TipoArvore InsereEntre(String k, TipoArvore *t, short i);
TipoArvore Insere(String k, TipoArvore *t);
void printNo(TipoArvore no);
void ImprimePatriciaOrdem(TipoArvore ap);


#endif
