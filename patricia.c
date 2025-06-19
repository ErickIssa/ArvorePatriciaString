#include "patricia.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InicializaPatricia(TipoArvore* arvoreInicial) {
    *arvoreInicial = NULL;
}
// encontra a posicao onde duas strings diferem
int PosicaoQueDifere(String s1, String s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return i;
        } else {
            i++;
        }
    }
    if (s1[i] != s2[i]) {
        return i;
    } else {
        return -1; //palavras iguais
    }
}
// retorna a maior letra na posicao de diferenca
char MaiorLetraEntreStrings(String s1, String s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            if (s1[i] > s2[i]) {
                return s1[i];
            } else {
                return s2[i];
            }
        } else {
            i++;
        }
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return '\0';
    } else {
        if (s1[i] == '\0') {
            return s2[i];
        } else {
            return s1[i];
        }
    }
}
// decide para qual lado vai baseado no caractere
int Bit(int i, String k, char referencia) {
    char ck;
    if (i < strlen(k)) {
        ck = k[i];
    } else {
        ck = '\0';
    }
    if (ck < referencia) {
        return 0;  // Esquerda
    } else {
        return 1;  // Direita
    }
}

short EExterno(TipoArvore p) {
    return (p->nt == Externo);
}

TipoArvore CriaNoInt(int indice, char caractereDif, TipoArvore *Esq, TipoArvore *Dir) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = indice;
    p->NO.NInterno.caractere = caractereDif;
    return p;
}

TipoArvore CriaNoExt(String palavra, int IDdocumento) {
    TipoArvore p = (TipoArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    strcpy(p->NO.Chave, palavra);
    p->chaveExt.ocorrenciasPalavra.Primeiro = NULL;
    p->chaveExt.ocorrenciasPalavra.Ultimo = NULL;

    FLVaziaEncadeada(&p->chaveExt.ocorrenciasPalavra);
    InsereEncadeada(1,&p->chaveExt.ocorrenciasPalavra);
    return p;
}

// chamar essa funcao para inserir
TipoArvore InserePatricia(String palavra, TipoArvore *t, int IDdocumento) {
    TipoArvore p;
    int i;
    if (*t == NULL) { //se vazia, ja cria no externo
        return CriaNoExt(palavra, IDdocumento);
    } else {
        p = *t;
        while (!EExterno(p)) { //esse while utiliza de BIT para decidir qual lado da arvore vai
            if (Bit(p->NO.NInterno.Index, palavra, p->NO.NInterno.caractere) == 1)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        i = PosicaoQueDifere(palavra, p->NO.Chave);    // calcula posição que difere
        if (i == -1) { // se i = -1 ja ta na arvore
            printf("A palavra '%s' já está na árvore\n", palavra);
            InsereEncadeada(IDdocumento,&p->chaveExt.ocorrenciasPalavra);
            printf("%d, %d\n", p->chaveExt.ocorrenciasPalavra.Ultimo->idDoc,p->chaveExt.ocorrenciasPalavra.Ultimo->numeroOcorrencias);
            return *t;
        } else {
            return InsereEntre(palavra, t, i, IDdocumento); //else ele insere entre o no atual e a palavra
        }
    }
}

// essa funcao insere entre os nos, NAO CHAMAR ELA
TipoArvore InsereEntre(String k, TipoArvore *t, int i, int IDdocumento) {
    TipoArvore p;

    if (EExterno(*t)) {
        p = CriaNoExt(k, IDdocumento);
        char letraRef = MaiorLetraEntreStrings(k, (*t)->NO.Chave); // determina letra no interno compara a do no atual e a que ta chegando

        if (Bit(i, k, letraRef) == 1)//usa BIT para ver pra qual lado vai
            return CriaNoInt(i, letraRef, t, &p);
        else
            return CriaNoInt(i, letraRef, &p, t);
    }
    else if (i < (*t)->NO.NInterno.Index) { //caso onde a divergencia acontece antes do no atual
        p = CriaNoExt(k, IDdocumento);
        TipoArvore temp = *t;
        while (!EExterno(temp)) {
            if (temp->NO.NInterno.Esq != NULL) {
                temp = temp->NO.NInterno.Esq;
            } else {
                temp = temp->NO.NInterno.Dir;
            }
        }
        char letraRef = MaiorLetraEntreStrings(k, temp->NO.Chave);

        if (Bit(i, k, letraRef) == 1)
            return CriaNoInt(i, letraRef, t, &p);
        else
            return CriaNoInt(i, letraRef, &p, t);
    }
    else {  // caso em que a divergencia acontece depois ou no mesmo nivel do no atual
        int idx = (*t)->NO.NInterno.Index;
        char letraRef = (*t)->NO.NInterno.caractere;
        if (Bit(idx, k, letraRef) == 1)
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i, IDdocumento);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i,IDdocumento);
        return (*t);
    }
}

void ImprimePatriciaEmOrdem(TipoArvore arvore) {
    if (arvore == NULL) return;
    if (EExterno(arvore)) {
        printf("%s\n", arvore->NO.Chave);
    } else {
        ImprimePatriciaEmOrdem(arvore->NO.NInterno.Esq);
        ImprimePatriciaEmOrdem(arvore->NO.NInterno.Dir);
    }
}

TipoArvore getPesquisaPalavra(String palavra, TipoArvore t) {
    if (t == NULL) {
        return NULL; //arvore vazia
    }
    TipoArvore p = t;
    while (!EExterno(p)) {
        if (Bit(p->NO.NInterno.Index, palavra, p->NO.NInterno.caractere) == 1)
            p = p->NO.NInterno.Dir;
        else
            p = p->NO.NInterno.Esq;
    }
    if (strcmp(palavra, p->NO.Chave) == 0) {
        return p;  // Encontrou
    } else {
        return NULL;  // Nao encontrado
    }
}

void PesquisaPrintPatricia(String palavra, TipoArvore t) {
    if (t == NULL) {
        printf("Palavra não encontrada(ARVORE VAZIA)\n"); 
    }
    TipoArvore p = t;
    while (!EExterno(p)) {
        if (Bit(p->NO.NInterno.Index, palavra, p->NO.NInterno.caractere) == 1)
            p = p->NO.NInterno.Dir;
        else
            p = p->NO.NInterno.Esq;
    }
    if (strcmp(palavra, p->NO.Chave) == 0) {
        printf("A palavra [%s] foi encontrada\n", p->NO.Chave);
        if(VerificaVaziaEncadeada(p->chaveExt.ocorrenciasPalavra) == 0){
          printf("listaVAzas\n");
        }
        else{
          ImprimeEncadeada(p->chaveExt.ocorrenciasPalavra);
        }
    } else {
         printf("Palavra nao encontrada\n");  
    }
}
