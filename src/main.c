#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "contexto.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(){

    #ifdef _WIN32
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
    #endif
    inicializarSistema();
    exibirMenuPrincipal();

    return 0;
}