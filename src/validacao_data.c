#include "validacao_data.h"
#include <stdio.h>
#include <string.h>

// Obtém a data e hora atual do sistema
DataHora obterDataHoraAtual() {
    DataHora atual;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    atual.dia = tm_info->tm_mday;
    atual.mes = tm_info->tm_mon + 1; // tm_mon é 0-11
    atual.ano = tm_info->tm_year + 1900; // tm_year é anos desde 1900
    atual.hora = tm_info->tm_hour;
    
    return atual;
}

// Verifica se o ano é bissexto
static int anoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Retorna o número de dias em um mês
static int diasNoMes(int mes, int ano) {
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (mes < 1 || mes > 12) return 0;
    
    if (mes == 2 && anoBissexto(ano)) {
        return 29;
    }
    
    return dias[mes - 1];
}

// Verifica se uma data é válida
int dataValida(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > diasNoMes(mes, ano)) return 0;
    return 1;
}

// Verifica se hora é válida
int horaValida(int hora) {
    return (hora >= 0 && hora <= 23);
}

// Converte data/hora para timestamp (dias desde 1/1/1900 + fração do dia)
static long long dataHoraParaTimestamp(DataHora dh) {
    // Contagem simplificada de dias desde 1900
    long long dias = 0;
    
    // Adiciona anos completos
    for (int a = 1900; a < dh.ano; a++) {
        dias += anoBissexto(a) ? 366 : 365;
    }
    
    // Adiciona meses completos do ano atual
    for (int m = 1; m < dh.mes; m++) {
        dias += diasNoMes(m, dh.ano);
    }
    
    // Adiciona dias do mês atual
    dias += dh.dia;
    
    // Converte para timestamp incluindo horas (dias * 24 + hora)
    return dias * 24 + dh.hora;
}

// Compara duas datas/horas
int compararDataHora(DataHora data1, DataHora data2) {
    long long ts1 = dataHoraParaTimestamp(data1);
    long long ts2 = dataHoraParaTimestamp(data2);
    
    if (ts1 < ts2) return -1;
    if (ts1 > ts2) return 1;
    return 0;
}

// Verifica se uma data/hora já passou
int dataHoraPassou(int dia, int mes, int ano, int hora) {
    DataHora atual = obterDataHoraAtual();
    DataHora verificar = {dia, mes, ano, hora};
    
    return compararDataHora(verificar, atual) < 0;
}

// Verifica se uma data/hora é futura
int dataHoraFutura(int dia, int mes, int ano, int hora) {
    DataHora atual = obterDataHoraAtual();
    DataHora verificar = {dia, mes, ano, hora};
    
    return compararDataHora(verificar, atual) > 0;
}

// Verifica se o horário está dentro do horário comercial
int horarioComercialValido(int hora) {
    return (hora >= 8 && hora <= 18);
}

// Formata uma data para string legível
void formatarData(int dia, int mes, int ano, int hora, char* buffer) {
    sprintf(buffer, "%02d/%02d/%04d às %02d:00h", dia, mes, ano, hora);
}