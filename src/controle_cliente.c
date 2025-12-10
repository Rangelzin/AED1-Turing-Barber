#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contexto.h"
#include "utils.h"
#include "controle_cliente.h" 
#include "estruturas.h"

// ID TEMPORÁRIO para simular o cliente logado, pois não há login
// OBS: Você deve mudar isso quando implementar o login.
#define CLIENTE_LOGADO_ID 1 

// ============================================================================
//                                FUNÇÕES AUXILIARES
// ============================================================================

NoCliente* criarCliente(){
    NoCliente* novoCliente = (NoCliente*)malloc(sizeof(NoCliente));

    if(novoCliente == NULL){
        printf("Memória insuficiente.\n");
        return NULL;
    }

    novoCliente->id = sistema.qtdClientes + 1;
    
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novoCliente->nome);
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]", novoCliente->telefone);
    printf("Digite a senha do cliente: ");
    scanf(" %[^\n]", novoCliente->senha);

    limparBufferInput();

    novoCliente->proximo = NULL;

    return novoCliente;
}

// ============================================================================
//                        CRUD DE CLIENTES (Para o ADMIN)
// ============================================================================

void gerenciarClientes(){
    int opcao;
    
    do {
        limparTela();
        printf("======================================\n");
        printf("     GERENCIAR CLIENTES (ADMIN)       \n");
        printf("======================================\n");
        
        printf("  [1] Adicionar novo Cliente\n");
        printf("  [2] Listar Clientes\n");
        printf("  [3] Excluir Cliente\n");
        printf("  [4] Atualizar dados do Cliente\n");
        printf("  [0] Voltar\n");
        printf("======================================\n");

        printf("Escolha: ");

        opcao = lerOpcao();

        switch(opcao){
            case 1:
                adicionarCliente();
                pausarTela();
                break;
            case 2:
                listarClientes();
                pausarTela();
                break;
            case 3:
                deletarCliente();
                pausarTela();
                break;
            case 4:
                atualizarCliente();
                pausarTela();
                break;
            case 0:
                break;
            default:    
                printf("\nOpção inválida!\n");
                pausarTela();
        }
    } while (opcao != 0);
}

void adicionarCliente(){
    NoCliente* novoCliente = criarCliente();

    if (novoCliente == NULL) {
        printf("Cliente não foi criado corretamente!\n");
        return; 
    }

    NoCliente** head = &sistema.listaClientes;

    if (*head == NULL){
        *head = novoCliente;
    }
    else {
        NoCliente* temp = *head;
        while(temp->proximo != NULL){
            temp = temp->proximo;
        }
        temp->proximo = novoCliente;
    }

    printf("Novo Cliente (ID: %d) adicionado com sucesso!\n", novoCliente->id);
    sistema.qtdClientes++;
}

void listarClientes(){
    limparTela();
    printf("======================================\n");
    printf("          LISTA DE CLIENTES           \n");
    printf("======================================\n");

    if(sistema.listaClientes == NULL){
        printf("Não há clientes cadastrados !\n");
        return;
    }

    NoCliente* temp = sistema.listaClientes;

    while (temp != NULL){
        printf("\nCliente %d\n", temp->id);
        printf("  Nome: %s\n", temp->nome);
        printf("  Telefone: %s\n", temp->telefone);
        temp = temp->proximo;
    }

    printf("======================================\n");
}

void deletarCliente(){
    int id_lido;
    printf("Digite o ID do Cliente que deseja excluir: ");
    scanf("%d",&id_lido);
    limparBufferInput();

    if(sistema.listaClientes == NULL){
        printf("Não há clientes cadastrados!\n");
        return;
    }

    NoCliente* atual = sistema.listaClientes;
    NoCliente* anterior = NULL;

    if (atual != NULL && atual->id == id_lido) {
        sistema.listaClientes = atual->proximo;
        free(atual);
        printf("Cliente ID %d excluído com sucesso!\n", id_lido);
        sistema.qtdClientes--;
        return;
    }

    while (atual != NULL && atual->id != id_lido) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("ID inexistente!\n");
        return;
    }

    anterior->proximo = atual->proximo;
    free(atual);
    printf("Cliente ID %d excluído com sucesso!\n", id_lido);
    sistema.qtdClientes--;
}

