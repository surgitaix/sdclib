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
    - **sudo apt-get install xsdcxx**  
    - **sudo apt-get install libxerces-c-dev**  
    - **sudo apt-get install libxerces-c3.1**  

##### ***Note:*** on Ubuntu 18.04 and higher libxerces-c version has changed to 3.2:  
- **sudo apt-get install libxerces-c3.2**  

## Build SDCLib using CMAKE
We recommend using CMake GUI to configure and generate the project.  
- **sudo apt-get install cmake-gui**  
  
(Hint: Select the "Grouped" checkbox to group name related variables together in a tree view structure)

### Steps to Generate the Project (in source) ###
(*Note: We recommend using out of source build as described below!*)  
- clone this project:  
    - **git clone** https://github.com/surgitaix/sdclib.git  
- navigate to the source directory:  
    - **cmake .**

### Steps to Generate the Project (out of source) ###
(Steps with cmake-gui!)
- clone this project:  
    - **git clone** https://github.com/surgitaix/sdclib.git  
- Open cmake gui.  
- Browse Source... -> select the cloned folder (default should be this projects name: *sdclib*)  
- Browse Build... -> select **another** folder (e.g. *sdclib_build*)  
- Click Configure: You will be asked a few questions, like if you want to generate the folder if it does not exist etc.  
- You will most likely see a Warning (red text): It tells you that it could not find the sdclib (yet) and that you can add the given variable for out of source builds to specify its location.  
To add this variable click the button 'Add Entry', copy the given variable ( *SDCLib_ADDITIONAL_LIBRARY_DIRS* ), select Type PATH. Next a new input will appear, click on the [...] button and navigate to the build folder (e.g.: *sdclib_build*. Search for the bin folder inside and select it. This way you tell the script where it can find the sdclib binaries later.  
- Configure and Generate again. The new variable will be hightlighted by cmake.  
NOTE: The Warning wont disappear unless you finally built the library.  
- Your project should now be generated inside the selected build folder.

### Using the SDCLib inside your project ###
To use the SDCLib inside your project we provide **FindSDCLib.cmake** .  
You can include the following lines inside your CMakeLists file (Change the variables where marked with <...>):
```cmake
###### Set the Search Path - FindSDCLib.cmake requires this variable as "entry point"
set(SDCLib_SEARCH_DIRS "<ABSOLUTE PATH TO SDCLIB FOLDER>" CACHE STRING "SDCLib root dir")
###### Out of Source build - The the additional search path manually (dont change build folder later or change this too)
set(SDCLib_ADDITIONAL_LIBRARY_DIRS "<ABSOLUTE PATH TO SDCLIB BUILD FOLDER>/bin" CACHE STRING "Additional Dirs")
include(${SDCLib_SEARCH_DIRS}/FindSDCLib.cmake)
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
Note: There may be side effects in using CMAKE_CURRENT_LIST_DIR, so refer to the official cmake documentation [here](https://cmake.org/cmake/help/v3.0/variable/CMAKE_CURRENT_LIST_DIR.html).
  
You can link to the SDCLib by using:
```cmake
target_link_libraries(MyExecutable PRIVATE ${SDCLib_LIBRARIES})
```
### Further configuration ###
#### BuildType ####
The Buildtype is controlled by CMAKE_BUILD_TYPE and defaults to Debug. If you want to change it, you can either do this inside the gui before calling configure/generate or pass it via the command line e.g.:
- cmake -DCMAKE_BUILD_TYPE=Release
#### Examples and Tests ####
Examples and Tests are built by default. If you dont want to built them, you can set the option to *OFF* before building.
- SDC_EXAMPLES [*ON/OFF*]
- SDC_TESTS [*ON/OFF*]  
  
See the 'Examples' and 'Tests' folders for example implementations.  
To run OSCP related tests run './UnitTests'.

### Building the Project ###
To build the project navigate to the build folder and enter:  
- **make**
  
You can specify the number of parallel **jobs** with **j** (The following command uses 4 parallel jobs):
- **make -j4**  
#### Note: On a Raspberry Pi you have to lower the number of parallel jobs ( -j ) or just use ***make*** without arguments. ####

## Firewall configuration
Install ufw and open ports:  
- **sudo apt-get install ufw**  
- **sudo ufw allow 3702/udp # discovery**  
- **sudo ufw allow 5555/udp # streaming**  

## Optional dependencies for MdibVisualizer
- graphviz, evince, pdfunite
