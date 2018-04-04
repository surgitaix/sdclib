# SDCLib

## HowTo build

### Essential requirements
- Linux: GCC (> 4.8), pthread, Cmake (> 2.8)
- Supported compilers: GCC, LLVM, MSVC++

### Additional dependecies: 
- XSD, Xerces
- Examples for Debian / Ubuntu:
 - sudo apt-get install xsdcxx
 - sudo apt-get install libxerces-c3.1
 - sudo apt-get install libxerces-c-dev

## Build SDCLib using CMAKE
- Example (Linux):
 - cmake .
 - make -j 4

See the 'Examples' and 'Tests' folders for example implementations.
Run './UnitTests' for running  OSCP related tests.

## Optional dependencies for MdibVisualizer 
- graphviz, evince, pdfunite
