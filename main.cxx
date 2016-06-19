#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{    
    Hospital hospital;

    std::string s = "instances/25_7_4_1.nsp";
    hospital.loadData(s);
    hospital.genPopulation();
    hospital.print();
	return 0;
};


