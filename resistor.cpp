//
//  resistor.cpp
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 29/03/2017.
//

#include "resistor.h"

resistor::resistor() // default constructor with L=0
{
    R = 0.;
}

resistor::resistor( double r_in, double q_in, char c_in )
{
    R = r_in;
    conn = c_in;
}

resistor::resistor( double r_in, double q_in, char c_in, bool nested_in)
{
    R = r_in;
    conn = c_in;
    n = nested_in;
}

std::string resistor::name()
{
    return "resistor";
}

double resistor::getR() // get the inductance
{
    return R;
}
double resistor::getVal() // return value
{
    return getR();
}

void resistor::setR(double r_in) // set the inductance
{
    R = r_in;
}

char resistor::getConn() // get connection type
{
    return conn;
}

bool resistor::getNested() // get nested yes/no
{
    return n;
}

double resistor::getQ() // get the inductance
{
    return 0;
}

void resistor::compInfo(double w) // cout component info
{
    std::cout.precision(3);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield ); // floatfield set to fixed
    std::cout<<"resistor with\tR = "<<this->getR()/1.e3<<"\tkΩ\tin "<<(getConn()=='s' ? "ser." : "par." )<<
    ",\tZ = "<<this->getComponentImp(w)<<" Ω,\t\tϕ = "<<this->getComponentPhi()/M_PI<<(this->getComponentPhi()==0 ? "" : " π" )<<(this->getNested() ? ", nested" :"")<<std::endl;
}

complex<double> resistor::getComponentImp(double w)// get component impedance
{
    return complex<double> (R,0.);
}

double resistor::getComponentPhi() // get component phase shift
{
    return 0.;
}

