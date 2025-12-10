#include "contexto.h"
#include "validacao_data.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"
#include <string.h>

#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_BARBEIROS "barbeiros.dat"

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

void salvarDados() {
    // 1. SALVAR CLIENTES
    FILE* arquivoC = fopen(ARQUIVO_CLIENTES, "wb");
    if (arquivoC == NULL) {
        printf("Erro ao abrir %s para escrita.\n", ARQUIVO_CLIENTES);
        return;
    }

    NoCliente* atualC = sistema.listaClientes;
    while (atualC != NULL) {
        fwrite(atualC, sizeof(NoCliente) - sizeof(NoCliente*), 1, arquivoC); 
        atualC = atualC->proximo;
    }
    fclose(arquivoC);

    // 2. SALVAR BARBEIOS
    FILE* arquivoB = fopen(ARQUIVO_BARBEIROS, "wb");
    if (arquivoB == NULL) {
        printf("⚠️ Erro: Não foi possível abrir %s para escrita.\n", ARQUIVO_BARBEIROS);
        return;
    }

    NoBarbeiro* atualB = sistema.listaBarbeiros;
    size_t tamanhoNoBarbeiro = sizeof(NoBarbeiro) - sizeof(NoBarbeiro*);
    
    while (atualB != NULL) {
        fwrite(atualB, tamanhoNoBarbeiro, 1, arquivoB); // fwrite é usado para armazenar o conteúdo em binário
        atualB = atualB->proximo;
    }
    fclose(arquivoB);

    printf("\nDados salvos com sucesso!\n");
}

void carregarDados() {
    // 1. CARREGAR CLIENTES
    FILE* arquivoC = fopen(ARQUIVO_CLIENTES, "rb");
    if (arquivoC != NULL) {
        NoCliente tempCliente; 
        NoCliente* ultimoC = NULL;
        size_t tamanhoNoCliente = sizeof(NoCliente) - sizeof(NoCliente*); 

        while (fread(&tempCliente, tamanhoNoCliente, 1, arquivoC) == 1) {
            NoCliente* novoNo = (NoCliente*)malloc(sizeof(NoCliente));
            if (novoNo == NULL) {
                printf("Erro de alocação ao carregar clientes.\n"); break;
            }
            
            // Copia ID, nome, telefone e senha
            memcpy(novoNo, &tempCliente, tamanhoNoCliente);
            novoNo->proximo = NULL;

            if (sistema.listaClientes == NULL) {
                sistema.listaClientes = novoNo;
            } else {
                ultimoC->proximo = novoNo;
            }
            ultimoC = novoNo;

            // Atualiza o contador de ID para não repetir
            if (novoNo->id > sistema.qtdClientes) {
                sistema.qtdClientes = novoNo->id;
            }
        }
        fclose(arquivoC);
        printf("%d Clientes carregados.\n", sistema.qtdClientes);
    } else {
        printf("Arquivo de clientes não encontrado. Iniciando lista vazia.\n");
    }

    // 2. CARREGAR BARBEIROS
    FILE* arquivoB = fopen(ARQUIVO_BARBEIROS, "rb");
    if (arquivoB != NULL) {
        NoBarbeiro tempBarbeiro; // <- A VARIÁVEL TEMPORÁRIA AGORA É PARA BARBEIRO
        NoBarbeiro* ultimoB = NULL;
        size_t tamanhoNoBarbeiro = sizeof(NoBarbeiro) - sizeof(NoBarbeiro*);

        while (fread(&tempBarbeiro, tamanhoNoBarbeiro, 1, arquivoB) == 1) {
            NoBarbeiro* novoNo = (NoBarbeiro*)malloc(sizeof(NoBarbeiro));
            if (novoNo == NULL) {
                printf("Erro de alocação ao carregar barbeiros.\n"); break;
            }
            
            // Copia ID, nome, email, senha
            memcpy(novoNo, &tempBarbeiro, tamanhoNoBarbeiro);
            novoNo->proximo = NULL;

            if (sistema.listaBarbeiros == NULL) {
                sistema.listaBarbeiros = novoNo;
            } else {
                ultimoB->proximo = novoNo;
            }
            ultimoB = novoNo;

            if (novoNo->id > sistema.qtdBarbeiros) {
                sistema.qtdBarbeiros = novoNo->id;
            }
        }
        fclose(arquivoB);
        printf("%d Barbeiros carregados.\n", sistema.qtdBarbeiros);
    } else {
        printf("Arquivo de barbeiros não encontrado. Iniciando lista vazia.\n");
    }

    // 3. CARREGAR AGENDAMENTOS (TODO: Implementação similar com NoAgendamento)
    // 4. CARREGAR FILA (TODO: Implementação similar com NoFila)
}