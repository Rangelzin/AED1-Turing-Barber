#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
//                        FUNÇÕES INTERNAS (Privadas)
// ============================================================================

// Calcula o comprimento visual da string (ignora bytes extras de acentos UTF-8)
// Isso é crucial para que a caixa não fique torta com palavras como "Atenção".
static int calcularTamanhoVisual(const char* str) {
    int tamanho = 0;
    int i = 0;
    while (str[i] != '\0') {
        // Se o byte começar com 11xxxxxx, é um caractere multibyte (UTF-8 header)
        // Nós contamos apenas o primeiro byte do caractere, ignorando os bytes de continuação (10xxxxxx)
        if ((str[i] & 0xC0) != 0x80) {
            tamanho++;
        }
        i++;
    }
    return tamanho;
}

// Repete um caractere N vezes (auxiliar para desenhar bordas)
static void repetirChar(const char* c, int vezes) {
    for (int i = 0; i < vezes; i++) {
        printf("%s", c);
    }
}

// ============================================================================
//                          FUNÇÕES DE UI (Públicas)
// ============================================================================

void imprimirCabecalho(const char* titulo) {
    int lenVisual = calcularTamanhoVisual(titulo);
    int espacoLivre = (LARGURA_MENU - 2) - lenVisual; // -2 pelas bordas laterais
    int paddingEsq = espacoLivre / 2;
    int paddingDir = espacoLivre - paddingEsq;

    // Linha Superior: ╔══════╗
    printf("╔");
    repetirChar("═", LARGURA_MENU - 2);
    printf("╗\n");

    // Linha do Título: ║ Título ║
    printf("║");
    repetirChar(" ", paddingEsq);
    printf("%s", titulo);
    repetirChar(" ", paddingDir);
    printf("║\n");

    // Separador base do cabeçalho
    printf("╠");
    repetirChar("═", LARGURA_MENU - 2);
    printf("╣\n");
}

void imprimirRodape() {
    printf("╚");
    repetirChar("═", LARGURA_MENU - 2);
    printf("╝\n");
}

void imprimirSeparador() {
    // Usando o caractere específico solicitado
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

// ============================================================================
//                        FUNÇÕES DE UTILIDADE GERAL
// ============================================================================

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarTela() {
    printf("\n");
    imprimirSeparador();
    printf("[Pressione Enter para continuar...]");
    limparBufferInput(); 
}

int lerOpcao() {
    int opcao;
    
    // Pequena melhoria visual na leitura
    // printf(" > "); // Opcional: Adicionar um prompt visual
    if (scanf("%d", &opcao) == 1) {
        limparBufferInput();
        return opcao;
    } else {
        limparBufferInput();
        return -99; // Código de erro genérico
    }
}