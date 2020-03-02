
#######################################################################
# Linux
#######################################################################
Use your package manager:

# Ubuntu, Kubuntu, ...
sudo apt-get install xsdcxx

# Manjaro [UNTESTED]
pamac install xsd

[...]

#######################################################################
# Windows
#######################################################################

Download XSDCXX from official CodeSynthesis homepage:

-> Download the .zip file https://www.codesynthesis.com/download/xsd/4.0/windows/i686/xsd-4.0.0-i686-windows.zip
and extract it into this folder.

It now should contain a folder called "xsd-4.0.0-i686-windows".
Required xsd files reside inside xsd-4.0.0-i686-windows/libxsd
and are detected by SDC_XSD.cmake script and added to the project.

Proceeed to generate the SDCLib via cmake or cmake-gui (recommended).