#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

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
		recv(newConnection, (char *)&inf.pos.latitude, sizeof(float), NULL);
		std::cout << "latitude: " <<inf.pos.latitude << std::endl;

		recv(newConnection, (char *)&inf.pos.longitude, sizeof(float), NULL);
		std::cout << "longitude:" << inf.pos.longitude << std::endl;

		recv(newConnection, (char *)&inf.pos.altitude, sizeof(float), NULL);
		std::cout << "altitude: " << inf.pos.altitude << std::endl;

		recv(newConnection, (char *)&inf.spedV.speedVectorX, sizeof(float), NULL);
		std::cout << "velocity vector by x: " << inf.spedV.speedVectorX << std::endl;

		recv(newConnection, (char *)&inf.spedV.speedVectorY, sizeof(float), NULL);
		std::cout << "velocity vector by y:" << inf.spedV.speedVectorY << std::endl;

		recv(newConnection, (char *)&inf.spedV.speedVectorZ, sizeof(float), NULL);
		std::cout << "velocity vector by z:" << inf.spedV.speedVectorZ << std::endl;

		recv(newConnection, (char *)&inf.angPos.pitch, sizeof(float), NULL);
		std::cout << "roll:" << inf.angPos.pitch << std::endl;

		recv(newConnection, (char *)&inf.angPos.roll, sizeof(float), NULL);
		std::cout << "pitch:" << inf.angPos.roll << std::endl;

		recv(newConnection, (char *)&inf.angPos.yaw, sizeof(float), NULL);
		std::cout << "yaw:" << inf.angPos.yaw << std::endl;


	}


	system("pause");
	return 0;
}