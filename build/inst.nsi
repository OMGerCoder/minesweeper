Name "Minesweeper"
OutFile "Minesweeper_setup.exe"
InstallDir $DESKTOP\Minesweeper
RequestExecutionLevel user
Section
SetOutPath $INSTDIR
File Game.exe
CreateDirectory "$INSTDIR\resources"
SetOutPath $INSTDIR\resources
File /r "resources\*.*"
SetOutPath $INSTDIR
WriteUninstaller $INSTDIR\uninstaller.exe
SectionEnd
Section "Uninstall"
Delete $INSTDIR\Game.exe
RMDir /r $INSTDIR\resources
Delete $INSTDIR\uninstaller.exe
RMDir $INSTDIR
SectionEnd