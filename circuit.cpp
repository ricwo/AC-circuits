//
//  circuit.cpp
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include "circuit.h"
#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>
#include "component.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"

using namespace std;

circuit::circuit() // default constructor with w = 2𝜋f and f = 50 Hz
{
    w = 2.*PI*50.;
}

circuit::circuit(double f_in) // parameterised constructor with w = 2𝜋f_in, default is 50
{
    w = 2.*PI*f_in;
}

void circuit::computeZ(bool doNested) // compute the impedance of the circuit
{
    // Count subsequent components in series and submit them into the componentZ function
    shared_ptr<vector<complex<double>>> impcircuit (new vector<complex<double>>);// create vector of impedances
    shared_ptr<vector<component*>> serialOut (new vector<component*>); // create circuittor of components in series to send off to the componentZ function
    shared_ptr<vector<component*>> parallelOut (new vector<component*>); // create circuittor of components in parallel to send off to the componentZ function
    unique_ptr<vector<complex<double>>> nestedImpCircuitImport (new vector<complex<double>>);
    if( doNested ){
        // make local copy
        circuit* circSub = new circuit(*this); // make local copy for the operations
        shared_ptr<vector<complex<double>>> nestedImpCircuit;// (new vector<complex<double>>);
        shared_ptr<circuit> nestedOut;// (new circuit()); // create sub-circuit for nested
        bool doneNested = false;
        for( auto d = circSub->comp.begin(); d != circSub->comp.end(); ++d ){
            if( (*d)->getNested() == true ){
                nestedOut->addComp((*d)->name(),(*d)->getVal(),(*d)->getQ(),(*d)->getConn());
                doneNested = true;

            }
        }
        if( doneNested ){
            nestedOut->setF(this->getF());// call this function on the nestedOut circuit, give it the same frequency
            nestedOut->computeZ(false);
            nestedImpCircuit->push_back(nestedOut->getZ());
            *nestedImpCircuitImport = *nestedImpCircuit;
        }
    }
    
    for( auto c = comp.begin(); c != comp.end(); ++c ){
        if( (*c)->getConn()=='s' ){
            serialOut->push_back(*c);
            if( comp.size() == 1 ) { // if only one component, send off to component Z function
                impcircuit->push_back(componentZ(*serialOut));
                serialOut->clear();
            }
        }
        else if( (*c)->getConn()=='p' ){ // if component is in parallel, also send of to the componentZ function (with one component)
            parallelOut->push_back(*c);
            impcircuit->push_back(componentZ(*parallelOut));
            parallelOut->clear();
            impcircuit->push_back(componentZ(*serialOut)); // send to componentZ function and push back on vector
            serialOut->clear();
        }
    }

    // send remaining serialOut to componentZ function
    if( serialOut->size() > 0){
        impcircuit->push_back(componentZ(*serialOut));
    }
    // do the parallel computation of the various serial sub-circuits
    // find the reciprocal sum of all the impedances
    shared_ptr<complex<double>> recipSum (new complex<double>(0.,0.));
    shared_ptr<complex<double>> complexOne (new complex<double>(1.,0.));
    for( auto z = impcircuit->begin(); z != impcircuit->end(); ++z ){ // loop over series circuittor
        *recipSum += *complexOne/(*z);
    }
    if( nestedImpCircuitImport->size() > 0 ){
        for( auto x = nestedImpCircuitImport->begin(); x != nestedImpCircuitImport->end(); ++x ){ // loop over series circuittor
            *recipSum += *complexOne/(*x);
        }
    }
    
    // return the inverse of the reciprocal 
    try{ Z = *complexOne/(*recipSum); }
    catch(...) {
        cout<<"Error: Reciprocal sum division by zero."<<endl;
        exit(-1);
    }
}

void circuit::computeQ() // compute the impedance of the circuit
{
    double recipSum;
    for( auto c = comp.begin(); c != comp.end(); ++c ){
        double compQ = (*c)->getQ();
        if( compQ >= 0 ) recipSum += compQ;
    }
    // return the inverse of the reciprocal sum
    try{ Q = 1/recipSum; }
    catch(...) {
        cout<<"Error: Reciprocal sum division by zero."<<endl;
        exit(-1);
    }
}

complex<double> circuit::componentZ( vector<component*> const &in) const // compute the impedance of a (circuittor of) component(s)
{
    // first, add up the components in series together
    // loop over all components of the comp circuittor
    double R=0., X_L=0., X_C=0.; // define doubles for the reactances
    for( auto c = in.begin(); c != in.end(); ++c ){ // fill the reactances
        if( (*c)->name() == "resistor" ){
            R += (*c)->getVal(); // for resistor: R = R
        }
        else if( (*c)->name() == "capacitor" ){
            X_C += -1. / (w * (*c)->getVal() ); // for capacitor: X_C = -1/wc
        }
        else{
            X_L += w * (*c)->getVal(); // for inductor X_L = wL
        }
    }
    return complex<double>(R,X_L+X_C); // return complex impedance (a + bi) = (R + (X_L+X_C)i )
}


complex<double> circuit::getZ() const // get the complex impedance
{
    return Z;
}

double circuit::magZ() const // get magnitude
{
    return abs(getZ());
}

