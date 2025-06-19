#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "patricia.h"

#define MAX_PALAVRAS 5000
#define TAM_PALAVRA 50
// //essas funções aqui to so usando pra debugar pq elas mostram cada nivel, tlvz dps implemento na patricia.c
// void ImprimeArvoreRec(TipoArvore t, int nivel, char tipo) {
//     if (!t) return;
//     for (int i = 0; i < nivel; ++i) printf("    ");
//     /* imprime prefixo de tipo de filha */
//     if (nivel == 0) printf("[Root] ");
//     else if (tipo == 'L') printf("[Esquerdo] ");
//     else if (tipo == 'R') printf("[Direito] ");
//     if (t->nt == Interno) {
//         printf("[I idx=%d c=%c]\n", t->NO.NInterno.Index,
//                t->NO.NInterno.caractere);
//         ImprimeArvoreRec(t->NO.NInterno.Esq, nivel + 1, 'L');
//         ImprimeArvoreRec(t->NO.NInterno.Dir, nivel + 1, 'R');
//     } else {
//         printf("[E %s]\n", t->NO.Chave);
//     }
// }

int main() {

    //leitura de arquivos basicona pra testa
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
        ArvoreInicial = InserePatricia(palavras[j],&ArvoreInicial, 1);
    }
    char pesq[50];
    for(int i = 0;i<5;i++){
        scanf("%s", pesq);
        PesquisaPrintPatricia(pesq, ArvoreInicial);
    }
    ImprimePatriciaEmOrdem(ArvoreInicial);
    return 0;
}