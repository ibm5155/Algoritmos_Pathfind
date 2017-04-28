#include "mapa.h"
#include "interface_mapa.h"
#include "socket_comunicacao.h"

void Melhor_Caminho_JS(mapa *m)
{
	int Passos = 1;
	int Tentativas = 1;
	socket_aguarda_conexao();
	socket_envia_mapa(m);
	while(!mapa_Chegou_Destino(m))
	{
		m->dado_algoritmo[m->ALG_POS_ATUAL_Y][m->ALG_POS_ATUAL_X] = ALG_PERCORRIDO_ATUAL;

		desenha_interface_mapa(m,&Passos,&Tentativas,0,0,0,0,0);
		//Espera para o proximo passo

		if(socket_recebe_novo_passo(m))
		{
			Tentativas++;
		}
		Passos++;
	}
		desenha_interface_mapa(m,&Passos,&Tentativas,1,0,0,0,0);
}