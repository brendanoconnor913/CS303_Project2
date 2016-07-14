#include "Passenger.h"

Passenger::Passenger(unsigned int arrival_time, int start, int desired) {
	arrivalTime = arrival_time;
	waitTime = 0;
	onElevator = 0;
	id = id_num++;
	startingFloor = start;
	desiredFloor = desired;

	if (start < desired) {
		direction = 1;
	}
	else if (desired < start) {
		direction = 0;
	}
	else {
		throw exception("Must have different start and desire floors");
	}
}

int Passenger::id_num = 0;