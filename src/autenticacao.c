#include "autenticacao.h"
#include "contexto.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ============================================================================
//                          FUNÇÕES AUXILIARES DE BUSCA
// ============================================================================

/**
 * Busca um cliente na lista encadeada usando telefone e senha.
 * Retorna o ponteiro para o NoCliente se encontrado, ou NULL.
 */
static NoCliente* buscarClientePorCredenciais(char* telefone, char* senha) {
    NoCliente* temp = sistema.listaClientes;
    while (temp != NULL) {
        // Usa strcmp para comparar strings (case-sensitive)
        if (strcmp(temp->telefone, telefone) == 0 && strcmp(temp->senha, senha) == 0) {
            return temp; 
        }
        temp = temp->proximo;
    }
    return NULL; 
}

/**
 * Busca um barbeiro na lista encadeada usando email e senha.
 * Retorna o ponteiro para o NoBarbeiro se encontrado, ou NULL.
 */
static NoBarbeiro* buscarBarbeiroPorCredenciais(char* email, char* senha) {
    NoBarbeiro* temp = sistema.listaBarbeiros;
    while (temp != NULL) {
        // Usa strcmp para comparar strings (case-sensitive)
        if (strcmp(temp->email, email) == 0 && strcmp(temp->senha, senha) == 0) {
            return temp; 
        }
        temp = temp->proximo;
    }
    return NULL; 
}

// ============================================================================
//                                FUNÇÕES DE LOGIN
// ============================================================================

int fazerLoginCliente() {
    char telefone[20];
    char senha[20];
    
    limparTela();
    printf("======================================\n");
    printf("         LOGIN DO CLIENTE             \n");
    printf("======================================\n");
    
    printf("Telefone: ");
    scanf(" %19[^\n]", telefone); 
    limparBufferInput();
    
    printf("Senha: ");
    scanf(" %19[^\n]", senha);
    limparBufferInput();

    NoCliente* cliente = buscarClientePorCredenciais(telefone, senha);

    if (cliente != NULL) {
        sistema.idClienteLogado = cliente->id;
        printf("\nLogin do Cliente %s (ID %d) realizado com sucesso!\n", cliente->nome, cliente->id);
        pausarTela();
        return 1;
    } else {
        printf("\nCredenciais de Cliente inválidas! Tente novamente ou cadastre-se.\n");
        pausarTela();
        return 0;
    }
}

int fazerLoginBarbeiro() {
    char email[100];
    char senha[20];

    limparTela();
    printf("======================================\n");
    printf("         LOGIN DO BARBEIRO            \n");
    printf("======================================\n");
    
    printf("Email: ");
    scanf(" %99[^\n]", email);
    limparBufferInput();
    
    printf("Senha: ");
    scanf(" %19[^\n]", senha);
    limparBufferInput();

    NoBarbeiro* barbeiro = buscarBarbeiroPorCredenciais(email, senha);

    if (barbeiro != NULL) {
        sistema.idBarbeiroLogado = barbeiro->id;
        printf("\nLogin do Barbeiro %s (ID %d) realizado com sucesso!\n", barbeiro->nome, barbeiro->id);
        pausarTela();
        return 1;
    } else {
        printf("\nCredenciais de Barbeiro inválidas! Acesso negado.\n");
        pausarTela();
        return 0;
    }
}

void fazerLogout() {
    sistema.idClienteLogado = 0;
    sistema.idBarbeiroLogado = 0;
}