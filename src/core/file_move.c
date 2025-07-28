// src/core/file_move.c

#include "file_move.h"
#include "file_scan.h" // pour is_valid_filename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

int starts_with(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void move_files(const char* source_dir, const char* dest_dir, int* moved_count, int* ignored_count) {
    *moved_count = 0;
    *ignored_count = 0;

    WIN32_FIND_DATA findFileData;
    char search_path[MAX_PATH];
    snprintf(search_path, MAX_PATH, "%s\\*", source_dir);

    HANDLE hFind = FindFirstFile(search_path, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erreur : impossible d'ouvrir le dossier source\n");
        return;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            const char* filename = findFileData.cFileName;

            if (!is_valid_filename(filename)) continue;

            // Récupère les 5 premiers chiffres
            char service_num[6] = {0};
            strncpy(service_num, filename, 5);

            // Chercher un dossier existant qui commence par les 5 chiffres
            char matching_folder[MAX_PATH] = {0};
            int found = 0;

            WIN32_FIND_DATA dirData;
            char dest_search_path[MAX_PATH];
            snprintf(dest_search_path, MAX_PATH, "%s\\*", dest_dir);
            HANDLE hDir = FindFirstFile(dest_search_path, &dirData);

            if (hDir != INVALID_HANDLE_VALUE) {
                do {
                    if ((dirData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                        strcmp(dirData.cFileName, ".") != 0 &&
                        strcmp(dirData.cFileName, "..") != 0) {
                        if (starts_with(dirData.cFileName, service_num)) {
                            snprintf(matching_folder, MAX_PATH, "%s\\%s", dest_dir, dirData.cFileName);
                            found = 1;
                            break;
                        }
                    }
                } while (FindNextFile(hDir, &dirData));
                FindClose(hDir);
            }

            if (!found) {
                snprintf(matching_folder, MAX_PATH, "%s\\%s", dest_dir, service_num);
                CreateDirectory(matching_folder, NULL); // Création si nécessaire
            }

            // Construire les chemins complet source -> destination
            char src_path[MAX_PATH];
            char dest_path[MAX_PATH];
            snprintf(src_path, MAX_PATH, "%s\\%s", source_dir, filename);
            snprintf(dest_path, MAX_PATH, "%s\\%s", matching_folder, filename);

            // Vérifier s’il existe déjà
            DWORD attr = GetFileAttributes(dest_path);
            if (attr != INVALID_FILE_ATTRIBUTES) {
                (*ignored_count)++;
                continue;
            }

            // Déplacement
            if (!MoveFile(src_path, dest_path)) {
                printf("Erreur lors du déplacement de %s vers %s\n", src_path, dest_path);
            } else {
                (*moved_count)++;
            }
        }
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);
}
