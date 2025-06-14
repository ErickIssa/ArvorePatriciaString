#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "patricia.h"

#define MAX_PALAVRAS 5000
#define TAM_PALAVRA 50

void ImprimeArvoreRec(TipoArvore t, int nivel, char tipo) {
    if (!t) return;
    for (int i = 0; i < nivel; ++i) printf("    ");
    /* imprime prefixo de tipo de filha */
    if (nivel == 0) printf("[Root] ");
    else if (tipo == 'L') printf("[Esquerdo] ");
    else if (tipo == 'R') printf("[Direito] ");
    if (t->nt == Interno) {
        printf("[I idx=%d c=%c]\n", t->NO.NInterno.Index,
               t->NO.NInterno.caractere);
        ImprimeArvoreRec(t->NO.NInterno.Esq, nivel + 1, 'L');
        ImprimeArvoreRec(t->NO.NInterno.Dir, nivel + 1, 'R');
    } else {
        printf("[E %s]\n", t->NO.Chave);
    }
}

void ImprimeArvore(TipoArvore t) {
    ImprimeArvoreRec(t, 0, ' ');
}

int main() {
    FILE *arquivo;
    char linha[256];
    char palavras[MAX_PALAVRAS][TAM_PALAVRA];
    int i = 0;
    TipoArvore ArvoreInicial;
    InicializaPatricia(&ArvoreInicial);

    // Abre o arquivo "entrada.txt"
    arquivo = fopen("palavras5000.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove '\n'

        char *token = strtok(linha, " ");
        while (token != NULL && i < MAX_PALAVRAS) {
            // Only copy words with more than 3 characters
            if (strlen(token) > 3) {
                strncpy(palavras[i], token, TAM_PALAVRA - 1);
                palavras[i][TAM_PALAVRA - 1] = '\0'; // Garante terminação
                i++;
            }
            token = strtok(NULL, " ");
        }

        if (i >= MAX_PALAVRAS)
            break;
    }

    fclose(arquivo);

    // Exibe e insere as palavras na árvore
    printf("Palavras encontradas (com mais de 3 caracteres):\n");
    for (int j = 0; j < i; j++) {
        printf("palavras[%d] = %s\n", j, palavras[j]);
        ArvoreInicial = Insere(palavras[j], &ArvoreInicial);
    }

    char pessq[50];
    for (int i = 0; i < 5; i++) {
        scanf("%s", pessq);
        Pesquisa(pessq, ArvoreInicial);
    }
    
    ImprimeEmOrdem(ArvoreInicial);
    ImprimeArvore(ArvoreInicial);
    return 0;
}