#include <stdlib.h>
#include "No.h"
#include "Lista.h"



Lista *Lista_Cria(){
	Lista *L = (Lista*)malloc(sizeof(Lista));
	L->Tamanho=0;
	L->Vetor = NULL;

	return L;
}

void Lista_Adiciona_No(Lista *L, No *N){
	if(L->Tamanho == 0){
		L->Vetor = (No*)malloc(sizeof(No));
	}
	else{
		No *tmp = (No*)realloc(L->Vetor,(L->Tamanho+2)*sizeof(No));
		L->Vetor = tmp;
	}
	//adiciona uma copia do no e nao um ponteiro
	L->Vetor[L->Tamanho] = *CriaNo(0,N->Px,N->Py,N->F,N->G,N->H,N->Anterior);

	L->Tamanho++;
}

void Lista_Remove_No(Lista *L, No *N){
	int i=0;
	for(; i < L->Tamanho; i++){
		if(L->Vetor[i].Px == N->Px && L->Vetor[i].Py == N->Py){
			break;
		}
	}
	if(L->Vetor[i].Px == N->Px && L->Vetor[i].Py == N->Py){
		for(; i < L->Tamanho -1; i++){
			L->Vetor[i] = L->Vetor[i+1];
		}
		L->Tamanho--;
		No *Tmp = (No*)realloc(L->Vetor,L->Tamanho*sizeof(No));
		L->Vetor = Tmp;
	}
}