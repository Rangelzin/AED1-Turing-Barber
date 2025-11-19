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

#endif
