#define HOSPITAL_CXX
#include "hospital.h"

#include <string>

int main(int argc, char* argv[])
{
	// If you want to track the program each time it finds a better solution,
	// then set this constant called DEBUG as true, otherwise as false
	bool DEBUG = false;

	if (argc > 1)
	{
		std::string filename = (std::string) argv[1];
	    Hospital hospital;

	    if (hospital.loadData(filename))
	    {
	    	int MAX_RESTARTS = 10;
			int MAX_POPULATION = 5000;

		    hospital.setViolatedConstraints();
		    hospital.setBestSchedule();
		    hospital.setTime();
		    hospital.setDebug(DEBUG);

		    for (int restart = 0; restart < MAX_RESTARTS; restart++)
		    {
			    // Set parameters
			    hospital.setCrossOverProbability();
			    hospital.setMutationProbability();
			    hospital.genPopulation();
			    hospital.setPopulationFitness();
			    hospital.setRouletteWheel();
			    
			  	for (int population = 0; population < MAX_POPULATION; population++)
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


