//
//  circuit.h
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include <complex>
#include <iostream>
#include <vector>
#include "component.h"

#define PI 3.14159265359

using namespace std;

#ifndef circuit_h
#define circuit_h

class circuit{
    friend std::ostream& operator<<(std::ostream& , circuit const&);
private:
    complex<double> Z; // impedance of circuit
    double Q; // Q factor of circuit
    double w; // angular of AC driving force
    vector<component*> comp; // vector of pointers to components
public:
    circuit(); // default constructor with w = 2𝜋f and f = 50 Hz
    circuit(double); // parameterised constructor with w = 2𝜋f_in
    void computeZ(bool doNested = true); // function to compute the impedance and store it in member data
    void computeQ(); // compute Q factor
    complex<double> componentZ(vector<component*> const &) const; // function to compute impedance of a serial circuit
    complex<double> getZ() const; // function to retrieve the impedance of the circuit
    double magZ() const;
    void setF(double); // set frequency
    void setOmega(double); // set angular frequency
    double getF() const; // get frequency
    double getQ() const; // get Q
    double getOmega() const; // get omega
    double getPhi() const; // get phase difference
    void addComp(const string&, double, double, char); // add component
    void addComp(const string&, double, double, char, bool); // add component
    void removeComp(int); // function to remove component by #
    unsigned long int Ncomp() const; // number of components
    double componentQ(vector<component*> const &) const; // component Q
    void printZ() const;
    void plotPhasorDiagram() const; // function to plot phasor diagram of this circuit
    void info(); // generate and print circuit info
    circuit(circuit&); // Copy constructor
    circuit(circuit&&); // Move constructor
    circuit& operator=(circuit&); // Copy assignment operator
    circuit& operator=(circuit&&); // Move assignment operator
    ~circuit() {} // circuit destructor
};





#endif /* circuit_h */
