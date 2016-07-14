#ifndef USER_H
#define USER_H
#include"elevator.h"

struct User{
public:
	friend class elevator;
	bool desiredDirection;
	bool inElevator;
	int boardingFloor;
	int desiredFloor;
	User(){};
	User(bool desiredDirection, bool inElevator, int boardingFloor, int desiredFloor){}

};

#endif