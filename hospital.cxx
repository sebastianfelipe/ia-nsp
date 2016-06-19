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
	std::srand(4);
	this->populationSize = 3;

	for (unsigned i = 0; i < this->populationSize; i++)
	{
		std::vector<std::vector<int> > p;
		this->population.push_back(p);
	}
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
				this->ALONG.push_back(vsi);
			}

		  	//std::cout << line << '\n';
		 	iLine++;
		}
		file.close();
	}

	else std::cout << "Unable to open the file"; 
};

void Hospital::genFirstPopulation()
{
	//this->schedule;
	for (unsigned p = 0; p < this->populationSize; p++)
	{
		for (unsigned n = 0; n < this->N; n++)
		{
			std::vector<int> v(this->D);

			for (unsigned d = 0; d < this->D; d++)
			{
				v.at(d) = std::rand()%(this->S);
			}
			
			this->population.at(p).push_back(v);
		}
	}
};

void Hospital::genPopulation()
{
};

void Hospital::genRouletteWheel()
{
};

void Hospital::applyCrossOver()
{
};

void Hospital::applyMutation()
{
};

void Hospital::applyMovement()
{
};

void Hospital::nextEvolutiveStep()
{
};

float Hospital::evaluate()
{
	return 0;
};

std::vector<std::vector<std::vector<int> > > Hospital::getPopulation()
{
	return this->population;
};

std::vector<std::vector<int> > Hospital::getBestSchedule()
{
	return this->bestSchedule;
};

void Hospital::print()
{
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

	/*
	for (unsigned n = 0; n < this->N; n++ )
	{	
		for (unsigned d = 0; d < this->D; d++ )
		{
			std::cout << this->schedule.at(0).size() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/

	/*
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
	*/
};

/*
void Hospital::init()
{
	// Initialize Coverage
	for (unsigned d = 0; d < this->D; d++ )
	{
		std::vector<int> v(this->S, 0);
		this->coverage.push_back(v);
	}

	// Initialize Preferences
	for (unsigned n = 0; n < this->N; n++ )
	{
		std::vector<std::vector<int> > v;
		this->preferences.push_back(v);

		for (unsigned d = 0; d < this->D; d++ )
		{
			std::vector<int> v(this->S, 0);
			this->preferences.at(n).push_back(v);
		}
	}
};
*/