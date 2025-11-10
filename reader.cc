#include "reader.h"

#include <cstdio>
#include <cstdint>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void reader_buffer(string filename, uint32_t **A, uint16_t **IA, uint16_t **JA, uint32_t *A_size, uint32_t *IA_size, uint32_t *JA_size) {
	ifstream	file(filename);
	
	string	line;
	uint16_t	row_size, col_size, non_zero;
	do {
		getline(file, line);
	}while (line[0] == '%');

	istringstream	iss(line);
	iss >> row_size >> col_size >> non_zero;
#ifdef DEBUG
	printf("row_size: %hu col_size: %hu non_zero: %hu\n", row_size, col_size, non_zero);
#endif
	row_col_value *rc_v = new row_col_value[non_zero];
	if (rc_v == nullptr) {
		delete[] rc_v;
		cerr << "cannot allocate rc_v\n";
		exit(2);
	}
	
	// read value
	uint16_t	row, col;
	uint32_t	value;
		for (int i = 0; i < non_zero; i++) {
		getline(file, line);
		istringstream	iss(line);
		iss >> row >> col >> value;
		if (row > row_size || col > col_size) {
			cerr << "Invalid row or col\n";
			delete[] rc_v;
			exit(2);
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
	sort(rc_v, rc_v+non_zero, compare_rcv);
#ifdef DEBUG
	printf("=====\n");
	printf("after sort\n");

	for (int i = 0; i < non_zero; i++) {
		printf("%hu ", rc_v[i].row);
		printf("%hu ", rc_v[i].col);
		printf("%u\n", rc_v[i].value);
	}
#endif

	*IA = new uint16_t[row_size+1];
	*JA = new uint16_t[non_zero];
	*A = new uint32_t[non_zero];
	*IA_size = row_size+1;
	*JA_size = non_zero;
	*A_size = non_zero;

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
	delete[] rc_v;
}

bool compare_rcv(const row_col_value &p1, const row_col_value &p2) {
	if (p1.row != p2.row)
		return p1.row < p2.row;
	return p1.col < p2.col;
}