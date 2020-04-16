/* This file contains the basic code to move control between the server and the client programs */
/* some functions need definitions from the following header files */
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

/* two main funcions for client and the server are declared here */
extern int local_server (char *);
extern int local_client (char *);
extern int internet_client (char *);
extern int internet_server (char *);

/* function for helping the user for options and the arguments */
void print_usage (FILE * stream, int exit_code)
{
        fprintf (stream, "Usage of mestra\n");
	fprintf (stream, "Syntax.:\n"
			 "mestra -option [client/server IP ADDRESS or local file name for socket.............]\n");
	fprintf (stream, "\nOptions.:\n");
        fprintf (stream, "\n\t\t-h     --help           	for help\n"
                         "\t\t-s     --server			for internet server program\n"
                         "\t\t-c     --client			for internet client program\n"
                         "\t\t-r	 --local_server 	for local server program\n"
                         "\t\t-t	 --local_client 	for local client program\n");
        exit (exit_code);
}


/* the main function for controlling the flow of the program for client and the server */
int main (int argc, char * argv[])
{
	fprintf (stdout, "\n\t\t\t\t\tMESTRA\t\n");
	fprintf (stdout, "\t\tCopyright (C) 2019 version.1.0 <deeprasad1996@gmail.com>\n\n");
	int i;
	char * short_options = "hs:c:r:t:"; /* defining the short options */
	struct option long_option [] = {{"help", 0, NULL, 'h'}, {"server", 1, NULL, 's'}, {"client", 1, NULL, 'c'}, {"local_client", 1, NULL, 't'}, {"local_server", 1, NULL, 'r'}}; /* defining the long options*/

	int next_option;
	i = 1;
	do 
	{
		/* using the getopt_long () function call for getting next option of the user */
		next_option = getopt_long (argc, argv, short_options, long_option, NULL);
		switch (next_option)
		{
			case 'h':

					print_usage (stdout, 0);
					break;
			case 's':
					/* transfer the flow control to the server program */
					i = internet_server (argv [optind - 1]);
					if (i == 0)
					{
						printf ("Internet Server Program has worked.\n");
					}
					else if (i == -1)
					{
						printf ("Oops !! Error occured in the internet server program.\n");
						exit (EXIT_FAILURE);
					}
					break;
			case 'c':
					/* transfer the flow control to the client program */
					i = internet_client (argv [optind - 1]);
					if (i == 0)
					{
						printf ("Internet Client Program has worked.\n");
					}
					else if (i == -1)
					{
						printf ("Oops !! Error occured in the internet client program.\n");
						exit (EXIT_FAILURE);
					}
					break;
			case 't':
					/* transfer the flow control to the client program */
					i = local_client (argv [optind - 1]);
					if (i == 0)
					{
						printf ("Local Client Program has worked.\n");
					}
					else if (i == -1)
					{
						printf ("Oops !! Error occured in the local client program.\n");
						exit (EXIT_FAILURE);
					}
					break;
			case 'r':
					/* transfer the flow control to the server program */
					i = local_server (argv [optind - 1]);
					if (i == 0)
					{
						printf ("Local server Program has worked.\n");
					}
					else if (i == -1)
					{
						printf ("Oops !! Error occured in the local server program.\n");
						exit (EXIT_FAILURE);
					}
					break;
			case '?':
					print_usage (stderr, -1);
					break;
			case -1:
					break;
			default :
					abort ();
		}
	}while (next_option != -1);
	return 0;
}
