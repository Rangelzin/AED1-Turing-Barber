#include <stdio.h>
#include <stdlib.h>
#include "contexto.h"

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
        printf("Novvo Barbeiro adicionado!");
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

