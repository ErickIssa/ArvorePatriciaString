#include "patricia.h"
#include <stdio.h>
#include <string.h>

void InicializaPatricia(TipoArvore* arvoreInicial) {
    *arvoreInicial = NULL;
}

int PosicaoQueDifere(String s1, String s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return i;  // Posicao que difere
        }
        i++;
    }
    // solucao pra prefixo
    if (s1[i] != s2[i]) {
        return i;
    }
    return -1;  // palavra igaul
}

char MaiorLetraEntreStrings(String s1, String s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            if (s1[i] > s2[i]) {
                return s1[i];
            } else {
                return s2[i];
            }
        }
        i++;
    }
    if (s1[i] != '\0') {
        return s1[i];
    }
    if (s2[i] != '\0') {
        return s2[i];
    }
    return '!';
}

int Bit(int i, String k, char referencia) {
    int lenK = strlen(k);
    char ck;
    if (i < lenK) {
        ck = k[i];
    } else {
        ck = '\0';  // Simula fim de string
    }

    if (ck <= referencia) {
        return 0;  // Vai para esquerda
    } else {
        return 1;  // Vai para direita
    }
}


short EExterno(TipoArvore p)
{ /* Verifica se p^ e nodo externo */
  return (p->nt == Externo);
}

TipoArvore CriaNoInt(int indice,char caractereDif, TipoArvore *Esq,  TipoArvore *Dir){ TipoArvore p;
  p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Interno; 
  p->NO.NInterno.Esq = *Esq;
  p->NO.NInterno.Dir = *Dir; 
  p->NO.NInterno.Index = indice;
  p->NO.NInterno.caractere =  caractereDif;
  return p;
}

TipoArvore CriaNoExt(String palavra)
{ TipoArvore p;
  p = (TipoArvore)malloc(sizeof(TipoPatNo));
  p->nt = Externo; 
  strcpy(p->NO.Chave,palavra);
  return p;
}  

TipoArvore Insere(String palavra, TipoArvore *t)
{ TipoArvore p;
  int i;
  if (*t == NULL) 
  return (CriaNoExt(palavra));
  else 
  { p = *t;
    while (!EExterno(p)) 
      { if (Bit(p->NO.NInterno.Index, palavra, p->NO.NInterno.caractere) == 1)
        p = p->NO.NInterno.Dir;
        else p = p->NO.NInterno.Esq;
      }
    /* acha o primeiro bit diferente */
    i = 0;
    while (palavra[i] == p->NO.Chave[i] && palavra[i] != '\0') 
      i++;
    if (strcmp(palavra, p->NO.Chave) == 0)
    { printf("Erro: chave ja esta na arvore\n");  
      return (*t); } 
    else  
      return (InsereEntre(palavra, t, i));
  }
}

TipoArvore InsereEntre(String k, TipoArvore *t, int i)
{
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        p = CriaNoExt(k);
        char letraRef = k[i];  //caractere da palavra na posição de diferença

        if (Bit(i, k, letraRef) == 1)
            return CriaNoInt(i, letraRef, t, &p);
        else
            return CriaNoInt(i, letraRef, &p, t);
    } else {
        int idx = (*t)->NO.NInterno.Index;
        char letraRef = (*t)->NO.NInterno.caractere;

        if (Bit(idx, k, letraRef) == 1)
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i);
        return (*t);
    }
}
