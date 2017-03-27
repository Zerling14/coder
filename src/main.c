#include <stdio.h>
#include <inttypes.h>
#include "command.h"
#include <stdlib.h>
int main(int argc, char *argv[])
{
	
	//CodeUnit code_units;
	//encode(atoi(argv[1]), &code_units);
	//decode(&code_units);
	
	if (decode_file("file1.txt", "file2.txt")) {
		printf("Error decode file\n");
		return -1;
	} 
	
	return 0;
}
