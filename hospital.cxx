#define HOSPITAL_CXX
#include "hospital.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Hospital::Hospital()
{
};

void Hospital::init()
{
	
};

void Hospital::loadData(std::string filename)
{
	
	std::cout << "Hola The Gang!" << std::endl;
	
	std::string line;
	std::ifstream file (filename);

	if (file.is_open())
	{
		unsigned iLine = 1;
		while ( std::getline (file,line) )
		{
			std::cout << "The line is " << iLine << std::endl;

			std::stringstream ss(line);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<std::string> vss(begin, end);

			if (iLine == 1)
			{
				std::cout << "N D S" << std::endl;
				std::cout << line << '\n';
				this->N = atoi(vss.at(0).c_str());
				this->D = atoi(vss.at(1).c_str());
				this->S = atoi(vss.at(2).c_str());
				this->init();
				//std::cout << this->N << "----" << this->D << "-----" << this->S << std::endl;
			}

			else if (iLine >= 3 and iLine <= (this->D + 2))
			{
				std::cout << "Coverage" << std::endl;
			}
			else if (iLine >= (this->D + 4) and iLine <= (this->N + this->D + 3))
			{
				std::cout << "Preferences" << std::endl;
			}

			else if (iLine == (this->N + this->D + 5))
			{
				std::cout << "D S" << std::endl;
			}

			else if (iLine == (this->N + this->D + 7))
			{
				std::cout << "Cantidad de asignaciones" << std::endl;
			}

			else if (iLine == (this->N + this->D + 9))
			{
				std::cout << "turnos trabajados consecutivos" << std::endl;
			}

			else if (iLine >= (this->N + this->D + 12) and iLine <= (this->N + this->D + this->S + 11))
			{
				std::cout << "ultimos" << std::endl;
			}

		  	//std::cout << line << '\n';
		 	iLine++;
		}
		file.close();
	}

	else std::cout << "Unable to open the file"; 

	/*
	std::string s = "1 2 3 4 7 8\n";
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);


	std::vector<int> intNumbers;
	//std::vector<std::vector<int> > matrix;
	int sum = 0;
    for (unsigned i=0; i < vstrings.size(); i++)
    {
     	int num = atoi(vstrings.at(i).c_str());
     	intNumbers.push_back(num);
     	sum = sum + num;
    }

    std::cout << sum << std::endl;
    */
};

void Hospital::setInitialGuess()
{
};

void Hospital::genNewPopulation()
{
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

std::vector<std::vector<int> > Hospital::getSchedule()
{
	return this->schedule;
};

void Hospital::print()
{
};