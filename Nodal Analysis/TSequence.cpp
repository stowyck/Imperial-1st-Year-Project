// TSequence.cpp implementation file
#include "TSequence.h"


TSequence makeTSequence(int noRows, int noCols)
{
     static TSequence tmp;
     TComplex Zeroed = {0.0, 0.0};
     tmp.noRows = noRows;
     tmp.noCols = noCols;
     tmp.theData.resize(noRows * noCols);
     for (int i = 0; i < noRows*noCols; i++)
         tmp.theData[i] = Zeroed;//contains complex numbers
     return tmp;
} // makeTSequence()
//TSequence is a struct containing the number of rows, columns and a vector

int getNoRows(const TSequence *readOnlySequence)
{
     return readOnlySequence->noRows;
} // getNoRows()


int getNoCols(const TSequence *readOnlySequence)
{
     return readOnlySequence->noCols;
} // getNoCols()


void put(int row, int col, TComplex value, TSequence *readWriteSequence)//TSequence is a matrix
{
      readWriteSequence->theData[(readWriteSequence->noCols * row) + col] = value;
} // put()


TComplex at(int row, int col, const TSequence *readOnlySequence)
{
      return readOnlySequence->theData[(readOnlySequence->noCols * row) + col];
} // at()


TComplex determinant(const TSequence *readOnlySequence)//we are pointing to a 3by3 matrix here
{   //create three 2by2 matrices use those values
	//TComplex Nil = {NULL,NULL}
	TComplex nil = {NULL,NULL};


    if(getNoRows(readOnlySequence) == 2)
    {
      return subtractComplex(multiplyComplex(at(0,0,readOnlySequence),at(1,1,readOnlySequence)) , multiplyComplex(at(0,1,readOnlySequence),at(1,0,readOnlySequence)));
    }
    if(getNoRows(readOnlySequence) == 3)
    {
    TSequence minorDetOne = makeTSequence(2,2), minorDetTwo, minorDetThree;
    minorDetThree = minorDetTwo = minorDetOne;
    TComplex DetOne, DetTwo, DetThree;
    TComplex TermOne, TermTwo, TermThree;

    //CHANGE ALL THE VALUES USING THE at functions
                                                                  //row col
    put(0, 0, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 1], &minorDetOne);
    put(0, 1, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 2], &minorDetOne);
    put(1, 0, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 1], &minorDetOne);
    put(1, 1, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 2], &minorDetOne);

    DetOne = determinant(&minorDetOne);

    put(0, 0, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 0], &minorDetTwo);
    put(0, 1, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 2], &minorDetTwo);
    put(1, 0, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 0], &minorDetTwo);
    put(1, 1, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 2], &minorDetTwo);

    DetTwo = determinant(&minorDetTwo);

    put(0, 0, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 0], &minorDetThree);
    put(0, 1, readOnlySequence->theData[(readOnlySequence->noCols * 1) + 1], &minorDetThree);
    put(1, 0, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 0], &minorDetThree);
    put(1, 1, readOnlySequence->theData[(readOnlySequence->noCols * 2) + 1], &minorDetThree);

    DetThree = determinant(&minorDetThree);

    TermOne = multiplyComplex(readOnlySequence->theData[(readOnlySequence->noCols * 0) + 0],DetOne);
    TermTwo = multiplyComplex(readOnlySequence->theData[(readOnlySequence->noCols * 0) + 1],DetTwo);
    TermThree = multiplyComplex(readOnlySequence->theData[(readOnlySequence->noCols * 0) + 2],DetThree);

    return subtractComplex(addComplex(TermOne, TermThree), TermTwo);
    }

	if(getNoRows(readOnlySequence) !=2 && getNoRows(readOnlySequence) != 3){cout << "Determinant was not found, complex number has been Nulled." << endl; return nil;}
}


bool notSingular(const TSequence *readOnlySequence)
{  // return true if not equal to (near) zero otherwise return false
      return ((determinant(readOnlySequence).re) > 0.0000001 && (determinant(readOnlySequence).im > 0.0000001));
} // notSingular


