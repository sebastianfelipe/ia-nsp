#ifndef hospital_h
#define hospital_h

// Headers
#include "vector"

//Code
class Hospital
{
	private:
		int N, D, S;
		int **coverage;
		int ***preferences;
		int **x;
		
		// Algorithm Parameters
		int populationSize;
		int *rouletteWheel;

	public:
		Hospital();

		void loadData(string filename);
		void setInitialGuess();
		void genNewPopulation();
		void genPopulation(); // Possible the same as setInitialGuess
		void genRouletteWheel();

		void applyCrossOver();
		void applyMutation();
		void applyMovement();

		void nextEvolutiveStep();

		float evaluate();
		int **getX();
		void print();
};
#endif

// Definitions
#ifdef hospital_cxx
