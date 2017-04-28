#include "mapa.h"
#include "interface_socket.h"
#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#include <MT2D/MT2D_System_Calls.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

bool socket_Inicializado = false;
char *buffer_mensagem,*lixo;
const int MAXRECV = 1024;
WSADATA wsa;
SOCKET master , new_socket , client_socket[30] , s;
struct sockaddr_in server, address;
int activity, addrlen, valread;

void socket_inicia()
{
	
	socket_Inicializado = true;

    //1 extra for null character, string termination
    buffer_mensagem =  (char*) malloc((MAXRECV + 1) * sizeof(char));
	lixo =  (char*) malloc((MAXRECV + 1) * sizeof(char));
 
    client_socket[0] = 0;
 
//    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
		socket_Inicializado = false;
//        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
     
//    printf("Initialised.\n");
     
    //Create a socket
    if((master = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
		socket_Inicializado = false;
//        printf("Could not create socket : %d" , WSAGetLastError());
//        exit(EXIT_FAILURE);
    }
 
//    printf("Socket created.\n");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(master ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
		socket_Inicializado = false;
		//        printf("Bind failed with error code : %d" , WSAGetLastError());
       // exit(EXIT_FAILURE);
    }
     
   // puts("Bind done");
 
    //Listen to incoming connections
    listen(master , 3);
     
}

void socket_envia_dado(char *dado)
{
	if( send(new_socket, dado, strlen(dado), 0) != strlen(dado) ) 
    {
        //perror("send failed");
    }
}

char *socket_recebe_dado()
{
	int end_string = -1;
	buffer_mensagem[0] = '\0'; // pra 
	do
	{
	recv( client_socket[0] , lixo, MAXRECV, 0);
	end_string = recv( client_socket[0] , buffer_mensagem, MAXRECV, 0);
	if(buffer_mensagem[0] == '\0')
	{
		MT2D_System_Delay(1);
	}
	else
	{
		buffer_mensagem[end_string] = '\0';
	}
	}while(buffer_mensagem[0] == '\0');
	return buffer_mensagem;
}

bool socket_envia_mapa(mapa *m)
{
	sprintf(buffer_mensagem,"INICIO\n");
	socket_envia_dado(buffer_mensagem);
	sprintf(buffer_mensagem,"MAPSIZE: %d,%d\n",m->X_MAX,m->Y_MAX);
	socket_envia_dado(buffer_mensagem);
	sprintf(buffer_mensagem,"INICIO: %d,%d\n",m->ALG_POS_ATUAL_X,m->ALG_POS_ATUAL_Y);
	socket_envia_dado(buffer_mensagem);
	sprintf(buffer_mensagem,"DESTINO: %d,%d\n",m->DESTINO_X,m->DESTINO_Y);
	socket_envia_dado(buffer_mensagem);
	for(int y=0; y < m->Y_MAX; y++)
	{
		for(int x=0; x < m->X_MAX; x++)
		{
			switch(m->dado_mapa[y][x])
			{
			case MAP_BLOQUEADO:
			sprintf(buffer_mensagem,"MAP_BLOQUEADO: %d,%d\n",x,y);
			socket_envia_dado(buffer_mensagem);
			break;
			case MAP_PESO_40:
			sprintf(buffer_mensagem,"MAP_PESO_40: %d,%d\n",x,y);
			socket_envia_dado(buffer_mensagem);
			break;
			case MAP_PESO_20:
			sprintf(buffer_mensagem,"MAP_PESO_20: %d,%d\n",x,y);
			socket_envia_dado(buffer_mensagem);
			break;
			}
		}
	}
	sprintf(buffer_mensagem,"FIM");
	socket_envia_dado(buffer_mensagem);
	return true;
}

bool socket_atualiza_rota_algoritmo();


