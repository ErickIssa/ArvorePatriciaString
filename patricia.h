
 // Adaptado de: Arvore-Patricia - GitHub/FurlanV (https://github.com/FurlanV/Arvore-Patricia/blob/master/Patricia.c)

#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define D 50  //quantidade de caracteres que analisa
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
short EExterno(TipoArvore p);
TipoArvore Insere(String k, TipoArvore *t);
TipoArvore InsereEntre(String k, TipoArvore *t, int indice);
int MaiorLetraDivergente(const String a, const String b);
TipoArvore CriaNoExt(String chave);
TipoArvore CriaNoInt(int indice, char c, TipoArvore *Esq, TipoArvore *Dir);
TipoArvore Pesquisa(String chave, TipoArvore t);
void ImprimeNo(TipoArvore t);
void ImprimeEmOrdem(TipoArvore t);


#endif
