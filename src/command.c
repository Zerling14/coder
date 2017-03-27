#include <inttypes.h>
#include "command.h"
#include "coder.h"
#include <stdio.h>
int decode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r"); 
	if (in == NULL) {
		return -1;
	}
	CodeUnit code_unit;
	FILE *out = fopen(out_file_name, "w+");
	if (out == NULL) {
		return -1;
	}
	while (!read_next_code_unit(in, &code_unit)) {
		uint32_t buffer = decode(&code_unit);
		fprintf(out, "%X" PRIx32 "\n", buffer);
	}
	fclose(in);
	fclose(out);
	return 0;
}

int encode_file(const char *in_file_name, const char *out_file_name)
{
	return 0;
}


