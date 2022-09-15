#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#pragma warning(disable: 4996)

class Timer
{
public:
	void delay()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

};

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
	float speedVectorY;
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

void readPos(SOCKET Connection, position &pos)
{
	Timer T;

	std::cout << "Enter the position.\n";
	std::cout << "Enter the latitude:\n";
	std::cin >> pos.latitude;
	T.delay();
	send(Connection, (char *)&pos.latitude, sizeof(float), NULL);

	std::cout << "Enter the longitude:\n";
	std::cin >> pos.longitude;
	T.delay();
	send(Connection, (char *)&pos.longitude, sizeof(float), NULL);

	std::cout << "Enter the altitude:\n";
	std::cin >> pos.altitude;
	T.delay();
	send(Connection, (char *)&pos.altitude, sizeof(float), NULL);

}

void readSpeed(SOCKET Connection, speedVector &spedV)
{
	Timer T;

	std::cout << "\nEnter the velocity vector.\n";
	std::cout << "Enter the velocity vector by x:\n";
	std::cin >> spedV.speedVectorX;
	T.delay();
	send(Connection, (char *)&spedV.speedVectorX, sizeof(float), NULL);

	std::cout << "Enter the velocity vector by y:\n";
	std::cin >> spedV.speedVectorY;
	T.delay();
	send(Connection, (char *)&spedV.speedVectorY, sizeof(float), NULL);

	std::cout << "Enter the velocity vector by z:\n";
	std::cin >> spedV.speedVectorZ;
	T.delay();
	send(Connection, (char *)&spedV.speedVectorZ, sizeof(float), NULL);

}

void readAngle(SOCKET Connection, angularPosition &angPos)
{
	Timer T;

	std::cout << "\nEnter the angular position.\n";
	std::cout << "Enter the roll:\n";
	std::cin >> angPos.roll;
	T.delay();
	send(Connection, (char *)&angPos.roll, sizeof(float), NULL);

	std::cout << "Enter the pitch:\n";
	std::cin >> angPos.pitch;
	T.delay();
	send(Connection, (char *)&angPos.pitch, sizeof(float), NULL);

	std::cout << "Enter the yaw:\n";
	std::cin >> angPos.yaw;
	T.delay();
	send(Connection, (char *)&angPos.yaw, sizeof(float), NULL);

}


void send_mes(SOCKET Connection, float mes)
{
	send(Connection, (char *)&mes, sizeof(float), NULL);
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

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n\n";

	data inf;
	
	readPos(Connection, inf.pos);
	readSpeed(Connection, inf.spedV);
	readAngle(Connection, inf.angPos);



	system("pause");
	return 0;
}