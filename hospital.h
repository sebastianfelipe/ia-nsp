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
		std::vector<std::vector<std::vector<int> > > population;
		std::vector<std::vector<int> > bestSchedule;

		// Restrictions: Nurse Parameters
		unsigned NURSE_MIN_DAYS, NURSE_MAX_DAYS;
		unsigned NURSE_MIN_CONSECUTIVE_DAYS, NURSE_MAX_CONSECUTIVE_DAYS;

		// Restrictions: Work Parameters
		std::vector<std::vector<int> > ALONG;

		// Algorithm Parameters
		unsigned POPULATION_SIZE;
		int *rouletteWheel;
		float PENALTY;
		std::vector<float> MUTATION_PROBABILITY;
		float CROSS_OVER_PROBABILITY;

	public:
		Hospital();

		//void init();
		void loadData(std::string filename);
		void genChromosome(unsigned chromosome);
		void setMutationProbability();
		void setCrossOverProbability();
		void genPopulation();
		void genRouletteWheel();

		void crossOver(unsigned chromosome1, unsigned chromosome2);
		void mutate(unsigned chromosome);

		void nextEvolutiveStep();

		float evaluate(unsigned chromosome);
		//void evaluate();
		//int **getX();
		std::vector<std::vector<std::vector<int> > > getPopulation();
		std::vector<std::vector<int> > getBestSchedule();
		void print();
};

#endif
