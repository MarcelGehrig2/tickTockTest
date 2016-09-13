#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>
#include <iostream>
#include "PeriodicCounter.hpp"

#define MY_PRIORITY (90) /* we use 49 as the PRREMPT_RT use 50
                            as the priority of kernel tasklets
                            and interrupt handler by default */

#define MAX_SAFE_STACK (8*1024) /* The maximum stack size which is
                                   guaranteed safe to access without
                                   faulting */

#define NSEC_PER_SEC    (1000000000) /* The number of nsecs per sec. */

void stack_prefault(void) {

        unsigned char dummy[MAX_SAFE_STACK];

        memset(dummy, 0, MAX_SAFE_STACK);
        return;
}

int main(int argc, char* argv[])
{
    std::cout << "Tick Tock Test:" << std::endl;
	std::cout << "Robot-Control built at:\t" << __DATE__ << "   " << __TIME__ << std::endl;
	struct timespec t;
	struct sched_param param;
	//         int interval = 50000; /* 50us*/
	int interval = 1000000; /* 1ms*/

	/* Declare ourself as a real time task */

	param.sched_priority = MY_PRIORITY;
	if(sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
			perror("sched_setscheduler failed");
			exit(-1);
	}

	/* Lock memory */

	if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
			perror("mlockall failed");
			exit(-2);
	}

	/* Pre-fault our stack */

	stack_prefault();

	clock_gettime(CLOCK_MONOTONIC ,&t);
	/* start after one second */
	t.tv_sec++;


	eeros::PeriodicCounter counter(0, 0);
	int iterations = 1e3;
	int i = iterations;

	while(i>0) {
			/* wait until next shot */
			clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

			/* do the stuff */
			counter.tick();
			counter.tock();
			i--;

			/* calculate next shot */
			t.tv_nsec += interval;

			while (t.tv_nsec >= NSEC_PER_SEC) {
					t.tv_nsec -= NSEC_PER_SEC;
					t.tv_sec++;
			}
	}

	std::cout	<< "iterations:  " << iterations << std::endl;

	std::cout 	<< "run Mean:    " << counter.run.mean 
			<< "\trun Max:     " << counter.run.max
			<< std::endl;

	std::cout 	<< "Period Mean: " << counter.period.mean 
			<< "\tPeriod Max:  " << counter.period.max
			<< std::endl;
}

