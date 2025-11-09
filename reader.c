#include "reader.h"

void reader_buffer(char *filename, uint32_t **A, uint16_t **IA, uint16_t **JA) {
	FILE	*file;
	char	buffer[255];
	uint16_t	row_size, col_size, non_zero;

	file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file\n");
		exit(1);
	}
	// skip title
	do {
		fgets(buffer, sizeof(buffer), file);
	}while (buffer[0] == '%');

	sscanf(buffer, "%hu %hu %hu", &row_size, &col_size, &non_zero);

	row_col_value *rc_v = malloc(sizeof(row_col_value)*non_zero);
	if (rc_v == NULL) {
		perror ("malloc error\n");
		exit(1);
	}

	//read value
	uint16_t	row, col;
	uint32_t	value;

	for (int i = 0; i < non_zero; i++) {
		fgets(buffer, sizeof(buffer), file);
		sscanf(buffer, "%hu %hu %u", &row, &col, &value);
		if (row > row_size || col > col_size) {
			perror("Invalid row or col\n");
			free(rc_v);
			exit(1);
		}
		rc_v[i].row = row;
		rc_v[i].col = col;
		rc_v[i].value = value;
	}

#ifdef DEBUG
	printf("row: %hu col: %hu non: %hu\n", row_size, col_size, non_zero);
	printf("before sort\n");
	for (int i = 0; i < non_zero; i++) {
		printf("%hu ", rc_v[i].row);
		printf("%hu ", rc_v[i].col);
		printf("%u\n", rc_v[i].value);
	}
#endif
	qsort(rc_v, non_zero, sizeof(row_col_value), compare_rcv);
#ifdef DEBUG
	printf("=====\n");
	printf("after sort\n");

	for (int i = 0; i < non_zero; i++) {
		printf("%hu ", rc_v[i].row);
		printf("%hu ", rc_v[i].col);
		printf("%u\n", rc_v[i].value);
	}
#endif

	*IA = malloc(sizeof(uint16_t)*row_size+1);
	*JA = malloc(sizeof(uint16_t)*non_zero);
	*A = malloc(sizeof(uint32_t)*non_zero);

	for (int i = 0; i < non_zero; i++) {
		(*IA)[rc_v[i].row]++;
		(*JA)[i] = rc_v[i].col-1;
		(*A)[i] = rc_v[i].value;
	}
	for (int i = 0; i < row_size; i++) {
		(*IA)[i+1] += (*IA)[i];
	}
#ifdef DEBUG
	printf("IA: ");
	for (int i = 0; i <= row_size; i++) {
		printf("%i ", (*IA)[i]);
	}
	printf("\nJA: ");
	for (int i = 0; i < non_zero; i++) {
		printf("%i ", (*JA)[i]);
	}
	printf("\nA: ");
	for (int i = 0; i < non_zero; i++) {
		printf("%i ", (*A)[i]);
	}
	printf("\n");
#endif
	free(rc_v);
}

int compare_rcv(const void *p1, const void *p2) {
	short row_com = (((row_col_value *)p1)->row - ((row_col_value *)p2)->row);
	if (row_com != 0) return row_com;
	short col_com = (((row_col_value *)p1)->col - ((row_col_value *)p2)->col);
	return col_com;
}
