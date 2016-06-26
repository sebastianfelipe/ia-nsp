#define HOSPITAL_CXX
#include "hospital.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Definir función objetivo con penalizaciones
// Definir restricciones (queriers)
// Definir movimientos (cross-over y mutation)
// Armar la ruleta
// Generar algoritmo evolutivo
// Definir número de pasos y otras características incluyendo el control
// Definir el comportamiento del algoritmo incluyendo los restarts

Hospital::Hospital()
{
	// Set the srand (semilla)
	unsigned seed = 4;
	std::srand(seed);
	this->POPULATION_SIZE = 4;
	
	this->GENERAL_MUTATION_PROBABILITY = .5;
	this->GENERAL_CROSS_OVER_PROBABILITY = .5;

	int penaltyWeights[4] = {1000, 1000, 1000, 1000};
	this->PENALTY_WEIGHTS.assign(&penaltyWeights[0], &penaltyWeights[0]+4);
};

void Hospital::loadData(std::string filename)
{	
	std::string line;
	std::ifstream file (filename);

	if (file.is_open())
	{
		unsigned iLine = 1;
		std::vector<int>::const_iterator first, last;

		while ( std::getline (file,line) )
		{
			// Standard reading and conversion to vectors of ints
			std::stringstream ss(line);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<std::string> vss(begin, end);

			std::vector<int> vsi;
		    for (unsigned i=0; i < vss.size(); i++)
		    {
		     	vsi.push_back(atoi(vss.at(i).c_str()));
		    }

		    // Retrieving the N, D and S parameters
			if (iLine == 1)
			{
				this->N = vsi.at(0);
				this->D = vsi.at(1);
				this->S = vsi.at(2);
			}

			// Retrieving the coverage DxS matrix
			else if (iLine >= 3 and iLine <= (this->D + 2))
			{
				this->COVERAGE.push_back(vsi);
			}

			// Retrieving the preferences NxDxS matrix
			else if (iLine >= (this->D + 4) and iLine <= (this->N + this->D + 3))
			{
				std::vector<std::vector<int> > dV;
				
				for (unsigned d = 0; d < this->D; d++)
				{
					first = vsi.begin() + d*this->S;
					last = vsi.begin() + d*this->S + this->S + 1;
					std::vector<int> sV(first, last);

					dV.push_back(sV);
				}

				this->PREFERENCES.push_back(dV);
			}

			// These lines contains the same information, already retrieved
			else if (iLine == (this->N + this->D + 5))
			{
				// Do nothing
			}

			else if (iLine == (this->N + this->D + 7))
			{
				this->NURSE_MIN_DAYS = vsi.at(0);
				this->NURSE_MAX_DAYS = vsi.at(1);
			}

			else if (iLine == (this->N + this->D + 9))
			{
				this->NURSE_MIN_CONSECUTIVE_DAYS = vsi.at(0);
				this->NURSE_MAX_CONSECUTIVE_DAYS = vsi.at(1);
			}

			else if (iLine >= (this->N + this->D + 12) and iLine <= (this->N + this->D + this->S + 11))
			{
				this->SHIFT_CONSTRAINTS.push_back(vsi);
			}

		  	//std::cout << line << '\n';
		 	iLine++;
		}
		file.close();
	}

	else std::cout << "Unable to open the file"; 
};

void Hospital::setTime()
{

};

void Hospital::setMutationProbability()
{
	// The mutation probability has to be defined for every cromosome
	for (unsigned d = 0; d < this->D; d++)
	{
		float probability = std::rand()/ ((double) RAND_MAX);
		this->MUTATION_PROBABILITY.push_back(probability);
	}
};

void Hospital::setCrossOverProbability()
{
	float probability = std::rand() / ((double) RAND_MAX);
	this->CROSS_OVER_PROBABILITY = probability;
};

void Hospital::setPopulationFitness()
{
	this->totalFitness = 0;
	for (unsigned chromosome = 0; chromosome < this->population.size(); chromosome++)
	{
		unsigned fitness = this->getFitness(chromosome);
		this->populationFitness.push_back(fitness);
		this->totalFitness = this->totalFitness + fitness;
	}
};

void Hospital::setRouletteWheel()
{
	float cumulativeProbability = .0;
	for (unsigned chromosome = 0; chromosome < this->population.size(); chromosome++)
	{
		cumulativeProbability = cumulativeProbability + ((float) this->populationFitness.at(chromosome))/((float) this->totalFitness);
		this->rouletteWheel.push_back(cumulativeProbability);
	}
};

