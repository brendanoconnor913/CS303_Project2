#include "Simulation.h"
#include "Elevator.h"
#include "Passenger.h"
#include <iostream>

using namespace std;


int main() {
	int floors = 30;
	int totalTime = 200;
	double arrivalRate = .1;
	bool showAllActions = true;

	Simulation sim(floors, totalTime, arrivalRate, showAllActions);
	sim.run_simulation();
	sim.show_stats();

	cin.get();
	return 0;
}