void invert(const TSequence *readOnlySequence, TSequence *readWriteSequence)
{
     TComplex negOne = {-1.0, 0.0};

        // invert 2x2 matrix
     if(getNoRows(readOnlySequence) == 2)
     {
     TComplex d = determinant(readOnlySequence);

     put(0, 0,  divideComplex(at(1, 1, readOnlySequence),d), readWriteSequence);
     put(0, 1, multiplyComplex(negOne, divideComplex(at(0, 1, readOnlySequence),d)), readWriteSequence);
     put(1, 0, multiplyComplex(negOne, divideComplex(at(1, 0, readOnlySequence),d)), readWriteSequence);
     put(1, 1,  divideComplex(at(0, 0, readOnlySequence),d),readWriteSequence);
     }

        // invert 3x3 matrix
     if(getNoRows(readOnlySequence) == 3)
     {
         TComplex dRpcl = reciprocalComplex(determinant(readOnlySequence));
         TComplex currentDet;
         TSequence minorMatrix = makeTSequence(3,3);
         TSequence currentMinor = makeTSequence(2,2);


         put(0,0, at(1,1,readOnlySequence), &currentMinor);
         put(0,1, at(1,2,readOnlySequence), &currentMinor);
         put(1,0, at(2,1,readOnlySequence), &currentMinor);
         put(1,1, at(2,2,readOnlySequence), &currentMinor);

         put(0,0, determinant(&currentMinor), &minorMatrix);//1


         put(0,0, at(1,0,readOnlySequence), &currentMinor);
         put(0,1, at(1,2,readOnlySequence), &currentMinor);
         put(1,0, at(2,0,readOnlySequence), &currentMinor);
         put(1,1, at(2,2,readOnlySequence), &currentMinor);

         put(0,1, determinant(&currentMinor), &minorMatrix);//2


         put(0,0, at(1,0,readOnlySequence), &currentMinor);
         put(0,1, at(1,1,readOnlySequence), &currentMinor);
         put(1,0, at(2,0,readOnlySequence), &currentMinor);
         put(1,1, at(2,1,readOnlySequence), &currentMinor);

         put(0,2, determinant(&currentMinor), &minorMatrix);//3


         put(0,0, at(0,1,readOnlySequence), &currentMinor);
         put(0,1, at(0,2,readOnlySequence), &currentMinor);
         put(1,0, at(2,1,readOnlySequence), &currentMinor);
         put(1,1, at(2,2,readOnlySequence), &currentMinor);

         put(1,0, determinant(&currentMinor), &minorMatrix);//4


         put(0,0, at(0,0,readOnlySequence), &currentMinor);
         put(0,1, at(0,2,readOnlySequence), &currentMinor);
         put(1,0, at(2,0,readOnlySequence), &currentMinor);
         put(1,1, at(2,2,readOnlySequence), &currentMinor);

         put(1,1, determinant(&currentMinor), &minorMatrix);//5


         put(0,0, at(0,0,readOnlySequence), &currentMinor);
         put(0,1, at(0,1,readOnlySequence), &currentMinor);
         put(1,0, at(2,0,readOnlySequence), &currentMinor);
         put(1,1, at(2,1,readOnlySequence), &currentMinor);

         put(1,2, determinant(&currentMinor), &minorMatrix);//6


         put(0,0, at(0,1,readOnlySequence), &currentMinor);
         put(0,1, at(0,2,readOnlySequence), &currentMinor);
         put(1,0, at(1,1,readOnlySequence), &currentMinor);
         put(1,1, at(1,2,readOnlySequence), &currentMinor);

         put(2,0, determinant(&currentMinor), &minorMatrix);//7


         put(0,0, at(0,0,readOnlySequence), &currentMinor);
         put(0,1, at(0,2,readOnlySequence), &currentMinor);
         put(1,0, at(1,0,readOnlySequence), &currentMinor);
         put(1,1, at(1,2,readOnlySequence), &currentMinor);

         put(2,1, determinant(&currentMinor), &minorMatrix);//8


         put(0,0, at(0,0,readOnlySequence), &currentMinor);
         put(0,1, at(0,1,readOnlySequence), &currentMinor);
         put(1,0, at(1,0,readOnlySequence), &currentMinor);
         put(1,1, at(1,1,readOnlySequence), &currentMinor);

         put(2,2, determinant(&currentMinor), &minorMatrix);//9

         //I now have a matrix of minors
         //need to change matrix of minors into matrix of cofactors

         put(0,1, multiplyComplex(at(0,1,&minorMatrix),negOne), &minorMatrix);
         put(1,0, multiplyComplex(at(1,0,&minorMatrix),negOne), &minorMatrix);
         put(1,2, multiplyComplex(at(1,2,&minorMatrix),negOne), &minorMatrix);
         put(2,1, multiplyComplex(at(2,1,&minorMatrix),negOne), &minorMatrix);

         //now we must transpose and multiply by 1/det

         put(0,0, multiplyComplex(at(0,0,&minorMatrix),dRpcl), readWriteSequence);
         put(0,1, multiplyComplex(at(1,0,&minorMatrix),dRpcl), readWriteSequence);
         put(0,2, multiplyComplex(at(2,0,&minorMatrix),dRpcl), readWriteSequence);
         put(1,0, multiplyComplex(at(0,1,&minorMatrix),dRpcl), readWriteSequence);
         put(1,1, multiplyComplex(at(1,1,&minorMatrix),dRpcl), readWriteSequence);
         put(1,2, multiplyComplex(at(2,1,&minorMatrix),dRpcl), readWriteSequence);
         put(2,0, multiplyComplex(at(0,2,&minorMatrix),dRpcl), readWriteSequence);
         put(2,1, multiplyComplex(at(1,2,&minorMatrix),dRpcl), readWriteSequence);
         put(2,2, multiplyComplex(at(2,2,&minorMatrix),dRpcl), readWriteSequence);
     }

     if(getNoRows(readOnlySequence) !=2 && getNoRows(readOnlySequence) != 3){cout << "Inverse was not found." << endl;}

} // invert()


