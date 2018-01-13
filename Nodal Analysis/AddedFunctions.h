#include <fstream>
#include <string>
#include <iostream>
#include "DataDefinitions.h"


using namespace std;

extern double wOmega;


void displayDiagram();
TComplex makeImpedanceCapacitor(double);
TComplex makeImpedanceInductor(double);
TComplex makeImpedanceResistor(double);
