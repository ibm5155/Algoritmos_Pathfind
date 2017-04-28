#ifndef NO_H
#define NO_H

#include "mapa.h"

struct No{
	No *Anterior;
	No *Proximo;
	int Referencia;
	int CicloCnt;
	int Px,Py;
	float F,G,H;
};


No *CriaNo(int Referencia,int X,int Y);
No *CriaNo(int Referencia,int X,int Y,float F, float G, float H, No *Anterior);
void NoAdicionaUtimo(No *Raiz, No *N,No *Anterior);
void NoDesenhaMapa(No *Fim, mapa *m);
bool No_JaVisitado(int X, int Y, mapa *m, No *nos, bool Repete);

#endif