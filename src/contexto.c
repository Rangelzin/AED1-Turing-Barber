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