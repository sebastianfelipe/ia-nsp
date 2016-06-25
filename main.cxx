#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <iostream>
#include <ctime>

int main()
{
	//std::string s = "instances/25_7_4_1.nsp";
	std::string s = "instances/50_7_4_5649.nsp";

	unsigned MAX_RESTARTS = 100;
	unsigned MAX_POPULATION = 5000;

    Hospital hospital;
    hospital.loadData(s);
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
	    
	    timeElapsed = (clock() - initialTime);
	    
	    if (restart == 0)
	    {
	    	hospital.setBestSchedule();
	    	hospital.print(restart, 0, timeElapsed);
	    }
	    else if (hospital.updateBestSchedule())
	    {
    		hospital.print(restart, 0, timeElapsed);
	    }
	    
	  	for (unsigned population = 1; population < MAX_POPULATION; population++)
	  	{
	  		// If a better soluttion has been found, then print the information
	    	if (hospital.run())
	    	{
	    		timeElapsed = (clock() - initialTime);
	    		hospital.print(restart, population, timeElapsed);
	    	}
	    }
	    hospital.reset();
	}

	return 0;
};


