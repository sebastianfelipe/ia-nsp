#ifndef HOSPITAL_H
#define HOSPITAL_H

// Headers

#include "vector"
#include "string"

// Class

class Hospital
{
	private:
		// Problem Parameters
		int N, D, S;
		std::vector<std::vector<int> > COVERAGE;
		std::vector<std::vector<std::vector<int> > > PREFERENCES;

		// Restrictions: Nurse Parameters
		unsigned NURSE_MIN_DAYS, NURSE_MAX_DAYS;
		unsigned NURSE_MIN_CONSECUTIVE_DAYS, NURSE_MAX_CONSECUTIVE_DAYS;

		// Restrictions: Work Parameters
		std::vector<std::vector<int> > ALONG;

		// Algorithm Parameters
		unsigned POPULATION_SIZE;
		float PENALTY;
		std::vector<float> MUTATION_PROBABILITY;
		float CROSS_OVER_PROBABILITY;


		// Problem variables
		std::vector<std::vector<std::vector<int> > > population;
		std::vector<float> populationFitness;
		float totalFitness;
		std::vector<float> rouletteWheel;

		std::vector<std::vector<int> > bestSchedule;
		float bestFitness;

	public:
		Hospital();

		//void init();
		void loadData(std::string filename);

		void setTime();
		void setMutationProbability();
		void setCrossOverProbability();
		void setPopulationFitness();
		void setRouletteWheel();
		void setBestSchedule();
		
		void updatePopulationFitness();
		void updateRouletteWheel();
		bool updateBestSchedule();

		void genChromosome(unsigned chromosome);
		void genPopulation();
		unsigned getRouletteWheelChromosome();

		void crossOver(unsigned chromosome1, unsigned chromosome2);
		void mutate(unsigned chromosome);

		float getFitness(unsigned chromosome);

		bool run();
		void print(unsigned restart, unsigned iteration);
		void reset();
};

#endif
