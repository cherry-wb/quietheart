#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 9000


int main(int argc, char *argv[])
{
	int sockfd;
	int readn;
	fd_set rset;
	struct sockaddr_in servaddr;
	char buf[BUFSIZ] = {0, };

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "socket error!\n");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		fprintf(stderr, "inet_pton error!\n");
		exit(1);
	}

	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		fprintf(stderr, "connect error!\n");
		exit(1);
	}

	// while(fgets(buf, sizeof(buf), stdin))
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(fileno(stdin), &rset);
		FD_SET(sockfd, &rset);

		select(sockfd + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(sockfd,  &rset))
		{
			int n;
			n = read(sockfd, buf, sizeof(buf));
			if(n == 0)
			{
				exit(0);
			}
			else
			{
				buf[n] = '\0';
				printf("%s", buf);
			}

		}

		if(FD_ISSET(fileno(stdin),  &rset))
		{
			fgets(buf, sizeof(buf), stdin);
			write(sockfd, buf, sizeof(buf));
		}
	}

	return 0;
}
