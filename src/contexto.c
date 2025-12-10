#include "contexto.h"
#include "validacao_data.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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

int limparAgendamentosExpirados() {
    int removidos = 0;
    NoAgendamento* atual = sistema.agenda;
    NoAgendamento* anterior = NULL;
    
    while (atual != NULL) {
        // Verifica se o agendamento já passou
        if (dataHoraPassou(atual->dia, atual->mes, atual->ano, atual->hora)) {
            NoAgendamento* aRemover = atual;
            
            // Remove o nó da lista
            if (anterior == NULL) {
                // É o primeiro nó
                sistema.agenda = atual->proximo;
                atual = sistema.agenda;
            } else {
                anterior->proximo = atual->proximo;
                atual = atual->proximo;
            }
            
            free(aRemover);
            sistema.qtdAgendamentos--;
            removidos++;
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }
    
    return removidos;
}
