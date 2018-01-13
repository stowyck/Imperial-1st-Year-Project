#include "TSequence.h"
#include "AddedFunctions.h"
#include "TComplex.h"
#include "DataDefinitions.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <stdlib.h>


using namespace std;

double wOmega;

int main()
{

    cout << "This program is designed to calculate the unknown " << endl;
    cout << "currents I1, I2 and I3, and the voltage V1 and V2 in the diagram below." << endl;
    cout << "It will also plot the alternating voltages, and current values against time." << endl;

    displayDiagram();
	
	
    double component1, component2, component3, voltageValue, enteredFreq;
    string temp,c1, c2, c3;

    cout << "Enter C for capacitor, L for inductor and R for Resistor\n" << endl;

    while(true)
    {
        cout << "What is Component1: ";
        getline(cin, temp);
        //check
        if (stringCOMPARISON)
        {c1 = temp; break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    while(true)
    {
        cout << "The value of Component1: ";
        getline(cin, temp);
        stringstream ss(temp);
        if(ss >> component1){break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    cout << endl;


    while(true)
    {
        cout << "What is Component2: ";
        getline(cin, temp);
        //check
        if (stringCOMPARISON)
        {c2 = temp; break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    while(true)
    {
        cout << "The value of Component2: ";
        getline(cin, temp);
        stringstream ss(temp);
        if(ss >> component2){break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    cout << endl;


    while(true)
    {
        cout << "What is Component3: ";
        getline(cin, temp);
        //check
        if (stringCOMPARISON)
        {c3 = temp; break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    while(true)
    {
        cout << "The value of Component3: ";
        getline(cin, temp);
        stringstream ss(temp);
        if(ss >> component3){break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    cout << endl;

    while(true)
    {
        cout << "The value of the AC Voltage: ";
        getline(cin, temp);
        stringstream ss(temp);
        if(ss >> voltageValue){break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    cout << endl;

    while(true)
    {
        cout << "The frequency of this AC Voltage: ";
        getline(cin, temp);
        stringstream ss(temp);
        if(ss >> enteredFreq){wOmega = (2*M_PI*enteredFreq); break;}
        else{cout << "Value not valid. Please try again." << endl;}
    }
    cout << endl;

    TComplex comp1, comp2, comp3;

    switch(c1[0])
    {
        case 'c':
        comp1 = makeImpedanceCapacitor(component1);
        break;

        case 'C':
        comp1 = makeImpedanceCapacitor(component1);
        break;

        case 'l':
        comp1 = makeImpedanceInductor(component1);
        break;

        case 'L':
        comp1 = makeImpedanceInductor(component1);
        break;

        case 'r':
        comp1 = makeImpedanceResistor(component1);
        break;

        case 'R':
        comp1 = makeImpedanceResistor(component1);
        break;
    }

    switch(c2[0])
    {
        case 'c':
        comp2 = makeImpedanceCapacitor(component2);
        break;

        case 'C':
        comp2 = makeImpedanceCapacitor(component2);
        break;

        case 'l':
        comp2 = makeImpedanceInductor(component2);
        break;

        case 'L':
        comp2 = makeImpedanceInductor(component2);
        break;

        case 'r':
        comp2 = makeImpedanceResistor(component2);
        break;

        case 'R':
        comp2 = makeImpedanceResistor(component2);
        break;
    }

    switch(c3[0])
    {
        case 'c':
        comp3 = makeImpedanceCapacitor(component3);
        break;

        case 'C':
        comp3 = makeImpedanceCapacitor(component3);
        break;

        case 'l':
        comp3 = makeImpedanceInductor(component3);
        break;

        case 'L':
        comp3 = makeImpedanceInductor(component3);
        break;

        case 'r':
        comp3 = makeImpedanceResistor(component3);
        break;

        case 'R':
        comp3 = makeImpedanceResistor(component3);
        break;
    }


    TSequence impedances, inverseImpedances, IVunknowns, IVknowns;
    impedances = makeTSequence(3,3);
    inverseImpedances = impedances;
    IVunknowns = makeTSequence(3,1);
    IVknowns = IVunknowns;

	//error has something to with braces {}
    put(0, 0, reciprocalComplex(comp1), &impedances);
	TComplex ntry = {-1,0}; put(0, 1, multiplyComplex(reciprocalComplex(comp1),ntry), &impedances);
    ntry.re=1;ntry.im=0; put(0, 2, ntry, &impedances);
    ntry.re=-1;ntry.im=0; put(1, 0, multiplyComplex(reciprocalComplex(comp1),ntry), &impedances);
    put(1, 1, addComplex(addComplex(reciprocalComplex(comp1),reciprocalComplex(comp2)),reciprocalComplex(comp3)), &impedances);//no error here for some reason
    ntry.re=0;ntry.im=0; put(1, 2, ntry, &impedances);
    ntry.re=1;ntry.im=0; put(2, 0, ntry, &impedances);
    ntry.re=0;ntry.im=0; put(2, 1, ntry, &impedances);
    ntry.re=0;ntry.im=0; put(2, 2, ntry, &impedances);

    ntry.re=0;ntry.im=0; put(0, 0, ntry, &IVknowns);
    ntry.re=0;ntry.im=0; put(1, 0, ntry, &IVknowns);
    ntry.re=voltageValue;ntry.im=0; put(2, 0, ntry, &IVknowns);


    invert(&impedances,&inverseImpedances);

    multiplyMatrixByVector(&inverseImpedances,&IVknowns,&IVunknowns);

    TComplex node1, node2, totalCurrent;
    TComplex current1, current2, current3;

    node1 = at(0,0,&IVunknowns);
    node2 = at(1,0,&IVunknowns);
    totalCurrent = at(2,0,&IVunknowns);
    current1 = divideComplex(subtractComplex(node1, node2), comp1);
    current2 = divideComplex(node2, comp2);
    current3 = divideComplex(node2, comp3);

    cout << "V1: " << setw(4) << node1.re << "   +" << setw(4) << node1.im <<"i" << endl;
    cout << "V2: " << setw(4) << node2.re << "   +" << setw(4) << node2.im <<"i" << endl;
    cout << "I1: " << setw(4) << current1.re << "   +" << setw(4) << current1.im <<"i" << endl;
    cout << "I2: " << setw(4) << current2.re << "   +" << setw(4) << current2.im <<"i" << endl;
    cout << "I3: " << setw(4) << current3.re << "   +" << setw(4) << current3.im <<"i" << endl;

    cout << endl << endl;
    double magv1, magv2, arg1, arg2;
    magv1 = magnitudeComplex(node1); magv2 = magnitudeComplex(node2);
    arg1 = angleComplex(node1); arg2 = angleComplex(node2);



    cout << "v1(t): " << magv1 << "cos(2pi." << enteredFreq << ".t + " << arg1 << ")" << endl;
    cout << "v1(t): " << magv2 << "cos(2pi." << enteredFreq << ".t + " << arg2 << ")" << endl;

    //print out i1(t), i2(t), i3(t)





    //we will plot two time periods

    long double timePeriod = 1/enteredFreq;
    long double increment = 1/(enteredFreq*200);

    //the increment will take the the x values
    //the limit will be 2/enteredFreq

    ofstream fOut1, fOut2;

    fOut1.open("voltageR.txt");
    fOut1 << fixed << setprecision(10);

    for(long double i = 0; i < (2*timePeriod); i = i + increment)
    {
        fOut1 << setw(15) << i << "	" << setw(15) << magv1*cos(wOmega*i + arg1) << endl;//Change back to V1
    }
    fOut1.close();

    fOut2.open("voltageC.txt");
    fOut2 << fixed << setprecision(10);

    for(long double i = 0; i < (2*timePeriod); i = i + increment)
    {
        fOut2 << setw(15) << i << "	" << setw(15) << magv2*cos(wOmega*i + arg2) << endl;//Change back to V2
    }
    fOut2.close();

	
	
	system("PAUSE");
    return 0;
}











































//THIS IS SOME INPUT TO TEST THE FUNCTION CODE
/*
    TSequence Amatrix, Invmatrix;
    Amatrix = makeTSequence(2,2);
    Invmatrix = Amatrix;



    put(0,0,{3,0},&Amatrix);
    put(0,1,{1,0},&Amatrix);
    put(1,0,{4,0},&Amatrix);
    put(1,1,{2,0},&Amatrix);
    invert(&Amatrix, &Invmatrix);


    for(int i = 0; i < 2; i++)
    {
        cout << "|";
        for(int k = 0; k < 2; k++)
        {cout << setw(4) << at(i,k,&Invmatrix).re << "   +" << setw(4) << at(i,k,&Invmatrix).im <<"i | ";}
        cout << endl;
    }


    Amatrix = makeTSequence(3,3);
    Invmatrix = Amatrix;

    put(0,0,{1,0},&Amatrix);
    put(0,1,{2,0},&Amatrix);
    put(0,2,{3,0},&Amatrix);
    put(1,0,{0,0},&Amatrix);
    put(1,1,{1,0},&Amatrix);
    put(1,2,{5,0},&Amatrix);
    put(2,0,{5,0},&Amatrix);
    put(2,1,{6,0},&Amatrix);
    put(2,2,{0,0},&Amatrix);
    invert(&Amatrix, &Invmatrix);

    cout << endl << endl;


    for(int i = 0; i < 3; i++)
    {
        cout << "|";
        for(int k = 0; k < 3; k++)
        {cout << setw(4) << at(i,k,&Invmatrix).re << "   +" << setw(4) << at(i,k,&Invmatrix).im <<"i | ";}
        cout << endl;
    }
*/
/*
    TSequence Amatrix, readVector, writeVector;
    Amatrix = makeTSequence(3,3);
    readVector = makeTSequence(3,1);
    writeVector = readVector;

    put(0,0,{1,1},&Amatrix);
    put(0,1,{2,2},&Amatrix);
    put(0,2,{3,3},&Amatrix);
    put(1,0,{0,0},&Amatrix);
    put(1,1,{1,3},&Amatrix);
    put(1,2,{5,5},&Amatrix);
    put(2,0,{5,9},&Amatrix);
    put(2,1,{6,6},&Amatrix);
    put(2,2,{0,0},&Amatrix);

    put(0,0,{7,7},&readVector);
    put(1,0,{2,2},&readVector);
    put(2,0,{2,2},&readVector);

    multiplyMatrixByVector(&Amatrix,&readVector,&writeVector);

        for(int k = 0; k < 3; k++)
        {cout << setw(4) << at(k,0,&writeVector).re << "   +" << setw(4) << at(k,0,&writeVector).im <<"i" << endl;}
*/
