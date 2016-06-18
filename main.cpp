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