#!/bin/bash
python pyCodeGen.py
gsl complexTypesGSLformated.xml
mv *.h ../include/OSCLib/Data/OSCP/MDIB/
mv *.cpp ../src/Data/OSCP/MDIB/
# generate CMakeLists.txt block
echo "Generating the block to add in CMakeLists.txt.."
rm CMakeLists_ToAdd.txt
FILES=../src/Data/OSCP/MDIB/*
for f in $FILES
do
  if ! [ "$f" == "../src/Data/OSCP/MDIB/custom" ]; then
    echo "Processing $f file..."
    echo $f | cut -c 2- >> CMakeLists_ToAdd.txt
  fi
done
FILES=../src/Data/OSCP/MDIB/custom/*
for f in $FILES
do
  echo "Processing $f file..."
  echo $f | cut -c 2- >> CMakeLists_ToAdd.txt
done
echo " "
echo "Do not forget to add the content of CMakeLists_ToAdd.txt to CMakeLists.txt!"
echo " "
