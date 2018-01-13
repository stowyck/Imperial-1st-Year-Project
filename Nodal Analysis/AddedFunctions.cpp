#include "AddedFunctions.h"

void displayDiagram()
{
    ifstream fInp;
    fInp.open("diagram.txt");
    string buffer;

    while(fInp.eof() != true)
    {
        getline(fInp, buffer);
        cout << buffer << endl;
    }

}

TComplex makeImpedanceCapacitor(double C)
{
    static TComplex tmp;//retains value after
    //the function has finished
    tmp.re = 0.0;
    tmp.im = -(1/(C*wOmega));
    return tmp;
}

TComplex makeImpedanceInductor(double L)
{
    static TComplex tmp;
    tmp.re = 0.0;
    tmp.im = (L*wOmega);
    return tmp;
}

TComplex makeImpedanceResistor(double r)
{
    static TComplex tmp;
    tmp.re = r;
    tmp.im = 0.0;
    return tmp;
}
