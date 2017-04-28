#include "mapa.h"
char *MapaNome = 0;
mapa *MAPA = 0;

int posicao_tela_X = 0;
int posicao_tela_Y = 0;
bool mostra_tela_dados = true;

bool simulacao_com_parada = false;
int  simulacao_velocidade = 10;
int algoritmo_usado =0;

void reseta_interface()
{
	posicao_tela_X = 0;
	posicao_tela_Y = 0;
	mostra_tela_dados = true;
}