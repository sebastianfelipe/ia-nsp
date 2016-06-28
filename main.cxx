#define HOSPITAL_CXX
#include "hospital.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	// If you want to track the program each time it finds a better solution,
	// then set this constant called DEBUG as true, otherwise as false
	bool DEBUG = true;

	if (argc > 1)
	{
		std::string filename = (std::string) argv[1];
	    Hospital hospital;

	    if (hospital.loadData(filename))
	    {
	    	//unsigned MAX_RESTARTS = 100000;
			//unsigned MAX_POPULATION = 5000;
			unsigned SEED = 10;
			unsigned MAX_RESTARTS_DIFF = 20;
			unsigned MAX_POPULATION_DIFF = 5000;
			unsigned lastRestart;
			unsigned lastPopulation;

			hospital.setSeed(SEED);
		    hospital.setViolatedConstraints();
		    hospital.setBestSchedule();
		    hospital.setTime();
		    hospital.setDebug(DEBUG);

		    lastRestart = 0;
		    lastPopulation = 0;
		    //for (unsigned restart = 0; restart < MAX_RESTARTS; restart++)
		    clock_t initialTime = clock();

		    for (unsigned restart = 0; (restart - lastRestart) < MAX_RESTARTS_DIFF; restart++)
		    {
			    // Set parameters
			    hospital.setCrossOverProbability();
			    hospital.setMutationProbability();
			    hospital.genPopulation();
			    hospital.setPopulationFitness();
			    hospital.setRouletteWheel();

			    lastPopulation = 0;
			  	//for (unsigned population = 0; population < MAX_POPULATION; population++)
			  	for (unsigned population = 0; (population - lastPopulation) <  MAX_POPULATION_DIFF; population++)
			  	{
			    	hospital.run();
			    	if (hospital.hasTheBestChanged())
			    	{
			    		lastPopulation = population;
			    		lastRestart = restart;
			    		if (DEBUG)
			    		{
			    			hospital.print();
			    		}
			    		//std::cout << "lastRestart: " << lastRestart << " lastPopulation: " << lastPopulation << std::endl;
			    	}
			    }

			    hospital.reset();
			}

			if (!DEBUG)
			{
				hospital.print();
			}

			// Total time algorithm runing
			clock_t timeElapsed = clock() - initialTime;
			clock_t msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
			clock_t secondsElapsed = msElapsed/1000;
			clock_t hours = secondsElapsed/3600;
			clock_t minutes = secondsElapsed/60;
			clock_t seconds = secondsElapsed%60;
			clock_t ms = msElapsed%1000;

			std::cout << std::endl;
			std::cout << "The best solution was found at the restart: " << lastRestart << ", population: " << lastPopulation << std::endl; 
			std::cout << "Total Time Elapsed: " << hours << " hour(s), " << minutes << " minute(s), " << seconds << " second(s), " << ms << " millisecond(s)" << std::endl;
			std::cout << std::endl;
			return 0;
		}

		return 1;
	}

	return 1;
};


