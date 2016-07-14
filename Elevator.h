#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "list.h"
#include "Random.h"
#include "Passenger.h"
#include "Simulation.h"
#include "list_iterator.h"
#include "list_const_iterator.h"
class Elevator {
public:
	Elevator() {}

	Elevator(int floors, double arrival) : elevatorCalls(), numOnElev(0), direction(1), currentFloor(0), 
		passengersServed(0),totalWaitTime(0), arrivalRate(arrival), topFloor(floors) {}

	// moves elevator in the appropriate direction to execute task
	void nextFloor(bool show_all) {
		if (elevatorCalls.empty()) {
			return;
		}
		// determine if need to go up or down to execute current task
		list<Passenger>::iterator currentTask = elevatorCalls.begin();
		currentTask->incrementWait();
		if (currentTask->isOnElevator()) { // on elevator
			// at their destination
			if (currentFloor == currentTask->get_desired_floor()) {
				passengersServed++;
				totalWaitTime += currentTask->get_current_wait_time();
				numOnElev--;
				elevatorCalls.erase(currentTask);
				if (show_all) {
					cout << "A passenger reaches their destination and steps off the elevator" << endl;
				}
			}
			// in elevator going up to destination
			else if (currentFloor < currentTask->get_desired_floor()) {
				changeFloor(1, show_all);
			}
			// in elevator going down to destination
			else if (currentFloor > currentTask->get_desired_floor()) {
				changeFloor(0, show_all);
			}
		}
		else { // waiting to be picked up
			// being let on to elevator
			if (currentFloor == currentTask->get_start_floor()) {
				letPassengerOn(currentTask, show_all);
				direction = currentTask->get_direction();
			}
			// waiting for elevator to come up to starting floor
			else if (currentFloor < currentTask->get_start_floor()) {
				changeFloor(1, show_all);
			}
			// waiting for elevator to come down to starting floor
			else if (currentFloor > currentTask->get_start_floor()) {
				changeFloor(0, show_all);
			}
		}
	}

	// checks to see if anyone needs to off and handles passenger accordingly
	// returns false if no one gets on or off
	bool floorStop(bool show_all) {
		bool stops = false;
		if (elevatorCalls.size() <= 1) {
			return stops;
		}

		list<Passenger>::iterator current = ++elevatorCalls.begin();
		for (current; current != elevatorCalls.end(); current++) {
			current->incrementWait(); // increase time passenger waiting to get to destination
			if (current->isOnElevator()) {
				// on elevator and at destination floor
				if (current->get_desired_floor() == currentFloor) {
					// remove from elevator
					passengersServed++;
					totalWaitTime += current->get_current_wait_time();
					current = elevatorCalls.erase(current);
					if (show_all) {
						cout << "A passenger reaches their destination and steps off the elevator" << endl;
					}
					if (current == elevatorCalls.end()) {
						break;
					}
					stops = true;
				}
			}
			// person hasn't gotten on elevator
			else {
				// if person on floor and heading same direction as elevator 
				// let the person onto elevator
				if (current->get_start_floor() == currentFloor
					&& (current->get_direction() == direction)) {
					letPassengerOn(current, show_all);
					stops = true;
				}
			}
		}
		return stops;
	}

	// determines if a passenger should be randomly spawned
	void checkArrivals(int clock, bool showAll) {
		if (myRandom.next_double() < arrivalRate) {
			int startFloor = myRandom.Current_Floor_Generator(topFloor);
			int destFloor = myRandom.Desired_Floor_Generator(topFloor, startFloor);
			Passenger newPass(clock, startFloor, destFloor);
			elevatorCalls.push_back(newPass);
			if (showAll) {
				cout << "Time is "
					<< clock << ": "
					<< " a passenger at " << newPass.get_start_floor()
					<< " wants to go to floor " << newPass.get_desired_floor()
					<< " the new wait list has "
					<< elevatorCalls.size() << " people."<< endl;
			}
		}
	}

	// used to increase/decrease current floor
	void changeFloor(bool up, bool show) {
		if (up) {
			currentFloor++;
		}
		else {
			currentFloor--;
		}
		direction = up;
		if (show) {
			cout << "The elevator is now on floor " << currentFloor << endl;
		}
	}

	// used when passenger needs to get on elevator
	void letPassengerOn(list<Passenger>::iterator itr, bool show) {
		itr->get_on_elevator();
		numOnElev++;
		if (show) {
			cout << "The elevator stops to pickup a passenger" << endl;
		}
	}

	int getTotalWait() {
		return totalWaitTime;
	}

	int getPassengersServed() {
		return passengersServed;
	}

	int getNumOnElev() {
		return numOnElev;
	}

	int getTotalWaiting() {
		return elevatorCalls.size();
	}

	bool passengersWaiting() {
		return elevatorCalls.size() > 0;
	}

private:
	list<Passenger> elevatorCalls;
	int numOnElev;
	bool direction;
	int currentFloor;
	int passengersServed;
	int totalWaitTime;
	int topFloor;
	double arrivalRate;
	Random myRandom;
};

#endif