#include "/usr/include/stdio.h"
#include "/usr/include/stdlib.h"
#include "/usr/include/unistd.h"
#include "/usr/include/sys/socket.h"
#include "/usr/include/netdb.h"
#include "/usr/include/netinet/in.h"
#include "/usr/include/arpa/inet.h"
#include "/usr/include/sys/types.h"

int read_client (int socket_fd)
{
	char * text, ch;
	text = NULL;
	int i = 0, count = 1;
	
	while (count)
	{
		count = read (socket_fd, &ch, 1);
		text = realloc (text, i+1);
		if (text == NULL)
		{
			perror ("realloc");
			exit (EXIT_SUCCESS);
		}
		text [i] = ch;
		i++;
	}

	if (text[0] == 'q'&& text [1] == 'u' && text [2] == 'i' && text [3] == 't' && text [4] == '\0')
	{
		return 0;
	}
	printf ("%s", text);
	printf ("\n");
	return 1;
}

int internet_server (char * a)
{
	int socket_fd;
	socket_fd = socket (PF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		perror ("socket");
		return -1;
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons (9784);
	address.sin_addr.s_addr = inet_addr (a);
	int i;
	i = bind (socket_fd, (struct sockaddr *)&address, sizeof (address));
	if (i < 0)
	{
		perror ("bind");
		return -1;
	}
	listen (socket_fd, 5);
	int quit_message = 1;
	while (quit_message)
	{
		int client_socket_fd;
		struct sockaddr_in client_name;
		socklen_t client_len;

		client_socket_fd = accept (socket_fd, (struct sockaddr *) &client_name, &client_len);
		if (client_socket_fd == -1)
		{
			perror ("accept");
			return -1;
		}
		quit_message = read_client (client_socket_fd);
	}

	close (socket_fd);
	return 0;
}