void Hospital::setViolatedConstraints()
{
	int violatedConstraints[4] = {0, 0, 0, 0};
	this->violatedConstraints.assign(&violatedConstraints[0], &violatedConstraints[0]+4);

};

void Hospital::setBestSchedule()
{
	float min = *(std::min_element(this->populationFitness.begin(), this->populationFitness.end()));

	for (unsigned chromosome = 0; chromosome < this->populationFitness.size(); chromosome++)
	{
		// If the min is found, then the best solution is saved
		if (this->populationFitness.at(chromosome) == min)
		{
			for (unsigned n = 0; n < this->N; n++)
			{
				std::vector<int> gens(this->D, 0);
				for (unsigned d = 0; d < this->D; d++)
				{
					gens.at(d) = this->population.at(chromosome).at(n).at(d);
				}
				this->bestSchedule.push_back(gens);
			}

			this->updateViolatedConstraints(chromosome);
			for (unsigned i = 0; i < this->violatedConstraints.size(); i++)
			{
				this->bestViolatedConstraints.push_back(this->violatedConstraints.at(i));
			}

			this->bestFitness = min;
			break;
		}
	}
};

void Hospital::updatePopulationFitness()
{
	this->totalFitness = 0;
	for (unsigned chromosome = 0; chromosome < this->population.size(); chromosome++)
	{
		unsigned fitness = this->getFitness(chromosome);
		this->populationFitness.at(chromosome) = fitness;
		this->totalFitness = this->totalFitness + fitness;
	}
};

void Hospital::updateRouletteWheel()
{
	float cumulativeProbability = .0;
	for (unsigned chromosome = 0; chromosome < this->population.size(); chromosome++)
	{
		cumulativeProbability = cumulativeProbability + ((float) this->populationFitness.at(chromosome))/((float) this->totalFitness);
		this->rouletteWheel.at(chromosome) = (cumulativeProbability);
	}
};

void Hospital::updateViolatedConstraints(unsigned chromosome)
{
	this->resetViolatedConstraints();
	// Verification of violated constraints
	for (int n = 0; n < this->N; n++)
	{
		// Temporal variables declaration
		int lastShiftWorked = -1;
		
		std::vector<std::vector<int > > shiftWorked(this->S);
		std::vector<int> daysWorked;

		for (int d = 0; d < this->D; d++)
		{
			int shift = this->population.at(chromosome).at(n).at(d);

			if (shift > -1)
			{
				// Reducing information for constraints of the type 1 and 2
				if (lastShiftWorked == -1)
				{
					daysWorked.push_back(1);
				}
				else
				{
					daysWorked.back()++;
				}

				// Reducing information for contraints of the type 3 and 4
				if (shift != lastShiftWorked)
				{
					shiftWorked.at(shift).push_back(1);
				}
				else
				{
					shiftWorked.at(shift).back()++;
				}
			}

			lastShiftWorked = shift;
		}

		// Verification
		// Type 1 and 2
		int sum = 0;
		for (int i = 0; i < daysWorked.size(); i++)
		{
			// Type 2
			// If the value of the consecutive days worked are not in the necessary range, then this restriction is violated
			if (!((daysWorked.at(i) >= this->NURSE_MIN_CONSECUTIVE_DAYS) && (daysWorked.at(i) <= this->NURSE_MAX_CONSECUTIVE_DAYS)))
			{
				// Adding a value to the representation of the violated constraint of type 2
				this->violatedConstraints.at(1)++;
			}

			sum = sum + daysWorked.at(i);
		}

		// Type 1
		// If the value of the days worked are not in the necessary range, then this restriction is violated
		if (!((sum >= this->NURSE_MIN_DAYS) && sum <= (this->NURSE_MAX_DAYS)))
		{
			// Adding a value to the representation of the violated constraint of type 1
			this->violatedConstraints.at(0)++;
		}

		// Type 3 and 4
		
		//std::cout << "shiftWorked.size(): " << shiftWorked.size() << std::endl;
		
		for (int s = 0; s < shiftWorked.size(); s++)
		{
			int sum = 0;
			
			//std::cout << "S: " << s << " size: " << shiftWorked.size() << std::endl;
			
			// Type 4
			for (int i = 0; i < shiftWorked.at(s).size(); i++)
			{
				
				//std::cout << "for i=" << i << " it contains: " << shiftWorked.at(s).at(i) << std::endl;
				
				if ( !( (shiftWorked.at(s).at(i) >= this->SHIFT_CONSTRAINTS.at(s).at(0)) && (shiftWorked.at(s).at(i) <= this->SHIFT_CONSTRAINTS.at(s).at(1)) ) )
				{
					
					//std::cout << "fucked" << std::endl;
					
					// Adding a value to the representation of the violated constraint of type 4
					this->violatedConstraints.at(3)++;
				}

				sum = sum + shiftWorked.at(s).at(i);
			}

			// Type 3
			if (!( (sum >= this->SHIFT_CONSTRAINTS.at(s).at(2)) && (sum <= this->SHIFT_CONSTRAINTS.at(s).at(3))))
			{
				// Adding a value to the representation of the violated constraint of type 3
				this->violatedConstraints.at(2)++;
			}
		}

	}
};

