#include <MT2D/MT2D_Keyboard.h>
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/MT2D_Display.h>
#include <MT2D/MT2D_Layout.h>
#include <MT2D/MT2D.h>
#include "globais.h"
#include "mapa.h"

void desenha_interface_opcoes(int *Passos, int *Tentativas,char *O1,char *O2, char *O3, char *O4)
{
	if(mostra_tela_dados == true)
	{
		//desenha o layout da janela
		MT2D_Create_Window_Layout(60,0,19,MAX_VER-1,false,false,false,' ',DISPLAY_WINDOW1);
		//plota algoritmo usado
		switch(algoritmo_usado)
		{
		case 0:
			insert_string_on_display(Algoritmo_1,1,61,DISPLAY_WINDOW1);
			break;
		case 1:
			insert_string_on_display(Algoritmo_2,1,61,DISPLAY_WINDOW1);
			break;
		case 2:
			insert_string_on_display(Algoritmo_3,1,61,DISPLAY_WINDOW1);
			break;
		case 3:
			insert_string_on_display(Algoritmo_4,1,61,DISPLAY_WINDOW1);
			break;
		case 4:
			insert_string_on_display(Algoritmo_5,1,61,DISPLAY_WINDOW1);
			break;
		case 5:
			insert_string_on_display(Algoritmo_6,1,61,DISPLAY_WINDOW1);
			break;
		case 6:
			insert_string_on_display(Algoritmo_7,1,61,DISPLAY_WINDOW1);
			break;
		}
		//desenha a quantidade de passos dada
		insert_string_on_display("EXPANDIDOS:",3,61,DISPLAY_WINDOW1);
		if(Passos)
		{
			insert_number_on_display(Passos[0],3,72,DISPLAY_WINDOW1);
		}
		//desenha a quantidade de tentativas feita pelo algoritmo
		insert_string_on_display("DIST FINAL:",5,61,DISPLAY_WINDOW1);
		if(Tentativas)
		{
			insert_number_on_display(Tentativas[0],5,72,DISPLAY_WINDOW1);
		}
		//bota a velocidade da simulação na tela
		insert_string_on_display("VELOCIDADE:",7,61,DISPLAY_WINDOW1);
		if(simulacao_velocidade>=0){
			insert_number_on_display(simulacao_velocidade,7,73,DISPLAY_WINDOW1);
		}
		else{
			insert_string_on_display("TURBO",7,73,DISPLAY_WINDOW1);
		}

		insert_string_on_display("TAB MOSTRA/OCULTA.",9,61,DISPLAY_WINDOW1);

		insert_string_on_display("P DIRETO/PASSO A",11,61,DISPLAY_WINDOW1);
		insert_string_on_display(" PASSO.",12,61,DISPLAY_WINDOW1);

		insert_string_on_display("+/- altera VELOCID",13,61,DISPLAY_WINDOW1);
		insert_string_on_display("ADE.",14,61,DISPLAY_WINDOW1);

		if(O1)
		{
			insert_string_on_display(O1,16,61,DISPLAY_WINDOW1);
		}
		if(O2)
		{
			insert_string_on_display(O2,17,61,DISPLAY_WINDOW1);
		}
		if(O3)
		{
			insert_string_on_display(O3,18,61,DISPLAY_WINDOW1);
		}
		if(O4)
		{
			insert_string_on_display(O4,19,61,DISPLAY_WINDOW1);
		}


	}
}

