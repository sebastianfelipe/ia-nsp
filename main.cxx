#define HOSPITAL_CXX
#include "hospital.h"

#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		std::string filename = (std::string) argv[1];

		unsigned MAX_RESTARTS = 2;
		unsigned MAX_POPULATION = 5000;

	    Hospital hospital;
	    hospital.loadData(filename);
	    clock_t initialTime = clock();
	    clock_t timeElapsed = 0;

	    hospital.setViolatedConstraints();
	    hospital.setBestSchedule();

	    for (unsigned restart = 0; restart < MAX_RESTARTS; restart++)
	    {
		    // Set parameters
		    hospital.setCrossOverProbability();
		    hospital.setMutationProbability();
		    hospital.genPopulation();
		    hospital.setPopulationFitness();
		    hospital.setRouletteWheel();
		    
		  	for (unsigned population = 1; population < MAX_POPULATION; population++)
		  	{
		    	hospital.run();
		    	//hospital.print((clock() - initialTime));
		    }

		    hospital.reset();
		}

		timeElapsed = (clock() - initialTime);
		hospital.print(timeElapsed);

		return 0;
	}

	return 1;
};