bool Hospital::updateBestSchedule()
{
	float min = *(std::min_element(this->populationFitness.begin(), this->populationFitness.end()));

	if (min < this->bestFitness)
	{
		for (unsigned chromosome = 0; chromosome < this->populationFitness.size(); chromosome++)
		{
			// If the min is found, then the best solution is saved
			if (this->populationFitness.at(chromosome) == min)
			{
				for (unsigned n = 0; n < this->N; n++)
				{
					for (unsigned d = 0; d < this->D; d++)
					{
						this->bestSchedule.at(n).at(d) = this->population.at(chromosome).at(n).at(d);
					}
				}

				this->updateViolatedConstraints(chromosome);
				for (unsigned i = 0; i < this->violatedConstraints.size(); i++)
				{
					this->bestViolatedConstraints.at(i) = this->violatedConstraints.at(i);
				}

				this->bestFitness = min;
				return true;
			}
		}
	}

	return false;
};

void Hospital::genChromosome(unsigned chromosome)
{
	// The idea behind this step, is generate a feasible chromosome
	// The steps are very simple. First, choose randomly a nurse in a day,
	// then, for that day, choose the shift that requires immediate allocation (from left to right -> S_0...S_s)
	// In other words, this algorithm is a Greedy algorithm to find a feasible solution first

	// Copy the coverage matrix and sum the require allocation
	unsigned necessaryNurses = 0;
	std::vector<std::vector<int> > coverage;
	for (unsigned d = 0; d < this->D; d++)
	{
		for (unsigned s = 0; s < this->S; s++)
		{
			necessaryNurses = necessaryNurses + this->COVERAGE.at(d).at(s);
		}
		coverage.push_back(this->COVERAGE.at(d));
	}

	std::vector<unsigned> shuffle;
	for (unsigned i = 0; i < (this->N*this->D); i++)
	{
		shuffle.push_back(i);
	}

	
	// Shuffle the vector
	std::random_shuffle(shuffle.begin(), shuffle.end());
	
	// Allocate nurses to shifts
	unsigned allocation = 0;
	unsigned nurse = 0;
	while (allocation < necessaryNurses)
	{
		// Decode the nurse and the day to schedule
		unsigned n = shuffle.at(nurse)/this->D;
		unsigned d = shuffle.at(nurse)%this->D;

		// Looking for the immediate shift that need to be allocated
		for (unsigned s = 0; s < this->S; s++)
		{
			// If exists a shift to assign, then assign it to the nurse n
			if (coverage.at(d).at(s) > 0)
			{
				// Nurse allocation by day in a shift
				this->population.at(chromosome).at(n).at(d) = s;
				coverage.at(d).at(s)--;

				// ------------------------------
				// This code is to print the changes in the coverage matrix
				// in order to understand how the nurses are taking the shifts
				// This section is to develope
				/*
				std::cout << "This is the allocation: " << allocation + 1 << std::endl;
				std::cout << "n: " << n << " d: " << d << " s: " << s << std::endl;
				for (unsigned i = 0; i < this->D; i++)
				{
					for (unsigned j= 0; j < this->S; j++)
					{
						std::cout << coverage.at(i).at(j) << "\t";
					}
					std::cout << std::endl;
				}
				*/
				// ------------------------------

				allocation++;
				break;
			}
			
		}
		nurse++;
	}
	//std::cout << allocation << std::endl;
};