void circuit::printZ() const // print out the complex impedance of the circuit
{
    cout<<"This circuit has an impedance of Z = "<< this->getZ().real() << (this->getZ().imag() >=0 ? " + " : " - " )<< this->getZ().imag() << "i" << endl;
}

void circuit::setF(double f_in){ // set frequency
    w = 2.*PI*f_in;
}

void circuit::setOmega(double w_in){ // set angular frequency
    w = w_in;
}

double circuit::getQ() const { // set angular frequency
    return Q;
}


double circuit::getF()const // get frequency
{
    return w / (2.*PI);
}

double circuit::getOmega() const // get omega
{
    return w;
}

double circuit::getPhi() const // get phi
{
    return arg(Z);
}

unsigned long int circuit::Ncomp() const // return the number of components
{
    return comp.size();
}

void circuit::addComp(const string& type, double a, double b, char d ) // create component
{
    if( type == "resistor" ){ comp.push_back(new resistor(a,b,d));}
    else if ( type == "capacitor" ){ comp.push_back(new capacitor(a,b,d)); }
    else if ( type == "inductor" ){ comp.push_back(new inductor(a,b,d));}
    else{ std::cout<<"You must enter a valid component name\n"; }
}

void circuit::addComp(const string& type, double a, double b, char d, bool n ) // create nested component
{
    if( type == "resistor" ){ comp.push_back(new resistor(a,b,d,n));}
    else if ( type == "capacitor" ){ comp.push_back(new capacitor(a,b,d,n)); }
    else if ( type == "inductor" ){ comp.push_back(new inductor(a,b,d,n));}
    else{ std::cout<<"You must enter a valid component name\n"; }
}

void circuit::removeComp(int n) // remove component
{
    delete comp[n];
}

void circuit::info() // circuit computation and couting
{
    computeZ(); // compute Z
    cout << *this; // cout circuit
}

std::ostream& operator<<(std::ostream& os, circuit const & ic)
{
    cout << "\nThis circuit has " << ic.comp.size() << " components:\n";
    int counter(1);
    for( auto c = ic.comp.begin(); c != ic.comp.end(); ++c ){
        cout << "Element " << counter << ": ";
        (*c)->compInfo(ic.w);
        ++counter;
    }
    complex<double> imp = ic.getZ();
    cout << "Its impedance is " << imp.real()/1.e3<< (imp.imag() >=0 ? " + " : " " )<< imp.imag()/1.e3 << " i kΩ" << endl;
    cout << "Its magnitude is " << abs(imp)/1.e3 << " kΩ" << endl;
    cout << "The has AC frequency " << ic.getF() << " Hz" << endl;
    cout << "The circuit has Q factor " << ic.getQ() << endl;
    cout << "Its phase difference is " << ic.getPhi()*57.2958 << "°" << endl;
    // print out which components are nested
    return os;
}

circuit::circuit(circuit &c){// Copy assigment
    Z = c.Z; // assign impedance
    w = c.w; // assign frequency
    if( c.comp.size() > 0 )
        for( int i{0}; i < comp.size(); ++i ) comp[i] = c.comp[i];
    else {cout<<"Error: must have at least one component"<<endl; exit(1);}
}

circuit::circuit(circuit &&c ){ // move assignment
    Z = c.Z; w = c.w; comp = c.comp;
}

circuit & circuit::operator=(circuit &c){ // Copy assignment operator
    //cout << "Copy assignment\n";
    if( &c == this ) return *this; // no self-assignment
    Z=0; w=0; // delete data
    Z=c.Z; w=c.w;
    for( int i = 0; i<c.comp.size(); ++i ) comp[i]=c.comp[i];
    return *this;
}

circuit & circuit::operator=(circuit &&c){ // Move assignment operator
    //cout <<"move assignment\n";
    swap(Z,c.Z);
    swap(w,c.w);
    swap(comp,c.comp);
    return *this; // Special pointer!!!
}

void circuit::plotPhasorDiagram() const { // function to plot phasor diagram of this circuit
    cout << "\n\nThe phasor diagram for Z = " << Z.real() << (Z.imag() >=0 ? " + " : " " )<< Z.imag() << " i Ω looks like this:\n";
    double slope = tan(arg(Z)); // define slope as the tangent of the phase angle
    cout << "The phase angle is " << arg(Z)*57.2958 << "°\n\n";
    cout<<"X=Im(Z) ⬆\n        ❚\n";
    for(int i = 25; i > -1; --i){
        if( i == 0 ) cout << "      0 ❚";
        else if( i == 5 ) cout << "    0.2 ❚";
        else if( i == 10 ) cout << "    0.4 ❚";
        else if( i == 15 ) cout << "    0.6 ❚";
        else if( i == 20 ) cout << "    0.8 ❚";
        else if( i == 25 ) cout << "    1.0 ❚";
        else cout<<"        ❚";
        for(int j = 1; j < 81; ++j){
            if( round(3.2/slope*i) == j ) cout<<"●"; // need factor of 3.2 becaues of the asymmetric dimensions (80/25=3.2)
            else cout<<"‒";
        }
        if( i == 0 ) cout<<"―➡ R=Re(Z)\n";
        else cout<<"\n";
    }
    cout << "        |                |               |               |              |              |   \n"
         << "        0                .2              .4              .6             .8            1.0  \n";
    cout << endl;
}



