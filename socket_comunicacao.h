#ifndef SOCKET_H
#define SOCKET_H

void socket_inicia();
void socket_envia_dado(char *dado);
char *socket_recebe_dado();
bool socket_envia_mapa(mapa *m);
bool socket_recebe_novo_passo(mapa *m);
bool socket_atualiza_rota_algoritmo();
void socket_aguarda_conexao();
void socket_desliga();

#endif