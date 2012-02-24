

SetCompressor lzma


;--------------------------------

; The name of the installer
Name "pUML Windows Installer"

; The file to write
OutFile "pUMLsetup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\pUML\

; The text to prompt the user to enter a directory
DirText "This will install pUML on your computer. Choose a directory"

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

; Set output path to the installation directory.
SetOutPath $INSTDIR

; Put files there
File pUML.exe
File pUML.ico
File libgcc_s_dw2-1.dll
File mingwm10.dll
File QtCore4.dll
File QtGui4.dll

; Tell the compiler to write an uninstaller and to look for a "Uninstall" section
WriteUninstaller $INSTDIR\Uninstall.exe

; Now create shortcuts
CreateShortCut "$SMPROGRAMS\pUML.lnk" "$INSTDIR\pUML.exe" $INSTDIR\pUML.ico


SectionEnd ; end the section

; The uninstall section
Section "Uninstall"

Delete $INSTDIR\Uninstall.exe
Delete $INSTDIR\pUML.exe
Delete $INSTDIR\libgcc_s_dw2-1.dll
Delete $INSTDIR\mingwm10.dll
Delete $INSTDIR\QtCore4.dll
Delete $INSTDIR\QtGui4.dll
RMDir $INSTDIR

; Now remove shortcuts too
Delete "$SMPROGRAMS\pUML.lnk"

SectionEnd 