void desenha_interface_mapa(mapa *m, int *Passos, int *Tentativas,int Terminou, char *O1,char *O2, char *O3, char *O4)
{
	int y,x;
	bool continuar = simulacao_com_parada || (Terminou > 0);
	int Fim_Horiz = MAX_HOR - (20 * mostra_tela_dados);
	// Seleciona a parte inicial do mapa a ser visualizada
	// Garantindo que a posição inicial sempre estara na tela
	if(simulacao_velocidade >= 0 || Terminou == true)
	{
		posicao_tela_Y = (m->ALG_POS_ATUAL_Y/MAX_VER)*MAX_VER; 
		posicao_tela_X = (m->ALG_POS_ATUAL_X/Fim_Horiz)*Fim_Horiz;

		do{
			//limpa a tela
			MT2D_Clear_Main_Window();

			//desenha o mapa
			for(y = 0; y < MAX_VER && y + posicao_tela_Y < m->Y_MAX; y++){
				for(x = 0; x < Fim_Horiz && x + posicao_tela_X < m->X_MAX; x++){
					switch(m->dado_mapa[y + posicao_tela_Y][x + posicao_tela_X])
					{
					case MAP_INICIO:
						WINDOW1[y][x] = 'I';
						break;
					case MAP_PESO_0:
						//já limpamos a tela então não precisa fazer isso novamente
						WINDOW1[y][x] = 219;
						//vazio se console
						break;
					case MAP_PESO_20:
						WINDOW1[y][x] = 176;
						break;
					case MAP_PESO_40:
						WINDOW1[y][x] = 177;
						break;
					case MAP_BLOQUEADO:
						WINDOW1[y][x] = 255;
						//219
						break;
					case MAP_DESTINO:
						WINDOW1[y][x] = 243;//'D'
						break;
					}
				}
			}
			//desenha contorno mapa
			if(y < MAX_VER)
			{
				for(int i=0; i < x; i++)
				{
					WINDOW1[y][i] = 196;
				}
			}
			if(x < Fim_Horiz){
				for(int i =0; i < y; i++)
				{
					WINDOW1[i][x] = 179;
				}
			}
			if(x < Fim_Horiz && y < MAX_VER){
				WINDOW1[y][x] = 217;
			}
			//178
			//'.'
			//desenha o que o algoritmo fez
			for(y = 0; y < MAX_VER && y + posicao_tela_Y < m->Y_MAX; y++){
				for(x = 0; x < Fim_Horiz && x + posicao_tela_X < m->X_MAX; x++){
					switch(m->dado_algoritmo[y + posicao_tela_Y][x + posicao_tela_X])
					{
					case ALG_PERCORRIDO_ATUAL:
						WINDOW1[y][x] = 254;//197;
						break;
					case ALG_PERCORRIDO_ANTIGO:
						WINDOW1[y][x] = 253;//'.';
						break;
					}
				}
			}
			//coloca informações a mais na tela
			desenha_interface_opcoes(Passos,Tentativas,O1,O2,O3,O4);



			if(simulacao_com_parada || Terminou)
			{
				MT2D_System_Delay(30);
				//renderiza
				MT2D_Draw_Window(DISPLAY_WINDOW1);

			}
			if(MT2D_Keyboard_touched())
			{
				switch(MT2D_Keyboard_keytouched())
				{
				case enter_pressed:
					continuar = false;
					break;
				case arrow_key_pressed:
					switch(MT2D_Keyboard_keytouched())
					{
					case arrow_down_pressed:
						if(posicao_tela_Y < m->Y_MAX -3)
						{
							posicao_tela_Y++;
						}
						break;
					case arrow_up_pressed:
						if(posicao_tela_Y > 0)
						{
							posicao_tela_Y--;
						}
						break;
					case arrow_left_pressed:
						if(posicao_tela_X > 0)
						{
							posicao_tela_X--;
						}
						break;
					case arrow_right_pressed:
						if(posicao_tela_X < m->X_MAX -3)
						{
							posicao_tela_X++;
						}
						break;
					}
					break;
				case tab_pressed:
					mostra_tela_dados = !mostra_tela_dados;
				break;
				case 'P':
				case 'p':
					simulacao_com_parada = !simulacao_com_parada;
					continuar = simulacao_com_parada;
					break;
				case '+':
				case '=':
					if(simulacao_velocidade <200){
						simulacao_velocidade+=10;
					}
					break;
				case '-':
					if(simulacao_velocidade > -10){
						simulacao_velocidade-=10;
					}

					break;
				}
			}
			else{
				MT2D_System_Delay(10);
			}
			
		}while(continuar);
		//Espera um pouco
		//renderiza
		MT2D_Draw_Window(DISPLAY_WINDOW1);
		if(simulacao_velocidade > 0)
			MT2D_System_Delay(simulacao_velocidade);
	}
}
