#ifndef HOSPITAL_H
#define HOSPITAL_H

// Headers

#include "vector"
#include "string"

// Class

class Hospital
{
	private:
		int N, D, S;
		std::vector<std::vector<int> > coverage;
		std::vector<std::vector<std::vector<int> > > preferences;
		std::vector<std::vector<int> > schedule;
		
		// Algorithm Parameters
		int populationSize;
		int *rouletteWheel;

	public:
		Hospital();

		void init();
		void loadData(std::string filename);
		void setInitialGuess();
		void genNewPopulation();
		void genPopulation(); // Possible the same as setInitialGuess
		void genRouletteWheel();

		void applyCrossOver();
		void applyMutation();
		void applyMovement();

		void nextEvolutiveStep();

		float evaluate();
		//void evaluate();
		//int **getX();
		std::vector<std::vector<int> > getSchedule();
		void print();
};

#endif
