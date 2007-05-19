; This file is the NSIS script file. NSIS (Nullsoft Scriptable Install System) is a professional 
;open source system to create Windows installers, and we use it to create a Windows installer
;for SIVP.
;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

  
;--------------------------------
;General

;Name and file
Name "SIVP 0.4.3"
OutFile sivp-0.4.3.exe

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "COPYING"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "SimpChinese"

  LangString NOSCI_MSG ${LANG_ENGLISH} "No Scilab was detected in your system. SIVP needs Scilab to run. Please make sure you have installed Scilab. Continue?"
  LangString NOSCI_MSG ${LANG_SIMPCHINESE} "在系统中没有检测到Scilab，运行SIVP需要先安装Scilab，请确认您是否已经安装了Scilab。继续安装么？"


; The stuff to install
Section "Install section"

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ;ADD YOUR OWN FILES HERE...
  File /r ".\" 
  
  ; Create an item in program menu
  CreateDirectory "$SMPROGRAMS\SIVP-0.4.3\"
  CreateShortCut "$SMPROGRAMS\SIVP-0.4.3\Unintall.lnk" "$INSTDIR\uninstall.exe"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\SIVP\SIVP-0.4.3 "SIVP_PATH" "$INSTDIR"
  
  ;; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SIVP-0.4.3" "DisplayName" "SIVP-0.4.3"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SIVP-0.4.3" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SIVP-0.4.3" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SIVP-0.4.3" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd


Section "Uninstall"  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SIVP-0.4.3"
  DeleteRegKey HKLM SOFTWARE\SIVP\SIVP-0.4.3

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\SIVP-0.4.3\*.*"
  RMDir "$SMPROGRAMS\SIVP-0.4.3"

  ; Remove directories used
  Delete "$INSTDIR\config\*"
  RMDir "$INSTDIR\config"
  Delete "$INSTDIR\demos\*"
  RMDir "$INSTDIR\demos"
  Delete "$INSTDIR\images\*"
  RMDir "$INSTDIR\images"
  Delete "$INSTDIR\lib\*"
  RMDir "$INSTDIR\lib"
  Delete "$INSTDIR\macros\*"
  RMDir "$INSTDIR\macros"
  Delete "$INSTDIR\man\*"
  RMDir "$INSTDIR\man"
  Delete "$INSTDIR\src\*"
  RMDir "$INSTDIR\src"
  Delete "$INSTDIR\*"
  RMDir "$INSTDIR"
SectionEnd

;--------------------------------
Function .onInit

	;Language selection dialog

	Push ""
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_SIMPCHINESE}
	Push "简体中文"
	Push A ; A means auto count languages
	       ; for the auto count to work the first empty push (Push "") must remain
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
	
	;find where scilab was installed
	var /GLOBAL SCIVERSION
	var /GLOBAL SCIPATH
	ReadRegStr $SCIVERSION HKLM Software\Scilab "LASTINSTALL"
	ReadRegStr $SCIPATH HKLM Software\Scilab\$SCIVERSION "SCIPATH"
	StrCpy $INSTDIR "$SCIPATH\contrib\SIVP-0.4.3"
	
	StrCmp $SCIPATH "" 0 +5
		MessageBox MB_YESNO $(NOSCI_MSG) IDYES NoAbort
		Abort ; causes installer to quit.
		NoAbort:
		StrCpy $INSTDIR "$PROGRAMFILES\SIVP-0.4.3"
		Goto +1
		

FunctionEnd

