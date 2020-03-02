@ECHO OFF

:: Clone xerces to defined folder
SET XERCES_FOLDER=xerces-c

git.exe clone https://github.com/apache/xerces-c.git %XERCES_FOLDER%

cd %XERCES_FOLDER%

cmake -A x64 .