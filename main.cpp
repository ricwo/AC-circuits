//
//  main.cpp
//  AC Circuits Project
//
//  Created by Ricardo Wölker on 27/03/2017.
//

#include <iostream>
#include "circuit.h"
#include <vector>
#include <math.h>

using namespace std;

int main() {
    
    // let's create our circuit c1 using a smart shared pointer
    cout << "We're creating a big nested circuit out of nine components:\nshared_ptr<circuit> c1 ( new circuit() );" << endl;
    shared_ptr<circuit> c1 ( new circuit() ); // create c1 with the default constructor
    cout << "c1->addComp('resistor', 0.3, 0, 's'); ( and many more... )\n";
    c1->addComp("resistor", 10e2, 0, 's',false);
    c1->addComp("capacitor", 0.92e-12,3.2, 's',false);
    c1->addComp("inductor", 9.3e-3, 1.8, 's',false);
    c1->addComp("inductor", 2.0e-2, 2.3, 'p', true); // start nested circuit
    c1->addComp("resistor", 10, 0, 's', true); // end nested circuit
    c1->addComp("inductor", 0.2e-2, 0.8, 's',false);
    c1->addComp("capacitor", 0.99e-12,2.9, 'p',false);
    c1->addComp("inductor", 9.24e-2,100, 's',false);
    c1->addComp("inductor", 2.12e-7,100, 's',false);
    c1->setF(50); // set the frequency of the circuit
    c1->computeQ();
    c1->computeZ();
    
    // Demonstrate << overloading
    cout << "Demonstrate << overloading: cout << *c1\n\n" << *c1 << endl;
    
    // Show phasor diagram printing function
    c1->plotPhasorDiagram();
    
    cout << "###############################################################################" << endl <<
    "###############################################################################" << endl <<
    "###############################################################################" << endl << endl;
    
    cout << "\n\nNow we're creating a test circuit, consisting of three components in series\nshared_ptr<circuit> c2 ( new circuit() );\nc2->addComp('resistor', 1e3, 0, 's',false);\nc2->addComp('capacitor', 0.1e-3,0, 's',false);\nc2->addComp('inductor', 5, 0, 's',false);\nc2->computeZ();\nc2->plotPhasorDiagram();\n";
    shared_ptr<circuit> c2 ( new circuit() ); // create c1 with the default constructor
    c2->addComp("resistor", 1e3, 0, 's',false); // check that first component is in series!!!
    c2->addComp("capacitor", 0.1e-3,0, 's',false);
    c2->addComp("inductor", 5, 0, 's',false);
    c2->computeZ();
    cout << *c2 << endl;
    c2->plotPhasorDiagram();

    
    // Let user create their own circuit
    cout << "###############################################################################" << endl <<
            "###############################################################################" << endl <<
    "###############################################################################" << endl << endl;
    cout << "You will now create your own circuit: ";
    cout << "shared_ptr<circuit> userCircuit ( new circuit() );"<<endl;
    shared_ptr<circuit> userCircuit ( new circuit() );
    
    cout << "Enter the circuit's AC frequency in Hz:\n"; // ask for s or p connection
    string inputFreq; // pointer to char to store input frequency
    bool freqIn = true;
    while(freqIn){
        getline(std::cin, inputFreq); // cin user answer
        if( std::atof(inputFreq.c_str()) > 0) {
            cout << "Your frequency was stored.\n";
            freqIn = false;
        }
        else { cerr << "Input invalid, must be a double > 0. Try again.\n"; }
    }
    userCircuit->setF(std::atof(inputFreq.c_str())); // set the circuit's frequency
    
    do{
        cin.clear(); // flush the cin buffer
        cout << "What component would you like to add? Type resistor, capacitor or inductor. Type q if you want to finish.\n"; // prompt uswer
        string inputChoice;
        string compName = ""; // string to hold type of component
        string compVal = ""; // string to hold the component's defining value
        double compValDouble = 0;
        bool good = true; // define a Boolean that keeps the loop alive
        while(good) {
            getline(cin, inputChoice);// let user input value
            if (inputChoice == "inductor" ) {
                cout<< "Enter the inductance in mH:\n";
                getline(cin, compVal);
                if( atof(compVal.c_str()) <= 0){
                    cout<< "You must enter a non-negative value. Try again.\n";
                    cout << "What component would you like to add? Type resistor, capacitor or inductor. Type q if you want to finish.\n"; // prompt answer
                    good = true;
                }
                else good = false;
                compValDouble = std::atof(compVal.c_str());
                compValDouble /= 1.0e3;
            }
            else if (inputChoice == "resistor") {
                cout<< "Enter the resistance in kΩ:\n";
                getline(cin, compVal);
                if( atof(compVal.c_str()) <= 0){
                    cout<< "You must enter a non-negative value. Try again.\n";
                    cout << "What component would you like to add? Type resistor, capacitor or inductor. Type q if you want to finish.\n"; // prompt answer
                    good = true;
                }
                else good = false;
                compValDouble = std::atof(compVal.c_str());
                compValDouble *= 1.0e3;
            }
            else if (inputChoice == "capacitor" ) {
                cout<< "Enter the capacitance in pF:\n";;
                getline(cin, compVal);
                if( atof(compVal.c_str()) <= 0){
                    cout<< "You must enter a non-negative value. Try again.\n";
                    cout << "What component would you like to add? Type resistor, capacitor or inductor. Type q if you want to finish.\n"; // prompt answer
                    good = true;
                }
                good = false;
                compValDouble = std::atof(compVal.c_str());
                compValDouble /= 1.0e12;
            }
            else if (inputChoice== "q") break; // Exit if user types q
            else { cerr << "Input invalid. You must type inductor, resistor or capacitor. Try again.\n"; }
        }
        if (inputChoice == "q") break;
        cout << "Type s for a serial connection or p for a parallel connection of this component:\n"; // ask for s or p connection
        string connectionChoice; // char for user answer
        bool connIn = true;
        while(connIn){
            getline(std::cin, connectionChoice); // cin user answer
            if( connectionChoice.size() == 1 && (connectionChoice[0]=='s' || connectionChoice[0]=='p') ) {
                cout << "Your connection type was accepted.\n";
                connIn = false;
            }
            else { cerr << "Input invalid, you must enter s or p. Try again.\n"; }
        }
        cout << "Please enter the quality factor of this component (must be greater than or equal to 0, 0 = lossless):\n"; // ask for s or p connection
        string qChoice; // char for user answer
        bool qIn = true;
        while(qIn){
            getline(std::cin, qChoice); // cin user answer
            if( std::atof(qChoice.c_str()) >= 0 ) {
                cout << "Your quality factor type was accepted.\n";
                qIn = false;
            }
            else { cerr << "Input invalid, your quality factor must be a double greater than or equal to zero. Try again.\n"; }
        }
        cout << "Please enter wheter you would like to nest this component or not. Type y for yes and n for no:\n"; // ask for s or p connection
        string nestChoice; // char for user answer
        bool nestBool = false;
        bool nestIn = true;
        while(nestIn){
            getline(std::cin, nestChoice); // cin user answer
            if( nestChoice == "y") {
                cout << "Your nesting factor type was accepted.\n";
                nestIn = false;
                nestBool = true;
            }
            else if (  nestChoice == "n" ){
                cout << "Your nesting factor type was accepted.\n";
                nestIn = false;
            }
            else { cerr << "Input invalid, nesting choice must be y or n. Try again.\n"; }
        }
        userCircuit->addComp(inputChoice, compValDouble, std::atof(qChoice.c_str()), connectionChoice[0], nestBool); // create component using the addComp function
    } while(true);
    
    cout << "We'll compute your circuit's impedance now: userCircuit->computeZ()\n";
    userCircuit->computeZ(); // compute the circuit's impedance
    cout << userCircuit->getZ() << endl;
    cout << endl << *userCircuit << endl; // Print out the user circuit
    
    
//    cout << "Demonstrate copy assignment: shared_ptr<circuit> c2(c1): ";
//    shared_ptr<circuit> c2(c1);
//    cout << "cout << *c2\n" << *c2 << endl;
//    
//    cout << "Demonstrate move assignment: c3 = move(c2): ";
//    circuit c3;
//    c3 = move(*c2);
//    cout << "cout << c3\n" << c3 << endl;
//    
//    cout << "\nWhich means c2 is empty: cout << *c2\n";
//    cout << *c2 << endl;
    
    return 0;
}
