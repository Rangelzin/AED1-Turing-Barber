#include <stdio.h>
#include <stdlib.h>
#include "contexto.h"
#include "utils.h"
#include "controle_barbeiro.h"
#include "controle_cliente.h"
#include <string.h> 

// ============================================================================
//                            MENU GERENCIAR BARBEIROS
// ============================================================================

void menuGerenciarBarbeiros(){
    int opcao;
    
    do {
        limparTela();
        printf("======================================\n");
        printf("     GERENCIAR EQUIPE (BARBEIROS)     \n");
        printf("======================================\n");
        
        printf("  [1] Adicionar novo barbeiro\n");
        printf("  [2] Listar barbeiros\n");
        printf("  [3] Excluir Barbeiro\n");
        printf("  [4] Atualizar dados do Barbeiro\n");
        printf("  [0] Voltar / Logout\n");
        printf("======================================\n");

        printf("Escolha: ");

        opcao = lerOpcao();

        switch(opcao){
            case 1:
                adicionarBarbeiro();
                pausarTela();
                break;
            case 2:
                listarBarbeiros();
                pausarTela();
                break;
            case 3:
                deletarBarbeiro();
                pausarTela();
                break;
            case 4:
                atualizarBarbeiro();
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

// ============================================================================
//                                CRUD DE BARBEIROS
// ============================================================================

NoBarbeiro* criarBarbeiro(){
    NoBarbeiro* novoBarbeiro = (NoBarbeiro*)malloc(sizeof(NoBarbeiro));

    if(novoBarbeiro == NULL){
        printf("Mémoria insuficiente.\n");
    return NULL;
    }

    novoBarbeiro->id = sistema.qtdBarbeiros + 1;
    printf("Digite o nome do barbeiro: ");
    scanf(" %[^\n]", novoBarbeiro->nome);
    printf("Digite o email do barbeiro: ");
    scanf("%s",novoBarbeiro->email);
    printf("Digite a senha do barbeiro: ");
    scanf("%s",novoBarbeiro->senha);

    limparBufferInput();

    novoBarbeiro->proximo = NULL;

    return novoBarbeiro;
}

void adicionarBarbeiro(){
    NoBarbeiro* novoBarbeiro = criarBarbeiro();

    if (novoBarbeiro == NULL) {
        printf("Barbeiro não foi criado corretamente!");
        return; 
    }

    NoBarbeiro** head = &sistema.listaBarbeiros;

    if (*head == NULL){
        *head = novoBarbeiro;
        printf("Novo Barbeiro adicionado!");
        sistema.qtdBarbeiros++;
        return;
    }
    
    NoBarbeiro* temp = *head;

    while(temp->proximo!=NULL){
        temp = temp->proximo;
    }

    temp->proximo = novoBarbeiro;

    printf("Novo Barbeiro adicionado!");

    sistema.qtdBarbeiros++;
}

void listarBarbeiros(){

    if(sistema.listaBarbeiros == NULL){
        printf("Não há barbeiros cadastrados !");
        return;
    }

    limparTela();
    printf("======================================\n");
    printf("          LISTA DE BARBEIROS          \n");
    printf("======================================\n");

    NoBarbeiro* temp = sistema.listaBarbeiros;

    while (temp != NULL){
        printf("\nBarbeiro %d\n", temp->id);
        printf("Nome: %s\n", temp->nome);
        printf("Email: %s\n", temp->email);
        temp = temp->proximo;
    }

    printf("======================================\n");
}

void deletarBarbeiro(){
    int id_lido;
    printf("Digite o id do Barbeiro que deseja excluir: ");
    scanf("%d",&id_lido);
    limparBufferInput();

    if(sistema.listaBarbeiros == NULL){
        printf("Não há barbeiros cadastrados !");
        return;
    }
    
    NoBarbeiro* atual = sistema.listaBarbeiros;
    NoBarbeiro* anterior = NULL;

    if(atual != NULL && atual->id==id_lido){
        sistema.listaBarbeiros = atual->proximo;
        free(atual);
        printf("Barbeiro excluído com sucesso !\n");
        sistema.qtdBarbeiros--;
        return;
    }

    while(atual != NULL && atual->id != id_lido){
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("ID inexistente!\n");
        return;
    }
                
    anterior->proximo = atual->proximo;
    free(atual);

    printf("Barbeiro excluído com sucesso !\n");
    sistema.qtdBarbeiros--;
}


void atualizarBarbeiro(){
    int id_lido, option;
    printf("Digite o id do Barbeiro que deseja editar: ");
        scanf("%d",&id_lido);
        limparBufferInput();

        if(sistema.listaBarbeiros == NULL){
        printf("Não há barbeiros cadastrados !");
        return;
        }
            NoBarbeiro* temp = sistema.listaBarbeiros;

            while(temp != NULL && temp->id != id_lido){
                temp = temp->proximo;
            }

            if(temp == NULL){
                printf("ID inexistente!\n");
                return;
            }

            limparTela();
            printf("=================================\n");
            printf("  Barbeiro %d\n", temp->id);
            printf("  Nome: %s\n", temp->nome);
            printf("  Email: %s\n", temp->email);
            printf("=================================\n\n");
            printf("O que deseja editar do barbeiro selecionado ?\n");
            printf("  [1] Nome\n");
            printf("  [2] Email\n");
            printf("  [3] Senha\n");
            printf("  [4] Todas as informações\n");
            printf("  [0] Cancelar edição\n");
            
            printf("Escolha: \n");
            scanf("%d", &option);
            limparBufferInput();

            switch(option) {
                case 1:
                printf("Digite o novo nome: ");
                scanf( " %[^\n]", temp->nome);
                limparBufferInput();
                printf("Nome editado !\n");
                break;

                case 2:
                printf("Digite o novo email: ");
                scanf( " %[^\n]", temp->email);
                limparBufferInput();
                printf("Email editado !\n");
                break;

                case 3:
                printf("Digite a nova senha: ");
                scanf( " %[^\n]", temp->senha);
                limparBufferInput();
                printf("Senha editada !\n");
                break;

                case 4:
                printf("Digite o novo nome: ");
                scanf( " %[^\n]", temp->nome);
                limparBufferInput();
                printf("Nome editado !\n");

                printf("Digite o novo email: ");
                scanf( " %[^\n]", temp->email);
                limparBufferInput();
                printf("Email editado !\n");

                printf("Digite a nova senha: ");
                scanf( " %[^\n]", temp->senha);
                limparBufferInput();
                printf("Senha editada !\n");
                break;

                case 0:
                printf("Atualização de Barbeiro cancelada.\n");
                return;

                default:
            printf("Opcao invalida.\n");
            }
        printf("\n=================================\n");
        printf("  Barbeiro %d\n", temp->id);
        printf("  Nome: %s\n", temp->nome);
        printf("  Email: %s\n", temp->email);
        printf("=================================\n\n");
}


// ============================================================================
//                                RF-004: CONTROLAR FILA
// ============================================================================

void controlarFila() {
    limparTela();
    printf("======================================\n");
    printf("        CONTROLAR FILA DE ESPERA      \n");
    printf("======================================\n");

    if (sistema.filaInicio == NULL) {
        printf("A fila de espera está vazia.\n");
        return;
    }

    // O cliente na frente da fila
    int idProximo = sistema.filaInicio->idCliente;
    printf("Próximo Cliente a ser atendido: ID %d\n", idProximo);

    // Tentativa de encontrar o nome do cliente na lista de clientes (melhoria)
    char nomeCliente[100] = "Cliente Desconhecido";
    NoCliente* tempCliente = sistema.listaClientes;
    while(tempCliente != NULL) {
        if (tempCliente->id == idProximo) {
            strcpy(nomeCliente, tempCliente->nome);
            break;
        }
        tempCliente = tempCliente->proximo;
    }
    printf("Nome: %s\n", nomeCliente);
    printf("--------------------------------------\n");


    printf("[1] Chamar o Próximo (Remover da Fila)\n");
    printf("[2] Apenas Visualizar a Fila\n");
    printf("[0] Voltar\n");
    printf("Escolha: ");
    
    int opcao = lerOpcao();

    if (opcao == 1) {
        // Operação Dequeue (Desenfileirar)
        NoFila* proximo = sistema.filaInicio;
        sistema.filaInicio = proximo->proximo;
        
        // Se a fila esvaziou, o fim também é NULL
        if (sistema.filaInicio == NULL) {
            sistema.filaFim = NULL;
        }

        free(proximo);
        printf("\nCliente ID %d (%s) foi CHAMADO e removido da fila.\n", idProximo, nomeCliente);
    } else if (opcao == 2) {
        printf("\nLista completa da fila:\n");
        NoFila* atual = sistema.filaInicio;
        int posicao = 1;
        while (atual != NULL) {
            // Reutiliza o loop de busca de nome, mas precisa ser eficiente
            tempCliente = sistema.listaClientes;
            strcpy(nomeCliente, "ID Desconhecido");
            while(tempCliente != NULL) {
                if (tempCliente->id == atual->idCliente) {
                    strcpy(nomeCliente, tempCliente->nome);
                    break;
                }
                tempCliente = tempCliente->proximo;
            }
            printf("  %dº: ID %d | Nome: %s\n", posicao, atual->idCliente, nomeCliente);
            atual = atual->proximo;
            posicao++;
        }
    } else {
        printf("\nOperação cancelada.\n");
    }
}