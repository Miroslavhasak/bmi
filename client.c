#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <signal.h>
#include <arpa/inet.h> 
#include <unistd.h> 
#include <semaphore.h>
#include <pthread.h>

/*******************************GLOBALNE PREMENNE***********************/


void *thread_function(void *arg)
{
    printf("Test\n\n");
}
/*
timer_t vytvorCasovac(int);
void spustiCasovac(timer_t, int);
*/


int main() 
{  
    char buf[100];
    char b1[100];
    char b2[100];
    char b3[100];
    char b4[100];
    char meno[] = "Som klient";
    int cislo_klienta;

    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];

    
    fgets(b1,100,stdin);
    fgets(b2,100,stdin);
    fgets(b3,100,stdin);
    fgets(b4,100,stdin);

    /*
    printf("%s\n",b1);
    printf("%s\n",b2);
    printf("%s\n",b3);
    printf("%s\n",b4);
    */

    
    
    /*
    gets(b1);
    gets(b2);
    gets(b3);
    gets(b4);
    
   b1[100] = "180 70";
   b2[100] = "180 60";
   b3[100] = "180 50";
   b4 = "180 40";
   */
   

    /*
    timer_t casovac;
    casovac=vytvorCasovac(SIGKILL); //sigkill je to co posiela
    spustiCasovac(casovac,10);  //10 je kolko casu
    */

    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pipe(fd4);

    write(fd1[1],b1,100);
    write(fd2[1],b2,100);
    write(fd3[1],b3,100);
    write(fd4[1],b4,100);

    pid_t pid1 = fork();
    pid_t pid2 = fork();

    
    /*if (pid1 == 0 && 0 == pid2)
    {
        printf("vitaj client1\n");
    }*/


    pthread_t t1, t2;

    /*****************************VYTVORENIE SEMAFORA***************************/

    
    sem_t bin_sem;
 
    #define WORK_SIZE 1024
    char work_area[WORK_SIZE];

    int res;
    pthread_t a_thread;
    void *thread_result;

    res = sem_init(&bin_sem, 0, 0); //posledne cislo je hodnota semafora
    if (res != 0) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, NULL, thread_function, NULL);	//meno thread null ma nezaujima meno funkcie null nezaujima
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }



    





    /*****************************VYTVORENIE SOCKETU****************************/
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

    /****************************NASTAVENIE SOCKETU****************************/
    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));  
    client.sin_family = AF_INET;  
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(6838);  

    /*****************************KLIENT 1*************************************/
    
    if (pid1 > 0 && 0 < pid2)
    {
        read(fd1[0],buf,100);
        cislo_klienta = 1;
        printf("\n%s %d\n",meno, cislo_klienta);
          
    }

    /******************************KLIENT 2************************************/

    if (pid1 == 0 && 0 < pid2)
    {
        read(fd2[0],buf,100);
        cislo_klienta = 2;
        printf("\n%s %d\n",meno, cislo_klienta);
        //client.sin_port = htons(6837); 
    }

    /*******************************KLIENT 3***********************************/
    
    if (pid1 > 0 && 0 == pid2)
    {
        read(fd3[0],buf,100);
        cislo_klienta = 3;
        printf("\n%s %d\n",meno, cislo_klienta);
        //client.sin_port = htons(6836);
    }

    /********************************KLIENT 4**********************************/

    if  (pid1 == 0 && 0 == pid2)
    {
        read(fd4[0],buf,100);
        cislo_klienta = 4;
        printf("\n%s %d\n",meno, cislo_klienta);
        //client.sin_port = htons(6835);
        //sleep(5);
    }

    /******************************PRIPOJENIE SOCKETU*************************/
    if (connect(sock_desc, (struct sockaddr*)&client, sizeof(client)) != 0)
    {
        printf("\n%s %d;",meno, cislo_klienta);
        printf("cannot connect to server!\n");
        close(sock_desc);
    }
    printf("connected\n\n");

    if (pid1 > 0 && 0 < pid2)
    {
        wait(NULL);
    }
    /*
    int Second_sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (Second_sock_desc == -1)
    {
        printf("\n%s %d;",meno, cislo_klienta);
        printf("cannot create socket!\n");
        return 0;
    }
    */

    /*******************************NASTAVENIE SOCKETU************************/

    /*
    struct sockaddr_in server;  
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  
    server.sin_port = htons(16838);  
    if (bind(Second_sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0)
    {
        printf("\n%s %d;",meno, cislo_klienta);
        printf("cannot bind socket!\n");
        close(Second_sock_desc);  
        return 0;
    }
    	
    if (listen(Second_sock_desc, 20) != 0)
    {
        printf("\n%s %d;",meno, cislo_klienta);
        printf("cannot listen on socket!\n");
        close(Second_sock_desc);  
        return 0;
    }

    struct sockaddr_in Second_client;  
    memset(&Second_client, 0, sizeof(Second_client));  
    socklen_t Second_len = sizeof(Second_client); 
    int temp_sock_desc = accept(Second_sock_desc, (struct sockaddr*)&Second_client, &Second_len);  
    if (temp_sock_desc == -1)
    {
        printf("\n%s %d;",meno, cislo_klienta);
        printf("cannot accept client!\n");
        close(Second_sock_desc);  
        return 0;
    }
    */

    
    char c = '\n';
    char *p_buf;
    int k, len;  

    while(1) 
    {      
        //printf("Client: ");
        //gets(buf);

        len = strlen(buf);
        p_buf = buf;
  
        while (len > 0)
        {
            k = send(sock_desc, p_buf, len, 0);  // posielanie dat    
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(sock_desc, &c, 1, 0);      
        if (k == -1)
        {
            printf("cannot write to server!\n");
            break;
        }

        if (strcmp(buf, "exit\n") == 0)          
            break;  

	    k = recv(sock_desc, buf, 100, 0);      
        if (k == -1)
        {
            printf("\ncannot read from client!\n");
            break;
        }

        if (k == 0)
        {
            printf("\nclient disconnected.\n");
            break;
        }

        if (k > 0)          //tu je vystup
            printf("Server: pre klienta %d %s", cislo_klienta, buf); 

        if (strcmp(buf, "exit\n") == 0)
            break;

    break;
    }


 

    close(sock_desc);  // zatvorenie socketu
    printf("client disconnected\n");

    sem_destroy(&bin_sem);		//zmaze semafor
    exit(EXIT_SUCCESS);

    return 0;  
}
/*
timer_t vytvorCasovac(int signal)
{
  struct sigevent kam;              //struktura na signal
  kam.sigev_notify=SIGEV_SIGNAL;    //
  kam.sigev_signo=signal;
  
  timer_t casovac;
  timer_create(CLOCK_REALTIME, &kam, &casovac);   //vytvori casovac ktori mu priradi aky signal spusta
  return(casovac); 
}

void spustiCasovac(timer_t casovac, int sekundy)
{
  struct itimerspec casik;
  casik.it_value.tv_sec=sekundy;  //po kolkych to ma zacat
  casik.it_value.tv_nsec=0;       
  casik.it_interval.tv_sec=0;
  casik.it_interval.tv_nsec=0;
  timer_settime(casovac,CLOCK_REALTIME,&casik,NULL);  //funkcia ktora mi nastavi cas
}
*/