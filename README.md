# SDCLib

## HowTo build

### Essential requirements
- C++ 11 Compiler Support ([Overview](https://en.cppreference.com/w/cpp/compiler_support#cpp11))
- Cmake (> 3.5.0), pthread
- Supported Compilers:
    - GCC    ( **4.8.1** )	[full C++11 support](https://gcc.gnu.org/projects/cxx-status.html#cxx11)
    - Clang  ( **3.3** )  [full C++11 support](http://clang.llvm.org/cxx_status.html#cxx11)
    - MSVC++ ( **18.0** )  [partial C++11 support](https://docs.microsoft.com/en-us/cpp/visual-cpp-language-conformance?view=vs-2017) (**19.0** *or higher recommended*)

### Additional dependecies: 
- XSD, Xerces
- Examples for Debian / Ubuntu:
    - sudo apt-get install xsdcxx
    - sudo apt-get install libxerces-c-dev
    - sudo apt-get install libxerces-c3.1

##### ***Note:*** on Ubuntu 18.04 and higher libxerces-c version has changed to 3.2:
- sudo apt-get install libxerces-c3.2

## Build SDCLib using CMAKE
- Example (Linux):
    - cmake .
    - make -j 4

##### Note: On a Raspberry Pi you have to lower the number of parallel jobs ( -j ) or just use ***make*** without arguments.

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
