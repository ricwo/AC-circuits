//
//  inductor.cpp
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include "inductor.h"

inductor::inductor() // default constructor with L=0
{
    L = 0.; Q = 0;
}

inductor::inductor( double l_in, double q_in, char c_in ) // parameterised constructor
{
    L = l_in;
    conn = c_in;
    Q = q_in;
}

inductor::inductor( double l_in, double q_in, char c_in, bool nested_in ) // parameterised constructor
{
    L = l_in;
    conn = c_in;
    Q = q_in;
    n = nested_in;
    
}

std::string inductor::name()
{
    return "inductor";
}

double inductor::getL() // get the inductance
{
    return L;
}

double inductor::getQ() // get the inductance
{
    return Q;
}

double inductor::getVal() // return value
{
    return getL();
}

bool inductor::getNested() // return value
{
    return n;
}


void inductor::setL(double l_in) // get the inductance
{
    L = l_in;
}

void inductor::setQ(double q_in) // get the inductance
{
    Q = q_in;
}


char inductor::getConn() // get connection type
{
    return conn;
}

void inductor::compInfo(double w) // cout component info
{
    std::cout.precision(3);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed
    std::cout<<"inductor with\tL = "<<this->getL()*1.0e3<<"\tmH\tin "<<(getConn()=='s' ? "ser." : "par." )<<
    ",\tZ = "<<this->getComponentImp(w)<<" Ω,\t\tϕ = "<<this->getComponentPhi()/M_PI<<(this->getComponentPhi()==0 ? "" : " π" )<<", Q = "<<this->getQ()<<(this->getNested() ? ", nested" :"")<<std::endl;
}

complex<double> inductor::getComponentImp(double w)// get component impedance
{
    return complex<double> (0.,w*L);
}

double inductor::getComponentPhi() // get component phase shift
{
    return M_PI/2.;
}

