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
####***Note:*** on Ubuntu 18.04 and higher libxerces-c version has changed to 3.2:
 -- sudo apt-get install libxerces-c3.2

## Build SDCLib using CMAKE
- Example (Linux):
 - cmake .
 - make -j 4

##### Note: On a Raspberry Pi you have to lower the number of parallel jobs (-j) or just use ***make*** without arguments.

### Examples and Tests
See the 'Examples' and 'Tests' folders for example implementations.

Run './UnitTests' for running  OSCP related tests.

## Firewall configuration
Install ufw and open ports:

- sudo apt-get install ufw
- sudo ufw allow 3702/udp # discovery
- sudo ufw allow 5555/udp # streaming

## Optional dependencies for MdibVisualizer
- graphviz, evince, pdfunite
