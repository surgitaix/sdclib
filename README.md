# SDCLib

## HowTo build

### Essential requirements
- C++ 11 Compiler Support ([Overview](https://en.cppreference.com/w/cpp/compiler_support#cpp11))
- CMake (> 3.5.0), pthread
- Supported Compilers:
    - GCC    ( **4.8.1** )	[full C++11 support](https://gcc.gnu.org/projects/cxx-status.html#cxx11)
    - Clang  ( **3.3** )  [full C++11 support](http://clang.llvm.org/cxx_status.html#cxx11)
    - MSVC++ ( **18.0** )  [partial C++11 support](https://docs.microsoft.com/en-us/cpp/visual-cpp-language-conformance?view=vs-2017) (**19.0** *or higher recommended*)

### Additional dependecies: 
- XSD, Xerces, OpenSSL  
- Examples for Debian / Ubuntu:  
    - **sudo apt-get install xsdcxx**  
    - **sudo apt-get install libxerces-c-dev**  
    - **sudo apt-get install libssl-dev**  
- Examples for Manjaro:  
    - **pamac install xerces-c**  
    - **pamac install xsd**  
    
<br/>

## Build SDCLib using CMake
####**++ Check the doc/ folder for additional information! ++**
We recommend using CMake GUI to configure and generate the project.  
- **sudo apt-get install cmake-gui**  
For a quick start follow the instructions below to build in source.  

### Generate and build in source
- clone:
    - **git clone** https://github.com/surgitaix/sdclib.git
- navigate to the cloned folder and generate:
	- **cmake .**
- navigate to the build folder and build:
	- **make -j4**  
  
**Note**  
On a Raspberry Pi you might have to lower the number of parallel jobs ( -j ) or just use ***make*** (without args).
  
## Building for non CMake Projects ##
To get all the necessary files to integrate the SDCLib into other projects (without CMake) follow the instructions above, but instead of **make** issue **make install** (with the optional -j parameter).
This will copy the executable files / SDCLibrary and the header files into the folder inside the CMake Variable *CMAKE_INSTALL_PREFIX*. By default this will be **<YOUR_BUILD_FOLDER\>/install**.

## Using the SDCLib inside your project ##
To use the SDCLib inside your project we provide **FindSDCLib.cmake** .  
You can include the following lines inside your CMakeLists file (Change the variables where marked with <...>):
```cmake
###### Set the Search Path - FindSDCLib.cmake requires this variable as "entry point"
set(SDCLib_SEARCH_DIRS "<ABSOLUTE PATH TO SDCLIB FOLDER>" CACHE STRING "SDCLib root dir")
# Add SDCLib modules folder to CMake Modules Path
get_filename_component(PROJECT_CMAKE_MODULES ${SDCLib_SEARCH_DIRS}/cmake/Modules REALPATH)
message(STATUS "Adding ${PROJECT_CMAKE_MODULES} to Modules Path...")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_CMAKE_MODULES})
###### Out of Source build - Set the additional search path manually (dont change build folder later or change this too)
set(SDCLib_EXTERNAL_LIBRARY_DIRS "<ABSOLUTE PATH TO SDCLIB BUILD FOLDER>/bin" CACHE STRING "External Dirs")
find_package(SDCLib)
if(NOT SDCLib_FOUND)
    message(FATAL_ERROR "SDC not found, build it first or specify correct path!")
endif()
```
Hint: Depending on your project structure you can get the absolute file path (cleaned from symbolic links) with the following command and refer to the sdclib root folder like:
```cmake
###### Example where 'dependencies/' is a subfolder inside your projects root folder
get_filename_component(MY_DEPENDENCIES_FOLDER ${CMAKE_CURRENT_LIST_DIR}/dependencies/ REALPATH)
set(SDCLib_SEARCH_DIRS "${MY_DEPENDENCIES_FOLDER}/sdclib" CACHE STRING "SDCLib root dir")
...
```
Note: There may be side effects in using CMAKE_CURRENT_LIST_DIR, so refer to the official CMake documentation [here](https://cmake.org/cmake/help/v3.0/variable/CMAKE_CURRENT_LIST_DIR.html).
  
Use the set SDCLib_XXX Variables with your target:
```cmake
target_include_directories(MyExecutable PRIVATE ${SDCLib_INCLUDE_DIRS})
target_link_libraries(MyExecutable PRIVATE ${SDCLib_LIBRARIES})

```
**Note: You can find a small CMake Project using the SDCLib under Examples/CMakeExample!**
  
## Firewall configuration
Install ufw and open ports:  
- **sudo apt-get install ufw**  
- **sudo ufw allow 3702/udp # discovery**  
- **sudo ufw allow 5555/udp # streaming**  

## Optional dependencies for MdibVisualizer
- graphviz, evince, pdfunite
