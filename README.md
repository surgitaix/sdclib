# SDCLib

## Project status and limitations
SDCLib/C originated in several publicly funded research projects. We are happy to keep it available for the community, but please be aware of the following before you start using it:

- **No longer maintained:** There will be no further development, bug fixes or security updates. Issues and pull requests will not be processed.
- **Not interoperable with other SDC implementations:** Core features such as the **Eventing Service are not compatible** with other IEEE 11073 SDC implementations. Interoperability in mixed SDC networks can therefore not be expected.
- **Incomplete feature set:** SDCLib/C covers only a **subset** of the IEEE 11073 SDC standard family. Many features required for real-world devices are not implemented.
- **Not intended for medical devices:** The library was not developed under a medical device quality management system (e.g. IEC 62304 / ISO 13485) and must not be used in medical products.

**Suitable for:** academic research, teaching, and getting a first hands-on impression of SDC.

**Not suitable for:** commercial products, medical devices, or any production environment.

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

## Commercial use: sdcX
If you are developing a commercial product or a medical device, please use **sdcX**, our actively maintained, closed-source IEEE 11073 SDC stack. sdcX offers broad coverage of the SDC standard family, interoperability with other SDC implementations and documentation suited for regulatory submissions. More information: [https://surgitaix.com/wordpress/sdcx-softwarebibliothek/](https://surgitaix.com/wordpress/sdcx-softwarebibliothek/)
