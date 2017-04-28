#include <stdlib.h>
#include <math.h>
#include "mapa.h"
#include "Lista.h"
#include "No.h"
#include "interface_mapa.h"
#include <string>
#include <MT2D/MessageBox/MT2D_MessageBox.h>

float H(int X, int Y, mapa *m)
{
	float ret = ((float)m->DESTINO_X - X) * ((float)m->DESTINO_X - X) + ((float)m->DESTINO_Y - Y)* ((float)m->DESTINO_Y - Y);
	ret = sqrt((float)ret);
	ret += (m->dado_mapa[Y][X] != MAP_DESTINO ? m->dado_mapa[Y][X] * 2 : 0);
	return ret;

}

bool checkNodeWeight(No *neighbor,Lista *list) {
	int result = false;
	float f = neighbor->F;
	float x = neighbor->Px;
	float y = neighbor->Py;
	int size = list->Tamanho;
//	list = list.list;//?
	for (int i = 0; i < size; i++) {
		if ((list->Vetor[i].Px == x) && list->Vetor[i].Py == y) {
			if (list->Vetor[i].F <= f) {
				result = true;
			}
		}
	}
	return result;
}

int NoCount(No *n)
{
	int i=0;
	for(No *m = n; m; m = m->Proximo, i++);
	return i;
}

No *GetLessNode(Lista *OpenList){

	int size = OpenList->Tamanho;
	float n = OpenList->Vetor[0].F;
	int idx = 0;
	for (int i = 0; i < size; i++) {
		if (OpenList->Vetor[i].F < n) {
			n = OpenList->Vetor[i].F ;
			idx = i;
		}
	}
	//retorna uma copia e não um ponteiro direto
	return CriaNo(0,OpenList->Vetor[idx].Px,OpenList->Vetor[idx].Py,OpenList->Vetor[idx].F,OpenList->Vetor[idx].G,OpenList->Vetor[idx].H,OpenList->Vetor[idx].Anterior);
}

float GetFn(No *Lessnode,bool TemG){
	float F =0;
	No *N = Lessnode;
	while(N){
			F += N->G + 1;

		N = N->Anterior;
	}
	return F;
}

Lista *GetNeihbors(mapa *m, No *LessNode){
	int x = LessNode->Px;
	int y = LessNode->Py;
	No *Novo;
	Lista *neighbors = Lista_Cria();

	if (x >= 0 && y-1 >= 0 ){
		if(m->dado_mapa[y-1][x] != MAP_BLOQUEADO){

			Lista_Adiciona_No(neighbors,CriaNo(NULL,x,y-1,0,0,0,LessNode));
		}
	}
	if (x + 1 < m->X_MAX && y-1 >= 0){
		if(m->dado_mapa[y-1][x+1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x+1,y-1,0,0,0,LessNode));
		}
	}
	if (x-1 >= 0 && y-1 >= 0){ //não precisa checar se ele passou do limite pois é garantido que o lessnode esteja em uma posicao valida
		if(m->dado_mapa[y-1][x-1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x-1,y-1,0,0,0,LessNode));
		}
	}
	if (y+1 < m->Y_MAX){
		if(m->dado_mapa[y+1][x] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x,y+1,0,0,0,LessNode));
		}
	}
	if (y+1 < m->Y_MAX && x-1 >= 0){
		if(m->dado_mapa[y+1][x-1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x-1,y+1,0,0,0,LessNode));
		}
	}
	if (x+1 <  m->X_MAX && y+1 < m->Y_MAX){
		if(m->dado_mapa[y+1][x+1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x+1,y+1,0,0,0,LessNode));
		}
	}
	if (x -1 >= 0){
		if(m->dado_mapa[y ][x -1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x-1,y,0,0,0,LessNode));
		}
	}
	if (x +1 < m->X_MAX){
		if(m->dado_mapa[y][x+1] != MAP_BLOQUEADO){
			Lista_Adiciona_No(neighbors,CriaNo(NULL,x + 1,y,0,0,0,LessNode));
		}
	}
	return neighbors;
}


