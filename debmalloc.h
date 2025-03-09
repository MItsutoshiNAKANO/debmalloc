#ifndef DEBMALLOC_H
#define DEBMALLOC_H 1

/// @file
/// @brief The debmalloc header file.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 1.0.0
/// @date 2025-03-09

#include <stdarg.h> ///< @see va_list(3)
#include <stddef.h> ///< @see size_t(3)

#ifdef __cplusplus
extern "C" {
#endif

/// @brief The type of pointer of the logging function.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @param fmt The vfprintf(3) format.
/// @param ap The vfprinf(3) arguments.
typedef void (*Vlog)(
    int priority, const char *file, long line, const char *func,
    const char *fmt, va_list ap
);

extern Vlog debmalloc_vlog;

void *debmalloc_malloc(
    size_t size, int priority, const char *file, long line, const char *func
);

void *debmalloc_calloc(
    size_t nmemb, size_t size, int priority, const char *file, long line,
    const char *func
);

void *debmalloc_realloc(
    void *ptr, size_t size, int priority, const char *file, long line,
    const char *func
);

void debmalloc_free(
    void *ptr, int priority, const char *file, long line, const char *func
);

char *debmalloc_strdup(
    const char *s, int priority, const char *file, long line, const char *func
);

char *debmalloc_strndup(
    const char *s, size_t n, int priority, const char *file, long line,
    const char *func
);

#ifdef __cplusplus
}
#endif

#endif // DEBMALLOC_H
