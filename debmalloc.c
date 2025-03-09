/// @file
/// @brief Debugging malloc memory leaks.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 1.0.0
/// @date 2025-03-09

#include <stdarg.h> ///< @see va_list(3)
#include <stdio.h>  ///< @see fprintf(3)
#include <stdlib.h> ///< @see malloc(3), calloc(3), realloc(3), free(3)
#include <string.h> ///< @see strdup(3), strndup(3)

#include "debmalloc.h"

/// @brief Default vlog function.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @param fmt The vfprintf(3) format.
/// @param ap The vfprinf(3) arguments.
static void
default_vlog(
    int priority, const char *file, long line, const char *func,
    const char *fmt, va_list ap
)
{
    fprintf(stderr, "%s:%ld:%s():%x:", file, line, func, priority);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

/// @brief The vlog function.
Vlog debmalloc_vlog = default_vlog;

/// @brief The log function.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @param fmt The fprintf(3) format.
/// @param ... The fprintf(3) arguments.
static void
debmalloc_log(
    int priority, const char *file, long line, const char *func,
    const char *fmt, ...
)
{
    va_list ap;
    va_start(ap, fmt);
    debmalloc_vlog(priority, file, line, func, fmt, ap);
    va_end(ap);
}

/// @brief The malloc(3) wrapper.
/// @param size Size.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of malloc(3).
/// @see malloc(3)
void *
debmalloc_malloc(
    size_t size, int priority, const char *file, long line, const char *func
)
{
    debmalloc_log(priority, file, line, func, "malloc(%zu)", size);
    void *p = malloc(size);
    debmalloc_log(priority, file, line, func, "malloc(%zu) = %p", size, p);
    return p;
}

/// @brief The calloc(3) wrapper.
/// @param nmemb The number of elements.
/// @param size The size of each element.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of calloc(3).
/// @see calloc(3)
void *
debmalloc_calloc(
    size_t nmemb, size_t size, int priority, const char *file, long line,
    const char *func
)
{
    debmalloc_log(priority, file, line, func, "calloc(%zu, %zu)", nmemb, size);
    void *p = calloc(nmemb, size);
    debmalloc_log(
        priority, file, line, func, "calloc(%zu, %zu) = %p", nmemb, size, p
    );
    return p;
}

/// @brief The realloc(3) wrapper.
/// @param ptr The previous pointer.
/// @param size The new size.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of realloc(3).
/// @see realloc(3)
void *
debmalloc_realloc(
    void *ptr, size_t size, int priority, const char *file, long line,
    const char *func
)
{
    debmalloc_log(priority, file, line, func, "realloc(%p, %zu)", ptr, size);
    void *p = realloc(ptr, size);
    debmalloc_log(
        priority, file, line, func, "realloc(%p, %zu) = %p", ptr, size, p
    );
    return p;
}

/// @brief The free(3) wrapper.
/// @param ptr The pointer to free.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @see free(3)
void
debmalloc_free(
    void *ptr, int priority, const char *file, long line, const char *func
)
{
    debmalloc_log(priority, file, line, func, "free(%p)", ptr);
    free(ptr);
}

/// @brief The strdup(3) wrapper.
/// @param s The string to duplicate.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of strdup(3).
/// @see strdup(3)
char *
debmalloc_strdup(
    const char *s, int priority, const char *file, long line, const char *func
)
{
    debmalloc_log(priority, file, line, func, "strdup(\"%s\")", s);
    char *p = strdup(s);
    debmalloc_log(priority, file, line, func, "strdup(\"%s\") = %p", s, p);
    return p;
}

/// @brief The strndup(3) wrapper.
/// @param s The string to duplicate.
/// @param n The length of characters to duplicate.
/// @param priority The priority.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of strndup(3).
/// @see strndup(3)
char *
debmalloc_strndup(
    const char *s, size_t n, int priority, const char *file, long line,
    const char *func
)
{
    debmalloc_log(priority, file, line, func, "strndup(\"%s\", %zu)", s, n);
    char *p = strndup(s, n);
    debmalloc_log(
        priority, file, line, func, "strndup(\"%s\", %zu) = %p", s, n, p
    );
    return p;
}
