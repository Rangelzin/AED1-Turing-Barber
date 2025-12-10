#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "contexto.h" 
#include "controle_barbeiro.h"
#include "controle_cliente.h"

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
        printf("======================================\n");
        printf("      AREA DO BARBEIRO (ADMIN)        \n");
        printf("======================================\n");
        // RF-008: Gerenciar Barbeiros
        printf("  [1] Gerenciar Equipe (Barbeiros)\n");
        // RF-007: Gerenciar Clientes
        printf("  [2] Gerenciar Clientes\n");
        // RF-006: Visualizar Agenda
        printf("  [3] Ver Agenda (Dia/Semana)\n");
        // RF-004: Visualizar Fila
        printf("  [4] Controlar Fila de Espera\n");
        printf("  [0] Voltar / Logout\n");
        printf("======================================\n");

        // Calculando quantos na fila
        int qtdFila = 0;
        NoFila* pFila = sistema.filaInicio;
        while(pFila != NULL) {
            qtdFila++;
            pFila = pFila->proximo;
        }

        // Exibindo estatísticas rápidas usando o contexto global
        printf(" Status: %d Clientes | %d Na Fila\n",
               sistema.qtdClientes,
               qtdFila); 
        printf("======================================\n");
        printf("Escolha: ");

        opcao = lerOpcao();

        switch (opcao)
        {
        case 1:
            menuGerenciarBarbeiros();
            pausarTela();
            break;
        case 2:
            gerenciarClientes(); // Implementado em controle_cliente.c
            pausarTela();
            break;
        case 3:
            listarAgendamentos();
            pausarTela();
            break;
        case 4:
            controlarFila(); // Implementado em controle_barbeiro.c
            pausarTela();
            break;
        case 0:
            printf("\nSaindo do perfil administrativo...\n");
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

void exibirMenuCliente()
{
    int opcao;
    do {
        limparTela();
        printf("======================================\n");
        printf("           AREA DO CLIENTE            \n");
        printf("======================================\n");
        // RF-002: Agendar
        printf("  [1] Agendar Horario (Futuro)\n");
        // RF-003: Fila Imediata
        printf("  [2] Entrar na Fila (Imediato)\n");
        // RNF-001: Meus Agendamentos
        printf("  [3] Meus Agendamentos\n");
        // RF-005: Sair da Fila
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
                break; // Retorna ao menu principal
            default:
                printf("\nOpcao invalida!\n");
                pausarTela();
            }
    } while (opcao != 0);
}

// ============================================================================
//                            ROTEADOR PRINCIPAL
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
                // Futuramente: validarSenhaAdmin();
                exibirMenuBarbeiro(); 
                break;
            case 2:
                // Futuramente: loginCliente();
                exibirMenuCliente(); 
                break;
            case 0:
                printf("\nObrigado por usar o Turing Barber. Encerrando...\n");
                // includes here para compatibilidade cross-platform
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