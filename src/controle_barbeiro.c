#include <stdio.h>
#include <stdlib.h>
#include "contexto.h"
#include "utils.h"
#include "controle_barbeiro.h"

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
                if(sistema.listaBarbeiros->id==id_lido){
                    NoBarbeiro* temp = sistema.listaBarbeiros;
                    sistema.listaBarbeiros = sistema.listaBarbeiros->proximo;
                    free(temp);
                    printf("Barbeiro excluído com sucesso !\n");
                    return;
                    }

                    NoBarbeiro* temp = sistema.listaBarbeiros;    

                    while(temp->proximo != NULL && temp->proximo->id != id_lido){
                        temp = temp->proximo;
                    }

                    if(temp->proximo == NULL){
                        printf("ID inexistente!\n");
                        return;
                    }
                                
                    NoBarbeiro* alvo =  temp->proximo;

                    temp->proximo = alvo->proximo;
                    free(alvo);

                    printf("Barbeiro excluído com sucesso !\n");
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

                while(temp->proximo!=NULL && temp->id != id_lido){
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
                        scanf( "%[^\n]", temp->nome);
                        limparBufferInput();
                        printf("Nome editado !\n");
                        printf("\n=================================\n");
                        printf("  Barbeiro %d\n", temp->id);
                        printf("  Nome: %s\n", temp->nome);
                        printf("  Email: %s\n", temp->email);
                        printf("=================================\n\n");
                        break;

                        case 2:
                        printf("Digite o novo email: ");
                        scanf( "%[^\n]", temp->email);
                        limparBufferInput();
                        printf("Email editado !\n");
                        printf("\n=================================\n");
                        printf("  Barbeiro %d\n", temp->id);
                        printf("  Nome: %s\n", temp->nome);
                        printf("  Email: %s\n", temp->email);
                        printf("=================================\n\n");
                        break;

                        case 3:
                        printf("Digite a nova senha: ");
                        scanf( "%[^\n]", temp->senha);
                        limparBufferInput();
                        printf("Senha editada !\n");
                        printf("\n=================================\n");
                        printf("  Barbeiro %d\n", temp->id);
                        printf("  Nome: %s\n", temp->nome);
                        printf("  Email: %s\n", temp->email);
                        printf("=================================\n\n");
                        break;

                        case 4:
                        printf("Digite o novo nome: ");
                        scanf( "%[^\n]", temp->nome);
                        limparBufferInput();
                        printf("Nome editado !\n");

                        printf("Digite o novo email: ");
                        scanf( "%[^\n]", temp->email);
                        limparBufferInput();
                        printf("Email editado !\n");

                        printf("Digite a nova senha: ");
                        scanf( "%[^\n]", temp->senha);
                        limparBufferInput();
                        printf("Senha editada !\n");
                        printf("\n=================================\n");
                        printf("  Barbeiro %d\n", temp->id);
                        printf("  Nome: %s\n", temp->nome);
                        printf("  Email: %s\n", temp->email);
                        printf("=================================\n\n");
                        break;

                        case 0:
                        printf("Atualização de Barbeiro cancelada.\n");
                        break;

                        default:
                    printf("Opcao invalida.\n");
                    }
}