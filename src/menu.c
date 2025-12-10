#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "contexto.h" 
#include "controle_barbeiro.h"
#include "controle_cliente.h"
#include "autenticacao.h" // Importante para as funções de login/logout

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
    do
    {
        limparTela();
        // O menu agora exibe o ID do barbeiro logado (Admin)
        printf("======================================\n");
        printf("      AREA DO BARBEIRO (ID: %d)       \n", sistema.idBarbeiroLogado);
        printf("======================================\n");
        
        printf("  [1] Gerenciar Equipe (Barbeiros)\n");
        printf("  [2] Gerenciar Clientes\n");
        printf("  [3] Ver Agenda (Dia/Semana)\n");
        printf("  [4] Controlar Fila de Espera\n");
        printf("  [0] Voltar / Logout\n");
        printf("======================================\n");

        // Calculando quantos na fila
        int qtdFila = 0;
        NoFila* atual = sistema.filaInicio;
        while(atual != NULL) {
            qtdFila++;
            atual = atual->proximo;
        }

        printf("Barbeiros Cadastrados: %d | Clientes: %d | Na Fila: %d\n", 
               sistema.qtdBarbeiros, sistema.qtdClientes, qtdFila);
        printf("======================================\n");
        
        printf("Escolha: ");
        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                menuGerenciarBarbeiros();
                pausarTela();
                break;
            case 2:
                gerenciarClientes();
                pausarTela();
                break;
            case 3:
                listarAgendamentos(); // Implementado em controle_barbeiro.c
                pausarTela();
                break;
            case 4:
                controlarFila(); // Implementado em controle_barbeiro.c
                pausarTela();
                break;
            case 0:
                fazerLogout(); // Zera o ID do barbeiro logado
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
    do
    {
        limparTela();
        // O menu agora exibe o ID do cliente logado
        printf("======================================\n");
        printf("      AREA DO CLIENTE (ID: %d)       \n", sistema.idClienteLogado);
        printf("======================================\n");
        
        printf("  [1] Agendar Horário\n");
        printf("  [2] Entrar na Fila de Espera\n");
        printf("  [3] Ver Meus Agendamentos\n");
        printf("  [4] Sair da Fila de Espera\n");
        printf("  [0] Voltar / Logout\n");
        printf("======================================\n");
        printf("Escolha: ");
        
        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                agendarHorario(); // Implementado em controle_cliente.c
                pausarTela();
                break;
            case 2:
                entrarNaFila(); // Implementado em controle_cliente.c
                pausarTela();
                break;
            case 3:
                listarMeusAgendamentos(); // Implementado em controle_cliente.c
                pausarTela();
                break;
            case 4:
                sairDaFila(); // Implementado em controle_cliente.c
                pausarTela();
                break;
            case 0:
                fazerLogout(); // Zera o ID do cliente logado
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
        printf("======================================\n");
        printf("      T U R I N G   B A R B E R       \n");
        printf("======================================\n");
        printf("  Bem-vindo! Identifique-se:\n\n");
        printf("  [1] Sou Barbeiro / Admin\n");
        printf("  [2] Sou Cliente\n");
        printf("  [0] Encerrar Programa\n");
        printf("======================================\n");
        printf("Escolha: ");

        opcao = lerOpcao();

        switch(opcao) {
            case 1:
                // Tenta fazer o login. Se for bem-sucedido (retorna 1), exibe o menu admin
                if (fazerLoginBarbeiro()) {
                    exibirMenuBarbeiro(); 
                }
                break;
            case 2:
                // Tenta fazer o login. Se for bem-sucedido (retorna 1), exibe o menu cliente
                if (fazerLoginCliente()) {
                    exibirMenuCliente(); 
                }
                break;
            case 0:
                printf("\nObrigado por usar o Turing Barber. Encerrando...\n");
                // Contagem regressiva de encerramento
                for (int i = 3; i >= 1; --i) {
                    printf("  Encerrando em %d...\r", i);
                    fflush(stdout);
                    #ifdef _WIN32
                        Sleep(1000); // milissegundos
                    #else
                        sleep(1); // segundos
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