#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <dirent.h>


pthread_mutex_t mutex; // precisa ser global!

char* listDir(){
	char *retorno = calloc(2048,1);
	int offset = 0;

	DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            offset = offset + sprintf(retorno + offset, "%s ", dir->d_name);
        }
        closedir(d);
    }

    return retorno;
}
				
void *func_thread(void *arg) {

	pthread_mutex_lock(&mutex);
	//região crı́tica
	pthread_mutex_unlock(&mutex);
	return 0;
}

void *print(void *threadid)
{
   int *connfd = (int *)threadid;
   char sendBuff[1025];

   
   printf("Socket na thread %d\n", *connfd);


   int recebido = read(*connfd, sendBuff, 1025);
   printf ("Valor recebido foi: %s", sendBuff);
   
   char msg[100];
   sprintf(msg, "Recebi o valor %d bytes\n", recebido);

   system("ls meuarquivo.txt > saida.txt");

   char* ls = listDir();


   write(*connfd, ls, 2048);
   free(ls);
   printf("Thread terminado\n");
   close(*connfd); 	


   free(connfd);
   pthread_exit(NULL);
};


int main(int argc, char **argv)
{

		int listenfd = 0;
		int message = 0;
		struct sockaddr_in serv_addr;

		
		//time_t ticks;


		listenfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&serv_addr, '0', sizeof(serv_addr));
		

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(5001);

		bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		listen(listenfd, 10);
		

		while(1)
		{

			int *connfd = calloc(sizeof(int),1);
			
			pthread_t thread;


			*connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
			

				printf("Socket criado: %d\n", *connfd);

				pthread_mutex_init(&mutex, NULL);

				pthread_create(&thread, NULL, print, connfd);
			
            
//            snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
 //			write(connfd, sendBuff, strlen(sendBuff));

			//bzero(sendBuff, sizeof(sendBuff));


            
            

			//close(connfd);
			//pthread_join(thread, NULL);
			//pthread_mutex_destroy(&mutex);
			//sleep(1);
		}

}
