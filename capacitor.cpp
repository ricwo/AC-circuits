//
//  capacitor.cpp
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include "capacitor.h"
#include <iomanip>

capacitor::capacitor() // default constructor with L=0
{
    C = 0.;
}

capacitor::capacitor( double C_in, double q_in, char c_in )
{
    C = C_in;
    conn = c_in;
    Q = q_in;
}

capacitor::capacitor( double C_in, double q_in, char c_in, bool nested_in )
{
    C = C_in;
    conn = c_in;
    Q = q_in;
    n = nested_in;
}

std::string capacitor::name()
{
    return "capacitor";
}

double capacitor::getC() // get the inductance
{
    return C;
}
double capacitor::getVal() // return value
{
    return getC();
}

void capacitor::setC(double c_in) // set the inductance
{
    C = c_in;
}

char capacitor::getConn() // get connection type
{
    return conn;
}

void capacitor::setQ(double q_in) // get the inductance
{
    Q = q_in;
}

double capacitor::getQ() // get the inductance
{
    return Q;
}

bool capacitor::getNested() // get nested boolean
{
    return n;
}

void capacitor::compInfo(double w) // cout component info
{
    std::cout.precision(3); // fixed precision
    std::cout.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed
    std::cout<<"capacitor with\tC = "<<(this->getC())*1e12<<"\tpF\tin "<<(getConn()=='s' ? "ser." : "par." )<<
    ",\tZ = "<<this->getComponentImp(w)<<" Ω,\tϕ = "<<this->getComponentPhi()/M_PI<<(this->getComponentPhi()==0 ? "" : " π" )<<", Q = "<<this->getQ()<<(this->getNested() ? ", nested" :"") <<std::endl;

}

complex<double> capacitor::getComponentImp(double w)// get component impedance
{
    return complex<double> (0.,-1/(w*C));
}

double capacitor::getComponentPhi() // get component phase shift
{
    return -M_PI/2.;
}

