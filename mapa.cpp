#include "mapa.h"
#include "mapa_ase.h"
#include <stdlib.h>

bool mapa_Chegou_Destino(mapa *m)
{
/*	bool achou = false;
	bool nao_chegou = false;
	int i,j;
	for(i=0;i < m->Y_MAX && achou == false && nao_chegou == false;i++)
	{
		for(j=0; j < m->X_MAX && achou == false && nao_chegou == false; j++){
			if(m->dado_mapa[i][j] == MAP_DESTINO)
			{
				if(m->ALG_POS_ATUAL_X == j && m->ALG_POS_ATUAL_Y == i)
				{
					achou = true;
				}
				else
				{
					nao_chegou = true;
				}
			}
		}
	}
*/
	return (m->ALG_POS_ATUAL_X == m->DESTINO_X && m->ALG_POS_ATUAL_Y == m->DESTINO_Y);
}

int mapa_Get_Posicao_InicialX(mapa *m)
{
	int achou = -1,i,j;
	for(i=0;i < m->Y_MAX && achou == -1;i++)
	{
		for(j=0; j < m->X_MAX && achou == -1; j++){
			if(m->dado_mapa[i][j] == MAP_INICIO)
			{
				achou = j;
			}
		}
	}
	return achou;
}
int mapa_Get_Posicao_InicialY(mapa *m)
{
	int achou = -1,i,j;
	for(i=0;i < m->Y_MAX && achou == -1;i++)
	{
		for(j=0; j < m->X_MAX && achou == -1; j++){
			if(m->dado_mapa[i][j] == MAP_INICIO)
			{
				achou = i;
			}
		}
	}
	return achou;
}

mapa *mapa_Gera_Exemplo()
{
	int i,j;
	mapa *m = (mapa*)malloc(sizeof(mapa));
	//define tamanho do mapa
	m->X_MAX = 70;
	m->Y_MAX = 23;
	//aloca memoria do mapa
	m->dado_mapa = (unsigned char**)malloc(m->Y_MAX*sizeof(unsigned char*));
	m->dado_algoritmo= (unsigned char**)malloc(m->Y_MAX*sizeof(unsigned char*));
	for(i=0; i < m->Y_MAX ; i++){
		m->dado_mapa[i] = (unsigned char*) malloc(m->X_MAX*sizeof(unsigned char));
		m->dado_algoritmo[i] = (unsigned char*) malloc(m->X_MAX*sizeof(unsigned char));
	}
	//limpa mapa
	for(i=0;i < m->Y_MAX;i++)
	{
		for(j=0; j < m->X_MAX; j++){
			m->dado_mapa[i][j] = MAP_PESO_0;
			m->dado_algoritmo[i][j] = ALG_NAO_PERCORRIDO;

		}
	}
	//define inicio e fim
	m->dado_mapa[0][0] = MAP_INICIO;
	m->dado_mapa[m->Y_MAX-1][m->X_MAX-1] = MAP_DESTINO;
	m->DESTINO_X = m->X_MAX-1;
	m->DESTINO_Y = m->Y_MAX-1;
	//define a posição de inicio do algoritmo
	m->ALG_POS_ATUAL_X = mapa_Get_Posicao_InicialX(m);
	m->ALG_POS_ATUAL_Y = mapa_Get_Posicao_InicialY(m);
	//cria barreiras
	for(i=5; i < m->Y_MAX ; i++)
	{
		m->dado_mapa[i][5] = MAP_BLOQUEADO;
		m->dado_mapa[i][15] = MAP_BLOQUEADO;

		m->dado_mapa[i][10] = MAP_PESO_20;

		m->dado_mapa[i][17] = MAP_PESO_40;
	}
	return m;
}

mapa *mapa_Carrega_Mapa_ase(char *end)
{
	return serializa_mapa_ase(end);
}

int mapa_Algoritmo_Distancia(mapa *M)
{
	int cnt =0;
	int i,j;
	for(i=0; i < M->Y_MAX; i++){
		for(j=0; j < M->X_MAX; j++)
		{
			if(M->dado_algoritmo[i][j] == ALG_PERCORRIDO_ATUAL){
				cnt++;
			}
		}
	}
	return cnt;
}

void mapa_Algoritmo_Nova_Rota(mapa *M)
{
	int i,j;
	for(i=0; i < M->Y_MAX; i++){
		for(j=0; j < M->X_MAX; j++)
		{
			if(M->dado_algoritmo[i][j] == ALG_PERCORRIDO_ATUAL){
				M->dado_algoritmo[i][j] = ALG_PERCORRIDO_ANTIGO;
			}
		}
	}
}

void mapa_Limpa_Mapa_Algoritmo(mapa *M)
{
	int i,j;
	for(i=0; i < M->Y_MAX; i++){
		for(j=0; j < M->X_MAX; j++)
		{
			M->dado_algoritmo[i][j] = ALG_NAO_PERCORRIDO;
		}
	}
	M->ALG_POS_ATUAL_X = mapa_Get_Posicao_InicialX(M);
	M->ALG_POS_ATUAL_Y = mapa_Get_Posicao_InicialY(M);
}

void mapa_Nova_Busca_Algoritmo(mapa *M)
{
	int i,j;
	for(i=0; i < M->Y_MAX; i++){
		for(j=0; j < M->X_MAX; j++)
		{
			if(M->dado_algoritmo[i][j] == ALG_PERCORRIDO_ATUAL)
			{
				M->dado_algoritmo[i][j] = ALG_PERCORRIDO_ANTIGO;
			}
		}
	}
	M->ALG_POS_ATUAL_X = mapa_Get_Posicao_InicialX(M);
	M->ALG_POS_ATUAL_Y = mapa_Get_Posicao_InicialY(M);
}


void mapa_Destroi(mapa *M)
{
	for(int y = 0 ; y < M->Y_MAX;y++){
		free(M->dado_algoritmo[y]);
		free(M->dado_mapa[y]);
	}
	free(M->dado_algoritmo);
	free(M->dado_mapa);
	free(M);
}