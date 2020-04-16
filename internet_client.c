#include "/usr/include/stdio.h"
#include "/usr/include/sys/types.h"
#include "/usr/include/sys/socket.h"
#include "/usr/include/unistd.h"
#include "/usr/include/stdlib.h"
#include "/usr/include/fcntl.h"
#include "/usr/include/string.h"
#include "/usr/include/sys/un.h"

void write_data (int socket_fd, char * message)
{
	int length;
	length = strlen (message) + 1;
	//write (socket_fd, &length, sizeof (length));
	write (socket_fd, message, length);
}

int local_client (char * a)
{
	int socket_fd;
	int flag = 1;
	struct sockaddr_un name;
	char * socket_name;
	socket_name = a;
		
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	name.sun_family = AF_LOCAL;
	
	strcpy (name.sun_path, socket_name);
	
		int result = 0;
		result = connect (socket_fd,(struct sockaddr *)&name, sizeof (name));
		if (result == -1)
		{
			perror ("connect");
			return -1;
		}
		//while (1)
		//{
		char message[100];

		printf ("Enter message.:\t");
		scanf ("%[^\n]", message);
		write_data (socket_fd, message);
		/*if ((message[0] == 'q' || message [0] == 'Q') && (message [1] == 'u' || message [1] == 'U') && (message [2] == 'i' || message [2] == 'I') && (message [3] == 't' || message [3] == 'T') && message [4] == '\0')
		{
			break;
		}*/
	//}
	close (socket_fd);
	return 0;	
}
