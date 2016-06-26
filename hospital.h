#ifndef HOSPITAL_H
#define HOSPITAL_H

// Headers
#include "vector"
#include "string"
#include <ctime>

// Class

class Hospital
{
	private:
		// Time
		clock_t initialTime;
		
		// Problem Parameters
		int N, D, S;
		std::vector<std::vector<int> > COVERAGE;
		std::vector<std::vector<std::vector<int> > > PREFERENCES;

		// Restrictions: Nurse Parameters
		unsigned NURSE_MIN_DAYS, NURSE_MAX_DAYS;
		unsigned NURSE_MIN_CONSECUTIVE_DAYS, NURSE_MAX_CONSECUTIVE_DAYS;

		// Restrictions: Shift Parameters
		std::vector<std::vector<int> > SHIFT_CONSTRAINTS;

		// Algorithm Parameters
		unsigned POPULATION_SIZE;
		//float PENALTY;
		std::vector<int> PENALTY_WEIGHTS;
		std::vector<float> MUTATION_PROBABILITY;
		float CROSS_OVER_PROBABILITY;
		float GENERAL_MUTATION_PROBABILITY;
		float GENERAL_CROSS_OVER_PROBABILITY;


		// Problem variables
		std::vector<std::vector<std::vector<int> > > population;
		std::vector<float> populationFitness;
		float totalFitness;
		float fitness;
		std::vector<float> rouletteWheel;
		std::vector<int> violatedConstraints;

		// Best variables
		clock_t bestTime;
		std::vector<std::vector<int> > bestSchedule;
		std::vector<int> bestViolatedConstraints;
		float bestFitness;

		// Debug
		bool DEBUG;

	public:
		Hospital();

		//void init();
		bool loadData(std::string filename);

		void setTime();
		void setDebug(bool debug);
		void setMutationProbability();
		void setCrossOverProbability();
		void setPopulationFitness();
		void setRouletteWheel();
		void setViolatedConstraints();
		void setBestSchedule();
		
		void updateBestTime();
		void updatePopulationFitness();
		void updateRouletteWheel();
		void updateViolatedConstraints(unsigned chromosome);
		void updateBestSchedule(unsigned chromosome);

		void genChromosome(unsigned chromosome);
		void genPopulation();
		unsigned getRouletteWheelChromosome();

		void crossOver(unsigned chromosome1, unsigned chromosome2);
		void mutate(unsigned chromosome);

		float getFitness(unsigned chromosome);

		void runCrossOverProcess();
		void runMutationProcess();
		void run();

		void print();

		void resetViolatedConstraints();
		void reset();
};

#endif
