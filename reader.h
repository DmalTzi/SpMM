#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint16_t row;
	uint16_t col;
	uint32_t value;
} row_col_value;

int compare_rcv(const void *p1, const void *p2);

void reader_buffer(char *filename, uint32_t **A, uint16_t **IA, uint16_t **JA);
