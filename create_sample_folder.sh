#!/bin/bash

# Chemin du dossier où se trouve ce script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Dossier parent de ce script
PARENT_DIR="$(dirname "$SCRIPT_DIR")"

# Dossier à créer
TARGET_DIR="$PARENT_DIR/sample_folders"

FAKE_FILES=("21149 MEDTRONIC 1018596 PAMAB" "21320 INTEGRA 1056868 PAMAB" "21530 DIATEC 1126525 PAMAB" "21729 UGAP 1091535 PAMAB" "21730 LANDANGER 1109812 PAMAB")

# Création si non existant
if [ -d "$TARGET_DIR" ]; then
  echo "Le dossier existe déjà : $TARGET_DIR"
else
  echo "Création du dossier : $TARGET_DIR"
  mkdir -p "$TARGET_DIR"
  echo "Création du dossier : $TARGET_DIR/ATTENTES_SIGNATURE"
  mkdir -p "$TARGET_DIR/ATTENTES_SIGNATURE"
  echo "Création du dossier : $TARGET_DIR/TRAITES"
  mkdir -p "$TARGET_DIR/TRAITES"
  
  for file in "${FAKE_FILES[@]}"; do
    touch  "$TARGET_DIR/ATTENTES_SIGNATURE/$file"
    prefix="${file:0:5}"
    mkdir -p "$TARGET_DIR/TRAITES/$prefix"
  done
  echo "Remplissage des dossiers..."
  echo "Dossiers créés avec succès ✅"
fi
