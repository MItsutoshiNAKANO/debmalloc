#ifndef DEBMALLOC_H
#define DEBMALLOC_H 1

/// @file
/// @brief The debmalloc header file.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 0.1.0
/// @date 2025-03-04

#if defined(USE_DEBMALLOC)

#ifndef DEBMALLOC_LOG_LEVEL
/// @brief The default log level.
#define DEBMALLOC_LOG_LEVEL 5
#endif // End of `ifndef DEBMALLOC_LOG_LEVEL`

#ifndef DEBMALLOC_LOG
/// @brief The default log function.
/// @param level The debug level.
/// @param fmt The fprintf(3) format.
/// @param ... The fprintf(3) arguments.
#define DEBMALLOC_LOG(level, ...) \
    debmalloc_log(level, __FILE__, __LINE__, __func__, __VA_ARGS__)
#endif // End of `ifndef LOG`

#define malloc(size) \
    deb_malloc(size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__)
#define free(ptr) \
    deb_free(ptr, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__)
#define calloc(nmemb, size) \
    deb_calloc(nmemb, size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__)
#define realloc(ptr, size) \
    deb_realloc(ptr, size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__)

void *deb_malloc(
    size_t size, int level, const char *file, long line, const char *func
);

void *deb_calloc(
    size_t nmemb, size_t size, int level, const char *file, long line,
    const char *func
);

void *deb_realloc(
    void *ptr, size_t size, int level, const char *file, long line,
    const char *func
);

void
deb_free(void *ptr, int level, const char *file, long line, const char *func);

#endif // End of `defined(USE_DEBMALLOC)`

#endif // End of `ifndef DEBMALLOC_H`
