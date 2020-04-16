#include "/usr/include/stdio.h"
#include "/usr/include/sys/types.h"
#include "/usr/include/sys/socket.h"
#include "/usr/include/unistd.h"
#include "/usr/include/stdlib.h"
#include "/usr/include/fcntl.h"
#include "/usr/include/string.h"
#include "/usr/include/sys/un.h"
#include "/usr/include/signal.h"

int server_work (int client_socket_fd)
{
	char * text;
	text = NULL;
	char ch;
	
	int count = 1, i = 0;
	while (count) 
	{
		count = read (client_socket_fd, &ch, 1);
		text = realloc (text, i+1);
		text[i] = ch;
		i++;
	}
	text[i] = '\0';

	if (text[0] == 'q' && text[1] == 'u' && text[2] == 'i' && text[3] == 't' && text[4] == '\0')
	{
		free (text);
		return 0;
	}

	else 
	{
		printf  ("%s", text);
		printf ("\n");
		free (text);
		return 1;
	}
}

int local_server (char * a)
{
	int socket_fd;
	int quit_message = 1;
	char * socket_name = a;
	struct sockaddr_un server_address;
	server_address.sun_family = AF_LOCAL;
	strcpy (server_address.sun_path, socket_name);

	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	if (socket_fd < 0)
	{
		perror ("socket");
		return -1;
	}
	bind (socket_fd, (struct sockaddr *) &server_address, sizeof (server_address));

	listen (socket_fd, 5);
	
	
	
	while (quit_message)
	{
		int client_socket_fd;
		struct sockaddr_un client_name;
		socklen_t client_name_length;
		
		client_socket_fd = accept (socket_fd, (struct sockaddr *) &client_name, &client_name_length);
		if (client_socket_fd < 0)
		{
			perror ("accept");
			return -1;
		}
		quit_message = server_work (client_socket_fd);
		close (client_socket_fd);
	}
	close (socket_fd);
	unlink (socket_name);
	return 0;
}
