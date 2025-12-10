#ifndef VALIDACAO_DATA_H
#define VALIDACAO_DATA_H

#include <time.h>

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
} DataHora;

// Obtém a data e hora atual do sistema
DataHora obterDataHoraAtual();

// Verifica se uma data é válida (ex: não existe 31/02)
int dataValida(int dia, int mes, int ano);

// Verifica se hora é válida (0-23)
int horaValida(int hora);

// Compara duas datas/horas. Retorna:
// -1 se data1 < data2 (data1 é anterior)
//  0 se data1 == data2 (mesma data e hora)
//  1 se data1 > data2 (data1 é posterior)
int compararDataHora(DataHora data1, DataHora data2);

// Verifica se uma data/hora já passou (está no passado)
int dataHoraPassou(int dia, int mes, int ano, int hora);

// Verifica se uma data/hora é futura (está no futuro)
int dataHoraFutura(int dia, int mes, int ano, int hora);

// Verifica se um horário de agendamento é válido (horário comercial: 8h-18h)
int horarioComercialValido(int hora);

// Formata uma data para string legível
void formatarData(int dia, int mes, int ano, int hora, char* buffer);

#endif