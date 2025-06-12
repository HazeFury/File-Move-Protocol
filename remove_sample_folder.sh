#!/bin/bash

# Chemin du dossier où se trouve ce script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Dossier parent de ce script
PARENT_DIR="$(dirname "$SCRIPT_DIR")"

# Dossier à créer
TARGET_DIR="$PARENT_DIR/sample_folders"

if [ -d "$TARGET_DIR" ]; then
  rm -rf "$TARGET_DIR"
  echo "Dossiers supprimés avec succès ✅"
else
  echo "Il n'y a rien à supprimer."
fi