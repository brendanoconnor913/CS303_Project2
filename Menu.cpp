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
	char choice;

	while(true){
		cout << "Make your Elevator: \n 1. Set Number of Floors \n"
		<< "2. Set Simulation Time (clock cycles) \n 3. Set Passengers Arrival Rate \n"
		<< " 4. Run Simulation \n 5. Exit \n";
		cout << "Make your selection: ";
		cin >> choice;
		
		switch (choice) {
			case '1': {	
				cin >> floors;
				break; 
				}
			case '2': {
				cin >> totalTime;
				break;
				}
			case '3': {
				cin >> arrivalRate;
				break;
			}
			case '4': {
				Simulation sim(floors, totalTime, arrivalRate, showAllActions);
				sim.run_simulation();
				sim.show_stats();
				break;
			}
			case '5': {
				return false;
			}
			default: {
				cout << "Invalid input" << endl;
				break;
			}

		}
	}


	cin.get();
	return 0;
}
