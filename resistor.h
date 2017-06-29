//
//  resistor.h
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include <complex>
#include <iostream>
#include "component.h"

#ifndef resistor_h
#define resistor_h

class resistor : public component{
    double R; // the resistance, R
    bool n; // nested boolean
    char conn; // series or parallel choice
public:
    resistor(); // default constructor
    resistor( double, double, char); // parameterised constructor
    resistor( double, double, char, bool); // parameterised constructor for nested circuits
    std::string name();
    double getR();// get the resistance
    void setR(double);// set the resistance
    double getVal(); // get value
    double getQ(); // get the quality factor
    bool getNested(); // get nested yes/no
    void setZ(double );// set the resistance
    char getConn();// get connection type
    complex<double> getComponentImp(double); // get component impedance
    double getComponentPhi(); // get component phase shift
    void compInfo(double);
    ~resistor() {} // destructor
};

#endif /* resistor_h */
