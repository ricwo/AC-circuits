//
//  inductor.h
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include <complex>
#include <iostream>
#include "component.h"


#ifndef inductor_h
#define inductor_h

class inductor : public component{
    double L; // the inductance, L
    double Q; // its quality factor
    bool n; // nested bool
    char conn; // series or parallel choice
public:
    inductor(); // default constructor
    inductor(double, double, char); // parameterised constructor
    inductor(double, double, char, bool); // parameterised constructor
    std::string name(); // component name
    double getL(); // get the inductance
    double getVal(); // return value
    double getQ(); // get the quality factor
    bool getNested(); //get nested yes/no
    void setL(double); // set the inductance
    void setQ(double); // set the quality factor
    char getConn(); // get connection type
    complex<double> getComponentImp(double); // get component impedance
    double getComponentPhi(); // get component phase shift
    void compInfo(double);
    ~inductor() {} // destructor
};

#endif /* inductor_h */
