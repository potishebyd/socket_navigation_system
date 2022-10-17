#include <iostream>

union buffer {
	float f;

	struct {
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
	};
};

union buffer packingData(float float_n);

float unPackingData(union buffer buff_Tx);

