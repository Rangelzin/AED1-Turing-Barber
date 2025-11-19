#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct NoCliente {
    int id;
    char nome[100];
    char telefone[20];
    char senha[20];
    struct NoCliente* proximo;
} NoCliente;

typedef struct NoBarbeiro {
    int id;
    char nome[100];
    char email[100];
    char senha[20];
    struct NoBarbeiro* proximo;
} NoBarbeiro;

typedef struct NoAgendamento {
    int id;
    int idCliente;
    int idBarbeiro;
    int dia, mes, ano, hora;
    struct NoAgendamento* proximo;
} NoAgendamento;

typedef struct NoFila {
    int idCliente;
    struct NoFila* proximo;
} NoFila;

#endif
