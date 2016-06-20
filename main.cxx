#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{    
    Hospital hospital;

    std::string s = "instances/25_7_4_1.nsp";
    hospital.loadData(s);
    hospital.setMutationProbability();
    hospital.genPopulation();
    
    std::cout << "Before mutation" << std::endl;
    hospital.print();
    hospital.mutate(0);
    std::cout << "After mutation" << std::endl;
    hospital.print();
	return 0;
};


