#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>   // Pour WIN32_FIND_DATA, FindFirstFile, etc.
#include <direct.h>    // Pour _mkdir
#include "file_move.h"

// Fonction pour tester si une chaîne commence par 5 chiffres
int starts_with_5_digits(const char* name) {
    for (int i = 0; i < 5; ++i) {
        if (name[i] < '0' || name[i] > '9') return 0;
    }
    return 1;
}

void move_files(const char* source_dir, const char* dest_dir) {
    char search_path[MAX_PATH];
    snprintf(search_path, MAX_PATH, "%s\\*", source_dir);

    WIN32_FIND_DATA find_data;
    HANDLE hFind = FindFirstFile(search_path, &find_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erreur: impossible de lister les fichiers.\n");
        return;
    }

    do {
        // Ignorer les dossiers spéciaux "." et ".."
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }

        const char* filename = find_data.cFileName;

        if (strlen(filename) < 5 || !starts_with_5_digits(filename)) {
            printf("Nom invalide : %s\n", filename);
            continue;
        }

        // Extraire les 5 premiers caractères pour nom du sous-dossier
        char subdir[6];
        strncpy(subdir, filename, 5);
        subdir[5] = '\0';

        // Créer le chemin complet du sous-dossier
        char full_subdir_path[MAX_PATH];
        snprintf(full_subdir_path, MAX_PATH, "%s\\%s", dest_dir, subdir);

        // Créer le sous-dossier s’il n’existe pas déjà
        _mkdir(full_subdir_path);

        // Construire le chemin source complet
        char source_file_path[MAX_PATH];
        snprintf(source_file_path, MAX_PATH, "%s\\%s", source_dir, filename);

        // Construire le chemin destination complet
        char dest_file_path[MAX_PATH];
        snprintf(dest_file_path, MAX_PATH, "%s\\%s\\%s", dest_dir, subdir, filename);

        // Déplacer le fichier
        if (rename(source_file_path, dest_file_path) != 0) {
            perror("Erreur lors du déplacement");
        } else {
            printf("Déplacé : %s -> %s\n", source_file_path, dest_file_path);
        }

    } while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
}
