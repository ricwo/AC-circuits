# AC Circuits

A C++-based class hierarchy for the simulation of alternating-current circuits is developed. An abstract base class for generic components is used as an interface, from which the physical circuit components (resistors, capacitors and inductors) are derived. A circuit class computes and stores various properties of the whole circuit. Individual-component and whole-circuit phase changes are output, and the user is able to create their own circuit, with an arbitrary number of components, connected in series or parallel. A simple console output for an ASCII-based plotting method for phasor diagrams is developed. The addition of lossy components is introduced. Recursive definitions to account for nested circuits are implemented. The successful operation of the code is demonstrated using a simple three-component serial circuit.

## Author

Ricardo Wolker
