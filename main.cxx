#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <iostream>

int main()
{    
    Hospital hospital;

    //std::string s = "instances/25_7_4_1.nsp";
   	std::string s = "instances/25_7_4_2916.nsp";
    hospital.loadData(s);
    
    // Set parameters
    hospital.setTime();
    hospital.setCrossOverProbability();
    hospital.setMutationProbability();
    hospital.genPopulation();
    hospital.setPopulationFitness();
    hospital.setRouletteWheel();
    hospital.setBestSchedule();
    hospital.print();
    
    // One run by iteration
    
    unsigned iter = 0;
    //while (iter < hospital.getMaxIter())
    while (true)
    {
    	if (hospital.run())
    	{
    		hospital.print();
    	}
    	iter++;
    }

	return 0;
};


