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

int main()
{
  
		int linstenfd = 0, connfd = 0;
		struct sockaddr_in serv_addr;

		char senfBuff[1025];
		time_t ticks;

		listenfd = ( AF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&serv_addr, '0', sizeof(serv_addr));
		memset(sendBuff, '0', sizeof(sendBuff));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(5000);

		bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		listen(listenfd, 10);

		while(1)
		{
			connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

			ticks = time(NULL);
			snprint(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
			write(connfd, sendBuff, strlen(sendBuff));

			close(connfd);
			sleep(1);
		}
  
}