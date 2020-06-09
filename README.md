# SDCLib

## Essential requirements
### C++ Compiler
- C++ 11 Compiler Support ([Overview](https://en.cppreference.com/w/cpp/compiler_support#cpp11))
- CMake (> 3.5.0), pthread
- Supported Compilers:  
    - GCC    ( **4.8.1** )	[full C++11 support](https://gcc.gnu.org/projects/cxx-status.html#cxx11)
    - Clang  ( **3.3** )  [full C++11 support](http://clang.llvm.org/cxx_status.html#cxx11)
    - MSVC++ ( **18.0** )  [partial C++11 support](https://docs.microsoft.com/en-us/cpp/visual-cpp-language-conformance?view=vs-2017) (**19.0** *or higher recommended*)

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
