#include <inttypes.h>
#include "coder.h"
#include <stdio.h>

int encode(uint32_t code_point, CodeUnit *code_unit)
{
	int num_bit = 0;
	for (uint32_t i = code_point; i > 0; i >>= 1) {
		num_bit++;
	}
	
	if (num_bit <= 7) {
		code_unit->code[0] = code_point & 0x7F;
		code_unit->length = 1;
	} else if (num_bit <= 11) {
		code_unit->code[0] = code_point & 0x3F | 0x80;
		code_unit->code[1] = code_point & 0x1F | 0xC0;
		code_unit->length = 2;
	}
	print_code_unit (*code_unit);
	return 0;
}

void print_code_unit(CodeUnit code_unit)
{
	printf("bin code:\n");
	for (uint8_t i = code_unit.length; i > 0; i--) {
	uint8_t n = code_unit.code[i];
		while (n) {
    		if (n & 1) {
        		printf("1");
    		} else {
       			printf("0");
    		}
    		n >>= 1;
		}
		printf("\nlength: %d\n", code_unit.length);
	}
}
