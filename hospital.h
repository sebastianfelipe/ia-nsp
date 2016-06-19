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
		unsigned populationSize;
		int *rouletteWheel;
		float PENALTY;

	public:
		Hospital();

		//void init();
		void loadData(std::string filename);
		void genChromosome(unsigned chromosome);
		void genPopulation();
		void genRouletteWheel();

		void applyCrossOver();
		void applyMutation();
		void applyMovement();

		void nextEvolutiveStep();

		float evaluate();
		//void evaluate();
		//int **getX();
		std::vector<std::vector<std::vector<int> > > getPopulation();
		std::vector<std::vector<int> > getBestSchedule();
		void print();
};

#endif
