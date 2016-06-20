#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

int main()
{    
    Hospital hospital;

    //std::string s = "instances/25_7_4_1.nsp";
   	std::string s = "instances/25_7_4_2916.nsp";
    hospital.loadData(s);
    
    // Set parameters
    hospital.setCrossOverProbability();
    hospital.setMutationProbability();
    hospital.genPopulation();
    hospital.setPopulationFitness();
    hospital.setRouletteWheel();
    hospital.setBestSchedule();
    
    // One run by iteration
    hospital.run();

	return 0;
};


