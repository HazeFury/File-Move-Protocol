#ifndef FILE_MOVE_H
#define FILE_MOVE_H

#ifdef __cplusplus
extern "C" {
#endif

void move_files(const char* source_dir, const char* dest_dir, int* moved_count, int* ignored_count);

#ifdef __cplusplus
}
#endif

#endif
