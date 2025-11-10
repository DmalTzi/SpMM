#include <cstdint>
#include <string>
typedef struct {
	uint32_t row;
	uint32_t col;
	uint32_t value;
} row_col_value;


void reader_buffer(std::string filename, uint32_t **A, uint16_t **IA, uint16_t **JA, uint32_t *A_size, uint32_t *IA_size, uint32_t *JA_size);
bool compare_rcv(const row_col_value &p1, const row_col_value &p2);