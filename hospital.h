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
		int NURSE_MIN_DAYS, NURSE_MAX_DAYS;
		int NURSE_MIN_CONSECUTIVE_DAYS, NURSE_MAX_CONSECUTIVE_DAYS;

		// Restrictions: Shift Parameters
		std::vector<std::vector<int> > SHIFT_CONSTRAINTS;

		// Algorithm Parameters
		int POPULATION_SIZE;
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
		void updateViolatedConstraints(int chromosome);
		void updateBestSchedule(int chromosome);

		void genChromosome(int chromosome);
		void genPopulation();
		int getRouletteWheelChromosome();

		void crossOver(int chromosome1, int chromosome2);
		void mutate(int chromosome);

		float getFitness(int chromosome);

		void runCrossOverProcess();
		void runMutationProcess();
		void run();

		void print();

		void resetViolatedConstraints();
		void reset();
};

#endif
