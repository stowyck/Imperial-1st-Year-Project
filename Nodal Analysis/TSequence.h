// TSequence.h specification file
#ifndef TS
#define TS
#include <iostream>
#include <cstdio>
#include <vector>
#include "TComplex.h"

using namespace std;

//Datatype
struct TSeq
{
     int noRows;
     int noCols;
     vector <TComplex> theData;//may have to change to hold complex numbers i.e. TComplex
};

typedef struct TSeq TSequence;

// Function prototypes

TSequence makeTSequence(int, int);
int getNoRows(const TSequence *);
int getNoCols(const TSequence *);
void put(int, int, TComplex, TSequence *);
TComplex at(int, int, const TSequence *);
TComplex determinant(const TSequence *);
bool notSingular(const TSequence *);
void invert(const TSequence *, TSequence *);
void multiplyMatrixByVector(const TSequence *, const TSequence *, TSequence *);

//void returnDynamicMemory(TSequence *);



#endif
