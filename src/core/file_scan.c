#include "file_scan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <sys/types.h>
#include <dirent.h>

int is_regular_file(const char* path) {
    DWORD attrs = GetFileAttributes(path);
    return (attrs != INVALID_FILE_ATTRIBUTES) && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
}

int is_valid_filename(const char* filename) {
    if (strlen(filename) < 5) return 0;

    for (int i = 0; i < 5; ++i) {
        if (!isdigit((unsigned char)filename[i])) {
            return 0;
        }
    }
    return 1;
}

void scan_files(const char* source_dir, int* total, int* valid, int* invalid) {
    DIR* dir = opendir(source_dir);
    if (!dir) {
        printf("Erreur : impossible d'ouvrir le dossier source\n");
        return;
    }

    struct dirent* entry;
    char full_path[MAX_PATH];

    *total = *valid = *invalid = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." et ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, MAX_PATH, "%s\\%s", source_dir, entry->d_name);

        if (is_regular_file(full_path)) {
            (*total)++;
            if (is_valid_filename(entry->d_name)) {
                (*valid)++;
            } else {
                (*invalid)++;
            }
        }
    }

    closedir(dir);
}
