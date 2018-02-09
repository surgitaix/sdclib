#!/bin/bash
# save hand-edited files for replacing them later
mkdir backup
mkdir backup/src
mv ../src/Data/OSCP/MDIB/ConvertToCDM.cpp ./backup/src
mv ../src/Data/OSCP/MDIB/Defaults.cpp ./backup/src
mv ../src/Data/OSCP/MDIB/InstanceIdentifier.cpp ./backup/src
mv ../src/Data/OSCP/MDIB/OperatingJurisdiction.cpp ./backup/src
mv ../src/Data/OSCP/MDIB/OperationGroup.cpp ./backup/src
mv ../src/Data/OSCP/MDIB/ScoState.cpp ./backup/src
mv ../include/OSCLib/Data/OSCP/MDIB/ConvertToCDM.h ./backup
mv ../include/OSCLib/Data/OSCP/MDIB/MdState.h ./backup
mv ../include/OSCLib/Data/OSCP/MDIB/MdDescription.h ./backup

# generate files
python pyCodeGen.py
gsl complexTypesGSLformated.xml
# move them to the right directories
rm ../include/OSCLib/Data/OSCP/MDIB/*.h
rm ../src/Data/OSCP/MDIB/*.cpp
mv *.h ../include/OSCLib/Data/OSCP/MDIB/
mv *.cpp ../src/Data/OSCP/MDIB/
# replace the customized ones
mv ./backup/src/* ../src/Data/OSCP/MDIB/
mv  ./backup/ConvertToCDM.h ../include/OSCLib/Data/OSCP/MDIB/
mv  ./backup/MdState.h ../include/OSCLib/Data/OSCP/MDIB/
mv  ./backup/MdDescription.h ../include/OSCLib/Data/OSCP/MDIB/
rm -rf backup

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
