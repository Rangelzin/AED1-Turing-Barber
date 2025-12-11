#ifndef UTILS_H
#define UTILS_H

// Constantes de UI
// Define a largura total do menu (incluindo bordas)
#define LARGURA_MENU 42 

// Funções de Utilidade Geral
void limparTela();
void limparBufferInput();
void pausarTela();
int lerOpcao();

void imprimirCabecalho(const char* titulo);
void imprimirRodape();
void imprimirSeparador();

#endif