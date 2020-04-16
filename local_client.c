#include "/usr/include/stdio.h"
#include "/usr/include/string.h"
#include "/usr/include/stdlib.h"
#include "/usr/include/unistd.h"
#include "/usr/include/sys/socket.h"
#include "/usr/include/netinet/in.h"
#include "/usr/include/netdb.h"
#include "/usr/include/arpa/inet.h"

void write_message (int socket_fd, char * message)
{
	size_t len;
	len = strlen (message) + 1;
	write (socket_fd, message, len);
	
}

int internet_client (char * a)
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
	address.sin_addr.s_addr = inet_addr (a);
	address.sin_port = htons (9784);
	
	//while (1)
	//{
		int i = 0;
		i = connect (socket_fd, (struct sockaddr *)&address, sizeof (address));
		if (i == -1)
		{
			perror ("connect");
			return -1;
		}
		char message[100];
		printf ("Enter message.:\t");
		scanf ("%[^\n]", message);
		write_message (socket_fd, message);
		/*if ((message[0] == 'q' || message [0] == 'Q') && (message [1] == 'u' || message [1] == 'U') && (message [2] == 'i' || message [2] == 'I') && (message [3] == 't' || message [3] == 'T') && message [4] == '\0')
		{
			break;
		}
	}*/
	close (socket_fd);
	return 0;
}
