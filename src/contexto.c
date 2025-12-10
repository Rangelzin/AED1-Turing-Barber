#include "contexto.h"
#include <stddef.h> 

ContextoSistema sistema;

void inicializarSistema() {
    // 1. Inicializa Listas como vazias
    sistema.listaClientes = NULL;
    sistema.listaBarbeiros = NULL;
    sistema.agenda = NULL;
    
    // 2. Inicializa Fila
    sistema.filaInicio = NULL;
    sistema.filaFim = NULL;

    // 3. Inicializa Contadores de ID
    sistema.qtdClientes = 0;
    sistema.qtdBarbeiros = 0;
    sistema.qtdAgendamentos = 0;
}

NoBarbeiro* buscarBarbeiroPorId(int id) {
    if (sistema.listaBarbeiros == NULL) return NULL;
    NoBarbeiro* atual = sistema.listaBarbeiros;
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

NoCliente* buscarClientePorId(int id) {
    if (sistema.listaClientes == NULL) return NULL;
    NoCliente* atual = sistema.listaClientes;
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return NULL;
}