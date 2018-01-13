#include <cmath>  // atan2(), sqrt() //not needed as it is already included in main.c
// Global variables declared in main.c
#include "DataDefinitions.h"


TComplex makeComplex(double r, double i);

int compareComplex(TComplex c1, TComplex c2);

double angleComplex(TComplex c);

TComplex addComplex(TComplex c1, TComplex c2);

double magnitudeComplex(TComplex c);

TComplex subtractComplex(TComplex c1, TComplex c2);

TComplex multiplyComplex(TComplex c1, TComplex c2);

TComplex divideComplex(TComplex c1, TComplex c2);

TComplex reciprocalComplex(TComplex c);

TComplex conjugateComplex(TComplex c);

double getReal(TComplex c);

double getImag(TComplex c);