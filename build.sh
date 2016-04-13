#!/bin/bash

# Build datamodel, code and osclib
# Requires gcc, cmake, sed, doxygen, xsdcxx

# generate schema
cd datamodel
./build.sh
cd ..

# generate wrapper code
cd codegenerator
./build.sh
cd ..

# generate doxygen
doxygen
rm doc/doxygen_sqlite3.db

# build osclib
cmake .
make -j 4

