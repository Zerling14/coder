#include <inttypes.h>
#include "coder.h"
#include <stdio.h>
#include <math.h>
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
		code_unit->code[0] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[1] = (code_point & 0x1F) | 0xC0;
		code_unit->length = 2;
	} else if (num_bit <= 16) {
		code_unit->code[0] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[1] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[2] = (code_point & 0xF) | 0xE0;
		code_unit->length = 3;
	} else if (num_bit <= 21) {
		code_unit->code[0] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[1] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[2] = (code_point & 0x3F) | 0x80;
		code_point >>= 6;
		code_unit->code[3] = (code_point & 0x7) | 0xF0;
		code_unit->length = 4;
	} else {
		code_unit->length = 0;
		return -1;
	}
	
	print_code_unit (*code_unit);
	return 0;
}

uint32_t decode(const CodeUnit *code_unit)
{
	uint32_t tmp = 0;	
	for (int i = 0; i < code_unit->length; i++) {
		tmp = tmp + ((code_unit->code[i] & (((int)pow(2, i == code_unit->length - 1 ? code_unit->length == 1 ? 7 : 6 - i: 6)) - 1)) << (6 * i));
	}
	printf("decode: %" PRIx32 "\n", tmp);
	return tmp;
}

void print_code_unit(CodeUnit code_unit)
{
	printf("bin code:\n");
	int num_bait = code_unit.length;
	while (num_bait) {
		for (int j = 8; j > 0; j--) {
			printf("%d", (code_unit.code[num_bait - 1] >> (j - 1)) & 1);
		}
		num_bait--;
		printf(" ");
	}
	printf("\nlength: %d\n", code_unit.length);
}

int read_next_code_unit(FILE *in, CodeUnit *code_unit)
{
	code_unit->length = 0;
	uint8_t buffer = 0;
	while (buffer != 0xFF) {
		fread(&buffer, 1, 1, in);
		if (buffer == 0xFF) {
			rewind(in);     
			return -1;
		}
		uint8_t num_bait = 0;
		while (buffer & (1 << (7 - num_bait))) {
			num_bait++;
		}
		
		printf("bite: %" PRIx8 "\n", num_bait);
		if (num_bait == 1) {
			continue;
		}
		if (num_bait == 0) {
			num_bait = 1;
		}
		if (num_bait <= MaxCodeLength)
		{
			code_unit->length = 0;
			for (int i = 1; i <= num_bait; i++) {
				code_unit->code[num_bait - i] = buffer;
				code_unit->length++;
				if (i != num_bait) {
					fread(&buffer, 1, 1, in);
					if (buffer == 0xFF) {
						rewind(in); 
						return -1;
					}
					while ((buffer & 0xC0) != 0x80) {
						fread(&buffer, 1, 1, in);
					}
				}
			}
			break;
		}
	}
	printf("next_code_unit:\n");
	print_code_unit (*code_unit);
	return 0;
}

int read_next_code_unit_new(FILE *in, CodeUnit *code_unit)
{
	code_unit->length = 0;
	uint8_t buffer = 0;
	while (buffer != 0xFF) {
		fread(&buffer, 1, 1, in);
		if (buffer == 0xFF) {
			rewind(in);     
			return -1;
		}
		uint8_t num_bait = 0;
		while (buffer & (1 << (7 - num_bait))) {
			num_bait++;
		}
		
		printf("bite: %" PRIx8 "\n", num_bait);
		if (num_bait == 1) {
			continue;
		}
		if (num_bait == 0) {
			num_bait = 1;
		}
		if (num_bait <= MaxCodeLength)
		{
			code_unit->length = 0;
			for (int i = 1; i <= num_bait; i++) {
				code_unit->code[num_bait - i] = buffer;
				code_unit->length++;
				if (i != num_bait) {
					fread(&buffer, 1, 1, in);
					if (buffer == 0xFF) {
						rewind(in); 
						return -1;
					}
					while ((buffer & 0xC0) != 0x80) {
						fread(&buffer, 1, 1, in);
					}
				}
			}
			break;
		}
	}
	printf("next_code_unit:\n");
	print_code_unit (*code_unit);
	return 0;
}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
	
	return 0;
}