//
//  component.h
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include <complex>
#include <iostream>
#include <string>

using namespace std;

#ifndef component_h
#define component_h

class component {
public:
    virtual ~component() { std::cout << "Base class component destructor\n"; }
    virtual void compInfo(double)=0; // Component info
    virtual std::string name()=0; // Component name
    virtual char getConn()=0; // get connection type
    virtual bool getNested()=0; // get nested bool
    virtual double getQ()=0; // get Quality factor
    virtual complex<double> getComponentImp(double)=0; // get component impedance
    virtual double getComponentPhi()=0; // get component phase shift
    virtual double getVal()=0; // get the defining value
};

#endif /* component_h */
