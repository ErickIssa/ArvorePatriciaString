#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/time.h>
#include "patricia.h"

void InicializaPatricia(TipoArvore* arvoreInicial){
  *arvoreInicial = NULL;
}

char Caractere(short i, String k) {
  size_t len = strlen(k);
  if (i >= (short)len) 
      return '\0';
  return k[i];
}

boolean MenorIgual(char a, char b){
    return a <= b ? TRUE : FALSE;
}

boolean EExterno(TipoArvore p)
{
    /* Verifica se p^ e nó externo */
    return (p->nt == Externo)?TRUE:FALSE;
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char CaractereRecebido) {
  TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
  if (p == NULL) {
    fprintf(stderr, "Erro de alocação em CriaNoInt\n");
    exit(EXIT_FAILURE);
  }
  p->nt = Interno;
  p->NO.NInterno.Esq = *Esq;
  p->NO.NInterno.Dir = *Dir;
  p->NO.NInterno.Index = i;
  p->NO.NInterno.caractere = CaractereRecebido; //adaptado para receber o caractere de string na patricia
  return p;
} 

TipoArvore CriaNoExt(String k) {
  TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
  if (p == NULL) {
    fprintf(stderr, "Erro de alocação em CriaNoExt\n");
    exit(EXIT_FAILURE);
  }
  p->nt = Externo;
  p->NO.Chave = k;
  return p;
}  

void Pesquisa(String k, TipoArvore t) {
    if (!t) {
        printf("Elemento nao encontrado\n");
        return;
    }
    if (EExterno(t)) {
        printf(strcmp(k, t->NO.Chave) == 0
               ? "Elemento encontrado\n"
               : "Elemento nao encontrado\n");
        return;
    }
    char c = Caractere(t->NO.NInterno.Index, k);
    if (c < t->NO.NInterno.caractere)
        Pesquisa(k, t->NO.NInterno.Esq);
    else
        Pesquisa(k, t->NO.NInterno.Dir);
}


TipoArvore InsereEntre(String k, TipoArvore *t, short i) {
    char c_nova    = Caractere(i, k);
    char c_exist   = EExterno(*t)
                     ? Caractere(i, (*t)->NO.Chave)
                     : (*t)->NO.NInterno.caractere;
    char pivo      = (c_nova < c_exist) ? c_nova : c_exist;
    TipoArvore ext = CriaNoExt(k);

    // só <, nunca <=
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        if (c_nova < c_exist)
            return CriaNoInt(i, &ext, t, pivo);
        else
            return CriaNoInt(i, t, &ext, pivo);
    }

    // descida normal usando < também
    if (c_nova < (*t)->NO.NInterno.caractere)
        (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i);
    else
        (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i);

    return *t;
}


TipoArvore Insere(String k, TipoArvore *t) {
    TipoArvore p = *t;
    int i = 0;

    if (p == NULL)
        return CriaNoExt(k);

    // desce até externo
   while (!EExterno(p)) {
        char c = Caractere(p->NO.NInterno.Index, k);
        if (c < p->NO.NInterno.caractere)
            p = p->NO.NInterno.Esq;
        else
            p = p->NO.NInterno.Dir;
  }
    // busca primeiro bit diferente, mas pára no '\0'
    while (Caractere(i, k) == Caractere(i, p->NO.Chave) 
           && Caractere(i, k) != '\0') {
        i++;
    }

    // se chegaram juntos ao terminador, é duplicata
    if (Caractere(i, k) == '\0' && Caractere(i, p->NO.Chave) == '\0') {
        printf("Erro: chave já está na árvore: %s\n", k);
        return *t;
    }

    // cria o nó interno no bit i
    return InsereEntre(k, t, i);
}


void printNo(TipoArvore no)
{
    if(no == NULL)
        printf("No Nulo\n");
    else if(no->nt == Externo){
        printf("Chave:%s\n",no->NO.Chave);
    }
}

void ImprimePatriciaOrdem(TipoArvore ap) {
    if (!ap) return;
    if (EExterno(ap)) {
        printf("Chave:%s\n", ap->NO.Chave);
    } else {
        ImprimePatriciaOrdem(ap->NO.NInterno.Esq);
        ImprimePatriciaOrdem(ap->NO.NInterno.Dir);
    }
}
