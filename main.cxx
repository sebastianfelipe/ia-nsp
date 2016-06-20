#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <iostream>

int main()
{
	//std::string s = "instances/25_7_4_1.nsp";
	std::string s = "instances/25_7_4_2916.nsp";

	unsigned MAX_RESTARTS = 100;
	unsigned MAX_POPULATION = 100000;

    Hospital hospital;
    hospital.loadData(s);
    
    for (unsigned restart = 0; restart < MAX_RESTARTS; restart++)
    {
	    // Set parameters
	    hospital.setTime();
	    hospital.setCrossOverProbability();
	    hospital.setMutationProbability();
	    hospital.genPopulation();
	    hospital.setPopulationFitness();
	    hospital.setRouletteWheel();

	    if (restart == 0)
	    {
	    	hospital.setBestSchedule();
	    	hospital.print(restart, 0);
	    }
	    else if (hospital.updateBestSchedule())
	    {
    		hospital.print(restart, 0);
	    }
	    
	  	for (unsigned population = 1; population < MAX_POPULATION; population++)
	  	{
	    	if (hospital.run())
	    	{
	    		hospital.print(restart, population);
	    	}
	    }
	    hospital.reset();
	}

	return 0;
};


