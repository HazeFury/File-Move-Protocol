#!/bin/bash


# Chemin du dossier où se trouve ce script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Dossier parent de ce script
PARENT_DIR="$(dirname "$SCRIPT_DIR")"

# Dossier à créer
TARGET_DIR="$PARENT_DIR/sample_folders"

shopt -s nullglob
FILES_IN_SIGNATURE=("$TARGET_DIR/ATTENTES_SIGNATURE"/*)
shopt -u nullglob

if [ "${#FILES_IN_SIGNATURE[@]}" -eq "0" ]; then 
    echo "il n'y a aucun fichier actuellement."
else
    echo -e "Déplacement des fichiers suivants :\n"
    for file in "${FILES_IN_SIGNATURE[@]}"; do
        filename="$(basename "$file")"     
        echo "$filename"
        UF="${filename:0:5}"              
        mv --interactive "$file" "$TARGET_DIR/TRAITES/$UF"
    done
        echo -e "\nDéplacement terminé avec succès ✅"
        echo "-> Total de fichier(s) déplacé(s) : ${#FILES_IN_SIGNATURE[@]}"
fi
