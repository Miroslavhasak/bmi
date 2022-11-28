#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
#include <unistd.h> 
#include <signal.h>
#include <time.h>

char *body_mass_index(char *buffer) {
    float vyska_cm, vaha, bmi, vyska_m, vyska_2;
    int a = 0, b = 0;
    char odpoved[100] = "Tvoje bmi je: ", cislo[50], ch_vyska[50], ch_hmotnost[50];  
    

    memset(ch_vyska, 0, sizeof(ch_vyska));
    while (buffer[a] != ' ')
    {
        ch_vyska[a] = buffer[a];
        a++;
    }

    a = a + 1;
    while (buffer[a] != '\0')
    {
        ch_hmotnost[b] = buffer[a];
        b++;
        a++;
    }
    vyska_cm = atof(ch_vyska);       //atof premiena zo stringu na double 
    vaha = atof(ch_hmotnost);       //premenim si z charu na float

    /*
    printf("\nvyska_cm je>%f",vyska_cm);
    printf("\nvaha je>%f",vaha);
    printf("\nch_vyska je>%s",ch_vyska);
    printf("\nch_hmotnost je>%s",ch_hmotnost);

    printf("Zadaj tvoju vysku v cm a vahu v kg dodrz poradie!!!: \n");
    */
    //premena vysky z cm na m
    vyska_m = vyska_cm / 100.00;
    //printf("\nupravena ultra gbiga vyska_m je>%f",vyska_m);

    //vyska na druhu
    vyska_2 = vyska_m * vyska_m;
    //printf("\nvyska_2 je>%f",vyska_2);
    //vypocet bmi
    bmi = (vaha)/(vyska_2);
    //printf("\nbmi je>%f",bmi);

    memset(buffer, 0, sizeof(buffer));
    memset(ch_hmotnost, 0, sizeof(ch_hmotnost));
    memset(ch_vyska, 0, sizeof(ch_vyska));

    sprintf(cislo, "%.2f", bmi);
    strcpy(buffer, odpoved);
    strcat(buffer, cislo);

    /*
    printf("\nodpoved vo funkcii je: %s", odpoved);
    printf("\ncislo vo funkcii je: %s", cislo);*/
    //printf("\nbuffer vo funkcii je: %s\n", buffer);
    
    return buffer;
}

