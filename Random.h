
#include <cstdlib>
#include <ctime>

using namespace std;

class Random {

public:

	Random() {
		srand(std::time(0));
	}

	Random(int seed) {
		srand(seed);
	}

	int next_int(int n) {
		return int(next_double() * n);
	}

	double next_double() {
		double num = double(std::rand()) / RAND_MAX;
		return num;
	}

	int Current_Floor_Generator(int num_floors) {
		int current_floor;
		current_floor = int(std::rand()) % num_floors;

		return current_floor;
	}

	int Desired_Floor_Generator(int num_floors, int current_floor) {
		int desired_floor;
		bool equal = true;
		while (equal) {
			desired_floor = rand() % num_floors;
			if (desired_floor != current_floor) {
				equal = false;
			}
		}
		return desired_floor;
	}
};
