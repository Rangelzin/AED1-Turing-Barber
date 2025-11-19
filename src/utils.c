#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("\n[Pressione Enter para continuar...]");
    limparBufferInput(); 
}

int lerOpcao() {
    int opcao;
    
    if (scanf("%d", &opcao) == 1) {
        limparBufferInput();
        return opcao;
    } else {
        limparBufferInput();
        return -99;
    }
}