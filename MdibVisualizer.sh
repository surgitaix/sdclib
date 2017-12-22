#!/bin/sh
./MDIBVisualizer
mkdir -p MdibVisualizer_files
ls *.dot | xargs -I {} dot -Tpdf {} -o MdibVisualizer_files/{}.pdf
mv *.dot MdibVisualizer_files/
pdfunite MdibVisualizer_files/*.pdf MdibVisualizer_files/VisualizedMdibs.pdf
evince MdibVisualizer_files/VisualizedMdibs.pdf

