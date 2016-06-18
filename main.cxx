#define EVOLUTIVE_CXX
#define HOSPITAL_CXX
#include "evolutive.h"
#include "hospital.h"


int main()
{    
    Hospital hospital;

    std::string s = "instances/25_7_4_1.nsp";
    hospital.loadData(s);
    
	return 0;
};