bool socket_recebe_novo_passo(mapa *m)
{
	int i,j;
	int x,y;
	//retorno ? 0 = mesmo caminho
	//          1 = caminho trocado
	socket_recebe_dado();
	if(strstr(buffer_mensagem,"NOVO_CAMINHO"))
	{
		socket_recebe_dado();
		// " [X,Y],[X,Y],....
	}
	else
	{
		//"X,Y"
		i=0;
		while(buffer_mensagem[i] != ',') i++;
		j= 0;
		x=0;
		while(j < i)
		{
			x = x*10 + (buffer_mensagem[j] - '0' /*char to int*/);
			j++;
		}
		while(buffer_mensagem[i] != NULL) i++;
		y = 0;
		j++;
		while(j < i)
		{
			y = y*10 + (buffer_mensagem[j] - '0' /*char to int*/);
			j++;
		}
		m->ALG_POS_ATUAL_X = x;
		m->ALG_POS_ATUAL_Y = y;
	}
	return false;
}

void socket_aguarda_conexao()
{
	int Timeout = 1000;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	char *mensagem_boas_vinda = "Servidor conectado...\n";
    //size of our receive buffer, this is string length.
    //set of socket descriptors
    fd_set readfds;
	    //Accept and incoming connection
  //  puts("Waiting for incoming connections...");
     
    addrlen = sizeof(struct sockaddr_in);
     
    while(s == NULL && Timeout > 0)
    {
		animacao_conectando_socket(&Timeout,"local","8888",activity == SOCKET_ERROR);
        //clear the socket fd set
        FD_ZERO(&readfds);
  
        //add master socket to fd set
        FD_SET(master, &readfds);
         
        //add child sockets to fd set
        s = client_socket[0];
        if(s > 0)
        {
            FD_SET( s , &readfds);
        }
         
        //wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
        activity = select( 0 , &readfds , NULL , NULL ,&tv);
    
        if ( activity == SOCKET_ERROR ) 
        {
            //printf("select call failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
			socket_Inicializado = false;
        }
          
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master , &readfds)) 
        {
            if ((new_socket = accept(master , (struct sockaddr *)&address, (int *)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
          
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
        
            //send new connection greeting message
            if( send(new_socket, mensagem_boas_vinda, strlen(mensagem_boas_vinda), 0) != strlen(mensagem_boas_vinda) ) 
            {
                //perror("send failed");
				socket_Inicializado = false;
            }
              
            //puts("Welcome message sent successfully");
              
            //add new socket to array of sockets

            if (client_socket[0] == 0)
            {
                client_socket[0] = new_socket;
                //printf("Adding to list of sockets at index %d \n" , i);
                break;
            }
        }
          
        //else its some IO operation on some other socket :)
        s = client_socket[0];
        //if client presend in read sockets             
        if (FD_ISSET( s , &readfds)) 
        {
            //get details of the client
            getpeername(s , (struct sockaddr*)&address , (int*)&addrlen);
 
            //Check if it was for closing , and also read the incoming message
            //recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one).
            valread = recv( s , buffer_mensagem, MAXRECV, 0);
                 
            if( valread == SOCKET_ERROR)
            {
                int error_code = WSAGetLastError();
                if(error_code == WSAECONNRESET)
                {
                    //Somebody disconnected , get his details and print
                    printf("Host disconnected unexpectedly , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                      
                    //Close the socket and mark as 0 in list for reuse
                    closesocket( s );
                    client_socket[0] = 0;
                }
                else
                {
                    printf("recv failed with error code : %d" , error_code);
                }
            }
            if ( valread == 0)
            {
                //Somebody disconnected , get his details and print
                printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                      
                //Close the socket and mark as 0 in list for reuse
                closesocket( s );
                client_socket[0] = 0;
            }
                  
            //Echo back the message that came in
            else
            {
                //add null character, if you want to use with printf/puts or other string handling functions
//                buffer[valread] = '\0';
    //            printf("%s:%d - %s \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port), buffer);
  //              send( s , buffer , valread , 0 );
            }
        }
		Timeout--;
    }
}

//bool socket_


void socket_desliga()
{
	closesocket(s);
	WSACleanup();
}