void GenericIA(mapa *m, bool Repete,bool incluiH, bool incluiG){
	//var target
	int x = mapa_Get_Posicao_InicialX(m);
	int y = mapa_Get_Posicao_InicialY(m);
	int Passos = 1;//meu ui
	int Tentativas = 1;//meu ui
	int Distancia_Percorrida;//meu ui
	char FBUFFER[20] = {'\0'};
	No *lessNode;
	Lista *neighbors = Lista_Cria();
	Lista *OpenList = Lista_Cria(); 
	Lista *closeList = Lista_Cria();
	No *ThisLeaf;
	No *goTo;
	No *LastID;
	No *CurrentPath;
//	No *rTree = 0; é gerado durante o processamento
	No *Novo;
	bool stop = true;
	int expandedNode = 1;
	int Px,Py;
	int tmp;
	Lista_Adiciona_No(OpenList,CriaNo(0, m->ALG_POS_ATUAL_X, m->ALG_POS_ATUAL_Y,0,0,0,NULL));
	while(OpenList->Tamanho > 0 && stop){
		lessNode = GetLessNode(OpenList);
		neighbors = GetNeihbors(m,lessNode);
		//ThisLeaf = new ThisLeaf();
		Lista_Remove_No(OpenList,lessNode);
		tmp = 0;
		for(No *neighbor = 0; tmp < neighbors->Tamanho;tmp++){
			neighbor = &neighbors->Vetor[tmp];
			goTo = neighbor;

			//neighbor = neighbors[neighbor];
			//aqui não tem gambiarra de javascript, aqui é C RAIZ!!!
			Px = neighbor->Px;
			Py = neighbor->Py;	
			/*   == não é mais checado pois o filtro já é realizado no GetNeihbors
			if(m->dado_mapa[i][j] == MAP_BLOQUEADO){
				continue;
			}
			*/
			if(m->DESTINO_Y == Py && m->DESTINO_X == Px){
				//chegamos ao destino
				stop = false;
//				ThisLeaf = Addchildren(ThisLeaf, neighbor,Goto);
//				rTree.Addleaf(thisleaf);
				neighbor->G = 0;
				m->dado_algoritmo[Py][Px] = ALG_PERCORRIDO_ATUAL;
//				clearOldStart(current);
				m->ALG_POS_ATUAL_X = Px;
				m->ALG_POS_ATUAL_Y = Py;
//				setStart(current);
//				lastID = i+","+j;
				break;
			}
			neighbor->G = lessNode->G + m->dado_mapa[Py][Px];

			neighbor->H = H(Px,Py,m);
			neighbor->F = (incluiG == true ? neighbor->G : 0) + (incluiH == true ? neighbor->H : 0);
			if (!checkNodeWeight(neighbor,OpenList) && !checkNodeWeight(neighbor,closeList)) {
				Novo = CriaNo(0,Px,Py);
				Novo->F = neighbor->F;
				Novo->G = neighbor->G;
				Novo->H = neighbor->H;
				Novo->Anterior = lessNode;
				Lista_Adiciona_No(OpenList,Novo);
				//já é feito ao pegar a lista de vizinhos
				//thisLeaf.addChildren(neighbor,goTo);
				expandedNode++;
			}
		}
		Passos++;
		m->ALG_POS_ATUAL_X = lessNode->Px;
		m->ALG_POS_ATUAL_Y = lessNode->Py;
		Lista_Adiciona_No(closeList,lessNode);
		mapa_Algoritmo_Nova_Rota(m);
		NoDesenhaMapa(lessNode, m);
		Distancia_Percorrida = mapa_Algoritmo_Distancia(m);
		sprintf(FBUFFER,"Cus Tot=%f",GetFn(lessNode, incluiG));
		desenha_interface_mapa(m, &Passos, &Distancia_Percorrida, false,FBUFFER, 0, 0, 0);
		//thisLeaf.setLeaf(lessNode);
//		rTree.addLeaf(thisLeaf.getNode());
	}
	if (stop) {
		char buffer[200];
		sprintf(buffer,"%c%c%c                                                                  %c%c%c                 Nao existe caminho D=                            %c%c%c ",244,245,246,247,248,249,250,251,252);
		MT2D_MessageBox(buffer);
	}
	
	desenha_interface_mapa(m, &Passos, &Distancia_Percorrida, true, FBUFFER, 0, 0, 0);

//	rTree.algorithm = "A*";
//	rTree.lastID = lastID;
//	rTree.totalCost = lessNode.g;
//	rTree.expandedNode = expandedNode;

}
