Requirements (Linux):
 - Qt 4.7.4 (qmake must be in PATH)
 - g++
Requirements (Windows):
 - Qt 4.7.4
 - Visual Studio 2008 (MinGW is untested)
 - QtCreator

How to compile on Linux:
 - Pull down a fresh copy of the repository
 - Delete any Makefile in the src directory
 - run "qmake pUML.pro"
 - run "make"
 - run "./pUML"
 - ???
 - Profit

How to compile on Windows:
 - Have Qt Creator installed with the VC++ compiler configured
 - Pull down a fresh copy of the repository
 - Delete any .pro.user files
 - Open up the project from Creator by opening pUML.pro
 - Select the default build options
 - Click run
 - ???
 - Profit


Don't add your Makefile, pUML.pro.user file, or your build directory 
to the repository, they are specific to your computer. And remember 
to run "make --clean" on linux to clean up the src folder after compiling.

General Troubleshooting:
 - If you run into any undefined reference to vtable errors, try running qmake again. This happens when all the moc files aren't properly generated.

