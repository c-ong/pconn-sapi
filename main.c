/*
pconnect test for PHP

This product includes PHP software, freely available from
<http://www.php.net/software/>

Author: Johannes Schlüter
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "pconnect-sapi.h"

void run_php(char *startup, char *shutdown, int iterations, char *filename)
{
	pconn_init_php();
	if (startup)
		pconn_do_request(startup);
	while (iterations--) {
		pconn_do_request(filename);
	}
	if (shutdown)
		pconn_do_request(shutdown);
	pconn_shutdown_php();
}

void usage(char *name)
{
	fprintf(stderr, "Usage: %s [-i iterations] [-a startup_script] [-z shutdown-script] script\n", name);
}

int main(int argc, char *argv[])
{
	int iterations = 2;
	int opt;
	char *startup_script = NULL, *shutdown_script = NULL;
 
	while ((opt = getopt(argc, argv, "hic:a:z:")) != -1) {
		switch (opt) {
		case 'i':
			pconn_phpinfo();
		case 'a':
			startup_script = optarg;
			break;
		case 'z':
			shutdown_script = optarg;
			break;
		case 'c':
			iterations = atoi(optarg);
			if (iterations > 1) {
				break;
			}
			/* fall through */
		default:
			usage(argv[0]);
			return 1;
		case 'h':		
			usage(argv[0]);
			return 0;
		}
	}

	if (optind >= argc) {
		usage(argv[0]);
		return 1;
	}

	run_php(startup_script, shutdown_script, iterations, argv[optind]);
	return 0;
}

