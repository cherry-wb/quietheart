#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 9000

struct User
{
	int index;
	int fd;
	struct User *next;
};

struct User *user_head = NULL;

void add_user(int index, int fd)
{
	struct User *u = NULL;
	struct User *p = NULL;
	u = malloc(sizeof(struct User));

	p = user_head;
	u->index = index;
	u->fd = fd;
	u->next = NULL;
	if(!p)
	{
		user_head = u;
	}
	else
	{
		while(p->next)
		{
			p = p->next;
		}
		p->next = u;
	}
}

void del_user(struct User *u)
{
	struct User *p = user_head;
	struct User *q = user_head;

	if(p == u)
	{
		user_head = p->next;
		free(u);
		return;
	}

	while(p)
	{
		q = p->next;
		if(q == u)
		{
			p->next = q->next;
		}
		p = p->next;
	}
}

struct Cmdline
{
	// char *cmd;
	int user;
	char *msg;
};

void parseCmd(char *buf, struct Cmdline *c)
{
	char *p = buf;
	char *q = buf;
	char *str = NULL;
	char *ps = NULL;
	while(isblank(*p))
		p++;
	while(!isblank(*q))
		q++;
	str = malloc(q - p + 1);
	bzero(str, q - p + 1);
	ps = str;
	while(p != q)
	{
		*ps++ = *p++;
	}
	c->user = atoi(str);

	while(!isblank(*p))
		p++;
	p++;

	c->msg = malloc(strlen(p) + 1);
	bzero(c->msg, strlen(p) + 1);
	strcpy(c->msg, p);
}

int main()
{
	int listenfd, connfd;
	struct sockaddr_in serveraddr;
	char buf[BUFSIZ];
	int readn;
	int flag = 1;
	fd_set rset;
	int maxfd;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <0 )
	{
		fprintf(stderr, "socket error!\n");
		exit(1);
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(PORT);
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));

	if(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		fprintf(stderr, "bind error!\n");
		exit(1);
	}

	if(listen(listenfd, 5) < 0)
	{
		fprintf(stderr, "listen error!\n");
		exit(1);
	}

	while(1)
	{
		int user;
		struct User *p = NULL;
		int user_flag = 0;
		FD_ZERO(&rset);
		FD_SET(listenfd, &rset);
		p = user_head;
		maxfd = listenfd;
		while(p)
		{
			FD_SET(p->fd, &rset);
			if(p->fd > maxfd)
				maxfd = p->fd;
			p = p->next;
		}
		select(maxfd + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(listenfd,  &rset))
		{
			char login_msg[32] = {0,};
			struct User *pp = NULL;
			if((connfd = accept(listenfd, NULL, NULL)) < 0)
			{
				fprintf(stderr, "accept error!\n");
				exit(1);
			}
			srandom((unsigned int)time(NULL));
			user = (int)(random() % 65535);
			fprintf(stderr, "user %d login!\n", user);
			add_user(user, connfd);
			user_flag = 1;
			pp = user_head;
			while(pp)
			{
				char log_user[32] = {0,};
				if(pp->fd != connfd)
				{
					sprintf(log_user, "user %d online!\n", pp->index);
					write(connfd, log_user, sizeof(log_user));
				}
				pp = pp->next;
			}

			pp = user_head;
			sprintf(login_msg, "user %d login\n", user);
			while(pp)
			{
				if(pp->fd == connfd)
				{
					pp = pp->next;
					continue;
				}
				else
				{
					write(pp->fd, login_msg, strlen(login_msg));
					pp = pp->next;
				}
			}
		}

		p = user_head;
		while(p)
		{
			if((p->fd == connfd) && user_flag)
			{
				p = p->next;
				user_flag = 0;
				continue;
			}
			if(FD_ISSET(p->fd, &rset))
			{
				int n;
				n = read(p->fd, buf, sizeof(buf));
				if(n == 0)
				{
					struct User *pp = user_head;
					bzero(buf, sizeof(buf));
					sprintf(buf, "user %d say goodbye!\n", p->index);
					p->fd = -1;

					while(pp)
					{
						if(pp->fd != p->fd)
						{
							write(pp->fd, buf, sizeof(buf));
						}
						pp = pp->next;
					}
				}
				else
				{
					struct Cmdline *c = malloc(sizeof(struct Cmdline));
					struct User *pp = user_head;
					parseCmd(buf, c);
					printf("user: %d\n", c->user);
					printf("msg: %s\n", c->msg);
					bzero(buf, sizeof(buf));
					sprintf(buf, "msg from %d: %s", p->index, c->msg);
					while(pp)
					{
						if(pp->index == c->user)
						{
							write(pp->fd, buf, sizeof(buf));
							break;
						}
						pp = pp->next;
					}
				}
			}
			p = p->next;
		}
		p = user_head;
		while(p)
		{
			if(p->fd == -1)
			{
				del_user(p);
			}
			p = p->next;
		}
	}

	return 0;
}
