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

	void nextFloor(bool show_all) {
		if (elevatorCalls.empty()) {
			return;
		}
		// determine if need to go up or down to execute current task
		list<Passenger>::iterator currentTask = elevatorCalls.begin();
		currentTask->incrementWait();
		if (currentTask->isOnElevator()) {
			if (currentFloor == currentTask->get_desired_floor()) {
				passengersServed++;
				totalWaitTime += currentTask->get_current_wait_time();
				numOnElev--;
				elevatorCalls.erase(currentTask);
				if (show_all) {
					cout << "A passenger reaches their destination and steps off the elevator" << endl;
				}
			}
			else if (currentFloor < currentTask->get_desired_floor()) {
				currentFloor++;
				direction = 1;
				if (show_all) {
					cout << "The elevator is now on floor " << currentFloor << endl;
				}
			}
			else if (currentFloor > currentTask->get_desired_floor()) {
				currentFloor--;
				direction = 0;
				if (show_all) {
					cout << "The elevator is now on floor " << currentFloor << endl;
				}
			}
		}
		else { // waiting to be picked up
			if (currentFloor == currentTask->get_start_floor()) {
				currentTask->get_on_elevator();
				direction = currentTask->get_direction();
				numOnElev++;
				if (show_all) {
					cout << "The elevator stops to pickup a passenger" << endl;
				}
			}
			else if (currentFloor < currentTask->get_start_floor()) {
				currentFloor++;
				direction = 1;
				if (show_all) {
					cout << "The elevator is now on floor " << currentFloor << endl;
				}
			}
			else if (currentFloor > currentTask->get_start_floor()) {
				currentFloor--;
				direction = 0;
				if (show_all) {
					cout << "The elevator is now on floor " << currentFloor << endl;
				}
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
					// remove from list and add wait time to totalwait and increment passenger counter
					passengersServed++;
					totalWaitTime += current->get_current_wait_time();
					elevatorCalls.erase(current++);
					if (show_all) {
						cout << "A passenger reaches their destination and steps off the elevator" << endl;
					}
					stops = true;
					if (elevatorCalls.empty()) {
						break;
					}
				}
			}
			// person hasn't gotten on elevator
			else {
				// person on floor and heading same direction as elevator
				if (current->get_start_floor() == currentFloor
					&& (current->get_direction() == direction)) {
					current->get_on_elevator();
					numOnElev++;
					if (show_all) {
						cout << "The elevator stops to pickup a passenger" << endl;
					}
					stops = true;
				}
			}
		}

		return stops;
	}

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

//void floorOperations() {
//	if (greatestPriority.inElevator) {
//		if (currentFloor == greatestPriority.desiredFloor) {
//			elevatorCalls.remove(greatestPriority);
//		}
//	}
//	else {
//		if (currentFloor == greatestPriority.boardingFloor) {
//			Passenger* temp = new Passenger(bool desiredDirection, bool inElevator, int boardingFloor,greatestPriority.boardingFloor)
//		}
//	}
//}

//Passenger& checkPriority(list<Passenger> listA) {
//	typename list<Passenger>::iterator itr = listA.begin();
//	Passenger temp = *itr;
//	while (itr != listA.end()){
//		itr++;
//		temp = findGreater(temp, *itr);
//	}
//	greatestPriority = temp;
//}

//Passenger findGreater(Passenger lhs, Passenger rhs) {
//	//use variables to simplify comparisons
//	int floor;
//	int rhsFloor;
//	//determine floors to compare
//	if (lhs.inElevator) {
//		floor = lhs.desiredFloor;
//	}
//	else {
//		floor = lhs.boardingFloor;
//	}
//	if (rhs.inElevator) {
//		rhsFloor = rhs.desiredFloor;
//	}
//	else {
//		rhsFloor = rhs.boardingFloor;
//	}

//	if (lhs.desiredDirection == direction && rhs.desiredDirection == direction) {
//		if (abs(floor - currentFloor) < abs(rhsFloor - currentFloor))
//			return lhs;
//		else
//			return rhs;
//	}
//	else if (lhs.desiredDirection == direction)
//		return lhs;
//	else if (rhs.desiredDirection == direction)
//		return rhs;
//}

#endif // !ELEVATOR_H#pragma once
