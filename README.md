# OSCLib (dev - unstable)

## HowTo build

### Essential requirements
- GCC, pthread
- Supported compilers: GCC, LLVM, MSVC++

### Additional dependecies: 
- XSD, Xerces
- Examples for Ubuntu:
 - audo apt-get install xsdcxx
 - audo apt-get install libxerces-c3.1
 - audo apt-get install libxerces-c-dev

## Build OSCLib using CMAKE
- Example:
 - cmake .
 - make -j 4

See the 'Examples' and 'Tests' folders for example implementations.
Run './UnitTests' for testing OSCP related tests.
