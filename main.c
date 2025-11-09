#include "reader.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("%s <matrix market format file>\n", argv[0]);
		exit(1);
	}

	uint16_t	*IA, *JA;
	uint32_t	*A;

	reader_buffer(argv[1], &A, &IA, &JA);
	free(A);
	free(IA);
	free(JA);
}
