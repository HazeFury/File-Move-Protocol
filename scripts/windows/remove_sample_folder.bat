@echo off

REM Aller 2 niveaux au-dessus du dossier contenant ce script
set SCRIPT_DIR=%~dp0
for %%I in ("%SCRIPT_DIR%\..\..") do set ROOT_DIR=%%~fI

REM Cible à supprimer
set TARGET_DIR=%ROOT_DIR%\SAMPLE_FOLDERS

if exist "%TARGET_DIR%" (
    rd /s /q "%TARGET_DIR%"
    echo Dossiers supprimés avec succès ✅
) else (
    echo Il n'y a rien à supprimer.
)
