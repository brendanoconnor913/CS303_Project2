#ifndef PASSENGER
#define PASSENGER

#include <iostream>
#include <set>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sstream>
#include <list>

using namespace std;

class Passenger {
public:
	Passenger(unsigned int arrival_time, int start, int desired);
	

	unsigned int get_desired_floor() {
		return desiredFloor;
	}

	unsigned int get_start_floor() {
		return startingFloor;
	}

	unsigned int get_id() {
		return id;
	}

	bool get_direction() {
		return direction;
	}

	void get_on_elevator() {
		onElevator = true;
	}

	unsigned int get_current_wait_time() {
		return waitTime;
	}

	unsigned int get_arrival_time() {
		return arrivalTime;
	}

	bool isOnElevator() {
		return onElevator;
	}

	void incrementWait() {
		waitTime++;
	}
	
private:
	unsigned int desiredFloor; // randomly generate
	unsigned int startingFloor; // randomly generate
	unsigned int id;
	static int id_num; // used for unique id's
	bool direction; // set via desired and starting floors at initalization
	bool onElevator;
	unsigned int waitTime; 
	unsigned int arrivalTime; 
};


#endif