void multiplyMatrixByVector(const TSequence *readOnlyMatrix, const TSequence *readOnlyVector, TSequence *readWriteVector)
{
    if(getNoRows(readWriteVector) == 2)
    { // multiply 2x2 matrix by 2x1 vector
     TComplex top = at(0, 0, readOnlyVector);
     TComplex bottom = at(1, 0, readOnlyVector);
     for (int r = 0; r < 2; r++)
     {put(r, 0, addComplex((multiplyComplex(at(r,0,readOnlyMatrix),top)), (multiplyComplex(at(r,1,readOnlyMatrix),bottom))), readWriteVector);}
    }
    if(getNoRows(readWriteVector) == 3)
    { // multiply 3x3 matrix by 3x1 vector
     TComplex top = at(0, 0, readOnlyVector);
     TComplex middle = at(1, 0, readOnlyVector);
     TComplex bottom = at(2, 0, readOnlyVector);
     for(int r = 0; r < 3; r++)
     {put(r, 0, addComplex(addComplex((multiplyComplex(at(r,0,readOnlyMatrix),top)), (multiplyComplex(at(r,1,readOnlyMatrix),middle))),multiplyComplex(at(r,2,readOnlyMatrix), bottom)), readWriteVector);}
    }
    if(getNoRows(readWriteVector) !=2 && getNoRows(readWriteVector) != 3){cout << "Program has not multiplied matrix by vector." << endl;}

} // multiplyMatrixByVector()


/*
void returnDynamicMemory(TSequence *readWriteSequence)//not needed for vectors
{
     delete [] readWriteSequence->theData;
     readWriteSequence->theData = NULL;
}
*/