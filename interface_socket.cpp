#include <MT2D/MT2D_Display.h>
#include <MT2D/MT2D.h>
#include <MT2D/MT2D_Keyboard.h>
#include <MT2D/MT2D_System_Calls.h>
#include <MT2D/MT2D_Layout.h>
#include <MT2D/Tools/Video/MT2D_Generic_Line.h>
#include <stdio.h>
#include <stdlib.h>

extern int Animacao;
extern void Desenha_Ondas();
/*{
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
*/
char *Carregando_cnt[6][2] = { {"\\"},{"|"},{"/"},{"-"},{"\\"},{"| "} };
char buff[80];
bool animacao_conectando_socket(int *timer,char *endereco, char *porta,bool conectado)
{
	bool Desistir = false;
	MT2D_Clear_Main_Window();
	Desenha_Ondas();
	MT2D_Create_Window_Layout(15,8,40,10,true,false,false,' ',DISPLAY_WINDOW1);
	insert_string_on_display(*Carregando_cnt[Animacao%6],9,16,DISPLAY_WINDOW1);
	insert_string_on_display("Aguardando conexao em",9,18,DISPLAY_WINDOW1);
	sprintf(buff,"%s:%s",endereco,porta);
	insert_string_on_display(buff,10,16,DISPLAY_WINDOW1);
	if(conectado)
	{
		insert_string_on_display("Conectado",12,16,DISPLAY_WINDOW1);
	}
	else
	{
		sprintf(buff,"Timeout em %d", timer[0]);
		insert_string_on_display(buff,12,16,DISPLAY_WINDOW1);
	}
	MT2D_Draw_Window(DISPLAY_WINDOW1);
	return Desistir;
}