#include "globais.h"
#include <stdio.h>
#include <stdlib.h>
#include <MT2D/MT2D.h>
#include <MT2D/MT2D_Display.h>
#include <MT2D/MT2D_Keyboard.h>
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/MT2D_Layout.h>
#include <MT2D/MessageBox/MT2D_MessageBox.h>
#include <MT2D/InputBox/MT2D_InputBox_String.h>
#include <MT2D/Tools/Video/MT2D_Generic_Line.h>

int Animacao=0;
void Desenha_Ondas()
{
	MT2D_Line_Draw_Vertical(Animacao,rand()%3+175);
	MT2D_Line_Draw_Vertical((Animacao+1)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+2)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+3)%MAX_VER,rand()%4+175);

	MT2D_Line_Draw_Vertical((Animacao+7)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+8)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+9)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+10)%MAX_VER,rand()%4+175);

	MT2D_Line_Draw_Vertical((Animacao+15)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+16)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+17)%MAX_VER,rand()%4+175);
	MT2D_Line_Draw_Vertical((Animacao+18)%MAX_VER,rand()%4+175);

	Animacao = (Animacao + 1)%MAX_VER;

}

void Apaga_Retangulo()
{
	for(int y=2;y < 17; y++) for(int x=9;x <61;x++) WINDOW1[y][x] = ' ';
}

int int_opcoes =-1;
int cnt2 =0;
void interface_opcoes()
{
	MT2D_Create_Window_Layout(15,8,40,10,true,false,false,' ',DISPLAY_WINDOW1);

			for(int y=9+ (int_opcoes*2); y < 12+ (int_opcoes*2) ; y+=2) {
			for(int x=16; x < 54 ; x++) {
				if(cnt2 < 15)
				{
					WINDOW1[y][x] = (y == 9+ (int_opcoes*2) ? 'v' : '^');
				}
			}
		}
		if(cnt2 < 15)
		{
			WINDOW1[10 + (int_opcoes*2)][16] = '>';
			WINDOW1[10 + (int_opcoes*2)][53] = '<';
		}
		cnt2++;
		if(cnt2 == 30) cnt2 = 0;


	insert_string_on_display("Simulacao Com Parada:",10,17,DISPLAY_WINDOW1);
	if(simulacao_com_parada == true)
	{
		insert_string_on_display("SIM",10,39,DISPLAY_WINDOW1);
	}
	else
	{
		insert_string_on_display("NAO",10,39,DISPLAY_WINDOW1);
	}

	insert_string_on_display("Velocidade Simulacao:",12,17,DISPLAY_WINDOW1);
	if(simulacao_velocidade == -10)
	{
	insert_string_on_display("TURBO",12,39,DISPLAY_WINDOW1);
	}
	else
	{
	insert_number_on_display(simulacao_velocidade,12,39,DISPLAY_WINDOW1);
	}


	insert_string_on_display("Detalhes   Simulacao:",14,17,DISPLAY_WINDOW1);
	if(mostra_tela_dados == true)
	{
		insert_string_on_display("SIM",14,39,DISPLAY_WINDOW1);
	}
	else
	{
		insert_string_on_display("NAO",14,39,DISPLAY_WINDOW1);
	}

	insert_string_on_display("FECHAR",16,17,DISPLAY_WINDOW1);
}

