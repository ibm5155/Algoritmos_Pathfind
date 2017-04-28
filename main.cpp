#include <stdio.h>
#include <stdlib.h>
#include <MT2D/MT2D.h>
#include <MT2D/MT2D_Keyboard.h>
#include <MT2D/MT2D_System_Calls.h>
#include "globais.h"
#include "mapa.h"
#include "interface_mapa.h"
#include "interface_menu.h"

#include "socket_comunicacao.h"

#include "Melhor_Caminho.h"
#include "Melhor_Caminho_JS.h"
#include "Busca_Largura.h"
#include "Busca_Gulosa.h"
#include "Busca_Uniforme.h"
#include "Astar.h"

void main()
{
	bool sair = false;
	MT2D_Init();

	socket_inicia();
//	reseta_interface(); // globais.h
//	MAPA = mapa_Carrega_Mapa_ase();//mapa_Gera_Exemplo();
	while(sair == false)
	{
		algoritmo_usado = interface_menu();
		if(algoritmo_usado != -1 && MAPA == NULL)
		{
			MAPA = mapa_Gera_Exemplo();
		}
		else if(MAPA != NULL)
		{
			mapa_Limpa_Mapa_Algoritmo(MAPA);
		}
		switch(algoritmo_usado)
		{
		case -1://sair
			sair = true;
			break;
		case 0:
			Melhor_Caminho(MAPA);
		break;
		case 1:
			Busca_Astar(MAPA,false);
			break;
		case 2:
			Melhor_Caminho_JS(MAPA);
			break;
		case 3:
			Busca_Largura(MAPA,true);
			break;
		case 4:
			Busca_Largura(MAPA,false);
			break;
		case 5:
			Busca_Gulosa(MAPA, false);
			break;
		case 6:
			Busca_Uniforme(MAPA,false);
			break;
		}
	}
	socket_desliga();
}