void Hospital::genPopulation()
{
	// Crear lista de enfermeras (sólo posición)
	// Shuffle
	// Por cada valor de esta lista, asignar enfermera a turno
	//this->schedule;
	for (unsigned i = 0; i < this->POPULATION_SIZE; i++)
	{
		std::vector<std::vector<int> > p;
		this->population.push_back(p);
	}

	for (unsigned chromosome = 0; chromosome < this->POPULATION_SIZE; chromosome++)
	{
		for (unsigned n = 0; n < this->N; n++)
		{
			std::vector<int> v(this->D);

			for (unsigned d = 0; d < this->D; d++)
			{
				// -1 represent that the nurse haven't been scheduled yet
				v.at(d) = -1;//std::rand()%(this->S);
			}
			
			this->population.at(chromosome).push_back(v);
		}

		this->genChromosome(chromosome);
	}
};

void Hospital::crossOver(unsigned chromosome1, unsigned chromosome2)
{
	// The cut has to be between the day 1 and the day D-1
	// in other case is like to do nothing, and that decision
	// has to be taken to decide wheter this step has to be done or not

	unsigned cut = (std::rand()%(this->D - 2)) + 1;
	for (unsigned n = 0; n < this->N; n++)
	{
		for (unsigned d = cut; d < this->D; d++)
		{
			int s1 = this->population.at(chromosome1).at(n).at(d);
			int s2 = this->population.at(chromosome2).at(n).at(d);
			this->population.at(chromosome1).at(n).at(d) = s2;
			this->population.at(chromosome2).at(n).at(d) = s1;
		}
	}
};

void Hospital::mutate(unsigned chromosome)
{
	// For this algorithm, the mutation is made by shuffling the nurses allocated in a day
	for (unsigned d = 0; d < this->D; d++)
	{
		float probability = std::rand()/ ((double) RAND_MAX);

		// If the probability calculated is greater than the fixed by day, then mutate
		if (probability > this->MUTATION_PROBABILITY.at(d))
		{
			std::vector<int> values;
			for (unsigned n = 0; n < this->N; n++)
			{
				values.push_back(this->population.at(chromosome).at(n).at(d));
			}

			std::random_shuffle(values.begin(), values.end());
			
			for (unsigned n = 0; n < this->N; n++)
			{
				this->population.at(chromosome).at(n).at(d) = values.at(n);
			}
		}
	}
};

float Hospital::getFitness(unsigned chromosome)
{
	// Declaration of the objetive function values
	float unhappiness = 0;
	float penalties = 0;

	// Verification of violated constraints
	this->updateViolatedConstraints(chromosome);

	// Calculate the unhappiness
	for (unsigned n = 0; n < this->N; n++)
	{
		for (unsigned d = 0; d < this->D; d++)
		{
			// The shifts allocated are the ones that are different than -1
			// -1 represents that a shift haven't been allocated yet
			int s = this->population.at(chromosome).at(n).at(d);
			if (s > -1)
			{
				unhappiness = unhappiness + this->PREFERENCES.at(n).at(d).at(s);
			}
		}
	}

	// Calculate the penalties
	for (unsigned constraint = 0; constraint < violatedConstraints.size(); constraint++)
	{
		penalties = penalties + violatedConstraints.at(constraint)*this->PENALTY_WEIGHTS.at(constraint);
	}

	float result = unhappiness + penalties;
	return result;
};

unsigned Hospital::getRouletteWheelChromosome()
{
	float probability = std::rand()/ ((double) RAND_MAX);
	for (unsigned chromosome = 0; chromosome < this->rouletteWheel.size(); chromosome++)
	{
		if (probability <= this->rouletteWheel.at(chromosome))
		{
			return chromosome;
		}
	}

	return this->rouletteWheel.size() - 1;
};

void Hospital::runCrossOverProcess()
{
	// Cross-Over Process
	// This process is inspired in the cross-over process for Genetic Algorithms,
	// but this one is a little bit different. This process transform by mixing (cross-over),
	// two chromosomes, but, those new chromosomes can be used to generate new ones. That's the difference.
	// This program applies this process as many times as chromosomes the population could have.
	for (unsigned i = 0; i < this->population.size(); i++)
	{
		float probability = std::rand()/ ((double) RAND_MAX);

		if (probability >= this->GENERAL_CROSS_OVER_PROBABILITY)
		{
			unsigned chromosome1 = this->getRouletteWheelChromosome();
			unsigned chromosome2 = this->getRouletteWheelChromosome();
			
			while (chromosome1 == chromosome2)
			{
				chromosome1 = this->getRouletteWheelChromosome();
				chromosome2 = this->getRouletteWheelChromosome();
			}
			this->crossOver(chromosome1, chromosome2);
			
			// If there is a solution better than the best solution saved, then update it
			//this->updatePopulationFitness();
			//this->updateRouletteWheel();
			//this->updateBestSchedule();
		}
	}
};

