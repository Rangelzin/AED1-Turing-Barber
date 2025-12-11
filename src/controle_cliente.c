#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contexto.h"
#include "utils.h"
#include "controle_cliente.h" 
#include "estruturas.h"
#include "validacao_data.h"

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
        imprimirCabecalho("GERENCIAR CLIENTES");

        printf("  [1] Adicionar novo Cliente\n");
        printf("  [2] Listar Clientes\n");
        printf("  [3] Excluir Cliente\n");
        printf("  [4] Atualizar dados do Cliente\n");
        printf("  [0] Voltar\n");
        imprimirRodape();

        printf("Escolha: ");
        opcao = lerOpcao();

        switch(opcao){
            case 1:
                adicionarCliente();
                salvarDados();
                pausarTela();
                break;
            case 2:
                listarClientes();
                salvarDados();
                pausarTela();
                break;
            case 3:
                deletarCliente();
                salvarDados();
                pausarTela();
                break;
            case 4:
                atualizarCliente();
                salvarDados();
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
    imprimirCabecalho("LISTA DE CLIENTES");

    if(sistema.listaClientes == NULL){
        printf("Não há clientes cadastrados !\n");
        imprimirRodape();
        return;
    }

    NoCliente *temp = sistema.listaClientes;
    while (temp != NULL){
        printf(" ID: %d | Nome: %s\n", temp->id, temp->nome);
        printf(" Tel: %s\n", temp->telefone);
        imprimirSeparador();
        temp = temp->proximo;
    }
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
    imprimirSeparador();
    printf("  Cliente %d\n", temp->id);
    printf("  Nome: %s\n", temp->nome);
    printf("  Telefone: %s\n", temp->telefone);
    imprimirSeparador();
    printf("\n");
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

    printf("\n━━━━ Dados Atualizados ━━━━\n");
    printf("  Cliente %d\n", temp->id);
    printf("  Nome: %s\n", temp->nome);
    printf("  Telefone: %s\n", temp->telefone);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}


// ============================================================================
//                    FUNÇÕES DO MENU DO CLIENTE LOGADO
// ============================================================================

