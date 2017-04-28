#include "No.h"
#include "mapa.h"
#include <stdlib.h>

No *CriaNo(int Referencia,int X,int Y)
{
	No *N= (No*)malloc(sizeof(No));
	N->Anterior = 0;
	N->Proximo = 0;
	N->F = 0;
	N->G = 0;
	N->H = 0;
	N->Px =X;
	N->Py = Y;
	N->CicloCnt = 4;
	N->Referencia = Referencia;
	return N;
}

No *CriaNo(int Referencia,int X,int Y,float F, float G, float H, No *Anterior)
{
	No *N= (No*)malloc(sizeof(No));
	N->Anterior = Anterior;
	N->Proximo = 0;
	N->F = F;
	N->G = G;
	N->H = H;
	N->Px =X;
	N->Py = Y;
	N->CicloCnt = 4;

	N->Referencia = Referencia;
	return N;
}
void NoAdicionaUtimo(No *Raiz, No *N, No *Anterior){
	No *P = Raiz;
	while(P->Proximo){
		P = P->Proximo;
	}
	N->Anterior = Anterior;
	P->Proximo = N;
}

void NoDesenhaMapa(No *Fim, mapa *m){
	No *P = Fim;
	while(P){
		m->dado_algoritmo[P->Py][P->Px] = ALG_PERCORRIDO_ATUAL;
		P = P->Anterior;
	}
}

bool No_JaVisitado(int X, int Y, mapa *m, No *nos, bool Repete) {
	bool visitado = false;
	No *prox = nos;
	if (X < 0 || Y < 0 || X >= m->X_MAX || Y >= m->Y_MAX)
	{
		visitado = true;
	}
	else if (m->dado_mapa[Y][X] == MAP_BLOQUEADO || m->dado_mapa[Y][X] == MAP_PESO_40 || m->dado_mapa[Y][X] == MAP_PESO_20) {
		visitado = true;
	}
	else if (Repete == false)
	{
		while (prox) {
			if (prox->Px == X && prox->Py == Y) {
				visitado = true;
				prox = 0;
			}
			else {
				prox = prox->Proximo;
			}
		}
	}
	return visitado;
}