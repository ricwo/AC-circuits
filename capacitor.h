//
//  capacitor.h
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include <complex>
#include <iostream>
#include "component.h"


#ifndef capacitor_h
#define capacitor_h

class capacitor : public component{
    double C; // the capacitance, C
    double Q; // its Q factor
    bool n; // nested yes/no
    char conn; // series or parallel choice
public:
    capacitor(); // default constructor
    capacitor( double, double, char ); // parameterised constructor
    capacitor( double, double, char, bool ); // parameterised constructor nested
    std::string name();
    double getC(); // get the resistance
    double getVal();
    bool getNested(); // nested yes/no
    double getQ(); // get the quality factor
    void setQ(double); // set the quality factor
    void setC(double ); // set the resistance
    char getConn(); // get connection type
    complex<double> getComponentImp(double); // get component impedance
    double getComponentPhi(); // get component phase shift
    void compInfo(double);
    ~capacitor() {} // destructor
};

#endif /* capacitor_h */