void agendarHorario() {
    limparTela();
    imprimirCabecalho("NOVO AGENDAMENTO");

    // Mostra data/hora atual para referência
    DataHora atual = obterDataHoraAtual();
    char bufferAtual[100];
    formatarData(atual.dia, atual.mes, atual.ano, atual.hora, bufferAtual);
    printf("Data/Hora Atual: %s\n", bufferAtual);
    printf("Horário de Funcionamento: 8h às 18h\n");
    imprimirSeparador();
    printf("\n");

    NoAgendamento* novoAgendamento = (NoAgendamento*)malloc(sizeof(NoAgendamento));
    
    if (novoAgendamento == NULL) {
        printf("Erro de alocação de memória para agendamento.\n");
        return;
    }

    novoAgendamento->id = sistema.qtdAgendamentos + 1;
    
    // ATUALIZAÇÃO: Usa o ID real do cliente logado no sistema
    novoAgendamento->idCliente = sistema.idClienteLogado;
    
    printf("Digite o ID do Barbeiro desejado: ");
    if (scanf("%d", &novoAgendamento->idBarbeiro) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    limparBufferInput();

    // Verifica se o barbeiro existe
    if (buscarBarbeiroPorId(novoAgendamento->idBarbeiro) == NULL) {
        printf("Barbeiro ID %d não existe! Agendamento cancelado.\n", novoAgendamento->idBarbeiro);
        free(novoAgendamento);
        return;
    }

    printf("\n--- Data do Agendamento ---\n");
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
    
    // VALIDAÇÃO 1: Data válida
    if (!dataValida(novoAgendamento->dia, novoAgendamento->mes, novoAgendamento->ano)) {
        printf("Data inválida! Verifique se a data existe (ex: não existe 31/02).\n");
        free(novoAgendamento);
        return;
    }
    
    printf("Digite a Hora (0-23): ");
    if (scanf("%d", &novoAgendamento->hora) != 1) {
        printf("Entrada inválida. Cancelando agendamento.\n");
        free(novoAgendamento);
        return;
    }
    limparBufferInput();
    
    // VALIDAÇÃO 2: Hora válida
    if (!horaValida(novoAgendamento->hora)) {
        printf("Hora inválida! Digite um valor entre 0 e 23.\n");
        free(novoAgendamento);
        return;
    }
    
    // VALIDAÇÃO 3: Horário comercial
    if (!horarioComercialValido(novoAgendamento->hora)) {
        printf("Horário fora do expediente! A barbearia funciona das 8h às 18h.\n");
        free(novoAgendamento);
        return;
    }
    
    // VALIDAÇÃO 4: Não agendar no passado
    if (dataHoraPassou(novoAgendamento->dia, novoAgendamento->mes, 
                       novoAgendamento->ano, novoAgendamento->hora)) {
        printf("Não é possível agendar em data/hora que já passou!\n");
        char bufferTentativa[100];
        formatarData(novoAgendamento->dia, novoAgendamento->mes, 
                    novoAgendamento->ano, novoAgendamento->hora, bufferTentativa);
        printf("   Você tentou agendar: %s\n", bufferTentativa);
        printf("   Data/Hora atual: %s\n", bufferAtual);
        free(novoAgendamento);
        return;
    }

    // Adiciona o agendamento na lista
    novoAgendamento->proximo = sistema.agenda;
    sistema.agenda = novoAgendamento;
    sistema.qtdAgendamentos++;
    
    char bufferConfirmacao[100];
    formatarData(novoAgendamento->dia, novoAgendamento->mes, 
                novoAgendamento->ano, novoAgendamento->hora, bufferConfirmacao);
    
    printf("\nAgendamento realizado com sucesso!\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("ID do Agendamento: %d\n", novoAgendamento->id);
    printf("Barbeiro ID: %d\n", novoAgendamento->idBarbeiro);
    printf("Data/Hora: %s\n", bufferConfirmacao);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void entrarNaFila() {
    // ATUALIZAÇÃO: Verifica o ID real do cliente logado
    if (buscarClientePorId(sistema.idClienteLogado) == NULL) {
        printf("Erro: Cliente logado (ID %d) não cadastrado. Operação cancelada.\n", sistema.idClienteLogado);
        return;
    }

    NoFila* temp = sistema.filaInicio;
    while(temp != NULL) {
        // Verifica se o ID do cliente logado já está na fila
        if (temp->idCliente == sistema.idClienteLogado) {
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
    
    // Atribui o ID do cliente logado
    novoNoFila->idCliente = sistema.idClienteLogado;
    novoNoFila->proximo = NULL;

    if (sistema.filaFim == NULL) {
        sistema.filaInicio = novoNoFila;
        sistema.filaFim = novoNoFila;
    } else {
        sistema.filaFim->proximo = novoNoFila;
        sistema.filaFim = novoNoFila;
    }

    printf("\nVocê foi adicionado à fila de espera (ID Cliente: %d)!\n", sistema.idClienteLogado);
    
    // Contar a posição na fila
    int posicao = 1;
    NoFila* p = sistema.filaInicio;
    while (p != NULL && p->idCliente != sistema.idClienteLogado) {
        posicao++;
        p = p->proximo;
    }
    printf("   Sua posição na fila: %dº\n", posicao);
}

void listarMeusAgendamentos()
{
    int removidos = limparAgendamentosExpirados();
    
    limparTela();
    char titulo[100];
    // ATUALIZAÇÃO: Título dinâmico com o ID real
    sprintf(titulo, "MEUS AGENDAMENTOS (ID: %d)", sistema.idClienteLogado);
    imprimirCabecalho(titulo);

    if (removidos > 0) {
        printf("ℹ️  %d expirado(s) removido(s).\n", removidos);
        imprimirSeparador();
    }
    
    if (sistema.agenda == NULL) {
        printf("Você não tem agendamentos futuros.\n");
        imprimirRodape();
        return;
    }

    NoAgendamento* atual = sistema.agenda;
    int encontrados = 0;
    
    // Removido 'DataHora agora' pois não estava sendo usado nesta função

    while (atual != NULL) {
        // ATUALIZAÇÃO: Filtra pelo ID do cliente logado
        if (atual->idCliente == sistema.idClienteLogado) {
            // Verifica se o agendamento é futuro
            if (dataHoraFutura(atual->dia, atual->mes, atual->ano, atual->hora)) {
                printf("\n📅 Agendamento ID: %d\n", atual->id);
                
                char nomeBarbeiro[100] = "Barbeiro Desconhecido";
                NoBarbeiro* tempBarbeiro = sistema.listaBarbeiros;
                while(tempBarbeiro != NULL) {
                    if (tempBarbeiro->id == atual->idBarbeiro) {
                        strcpy(nomeBarbeiro, tempBarbeiro->nome);
                        break;
                    }
                    tempBarbeiro = tempBarbeiro->proximo;
                }
                printf("   Barbeiro: %s\n", nomeBarbeiro);
                
                char bufferData[100];
                formatarData(atual->dia, atual->mes, atual->ano, atual->hora, bufferData);
                printf("   Data/Hora: %s\n", bufferData);
                
                encontrados++;
            }
        }
        atual = atual->proximo;
    }

    if (encontrados == 0) {
        printf("Você não tem agendamentos futuros.\n");
    } else {
        printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("Total de agendamentos futuros: %d\n", encontrados);
    }
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

void sairDaFila() {
    if (sistema.filaInicio == NULL) {
        printf("\nVocê não está na fila de espera.\n");
        return;
    }

    NoFila* atual = sistema.filaInicio;
    NoFila* anterior = NULL;

    // ATUALIZAÇÃO: Busca o cliente logado na fila
    while (atual != NULL && atual->idCliente != sistema.idClienteLogado) {
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
    printf("\nVocê foi removido da fila de espera (ID Cliente: %d)!\n", sistema.idClienteLogado);
}