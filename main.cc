#include <iostream>
#include "reader.h"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("%s <matrix market format file>\n", argv[0]);
		exit(1);
	}

	uint32_t A_size, IA_size, JA_size;
	uint32_t *A;
	uint16_t *IA, *JA;

	reader_buffer(argv[1], &A, &IA, &JA, &A_size, &IA_size, &JA_size);
	
	delete[] A;
    delete[] IA;
    delete[] JA;	
	return 0;
}
