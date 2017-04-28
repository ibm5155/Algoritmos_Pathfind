// Refeito e arrumado código gambiarra++ de autor original
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

//CPoint		m_cStart;
//CPoint		m_cEnd;

mapa *serializa_mapa_ase(char *Endereco)
{
	int i, j;
	FILE *io = fopen(Endereco,"r");
	mapa *m = NULL;
	int x =0 ,y =0, Versao =0;
	int Inicio[2] = {0,0};
	int Destino[2] = {0,0};
	int Tamanho_Mapa_Real[2] = {0 /*Y*/,0 /*X*/};//o mapa é sempre definido como 320x240, então vamos pegar o verdadeiro tamanho dele
	char formato[6];
	// pega formato
	for(i=0;i < 5;i++)  { ( i > 0 ? formato[i-1] = fgetc(io) : fgetc(io) );   }//é pra resultar em *ASE
	formato[i-1] = '\0';
	if(strcmp("*ASE",formato))
	{
		//arquivo não .ase
		return NULL;
	}
	//pega versao
	for(i=0;i < 4;i++) {  Versao += fgetc(io) << (i*8); } // é pra resultar em 200
	if(Versao != 200)
	{
		//versão diferente
		return NULL;
	}
	//pega tamanho horizontal do mapa
	for(i=0;i < 4;i++) {  x = x + ((int)fgetc(io) << (i*8) ); } // é pra resultar em 320
	//pega tamanho vertical do mapa
	for(i=0;i < 4;i++) { y += (int)fgetc(io) << (i*8); } // é pra resultar em 240

	m =(mapa*)malloc(sizeof(mapa));
	//define tamanho do mapa
	m->X_MAX = x;
	m->Y_MAX = y;
	//aloca memoria do mapa
	m->dado_mapa = (unsigned char**)malloc(m->Y_MAX*sizeof(unsigned char*));
	m->dado_algoritmo= (unsigned char**)malloc(m->Y_MAX*sizeof(unsigned char*));
	for(i=0; i < m->Y_MAX ; i++){
		m->dado_mapa[i] = (unsigned char*) malloc((m->X_MAX+1)*sizeof(unsigned char));
		m->dado_algoritmo[i] = (unsigned char*) malloc((m->X_MAX+1)*sizeof(unsigned char));
	}
	//limpa mapa
	for(i=0;i < m->Y_MAX;i++)
	{
		for(j=0; j < m->X_MAX; j++){
			m->dado_mapa[i][j] = MAP_PESO_0;
			m->dado_algoritmo[i][j] = ALG_NAO_PERCORRIDO;

		}
			m->dado_mapa[i][j] = '\0';
			m->dado_algoritmo[i][j] = '\0';
	}
	//Pega o Inicio do algoritmo
	for(i=0;i < 4;i++) { Inicio[1] += (int)fgetc(io) << (i*8); } // Posição Y
	for(i=0;i < 4;i++) { Inicio[0] += (int)fgetc(io) << (i*8); } // Posição X

	//Pega o Destino do algoritmo
	for(i=0;i < 4;i++) { Destino[1] += (int)fgetc(io) << (i*8); } // Posição Y
	for(i=0;i < 4;i++) { Destino[0] += (int)fgetc(io) << (i*8); } // Posição X
	m->DESTINO_X = Destino[1];
	m->DESTINO_Y = Destino[0];

	Tamanho_Mapa_Real[0] = (Inicio[0] > Destino[0] ? Inicio[0] : Destino[0]); // recebe a posição de inicio se ela for maior que a pos de destino ou a posiçãode destino se...
	Tamanho_Mapa_Real[1] = (Inicio[1] > Destino[1] ? Inicio[1] : Destino[1]); // recebe a posição de inicio se ela for maior que a pos de destino ou a posiçãode destino se...


	//Carrega mapa do arquivo
	for (i=0; i<x; i++) {
		for (j=0; j<y; j++) {
			 // não precisa fazer pitshift, vai resultar na mesma coisa X___X
 			 //a matriz estava invertida X____X
			switch(fgetc(io)) 
			{
			case 0:
				m->dado_mapa[j][i] = MAP_BLOQUEADO;
				Tamanho_Mapa_Real[0] = (j > Tamanho_Mapa_Real[0] ? j : Tamanho_Mapa_Real[0]);
				Tamanho_Mapa_Real[1] = (i > Tamanho_Mapa_Real[1] ? i : Tamanho_Mapa_Real[1]);
				break;
			case 192:
				m->dado_mapa[j][i] = MAP_PESO_20;
				Tamanho_Mapa_Real[0] = (j > Tamanho_Mapa_Real[0] ? j : Tamanho_Mapa_Real[0]);
				Tamanho_Mapa_Real[1] = (i > Tamanho_Mapa_Real[1] ? i : Tamanho_Mapa_Real[1]);
				break;
			case 128:
				m->dado_mapa[j][i] = MAP_PESO_40;
				Tamanho_Mapa_Real[0] = (j > Tamanho_Mapa_Real[0] ? j : Tamanho_Mapa_Real[0]);
				Tamanho_Mapa_Real[1] = (i > Tamanho_Mapa_Real[1] ? i : Tamanho_Mapa_Real[1]);
				break;
			//Não precisa carregar as partes em branco novamente
			}
		}
	}
	m->dado_mapa[Inicio[0]][Inicio[1]] = MAP_INICIO;
	m->dado_mapa[Destino[0]][Destino[1]] = MAP_DESTINO;

	// Redefine o tamanho do mapa
		//define tamanho do mapa
	m->Y_MAX = Tamanho_Mapa_Real[0]+1;
	m->X_MAX = Tamanho_Mapa_Real[1]+1;

	unsigned char **tmp =0;
	unsigned char *tmp2 =0;

	tmp = (unsigned char**)realloc(m->dado_mapa,m->Y_MAX*sizeof(unsigned char*));
	m->dado_mapa = tmp;
	tmp = (unsigned char**)realloc(m->dado_algoritmo,m->Y_MAX*sizeof(unsigned char*));
	m->dado_algoritmo  = tmp;
	//libera memoria do mapa
	for(i= 0; i < m->Y_MAX ; i++){
		tmp2 = (unsigned char*) realloc(m->dado_mapa[i],m->X_MAX*sizeof(unsigned char));
		m->dado_mapa[i] = tmp2;
		tmp2 = (unsigned char*) realloc(m->dado_algoritmo[i],m->X_MAX*sizeof(unsigned char));
		m->dado_algoritmo[i] = tmp2;
	}


	return m;
}