void atualizarCliente(){
    int id_lido, option;
    printf("Digite o ID do Cliente que deseja editar: ");
    scanf("%d",&id_lido);
    limparBufferInput();

    if(sistema.listaClientes == NULL){
        printf("Não há clientes cadastrados!\n");
        return;
    }

    NoCliente* temp = sistema.listaClientes;
    
    while(temp != NULL && temp->id != id_lido){
        temp = temp->proximo;
    }

    if(temp == NULL){
        printf("ID inexistente!\n");
        return;
    }

    limparTela();
    printf("=================================\n");
    printf("  Cliente %d\n", temp->id);
    printf("  Nome: %s\n", temp->nome);
    printf("  Telefone: %s\n", temp->telefone);
    printf("=================================\n\n");
    printf("O que deseja editar do cliente selecionado?\n");
    printf("  [1] Nome\n");
    printf("  [2] Telefone\n");
    printf("  [3] Senha\n");
    printf("  [4] Todas as informações\n");
    printf("  [0] Cancelar edição\n");
    
    printf("Escolha: ");
    option = lerOpcao();

    switch(option) {
        case 1:
        printf("Digite o novo nome: ");
        scanf( " %[^\n]", temp->nome);
        limparBufferInput();
        printf("Nome editado!\n");
        break;

        case 2:
        printf("Digite o novo telefone: ");
        scanf( " %[^\n]", temp->telefone);
        limparBufferInput();
        printf("Telefone editado!\n");
        break;

        case 3:
        printf("Digite a nova senha: ");
        scanf( " %[^\n]", temp->senha);
        limparBufferInput();
        printf("Senha editada!\n");
        break;

        case 4:
        printf("Digite o novo nome: ");
        scanf( " %[^\n]", temp->nome);
        limparBufferInput();

        printf("Digite o novo telefone: ");
        scanf( " %[^\n]", temp->telefone);
        limparBufferInput();

        printf("Digite a nova senha: ");
        scanf( " %[^\n]", temp->senha);
        limparBufferInput();

        printf("Todas as informações editadas!\n");
        break;

        case 0:
        printf("Atualização de Cliente cancelada.\n");
        return;

        default:
        printf("Opção inválida.\n");
        return;
    }

    printf("\n--- Dados Atualizados ---\n");
    printf("  Cliente %d\n", temp->id);
    printf("  Nome: %s\n", temp->nome);
    printf("  Telefone: %s\n", temp->telefone);
    printf("---------------------------\n");
}


// ============================================================================
//                    FUNÇÕES DO MENU DO CLIENTE LOGADO
// ============================================================================

