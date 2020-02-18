#!/bin/sh
echo "//********************************//"
echo "Visualizing MDIBs of all SDCProviders in the network."
echo "   "
echo "To install dependencies: sudo apt-get install graphviz, pdfunite, evince"
echo "//********************************//"
echo "   "
echo "   "
./MDIBVisualizer
mkdir -p MdibVisualizer_files
ls *.dot | xargs -I {} dot -Tpdf {} -o MdibVisualizer_files/{}.pdf
mv *.dot MdibVisualizer_files/
rm MdibVisualizer_files/VisualizedMdibs.pdf
pdfunite MdibVisualizer_files/*.pdf MdibVisualizer_files/VisualizedMdibs.pdf
evince MdibVisualizer_files/VisualizedMdibs.pdf

