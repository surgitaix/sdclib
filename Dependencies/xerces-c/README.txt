
#######################################################################
# Linux
#######################################################################
Use your package manager:

# Ubuntu, Kubuntu, ...
sudo apt-get install libxerces-c-dev

# Manjaro [UNTESTED]
pamac install xerces-c

[...]

#######################################################################
# Windows
#######################################################################

Execute the xerces_Win32.bat script.
It will clone xerces-c repository and configure
cmake to create a Win32 solution file.

After that open the solution file: xerces-c.sln
and build:
Lirary
 - xerces-c

in Debug / Release mode.

NOTE: SDCLib Applications will need the built xerces DLL. Either copy them to your
system folder or to the binary directory next to your executables.

Proceeed to generate the SDCLib via cmake or cmake-gui (recommended).