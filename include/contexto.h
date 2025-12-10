#ifndef CONTEXTO_H
#define CONTEXTO_H

#include "estruturas.h"

typedef struct {
    NoCliente* listaClientes;
    NoBarbeiro* listaBarbeiros;
    NoAgendamento* agenda;
    NoFila* filaInicio;
    NoFila* filaFim;
    int qtdClientes;
    int qtdBarbeiros;
    int qtdAgendamentos;
} ContextoSistema;

extern ContextoSistema sistema;

void inicializarSistema();

// Procura um barbeiro pelo ID na lista do sistema. Retorna ponteiro para
// o nó do barbeiro ou NULL se não encontrado.
NoBarbeiro* buscarBarbeiroPorId(int id);

// Procura um cliente pelo ID na lista do sistema. Retorna ponteiro para
// o nó do cliente ou NULL se não encontrado.
NoCliente* buscarClientePorId(int id);

#endif
