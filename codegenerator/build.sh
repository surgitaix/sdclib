#!/bin/bash

# Some variables

INCLUDE_DIR="../include/SDCLib/Data/SDC/MDIB/"
SRC_DIR="../src/SDCLib/Data/SDC/MDIB/"


rm -rf BACK_ROOT
BACKUP_ROOT="backup/"
BACKUP_INCLUDE="backup/include/"
BACKUP_SRC="backup/src/"

# Some classes need to be customized: Save them and move them back later

# Create backup folder structure
mkdir $BACKUP_ROOT
mkdir $BACKUP_SRC
mkdir $BACKUP_INCLUDE
# Save customized files
# Source Files
yes | cp -f $SRC_DIR/ConvertToCDM.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/Defaults.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/InstanceIdentifier.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/OperatingJurisdiction.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/OperationGroup.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/ScoState.cpp $BACKUP_SRC
yes | cp -f $SRC_DIR/Relation.cpp $BACKUP_SRC
# ...
# Header Files
yes | cp -f $INCLUDE_DIR/ConvertToCDM.h $BACKUP_INCLUDE
# ...

# MAIN GENERATION PROCESS

# generate files
python pyCodeGen.py
gsl complexTypesGSLformated.xml
# move them to the right directories
mv *.h $INCLUDE_DIR/
mv *.cpp $SRC_DIR/

# Move saved files (force copy but keep the old ones)
yes | cp -f $BACKUP_SRC/*.cpp $SRC_DIR/
yes | cp -f $BACKUP_INCLUDE/*.h $INCLUDE_DIR/

echo "Done!"
