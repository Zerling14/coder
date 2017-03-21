#include <stdio.h>
#include <inttypes.h>
#include "coder.h"

int main(int argc, char *argv[])
{
	CodeUnit code_units;
	encode(74, &code_units);
	return 0;
}
