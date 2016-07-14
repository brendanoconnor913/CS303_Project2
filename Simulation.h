#ifndef SIMULATION
#define SIMULATION
#include "Elevator.h"
#include <iostream>

using namespace std;

class Simulation {

public:
	typedef KW::list<Passenger> list;
	
	Simulation() : clock(0) {}

	Simulation(int floors, int time, double arrival, bool show) : total_time(time),
		show_all(show), clock(0) {
		Elevator tmp(floors, arrival);
		elevator = tmp;
	}

	void run_simulation();
	void moveElevator();
	void show_stats();

private:
	Elevator elevator;
	int total_time;
	bool show_all;
	int clock;

};

// runs simulation till time reaches total_time
void Simulation::run_simulation() {
	for (clock = 0; clock < total_time; clock++) {
		elevator.checkArrivals(clock, show_all);
		moveElevator();
	}
}

// if calls to be executed work on it, else output idle
void Simulation::moveElevator() {
	if (elevator.passengersWaiting()) {
		if (elevator.floorStop(show_all)) {
			clock++; // increment time again for stop time
		}
		elevator.nextFloor(show_all);
	}
	else if (show_all) {
		cout << "The time is " << clock
			<< ", the elevator is idle." << endl;
	}
}

// output stat info from elevator
void Simulation::show_stats() {
	cout << "\n The number of passengers served was "
		<< elevator.getPassengersServed() << endl;

	double average_waiting_time = double(elevator.getTotalWait())
		/ double(elevator.getPassengersServed());
	cout << " with an average waiting time of "
		<< average_waiting_time << endl;

	cout << "There are currently " << elevator.getNumOnElev()
		 << " passengers in the elevator" << endl;

	cout << "Passengers waiting to get to their destination: "
		<< elevator.getTotalWaiting() << endl;
}

#endif