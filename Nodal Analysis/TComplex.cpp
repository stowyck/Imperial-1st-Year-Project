#include "TComplex.h"

//returns a struct containing two doubles
TComplex makeComplex(double r, double i)
{   static TComplex tmp;//retains value after
    //the function has finished

    tmp.re = r;
    tmp.im = i;
    return tmp;
}

int compareComplex(TComplex c1, TComplex c2)
{
    double LIMIT = 0.00000001;
//fabs returns the modulus or positive value
    if((fabs(c1.re-c2.re) < LIMIT) && (fabs(c1.im-c2.im) < LIMIT))
    {return true;}
    else
    {return false;}
}//returns true if c1 and c2 are equal



double angleComplex(TComplex c)
{
    return atan2(c.im, c.re);
}//returns arctan, or tan-inverse/argument of a complex number

TComplex addComplex(TComplex c1, TComplex c2)
{
    static TComplex tmp;
    tmp.re = c1.re + c2.re;
    tmp.im = c1.im + c2.im;
    return tmp;
}

double magnitudeComplex(TComplex c)
{
    return sqrt((c.re*c.re) + (c.im*c.im));
}


TComplex subtractComplex(TComplex c1, TComplex c2)
{
    static TComplex tmp;
    tmp.re = c1.re - c2.re;
    tmp.im = c1.im - c2.im;
    return tmp;
}


TComplex multiplyComplex(TComplex c1, TComplex c2)
{
    static TComplex tmp;
    tmp.re = (c1.re * c2.re)-(c1.im * c2.im);
    tmp.im = (c1.re * c2.im)+(c1.im * c2.re);
    return tmp;
}


TComplex divideComplex(TComplex c1, TComplex c2)//divide's c1 by c2
{
    static TComplex tmp;
    double c2MagnitudeSqrd = (magnitudeComplex(c2)*magnitudeComplex(c2));
    TComplex k = conjugateComplex(c2);
    tmp = multiplyComplex(c1, k);
    tmp.re = tmp.re / c2MagnitudeSqrd;
    tmp.im = tmp.im / c2MagnitudeSqrd;
    return tmp;
}


TComplex reciprocalComplex(TComplex c)
{
    static TComplex tmp;
    TComplex Unit;
    Unit.re = 1;
    Unit.im = 0;
    tmp = divideComplex(Unit, c);
    return tmp;
}

TComplex conjugateComplex(TComplex c)
{
    static TComplex tmp;
    tmp.re =  c.re;
    tmp.im = -c.im;
    return tmp;
}


double getReal(TComplex c)
{return c.re;}

double getImag(TComplex c)
{return c.im;}