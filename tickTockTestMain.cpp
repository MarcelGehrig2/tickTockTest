#include <iostream>
#include "PeriodicCounter.hpp"

using namespace eeros;

int main(int argc, char **argv) {
    std::cout << "Tick Tock Test:" << std::endl;
	
	PeriodicCounter counter(0, 0);
	
	int iterations = 1e6;
	
	for (int i=0; i<iterations; i++) {
		counter.tick();
		counter.tock();
	}
	
	std::cout	<< "iterations:  " << iterations << std::endl;
	
	std::cout 	<< "run Mean:    " << counter.run.mean 
				<< "\trun Max:     " << counter.run.max
				<< std::endl;
	
	std::cout 	<< "Period Mean: " << counter.period.mean 
				<< "\tPeriod Max:  " << counter.period.max
				<< std::endl;
	
	
	
	
	
	
	
    return 0;
}
