#ifndef GLOBAIS_H
#define GLOBAIS_H
#include "mapa.h"

extern char *MapaNome;
extern mapa *MAPA;
#define Algoritmo_1 "Melhor Caminho"
#define Algoritmo_2 "A*"
#define Algoritmo_3 "Algoritmo Externo (socket)"
#define Algoritmo_4 "Busca Largura"
#define Algoritmo_5 "Busca Largura Sem repeticao"
#define Algoritmo_6 "Busca Gulosa"
#define Algoritmo_7 "Busca Uniforme"

extern int posicao_tela_X;
extern int posicao_tela_Y;
extern bool mostra_tela_dados;
extern bool simulacao_com_parada;
extern int  simulacao_velocidade;
extern int algoritmo_usado;


void reseta_interface();

#endif