int main() 
{  

    float bmi;
    char len;
    char buf[100];  
    int k; 
    /*
    struct sockaddr_in client1;
    struct sockaddr_in client2;
    struct sockaddr_in client3; 
    */
    
    /*****************************VYTVORENIE SOCKETU***************************/

    int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    char c = '\n';
    char *p_buf, *save_buffer, *send_msg;

    if (sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

    /****************************NASTAVENIE BIND SOCKETU****************************/

    struct sockaddr_in server; 

    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  
    server.sin_port = htons(6838); 

    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0)
    {
        printf("cannot bind socket!\n");
        close(sock_desc);  
        return 0;
    }

    /****************************SERVER SOCKET**************************/

    int listen_socket;

    listen_socket = listen(sock_desc, 20);

    if (listen_socket == 0)
    {
        printf("Waiting for clients\n");
    }

    else {
        printf("Cannot listen on socket!\n");
        close(sock_desc);  
        return 0;
    }

    socklen_t addr_size;
    
    /*********************************1 CLIENT*****************************/

    
    int client1 = accept(sock_desc, NULL, NULL);  
    if (client1 == -1)
    {
        printf("cannot accept client 1\n");
        close(sock_desc);  
        return 0;
    }

    /*********************************2 CLIENT*****************************/
    

    int client2 = accept(sock_desc, NULL, NULL);  
    if (client2 == -1)
    {
        printf("cannot accept client 2\n");
        close(client1);
        close(sock_desc);
        return 0;
    }

    /*********************************3 CLIENT*****************************/


    int client3 = accept(sock_desc, NULL, NULL);  
    if (client3 == -1)
    {
        printf("cannot accept client 3\n");
        close(client1); 
        close(client2);
        close(sock_desc);  
        return 0;
    }
    /*********************************4 CLIENT*****************************/


    int client4 = accept(sock_desc, NULL, NULL);  
    if (client4 == -1)
    {
        printf("cannot accept client 4\n");
        close(client1);
        close(client2); 
        close(client3); 
        close(sock_desc);  
        return 0;
    }

    /*
    sleep(1);
    
	int Second_sock_desc = socket(AF_INET, SOCK_STREAM, 0); 
    if (Second_sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

    */
    /******************************NASTAVENIE SOCKETU**************************/
    /*
    struct sockaddr_in Second_client;  
    memset(&Second_client, 0, sizeof(Second_client));  
    Second_client.sin_family = AF_INET;  
    Second_client.sin_addr.s_addr = inet_addr("127.0.0.1");  
    Second_client.sin_port = htons(16838);  
    */

    /********************************PRIPOJENIE SOCKETU************************/
    /*
    if (connect(Second_sock_desc, (struct sockaddr*)&Second_client, sizeof(Second_client)) != 0)
    {
        printf("cannot connect to server!\n");
        close(Second_sock_desc);
    }
    */

	printf("Clienti sa pripojil\n");

    pid_t pid1 = fork();
    pid_t pid2 = fork();
    
    /***********************************CLIENT 1********************************/
    
    if (pid1 == 0 && 0 == pid2)
    {

    while(1) 
    {    
        k = recv(client1, buf, 100, 0);

        if (recv == -1)
        {
            printf("\ncannot read from client!\n");
            break;
        }

        if (recv == 0)
        {
            printf("\nclient disconnected.\n");
            break;
        }

        if (k > 0)          //tu je vystup
            printf("Client: %*.*s", k, k, buf);
            save_buffer = body_mass_index(buf);
            //printf("\nmuhahah buffer je: %s ", save_buffer);

        if (strcmp(buf, "exit") == 0)         
            break;     
	
	printf("Server: ");
    //gets(buf);

        len = strlen(save_buffer);
        p_buf = save_buffer;

        while (len > 0)
        {
            k = send(client1, save_buffer, len, 0);  // posielanie dat    
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(client1, &c, 1, 0);      
        if (k == -1)
        {
            printf("cannot write to server!\n");
            break;
        }

        

        if (strcmp(buf, "exit") == 0)          
            break;  
        
    break;
    }
    }

    /**********************************CLIENT 2*********************************/

    if (pid1 > 0 && 0 < pid2)
    {

    while(1) 
    {    
        k = recv(client2, buf, 100, 0);
        
        if (recv == -1)
        {
            printf("\ncannot read from client!\n");
            break;
        }

        if (recv == 0)
        {
            printf("\nclient disconnected.\n");
            break;
        }

        if (k > 0)          //tu je vystup
            printf("Client: %*.*s", k, k, buf);
            save_buffer = body_mass_index(buf);
            //printf("\nmuhahah buffer je: %s ", save_buffer);

        if (strcmp(buf, "exit") == 0)         
            break;     
	
	printf("Server: ");
    //gets(buf);

        len = strlen(save_buffer);
        p_buf = save_buffer;

        while (len > 0)
        {
            k = send(client2, save_buffer, len, 0);  // posielanie dat    
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(client2, &c, 1, 0);      
        if (k == -1)
        {
            printf("cannot write to server!\n");
            break;
        }

        

        if (strcmp(buf, "exit") == 0)          
            break; 
    break;
    }
    }

    /*****************************CLIENT 3**************************************/
    
    if (pid1 == 0 && 0 < pid2)
    {

    while(1) 
    {    
        k = recv(client3, buf, 100, 0);
        
        if (recv == -1)
        {
            printf("\ncannot read from client!\n");
            break;
        }

        if (recv == 0)
        {
            printf("\nclient disconnected.\n");
            break;
        }

        if (k > 0)          //tu je vystup
            printf("Client: %*.*s", k, k, buf);
            save_buffer = body_mass_index(buf);
            //printf("\nmuhahah buffer je: %s ", save_buffer);

        if (strcmp(buf, "exit") == 0)         
            break;     
	
	printf("Server: ");
    //gets(buf);

        len = strlen(save_buffer);
        p_buf = save_buffer;

        while (len > 0)
        {
            k = send(client3, save_buffer, len, 0);  // posielanie dat    
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(client3, &c, 1, 0);      
        if (k == -1)
        {
            printf("cannot write to server!\n");
            break;
        }
        
        if (strcmp(buf, "exit") == 0)          
            break;  
    break;
    }
    }

    /**************************************CLIENT 4****************************/
    
    if (pid1 > 0 && 0 == pid2)
    {

   while(1) 
    {    
        k = recv(client4, buf, 100, 0);
        
        if (recv == -1)
        {
            printf("\ncannot read from client!\n");
            break;
        }

        if (recv == 0)
        {
            printf("\nclient disconnected.\n");
            break;
        }

        if (k > 0)          //tu je vystup
            printf("Client: %*.*s", k, k, buf);
            save_buffer = body_mass_index(buf);
            //printf("\nmuhahah buffer je: %s ", save_buffer);

        if (strcmp(buf, "exit") == 0)         
            break;     
	
	printf("Server: ");
    //gets(buf);

        len = strlen(save_buffer);
        p_buf = save_buffer;

        while (len > 0)
        {
            k = send(client4, save_buffer, len, 0);  // posielanie dat    
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(client4, &c, 1, 0);      
        if (k == -1)
        {
            printf("cannot write to server!\n");
            break;
        }


        if (strcmp(buf, "exit") == 0)          
            break;  
    break;
    }
    }

    close(client1);  
    close(client2);
    close(client3);
    close(client4);
    close(sock_desc);  
    //close(Second_sock_desc);  
    printf("server disconnected\n");
    return 0;  
}
