!include MUI2.nsh
!include "nsDialogs.nsh"
Name "Minesweeper"
OutFile "dist\Minesweeper_setup.exe"
InstallDir $DESKTOP\Minesweeper
RequestExecutionLevel user
!define MUI_FINISHPAGE_RUN_TEXT "Run Minesweeper"
!define MUI_FINISHPAGE_RUN_CHECKBOX

; -- Specify the program to run (change it to your actual program)
!define MUI_FINISHPAGE_RUN "$INSTDIR\Game.exe"
!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_LANGUAGE "English"
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