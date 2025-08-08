#ifndef FILE_SCAN_H
#define FILE_SCAN_H

#ifdef __cplusplus
extern "C" {
#endif

void scan_files(const char* source_dir, int* total, int* valid, int* invalid);
int is_valid_filename(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
