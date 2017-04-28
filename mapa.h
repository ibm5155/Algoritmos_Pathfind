#ifndef MAPA_H
#define MAPA_H

enum mapa_dado_tipo
{
	//Dados salvos no mapa
	MAP_PESO_0,
	MAP_PESO_20,
	MAP_PESO_40,
	MAP_BLOQUEADO,
	MAP_INICIO,
	MAP_DESTINO,

	//Dados gerados pelo algoritmo
	ALG_NAO_PERCORRIDO = 0,
	ALG_PERCORRIDO_ATUAL,//posição atual percorrida
	ALG_PERCORRIDO_ANTIGO,   //caso não seja a melhor opção marca esse caminho como ruim
	ALG_POSICAO_ATUAL // o no atual que esta
};


struct mapa
{
	unsigned char **dado_mapa;
	unsigned char **dado_algoritmo;
	unsigned int X_MAX;
	unsigned int Y_MAX;
	int ALG_POS_ATUAL_X;
	int ALG_POS_ATUAL_Y;
	unsigned int DESTINO_X;
	unsigned int DESTINO_Y;
};

mapa *mapa_Gera_Exemplo();
mapa *mapa_Carrega_Mapa_ase(char *end);
void mapa_Limpa_Mapa_Algoritmo(mapa *M);
void mapa_Algoritmo_Nova_Rota(mapa *M);
int mapa_Algoritmo_Distancia(mapa *M);

//retorna -1 se não encontrado
int mapa_Get_Posicao_InicialX(mapa *m);
int mapa_Get_Posicao_InicialY(mapa *m);

bool mapa_Chegou_Destino(mapa *m);

void mapa_Destroi(mapa *M);

#endif