#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "patricia.h"

#define MAX_PALAVRAS 5000
#define TAM_PALAVRA 50


//Inserçao e pesquisa de palavras implementado, *não trata: palavras iguais, 
//erro ao inserir muitas palavras (EX: aviao e avo são consideradas maiores que rurgia)
int main() {
    FILE *arquivo;
    char linha[256];
    char palavras[MAX_PALAVRAS][TAM_PALAVRA];
    int i = 0;
    TipoArvore ArvoreInicial;
    InicializaPatricia(&ArvoreInicial);

    // Abre o arquivo "entrada.txt"
    arquivo = fopen("entrada.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove '\n'

        char *token = strtok(linha, " ");
        while (token != NULL && i < MAX_PALAVRAS) {
            strncpy(palavras[i], token, TAM_PALAVRA - 1);
            palavras[i][TAM_PALAVRA - 1] = '\0'; // Garante terminação
            i++;
            token = strtok(NULL, " ");
        }

        if (i >= MAX_PALAVRAS)
            break;
    }

    fclose(arquivo);

    // Exibe e insere as palavras na árvore
    printf("Palavras encontradas:\n");
    for (int j = 0; j < i; j++) {
        printf("palavras[%d] = %s\n", j, palavras[j]);
        ArvoreInicial = Insere(palavras[j], &ArvoreInicial);
    }
    char pessq[50];
    for (int i = 0; i < 5; i++)
    {
        scanf("%s", pessq);
        Pesquisa(pessq,ArvoreInicial);
    }
    ImprimePatriciaOrdem(ArvoreInicial);
    return 0;
}
