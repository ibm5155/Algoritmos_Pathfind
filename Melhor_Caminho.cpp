#include "mapa.h"
#include "interface_mapa.h"

void Melhor_Caminho(mapa *m)
{
	int Passos = 1;
	int Tentativas = 1;
	int DistanciaPercorrida;
	while(!mapa_Chegou_Destino(m))
	{
		//marca no mapa a posição atual
		m->dado_algoritmo[m->ALG_POS_ATUAL_Y][m->ALG_POS_ATUAL_X] = ALG_PERCORRIDO_ATUAL;
		DistanciaPercorrida = mapa_Algoritmo_Distancia(m);
		desenha_interface_mapa(m,&Passos,&DistanciaPercorrida,0,0,0,0,0);
		//Espera para o proximo passo

		//MOVE
		if(m->DESTINO_X > m->ALG_POS_ATUAL_X)
		{
			m->ALG_POS_ATUAL_X++;
		}
		else if(m->DESTINO_X < m->ALG_POS_ATUAL_X)
		{
			m->ALG_POS_ATUAL_X--;
		}
		if(m->DESTINO_Y > m->ALG_POS_ATUAL_Y)
		{
			m->ALG_POS_ATUAL_Y++;
		}
		else if(m->DESTINO_Y < m->ALG_POS_ATUAL_Y)
		{
			m->ALG_POS_ATUAL_Y--;
		}
		Passos++;
	}
		desenha_interface_mapa(m,&Passos,&DistanciaPercorrida,1,0,0,0,0);
}