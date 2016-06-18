#ifndef HOSPITAL_H
#define HOSPITAL_H

// Headers
#include "vector"
#include "string"

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

		void loadData();
		void setInitialGuess();
		void genNewPopulation();
		void genPopulation(); // Possible the same as setInitialGuess
		void genRouletteWheel();

		void applyCrossOver();
		void applyMutation();
		void applyMovement();

		void nextEvolutiveStep();

		//float evaluate();
		void evaluate();
		//int **getX();
		void getX();
		void print();
};
#endif

// Definitions
//#ifdef hospital_cxx
