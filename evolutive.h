#ifndef evolutive_h
#define evolutive_h

// Headers
#include "vector"

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

// Definitions
#ifdef evolutive_cxx