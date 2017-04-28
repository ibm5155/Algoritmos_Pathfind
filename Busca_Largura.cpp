#include <stdlib.h>
#include "mapa.h"
#include "No.h"
#include "interface_mapa.h"

void Busca_Largura(mapa *m, bool Repete)
{
	int x,y,i;
	int Passos = 1;
	int Tentativas = 1;
	int Distancia;
	x = mapa_Get_Posicao_InicialX(m);
	y = mapa_Get_Posicao_InicialY(m);
	No *raiz = CriaNo(0,x,y);
	No *Pnt = raiz;
	No *Novo =0;
	int noAtual =0;
	int noFinal = 0;
	while(!mapa_Chegou_Destino(m) && Pnt){
			
		m->ALG_POS_ATUAL_X--;
		m->ALG_POS_ATUAL_Y--;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);
			//Espera para o proximo passo
		}
		m->ALG_POS_ATUAL_X++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}
			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);

			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_X++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}
			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);

			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_Y++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}

			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);
			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_X-=2;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}

			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);

			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_Y++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}
			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);
			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_X++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}
			desenha_interface_mapa(m,&Passos,&Tentativas,0,0,0,0,0);
			//Espera para o proximo passo
		}

		m->ALG_POS_ATUAL_X++;
		if(!No_JaVisitado(m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y,m,raiz,Repete)){
			Novo = CriaNo(0,m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
			NoAdicionaUtimo(raiz,Novo,Pnt);
			mapa_Algoritmo_Nova_Rota(m);
			NoDesenhaMapa(Novo,m);
			Passos++;
			Distancia = mapa_Algoritmo_Distancia(m);
			if(mapa_Chegou_Destino(m))
			{
				break;	
			}
			desenha_interface_mapa(m,&Passos,&Distancia,0,0,0,0,0);
			//Espera para o proximo passo
		}

		Pnt = Pnt->Proximo;
		if(Pnt){
			m->ALG_POS_ATUAL_X = Pnt->Px;
			m->ALG_POS_ATUAL_Y = Pnt->Py;
		}
	}
	desenha_interface_mapa(m,&Passos,&Distancia,1,0,0,0,0);
	//Espera para o proximo passo

}