#include "packing.h"


union buffer packingData(float float_n) {
	union buffer buff_Tx;
	buff_Tx.f = float_n;

	return buff_Tx;
}

float unPackingData(union buffer buff_Tx) {
	union buffer buff_Rx;
	buff_Rx.byte0 = buff_Tx.byte0;
	buff_Rx.byte1 = buff_Tx.byte1;
	buff_Rx.byte2 = buff_Tx.byte2;
	buff_Rx.byte3 = buff_Tx.byte3;

	return buff_Tx.f;
}
