# Steps to generate install .exe #

1) Download NSIS http://nsis.sourceforge.net/Download.

2) Build pUML through Qt using whatever version, mine was Qt 4.8.0 for Desktop - MinGW (Qt SDK) Release.

3) Find the pUML.exe your build created and copy it to src/install.

4) Right click pUML.nsi and select "Compile NSIS Script".

5) There should now be a pUMLsetup.exe in the install folder.