int interface_menu() //Retorna o algoritmo a ser usado.
{
	int alg = 0; //nenhum / sair
	int tecla =0;
	bool sair = false;
	MapaNome = 0;
	int opcao=0;
	int cnt=0;
	char *map_name= 0;
	FILE *map_file;
	map_name = (char*)malloc(8*sizeof(char));
	sprintf(map_name,"exemplo");
	while(!sair)
	{
		// DESENHA TELA
		MT2D_Clear_Main_Window();
		Desenha_Ondas();
		MT2D_Create_Window_Layout(9,2,52,15,true,false,false,' ',DISPLAY_WINDOW1);
		for(int y=6+ (opcao*2); y < 9+ (opcao*2) ; y+=2) {
			for(int x=11; x < 60 ; x++) {
				if(cnt < 15)
				{
					WINDOW1[y][x] = (y == 6+ (opcao*2) ? 'v' : '^');
				}
			}
		}
		if(cnt < 15)
		{
			WINDOW1[7 + (opcao*2)][11] = '>';
			WINDOW1[7 + (opcao*2)][59] = '<';
		}
		cnt++;
		if(cnt == 30) cnt = 0;
		insert_string_on_display("Trabalho Feito por:",3,10,DISPLAY_WINDOW1);
		insert_string_on_display("-Lucas Zimerman",4,12,DISPLAY_WINDOW1);
		insert_string_on_display("-Raul Santos",5,12,DISPLAY_WINDOW1);
		insert_string_on_display("ALGORITMO:",7,12,DISPLAY_WINDOW1);
		switch(alg)
		{
		case 0:
			insert_string_on_display(Algoritmo_1,7,23,DISPLAY_WINDOW1);
			break;
		case 1:
			insert_string_on_display(Algoritmo_2,7,23,DISPLAY_WINDOW1);
			break;
		case 2:
			insert_string_on_display(Algoritmo_3,7,23,DISPLAY_WINDOW1);
			break;
		case 3:
			insert_string_on_display(Algoritmo_4,7,23,DISPLAY_WINDOW1);
			break;
		case 4:
			insert_string_on_display(Algoritmo_5,7,23,DISPLAY_WINDOW1);
			break;
		case 5:
			insert_string_on_display(Algoritmo_6, 7, 23, DISPLAY_WINDOW1);
			break;
		case 6:
			insert_string_on_display(Algoritmo_7, 7, 23, DISPLAY_WINDOW1);
			break;
		}
		insert_string_on_display("MAPA:",9,12,DISPLAY_WINDOW1);
			insert_string_on_display(map_name,9,18,DISPLAY_WINDOW1);
		insert_string_on_display("SIMULAR",11,12,DISPLAY_WINDOW1);
		insert_string_on_display("OPCOES",13,12,DISPLAY_WINDOW1);
		insert_string_on_display("SAIR",15,12,DISPLAY_WINDOW1);
		
		if(int_opcoes != -1)
		{
			interface_opcoes();
		}

		MT2D_Draw_Window(DISPLAY_WINDOW1);
		MT2D_System_Delay(100);
		//TRATA TECLADO

		if(MT2D_Keyboard_touched())
		{
			tecla = MT2D_Keyboard_keytouched();
			if(int_opcoes == -1) //menu principal
			{
				if(tecla == enter_pressed)
				{
					if(opcao == 4)
					{
						sair = true;
						alg = -1;
					}
					else if(opcao == 3)
					{
						int_opcoes =0;
					}
					else if(opcao == 2)
					{
						sair = true;
					}
					else if(opcao == 1)
					{
						map_name = MT2D_InputBox_String("Digite o endereco e o nome do mapa (se estiver na mesma pasta do programa entao so o nome");
						map_file = fopen(map_name,"r");
						if(!map_file)
						{
							MT2D_MessageBox("Arquivo nao encontrado");
							free(map_name);
							map_name = (char*)malloc(8*sizeof(char));
							sprintf(map_name,"exemplo");
						}
						else
						{
							MAPA = mapa_Carrega_Mapa_ase(map_name);
							if(MAPA == NULL)
							{
								MT2D_MessageBox("Formato de mapa desconhecido");
								free(map_name);
								map_name = (char*)malloc(8*sizeof(char));
								sprintf(map_name,"exemplo");
							}
						}
					}
				}
				else if(tecla == arrow_key_pressed)
				{
					cnt = 0;
					tecla = MT2D_Keyboard_keytouched();
					if(tecla == arrow_down_pressed)
					{
						if(opcao == 4)
						{
							opcao = 0;
						}
						else
						{
							opcao++;
						}
					}
					if(tecla == arrow_up_pressed)
					{
						if(opcao == 0)
						{
							opcao = 4;
						}
						else
						{
							opcao--;
						}
					}
					if(opcao ==0)
					{
						if(tecla == arrow_left_pressed )
						{
							if(alg == 0)
							{
								alg = 6;
							}
							else
							{
								alg--;
							}
						}
						if(tecla == arrow_right_pressed)
						{
							if(alg == 6)
							{
								alg = 0;
							}
							else
							{
								alg++;
							}
						}
					}
				}
			}
			else // MEU OPCOES
			{
				if(tecla == enter_pressed)
				{
					if(int_opcoes == 3)
					{
						int_opcoes = -1;
						cnt2 =0;
					}
				}
				else if(tecla == arrow_key_pressed)
				{
					cnt2 = 0;
					tecla = MT2D_Keyboard_keytouched();
					if(tecla == arrow_down_pressed)
					{
						if(int_opcoes == 3)
						{
							int_opcoes = 0;
						}
						else
						{
							int_opcoes++;
						}
					}
					if(tecla == arrow_up_pressed)
					{
						if(int_opcoes == 0)
						{
							int_opcoes = 3;
						}
						else
						{
							int_opcoes--;
						}
					}
					else if(tecla == arrow_left_pressed )
					{
						if(int_opcoes == 0){
							simulacao_com_parada = !simulacao_com_parada;
						}
						else if(int_opcoes == 1)
						{
							if(simulacao_velocidade > -10)
							{
								simulacao_velocidade -= 10;
							}
						}
						else if(int_opcoes == 2)
						{
							mostra_tela_dados = !mostra_tela_dados;
						}
					}
					if(tecla == arrow_right_pressed)
					{
						if(int_opcoes == 0){
							simulacao_com_parada = !simulacao_com_parada;

						}
						else if(int_opcoes == 1)
						{
							if(simulacao_velocidade < 200)
							{
								simulacao_velocidade += 10;
							}
						}
						else if(int_opcoes == 2)
						{
							mostra_tela_dados = !mostra_tela_dados;
						}
					}
				}

			}
		}
	
	}
	return alg;
}

