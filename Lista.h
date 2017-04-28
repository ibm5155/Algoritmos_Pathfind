#ifndef LISTA_H
#define LISTA_H

#include "No.h"

struct Lista{
	int Tamanho;
	No *Vetor;
};


Lista *Lista_Cria();
void Lista_Adiciona_No(Lista *L, No *N);

void Lista_Remove_No(Lista *L, No *N);

#endif