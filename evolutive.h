#ifndef EVOLUTIVE_H
#define EVOLUTIVE_H

// Headers

#include "vector"
#include "string"

// Class

class Evolutive
{
	private:
		float randomPeer;
		int populationSize;
		int restarts;
		int steps;
		int **bestX;

	public:
		Evolutive();
		void compareResults();
		void setParameters();
		void run();
};

#endif