#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>

void exibirMenuBarbeiro() {
    char senha[32];
    const char *SENHA_CORRETA = "TuringBarberUFG"; 

    limparTela();
    printf("=================================\n");
    printf("|         B A R B E I R O       |\n");
    printf("=================================\n");
    for (int i = 0; i < 3; i++){
        printf("\nDigite a senha: ");
        if (scanf("%31s", senha) != 1) {
            limparBufferInput();
            printf("\nErro ao ler senha.\n");
            pausarTela();
            return;
        }
    
        limparBufferInput();

        if (strcmp(senha, SENHA_CORRETA) != 0) {
            printf("\nSenha incorreta!\n");
            printf("Tentativas restantes: %d\n", 2 - i);
                if (i-2 == 0) return;
                else continue;
        } else {
            break;
        }
    } 
    if (strcmp(senha, SENHA_CORRETA) != 0) {
        return;
    }
    int opcao;
    do {
        limparTela();
        printf("=================================\n");
        printf("|         B A R B E I R O       |\n");
        printf("=================================\n");
        printf("| [1] Sou barbeiro \t\t|\n");
        printf("| [2] Sou cliente \t\t|\n");
        printf("| [0] Retornar para o Menu principal|\n");
        printf("=================================\n");
        printf("Escolha: ");

        opcao = lerOpcao(); 

        switch(opcao) {
            case 1:
                printf("\n[Placeholder] Listando clientes...\n");
                pausarTela();
                break;
            case 2:
                printf("\n[Placeholder] Iniciando atendimento...\n");
                pausarTela();
                break;
            case 0:
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausarTela();
        }

    } while (opcao != 0);

}

void exibirMenuPrincipal() {
    int opcao;
    
    do {
        limparTela();
        printf("=================================\n");
        printf("|    T U R I N G  B A R B E R   |\n");
        printf("=================================\n");
        printf("| [1] Sou barbeiro \t\t|\n");
        printf("| [2] Sou cliente \t\t|\n");
        printf("| [0] Sair\t\t\t|\n");
        printf("=================================\n");
        printf("Escolha: ");

        opcao = lerOpcao(); 

        switch(opcao) {
            case 1:
                exibirMenuBarbeiro();
                break;
            case 2:
                //exibirMenuCliente();
                break;
            case 0:
                printf("\nEncerrando o sistema.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausarTela();
        }

    } while (opcao != 0);
}