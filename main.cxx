#define HOSPITAL_CXX
#include "hospital.h"

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
	    	unsigned MAX_RESTARTS = 100000;
			unsigned MAX_POPULATION = 5000;

		    hospital.setViolatedConstraints();
		    hospital.setBestSchedule();
		    hospital.setTime();
		    hospital.setDebug(DEBUG);

		    for (unsigned restart = 0; restart < MAX_RESTARTS; restart++)
		    {
			    // Set parameters
			    hospital.setCrossOverProbability();
			    hospital.setMutationProbability();
			    hospital.genPopulation();
			    hospital.setPopulationFitness();
			    hospital.setRouletteWheel();
			    
			  	for (unsigned population = 0; population < MAX_POPULATION; population++)
			  	{
			    	hospital.run();
			    }

			    hospital.reset();
			}
			hospital.print();

			return 0;
		}

		return 1;
	}

	return 1;
};