void agendarHorario() {
    NoAgendamento* novoAgendamento = (NoAgendamento*)malloc(sizeof(NoAgendamento));
    
    if (novoAgendamento == NULL) {
        printf("Erro de alocação de memória para agendamento.\n");
        return;
    }

    novoAgendamento->id = sistema.qtdAgendamentos + 1;
    novoAgendamento->idCliente = CLIENTE_LOGADO_ID;
    
    printf("\n--- Novo Agendamento ---\n");
    printf("Digite o ID do Barbeiro desejado (Ex: 1): ");
    if (scanf("%d", &novoAgendamento->idBarbeiro) != 1) {
         printf("Entrada inválida. Cancelando agendamento.\n");
         free(novoAgendamento);
         return;
    }
    limparBufferInput();

    // Verifica se o barbeiro existe
    if (buscarBarbeiroPorId(novoAgendamento->idBarbeiro) == NULL) {
        printf("Barbeiro ID %d inexistente! Agendamento cancelado.\n", novoAgendamento->idBarbeiro);
        free(novoAgendamento);
        return;
    }

    printf("Digite o Dia (dd): ");
    if (scanf("%d", &novoAgendamento->dia) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    printf("Digite o Mês (mm): ");
    if (scanf("%d", &novoAgendamento->mes) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    printf("Digite o Ano (aaaa): ");
    if (scanf("%d", &novoAgendamento->ano) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    printf("Digite a Hora (hh): ");
    if (scanf("%d", &novoAgendamento->hora) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    limparBufferInput();

    novoAgendamento->proximo = sistema.agenda;
    sistema.agenda = novoAgendamento;

    sistema.qtdAgendamentos++;
    printf("\n✅ Agendamento realizado com sucesso!\n");
    printf("ID: %d | Barbeiro: %d | Data: %d/%d/%d às %dh\n", 
            novoAgendamento->id, 
            novoAgendamento->idBarbeiro, 
            novoAgendamento->dia, 
            novoAgendamento->mes, 
            novoAgendamento->ano, 
            novoAgendamento->hora);
}


void entrarNaFila() {
    // Verifica se o cliente logado existe no sistema antes de inserir na fila
    if (buscarClientePorId(CLIENTE_LOGADO_ID) == NULL) {
        printf("Erro: Cliente logado (ID %d) não cadastrado. Operação cancelada.\n", CLIENTE_LOGADO_ID);
        return;
    }

    NoFila* temp = sistema.filaInicio;
    while(temp != NULL) {
        if (temp->idCliente == CLIENTE_LOGADO_ID) {
            printf("\nVocê já está na fila de espera!\n");
            return;
        }
        temp = temp->proximo;
    }

    NoFila* novoNoFila = (NoFila*)malloc(sizeof(NoFila));
    if (novoNoFila == NULL) {
        printf("Erro de alocação de memória para fila.\n");
        return;
    }
    
    novoNoFila->idCliente = CLIENTE_LOGADO_ID;
    novoNoFila->proximo = NULL;

    if (sistema.filaFim == NULL) {
        sistema.filaInicio = novoNoFila;
        sistema.filaFim = novoNoFila;
    } else {
        sistema.filaFim->proximo = novoNoFila;
        sistema.filaFim = novoNoFila;
    }

    printf("\nVocê foi adicionado à fila de espera (ID Cliente: %d)!\n", CLIENTE_LOGADO_ID);
    
    // Contar a posição na fila
    int posicao = 1;
    NoFila* p = sistema.filaInicio;
    while (p != NULL && p->idCliente != CLIENTE_LOGADO_ID) {
        posicao++;
        p = p->proximo;
    }
    printf("Sua posição na fila é: %d.\n", posicao);
}

void listarMeusAgendamentos() {
    limparTela();
    printf("======================================\n");
    printf("        MEUS AGENDAMENTOS (ID: %d)     \n", CLIENTE_LOGADO_ID);
    printf("======================================\n");
    
    if (sistema.agenda == NULL) {
        printf("Você não tem agendamentos futuros.\n");
        return;
    }

    NoAgendamento* atual = sistema.agenda;
    int encontrados = 0;

    while (atual != NULL) {
        if (atual->idCliente == CLIENTE_LOGADO_ID) {
            printf("\nAgendamento ID: %d\n", atual->id);
            char nomeBarbeiro[100] = "Barbeiro Desconhecido";
            NoBarbeiro* tempBarbeiro = sistema.listaBarbeiros;
            while(tempBarbeiro != NULL) {
                if (tempBarbeiro->id == atual->idBarbeiro) {
                    strcpy(nomeBarbeiro, tempBarbeiro->nome);
                    break;
                }
                tempBarbeiro = tempBarbeiro->proximo;
            }
            printf("Barbeiro: %s\n", nomeBarbeiro);
            printf("  Data: %d/%d/%d às %dh\n", 
                    atual->dia, atual->mes, atual->ano, atual->hora);
            encontrados++;
        }
        atual = atual->proximo;
    }

    if (encontrados == 0) {
        printf("Você não tem agendamentos futuros.\n");
    }
    printf("======================================\n");
}

void sairDaFila() {
    if (sistema.filaInicio == NULL) {
        printf("\nVocê não está na fila de espera.\n");
        return;
    }

    NoFila* atual = sistema.filaInicio;
    NoFila* anterior = NULL;

    while (atual != NULL && atual->idCliente != CLIENTE_LOGADO_ID) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nVocê não está na fila de espera.\n");
        return;
    }

    if (anterior == NULL) {
        sistema.filaInicio = atual->proximo;
        if (sistema.filaInicio == NULL) {
            sistema.filaFim = NULL;
        }
    } 
    else {
        anterior->proximo = atual->proximo;
        if (atual == sistema.filaFim) {
            sistema.filaFim = anterior;
        }
    }

    free(atual);
    printf("\nVocê foi removido da fila de espera (ID Cliente: %d)!\n", CLIENTE_LOGADO_ID);
}