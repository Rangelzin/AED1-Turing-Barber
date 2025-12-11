#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "contexto.h" 
#include "controle_barbeiro.h"
#include "controle_cliente.h"
#include "autenticacao.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// ============================================================================
//                              ÁREA DO BARBEIRO
// ============================================================================

void exibirMenuBarbeiro() {
    int opcao;
    char titulo[100]; // Buffer para formatar o título com ID

    do {
        limparTela();
        
        // Formata o título com o ID dinâmico
        sprintf(titulo, "AREA DO BARBEIRO (ID: %d)", sistema.idBarbeiroLogado);
        imprimirCabecalho(titulo);
        
        printf("  [1] Gerenciar Equipe (Barbeiros)\n");
        printf("  [2] Gerenciar Clientes\n");
        printf("  [3] Ver Agenda (Dia/Semana)\n");
        printf("  [4] Controlar Fila de Espera\n");
        printf("  [0] Voltar / Logout\n");
        
        imprimirRodape(); // Fecha a caixa do menu

        // Calculando quantos na fila
        int qtdFila = 0;
        NoFila* atual = sistema.filaInicio;
        while(atual != NULL) {
            qtdFila++;
            atual = atual->proximo;
        }

        // Exibe estatísticas rápidas abaixo do menu
        printf("Barbeiros: %d | Clientes: %d | Na Fila: %d\n", 
               sistema.qtdBarbeiros, sistema.qtdClientes, qtdFila);
        imprimirSeparador();
        
        printf("Escolha: ");
        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                menuGerenciarBarbeiros();
                // O pausarTela já tem separador embutido no novo utils
                pausarTela(); 
                break;
            case 2:
                gerenciarClientes();
                pausarTela();
                break;
            case 3:
                listarAgendamentos();
                pausarTela();
                break;
            case 4:
                controlarFila();
                salvarDados();
                pausarTela();
                break;
            case 0:
                fazerLogout();
                printf("Logout realizado com sucesso.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausarTela();
        }
    } while (opcao != 0);
}

// ============================================================================
//                               ÁREA DO CLIENTE
// ============================================================================

void exibirMenuCliente() {
    int opcao;
    char titulo[100];

    do {
        limparTela();
        
        sprintf(titulo, "AREA DO CLIENTE (ID: %d)", sistema.idClienteLogado);
        imprimirCabecalho(titulo);
        
        printf("  [1] Agendar Horário\n");
        printf("  [2] Entrar na Fila de Espera\n");
        printf("  [3] Ver Meus Agendamentos\n");
        printf("  [4] Sair da Fila de Espera\n");
        printf("  [0] Voltar / Logout\n");
        
        imprimirRodape();

        printf("Escolha: ");
        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                agendarHorario();
                pausarTela();
                break;
            case 2:
                entrarNaFila();
                pausarTela();
                break;
            case 3:
                listarMeusAgendamentos();
                pausarTela();
                break;
            case 4:
                sairDaFila();
                pausarTela();
                break;
            case 0:
                fazerLogout();
                printf("Logout realizado com sucesso.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausarTela();
        }
    } while (opcao != 0);
}

// ============================================================================
//                             MENU PRINCIPAL
// ============================================================================

void exibirMenuPrincipal() {
    int opcao;

    do {
        limparTela();
        
        imprimirCabecalho("T U R I N G   B A R B E R");
        printf("  Bem-vindo! Identifique-se:\n\n");
        printf("  [1] Sou Barbeiro / Admin\n");
        printf("  [2] Sou Cliente\n");
        printf("  [0] Encerrar Programa\n");
        imprimirRodape();

        printf("Escolha: ");
        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                if (fazerLoginBarbeiro()) {
                    exibirMenuBarbeiro(); 
                }
                break;
            case 2:
                if (fazerLoginCliente()) {
                    exibirMenuCliente(); 
                }
                break;
            case 0:
                printf("\nObrigado por usar o Turing Barber. Encerrando...\n");
                for (int i = 3; i >= 1; --i) {
                    printf("  Encerrando em %d...\r", i);
                    fflush(stdout);
                    #ifdef _WIN32
                        Sleep(1000);
                    #else
                        sleep(1);
                    #endif
                }
                printf("  Encerrando em 0...   \n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausarTela();
        }
    } while (opcao != 0);
}