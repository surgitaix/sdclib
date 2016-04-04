#!/bin/bash

# Build and run osclib, osclib4java and unit tests
# Requires git, swig3.0, java sdk, gcc, cmake, sed, doxygen, xsdcxx

if [ "$1" != "" ]; then
    BRANCH=$1
else
    BRANCH="master"
fi

echo "Using branch $BRANCH"

# clean old
rm -rf osclib
rm -rf osclib4java
rm -rf cmake-osclib
rm -rf cmake-osclib4java

# clone repositories
git clone http://git.ornet.org/bestingandreas/osclib.git
git clone http://git.ornet.org/bestingandreas/osclib4java.git

# switch to branch
cd osclib
git checkout $BRANCH
cd ..

cd osclib4java
git checkout $BRANCH
cd ..

# generate schema
cd osclib/datamodel
./build.sh
cd ../..

# generate wrapper code
cd osclib/codegenerator
./build.sh
cd ../..

# generate doxygen
cd osclib
doxygen
rm doc/doxygen_sqlite3.db
cd ..

# create swig wrappers for java
cd osclib/swig
swig3.0 -outdir ../../osclib4java/OSCLib/src/osclib -c++ -java -package osclib OSCLibJava.i
cd ../..

# apply patch to wrappers for java
# OSCLibJNI.java
sed -i "s/  static {/static {NativeUtils.initNative\(\)\;/g" ./osclib4java/OSCLib/src/osclib/OSCLibJNI.java
# OSCPConsumer.java
sed -i "s/package osclib;/package osclib ;import java.util.HashSet;/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/  private boolean swigCMemOwn;/  private boolean swigCMemOwn ;private HashSet<Object> references = new HashSet<Object>(); private Object contextChangedHandler;/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/    delete();/    delete() ;references.clear();/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ registerStateEventHandler(OSCPConsumerEventHandler handler, AbstractState out) {/ registerStateEventHandler(OSCPConsumerEventHandler handler, AbstractState out)  {references.add(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ registerStateEventHandler(OSCPConsumerEventHandler handler) {/ registerStateEventHandler(OSCPConsumerEventHandler handler)  {references.add(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ unregisterStateEventHandler(OSCPConsumerEventHandler handler) {/ unregisterStateEventHandler(OSCPConsumerEventHandler handler)  {references.remove(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ setConnectionLostHandler(OSCPConsumerConnectionLostHandler handler) {/ setConnectionLostHandler(OSCPConsumerConnectionLostHandler handler)  {references.add(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler handler) {/ setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler handler)  {references.add(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
sed -i "s/ setContextStateChangedHandler(OSCPConsumerContextStateChangedHandler handler) {/ setContextStateChangedHandler(OSCPConsumerContextStateChangedHandler handler)  {contextChangedHandler = handler;/g" ./osclib4java/OSCLib/src/osclib/OSCPConsumer.java
# OSCPProvider.java
sed -i "s/package osclib;/package osclib ;import java.util.HashSet;/g" ./osclib4java/OSCLib/src/osclib/OSCPProvider.java
sed -i "s/  protected boolean swigCMemOwn;/  protected boolean swigCMemOwn ;private HashSet<Object> references = new HashSet<Object>();/g" ./osclib4java/OSCLib/src/osclib/OSCPProvider.java
sed -i "s/    delete();/    delete() ;references.clear();/g" ./osclib4java/OSCLib/src/osclib/OSCPProvider.java
sed -i "s/ addMDStateHandler(OSCPProviderMDStateHandler handler) {/ addMDStateHandler(OSCPProviderMDStateHandler handler)  {references.add(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPProvider.java
sed -i "s/ removeMDStateHandler(OSCPProviderMDStateHandler handler) {/ removeMDStateHandler(OSCPProviderMDStateHandler handler)  {references.remove(handler);/g" ./osclib4java/OSCLib/src/osclib/OSCPProvider.java

# create cmake build directories
mkdir cmake-osclib
mkdir cmake-osclib4java

# build osclib
cd cmake-osclib
cmake ../osclib/ -Djava=On
make -j 8
cd ..

# copy created lib to osclib4java
cp cmake-osclib/libOSCLib.so ./osclib4java/OSCLib/src/libs/

# edit nativelibs.txt
echo "/libs/libOSCLib.so" > ./osclib4java/OSCLib/src/nativelibs.txt

# build java wrappers
cd cmake-osclib4java
cmake ../osclib4java/OSCLib
make
cd ..

