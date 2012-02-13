Requirements (Linux):
 - Qt 4.7.4
 - g++
Requirements (Windows):
 - Qt 4.7.4
 - Visual Studio 2008 (MinGW is untested)
 - QtCreator

How to compile on Linux:
 - Pull down a fresh copy of the repository
 - Delete any Makefile in the src directory
 - run "qmake pUML.pro"
 - run "./pUMLTest2"
 - ???
 - Profit

How to compile on Windows:
 - Have Qt Creator installed with the VC++ configured
 - Pull down a fresh copy of the repository
 - Delete any Makefile in the src directory
 - Open up the project from Creator by opening pUML.pro
 - Click run
 - ???
 - Profit


Don't add your Makefile, pUML.pro.user file, or your build directory 
to the repository, they are specific to your computer.


