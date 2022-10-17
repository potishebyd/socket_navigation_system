#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

#include "packing.h"


struct position
{
	float latitude;
	float longitude;
	float altitude;
};

typedef struct position position;

struct speedVector
{
	float speedVectorX;
	float  speedVectorY;
	float speedVectorZ;
};

typedef struct speedVector speedVector;

struct angularPosition
{
	float roll;
	float pitch;
	float yaw;
};

typedef struct angularPosition angularPosition;

struct data
{
	position pos;
	speedVector spedV;
	angularPosition angPos;
};

typedef struct data data;


union buffer racData(SOCKET Connection) {
	union buffer buff_Tx;

	recv(Connection, (char *)&buff_Tx.byte0, sizeof(uint8_t), NULL);
	recv(Connection, (char *)&buff_Tx.byte1, sizeof(uint8_t), NULL);
	recv(Connection, (char *)&buff_Tx.byte2, sizeof(uint8_t), NULL);
	recv(Connection, (char *)&buff_Tx.byte3, sizeof(uint8_t), NULL);
	return buff_Tx;
}

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) {
		std::cout << "Error #2\n";
	}
	else {
		std::cout << "Client Connected!\n";
		data inf;

		union buffer buff_Tx;
		buff_Tx = racData(newConnection);
		inf.pos.latitude = unPackingData(buff_Tx);
		std::cout << "latitude: " <<inf.pos.latitude << std::endl;

		buff_Tx = racData(newConnection);
		inf.pos.longitude = unPackingData(buff_Tx);
		std::cout << "longitude:" << inf.pos.longitude << std::endl;

		buff_Tx = racData(newConnection);
		inf.pos.altitude = unPackingData(buff_Tx);
		std::cout << "altitude: " << inf.pos.altitude << std::endl;

		buff_Tx = racData(newConnection);
		inf.spedV.speedVectorX = unPackingData(buff_Tx);
		std::cout << "velocity vector by x: " << inf.spedV.speedVectorX << std::endl;

		buff_Tx = racData(newConnection);
		inf.spedV.speedVectorY = unPackingData(buff_Tx);
		std::cout << "velocity vector by y:" << inf.spedV.speedVectorY << std::endl;

		buff_Tx = racData(newConnection);
		inf.spedV.speedVectorZ = unPackingData(buff_Tx);
		std::cout << "velocity vector by z:" << inf.spedV.speedVectorZ << std::endl;

		buff_Tx = racData(newConnection);
		inf.angPos.pitch = unPackingData(buff_Tx);
		std::cout << "roll:" << inf.angPos.pitch << std::endl;

		buff_Tx = racData(newConnection);
		inf.angPos.roll = unPackingData(buff_Tx);
		std::cout << "pitch:" << inf.angPos.roll << std::endl;

		buff_Tx = racData(newConnection);
		inf.angPos.yaw = unPackingData(buff_Tx);
		std::cout << "yaw:" << inf.angPos.yaw << std::endl;

	}


	system("pause");
	return 0;
}