void Hospital::runMutationProcess()
{
	// Mutation Process
	float probability = std::rand()/ ((double) RAND_MAX);
	if (probability >= this->GENERAL_MUTATION_PROBABILITY)
	{
		for (unsigned chromosome = 0; chromosome < this->population.size(); chromosome++)
		{
			this->mutate(chromosome);
		}
	}
};

void Hospital::run()
{
	// The population has to be change, this methods performs that
	// Cross-Over Process
	this->runCrossOverProcess();

	// Mutation Process
	this->runMutationProcess();

	// New population was generated and the population fitness and the roulette wheel has to be generated too
	this->updatePopulationFitness();
	this->updateRouletteWheel();

	// If there is a solution better than the best solution saved, then update it
	this->updateBestSchedule();
};

void Hospital::print(clock_t timeElapsed)
{
	clock_t secondsElapsed = timeElapsed/((double) CLOCKS_PER_SEC);
	clock_t hours = secondsElapsed/3600;
	clock_t minutes = secondsElapsed/60;
	clock_t seconds = secondsElapsed%60;

	std::cout << "--------------------" << std::endl;
	std::cout << "Best Solution Found!" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "Time: " << hours << " hour(s), " << minutes << " minute(s), " << seconds << " second(s)" << std::endl;
	std::cout << std::endl;
	std::cout << "Fitness: " << this->bestFitness;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Total Violated Constraints:" << std::endl;
	std::cout << "Type 1: " << this->bestViolatedConstraints.at(0) << std::endl;
	std::cout << "Type 2: " << this->bestViolatedConstraints.at(1) << std::endl;
	std::cout << "Type 3: " << this->bestViolatedConstraints.at(2) << std::endl;
	std::cout << "Type 4: " << this->bestViolatedConstraints.at(3) << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	for (unsigned n = 0; n < this->bestSchedule.size(); n++)
	{
		for (unsigned d = 0; d < this->bestSchedule.at(n).size(); d++)
		{
			std::cout << this->bestSchedule.at(n).at(d) + 1 << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "--------------------" << std::endl;
};

void Hospital::resetViolatedConstraints()
{
	this->violatedConstraints.clear();
	this->setViolatedConstraints();
};

void Hospital::reset()
{
	this->MUTATION_PROBABILITY.clear();
	this->population.clear();
	this->populationFitness.clear();
	this->rouletteWheel.clear();
	this->violatedConstraints.clear();
	this->totalFitness = 0;
};

/*
void Hospital::print()
{

	// Print N, D  and S parameters
	std::cout << this->N << "\t" << this->D << "\t" << this->S << std::endl;
	std::cout << std::endl;

	// Print Coverage Matrix
	for (unsigned d = 0; d < this->D; d++ )
	{	
		for (unsigned s = 0; s < this->S; s++ )
		{
			std::cout << this->COVERAGE.at(d).at(s) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Print Population Matrix
	for (unsigned i = 0; i < this->population.size(); i++)
	{
		std::cout << "Cromosoma: " << i+1 << std::endl;
		for (unsigned n = 0; n < this->population.at(i).size(); n++)
		{	
			for (unsigned d = 0; d < this->population.at(i).at(n).size(); d++)
			{
				std::cout << this->population.at(i).at(n).at(d) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	for (unsigned n = 0; n < this->N; n++ )
	{	
		for (unsigned d = 0; d < this->D; d++ )
		{
			std::cout << this->schedule.at(0).size() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Print Preferences Matrix
	for (unsigned n = 0; n < this->N; n++ )
	{
		for (unsigned d = 0; d < this->D; d++ )
		{	
			for (unsigned s = 0; s < this->S; s++ )
			{
				std::cout << this->PREFERENCES.at(n).at(d).at(s) << "\t";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Print D and S parameters
	std::cout << this->D << "\t" << this->S << std::endl;
	std::cout << std::endl;

	std::cout << this->NURSE_MIN_DAYS << "\t" << this->NURSE_MAX_DAYS << std::endl;
	std::cout << std::endl;

	std::cout << this->NURSE_MIN_CONSECUTIVE_DAYS << "\t" << this->NURSE_MAX_CONSECUTIVE_DAYS << std::endl;
	std::cout << std::endl;

	// Print Along Matrix
	for (unsigned s = 0; s < this->S; s++ )
	{	
		for (unsigned i = 0; i < this->ALONG.at(s).size(); i++ )
		{
			std::cout << this->ALONG.at(s).at(i) << "\t";
		}
		std::cout << std::endl;
	}
};
*/