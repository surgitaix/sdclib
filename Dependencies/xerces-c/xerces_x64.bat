@ECHO OFF

:: Clone xerces to defined folder
SET XERCES_FOLDER=xerces-c

:: Clone explicit version branch
git.exe clone -b xerces-3.2.0 --depth 1 https://github.com/apache/xerces-c.git %XERCES_FOLDER%

cd %XERCES_FOLDER%

cmake -A x64 .
