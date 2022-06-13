# SDCLib

## Essential requirements
### C++ Compiler
- C++ 11 Compiler Support ([Overview](https://en.cppreference.com/w/cpp/compiler_support#cpp11))
- CMake (> 3.5.0), pthread

### Dependecies:  
- XSDCXX  
- xerces-c  
- OpenSSL  

## Docs
### Check the [doc](doc/) folder for further information!
#### You can find a dummy CMake Project [here](Examples/CMakeExample)!
  
## Firewall configuration
#### Consumer / Provider need network access to find each other and communicate.  
- 3702 UDP: discovery  
- 5555 UDP: streaming  
- Random (free system assigned) TCP: Unicast traffic  

### Optional dependencies for Advanced Examples
- asio (included as git submodule: see [doc](doc/) folder for further information).

### Optional dependencies for MdibVisualizer
- graphviz, evince, pdfunite

## Commercial version
The SDCLib/C is an outcome of several research projects. If you are looking for a commercial IEEE 11073 SDC implementation please contact us for our closed source stack. More information: https://surgitaix.com/wp/services-2/#/integrationservices
