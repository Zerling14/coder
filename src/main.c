//#define CODER_DEBUG
#include <stdio.h>
#include <inttypes.h>
#include "command.h"
#include <stdlib.h>
#include <string.h>

void print_usage()
{
	printf("Usage:\n"
		"coder encode <in-file-name> <out-file-name>\n"
		"coder decode <in-file-name> <out-file-name>\n");
}
int main(int argc, char *argv[])
{
	if (argc != 4) {
		print_usage();
		return -1;
	}
	
	if(!strcmp(argv[1], "decode")) {
		if (decode_file(argv[2], argv[3])) {
			printf("Error decode file\n");
			return -1;
		} 
	} else if(!strcmp(argv[1], "encode")) {
		if (encode_file(argv[2], argv[3])) {
			printf("Error encode file\n");
			return -1;
		} 
	} else {
		print_usage();
	}
	return 0;
}
