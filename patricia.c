#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/time.h>
#include "patricia.h"

void InicializaPatricia(TipoArvore* arvoreInicial) {
    *arvoreInicial = NULL;
}

int MaiorLetraDivergente(const String a, const String b) {
    int la = strlen(a), lb = strlen(b);
    int min = la < lb ? la : lb;
    for (int i = 0; i < min; ++i)
        if (a[i] != b[i])
            return i;
    return (la != lb) ? min : -1;
}


// Insere k(palavra que chego) entre a sub árvore *t, criando um nó interno no índice indice
TipoArvore InsereEntre(String k, TipoArvore *t, int indice) {
    TipoArvore p;
    // caso seja externo ou precise criar acima
    if (EExterno(*t) || indice < (*t)->NO.NInterno.Index) {
        p = CriaNoExt(k);
        // compara o caractere de k[indice] com o da chave existente do interno
        char c_exist = EExterno(*t)
                       ? (*t)->NO.Chave[indice]
                       : (*t)->NO.NInterno.caractere;
        if (k[indice] > c_exist) {
            // antigo *t vai à esquerda (é “menor”), pra direita
            return CriaNoInt(indice, c_exist, t, &p);
        } else {
            // p (“menor”) vai pra esquerda, antigo *t à direita
            return CriaNoInt(indice, k[indice], &p, t);
        }
    } else {
        // desce recursivamente com base no caractere em cada nó interno
        if (k[(*t)->NO.NInterno.Index] > (*t)->NO.NInterno.caractere) {
            (*t)->NO.NInterno.Dir =
                InsereEntre(k, &(*t)->NO.NInterno.Dir, indice);
        } else {
            (*t)->NO.NInterno.Esq =
                InsereEntre(k, &(*t)->NO.NInterno.Esq, indice);
        }
        return *t;
    }
}


TipoArvore Insere(String k, TipoArvore *t) {
    TipoArvore p;
    int indice;

    if (*t == NULL) {
        return CriaNoExt(k);
    }
    p = *t;
    while (!EExterno(p)) {
        if (k[p->NO.NInterno.Index] > p->NO.NInterno.caractere)
            p = p->NO.NInterno.Dir;
        else
            p = p->NO.NInterno.Esq;
    }
    //calc onde difere pra maior letra
    indice = MaiorLetraDivergente(k, p->NO.Chave);
    if (indice < 0) {
        printf("Erro: chave já está na árvore\n");
        return *t;
    }
    return InsereEntre(k, t, indice);
}

TipoArvore CriaNoExt(String chave) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    if (!p) return NULL;
    p->nt = Externo;
    p->NO.Chave = strdup(chave);
    return p;
}

TipoArvore CriaNoInt(int indice, char c, TipoArvore *Esq, TipoArvore *Dir) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    if (!p) return NULL;
    p->nt = Interno;
    p->NO.NInterno.Index = indice;
    p->NO.NInterno.caractere = c;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    return p;
}

TipoArvore Pesquisa(String chave, TipoArvore t) {
    if (!t) return NULL;
    TipoArvore p = t;

    while (p->nt == Interno) {
        int indice = p->NO.NInterno.Index;
        char c = p->NO.NInterno.caractere;
        // decide comparando indice
        if (indice < (int)strlen(chave) && chave[indice] > c)
            p = p->NO.NInterno.Dir;
        else
            p = p->NO.NInterno.Esq;
    }
    //confere nó externo
    if (strcmp(p->NO.Chave, chave) == 0){
        ImprimeNo(p);
        return p;
    }
    printf("chave não encontrada\n");
    return NULL;
}

void ImprimeNo(TipoArvore t) {
    if (!t) return;
    if (t->nt == Externo) {
        printf("Nó Externo - Chave: %s\n", t->NO.Chave);
    } else {
        printf("Nó Interno - Index: %d, Caractere: %c\n",
               t->NO.NInterno.Index,
               t->NO.NInterno.caractere);
    }
}

short EExterno(TipoArvore p) {
    return (p != NULL && p->nt == Externo);
}

void ImprimeEmOrdem(TipoArvore t) {
    if (!t) return;
    if (t->nt == Interno) {
        ImprimeEmOrdem(t->NO.NInterno.Esq);
        ImprimeEmOrdem(t->NO.NInterno.Dir);
    } else {
        printf("%s\n", t->NO.Chave);
    }
}