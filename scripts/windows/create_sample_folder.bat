@echo off
setlocal enabledelayedexpansion

REM Aller deux niveaux au-dessus du dossier du script
set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%\..\..") do set "ROOT_DIR=%%~fI"

REM Chemin du dossier cible
set "TARGET_DIR=%ROOT_DIR%\SAMPLE_FOLDERS"
set "ATTENTES_DIR=%TARGET_DIR%\ATTENTES_SIGNATURE"
set "TRAITES_DIR=%TARGET_DIR%\TRAITES"

REM Liste des fichiers (définie comme tableau indexé)
set count=0
set "file[0]=21149 MEDTRONIC 1018596 PAMAB"
set "file[1]=21320 INTEGRA 1056868 PAMAB"
set "file[2]=21530 DIATEC 1126525 PAMAB"
set "file[3]=21729 UGAP 1091535 PAMAB"
set "file[4]=21730 LANDANGER 1109812 PAMAB"
set /a count=5

REM Créer les dossiers principaux
if exist "%TARGET_DIR%" (
    echo Le dossier existe déjà : %TARGET_DIR%
    goto :eof
)

echo Création des dossiers...
mkdir "%ATTENTES_DIR%"
mkdir "%TRAITES_DIR%"

REM Boucle sur les fichiers
for /L %%i in (0,1,%count%) do (
    call set "FILENAME=%%file[%%i]%%"
    if not "!FILENAME!"=="" (
        echo Création du fichier : !FILENAME!
        echo. > "!ATTENTES_DIR!\!FILENAME!"
        
        set "PREFIX=!FILENAME:~0,5!"
        mkdir "!TRAITES_DIR!\!PREFIX!" >nul 2>&1
    )
)

echo Dossiers créés avec succès ✅
