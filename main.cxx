#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		std::string filename = (std::string) argv[1];

		unsigned MAX_RESTARTS = 20;
		unsigned MAX_POPULATION = 5000;

	    Hospital hospital;
	    hospital.loadData(filename);
	    clock_t initialTime = clock();
	    clock_t timeElapsed = 0;

	    for (unsigned restart = 0; restart < MAX_RESTARTS; restart++)
	    {
		    // Set parameters
		    hospital.setTime();
		    hospital.setCrossOverProbability();
		    hospital.setMutationProbability();
		    hospital.genPopulation();
		    hospital.setPopulationFitness();
		    hospital.setRouletteWheel();
		    hospital.setViolatedConstraints();
		    
		    if (restart == 0)
		    {
		    	hospital.setBestSchedule();
		    }
		    else if (hospital.updateBestSchedule())
		    {
		    }
		    
		  	for (unsigned population = 1; population < MAX_POPULATION; population++)
		  	{
		  		// If a better soluttion has been found, then print the information
		    	hospital.run();
		    }
		    hospital.reset();
		}

		timeElapsed = (clock() - initialTime);
		hospital.print(timeElapsed);

		return 0;
	}

	return 1;
};


