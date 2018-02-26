#!/bin/bash
# save hand-edited files for replacing them later
mkdir backup
mkdir backup/src
mv ../src/Data/SDC/MDIB/ConvertToCDM.cpp ./backup/src
mv ../src/Data/SDC/MDIB/Defaults.cpp ./backup/src
mv ../src/Data/SDC/MDIB/InstanceIdentifier.cpp ./backup/src
mv ../src/Data/SDC/MDIB/OperatingJurisdiction.cpp ./backup/src
mv ../src/Data/SDC/MDIB/OperationGroup.cpp ./backup/src
mv ../src/Data/SDC/MDIB/ScoState.cpp ./backup/src
mv ../include/OSCLib/Data/SDC/MDIB/ConvertToCDM.h ./backup
mv ../include/OSCLib/Data/SDC/MDIB/MdState.h ./backup
mv ../include/OSCLib/Data/SDC/MDIB/MdDescription.h ./backup

# generate files
python pyCodeGen.py
gsl complexTypesGSLformated.xml
# move them to the right directories
rm ../include/OSCLib/Data/SDC/MDIB/*.h
rm ../src/Data/SDC/MDIB/*.cpp
mv *.h ../include/OSCLib/Data/SDC/MDIB/
mv *.cpp ../src/Data/SDC/MDIB/
# replace the customized ones
mv ./backup/src/* ../src/Data/SDC/MDIB/
mv  ./backup/ConvertToCDM.h ../include/OSCLib/Data/SDC/MDIB/
mv  ./backup/MdState.h ../include/OSCLib/Data/SDC/MDIB/
mv  ./backup/MdDescription.h ../include/OSCLib/Data/SDC/MDIB/
rm -rf backup

# generate CMakeLists.txt block
echo "Generating the block to add in CMakeLists.txt.."
rm CMakeLists_ToAdd.txt
FILES=../src/Data/SDC/MDIB/*
for f in $FILES
do
  if ! [ "$f" == "../src/Data/SDC/MDIB/custom" ]; then
    echo "Processing $f file..."
    echo $f | cut -c 2- >> CMakeLists_ToAdd.txt
  fi
done
FILES=../src/Data/SDC/MDIB/custom/*
for f in $FILES
do
  echo "Processing $f file..."
  echo $f | cut -c 2- >> CMakeLists_ToAdd.txt
done
echo " "
echo "Do not forget to add the content of CMakeLists_ToAdd.txt to CMakeLists.txt!"
echo " "
