/// @file
/// @brief Debugging malloc memory leaks.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 0.1.0
/// @date 2025-03-04
/// @see
///     * 『Binary Hacks』 ISBN978-4-87311-288-6
///       * #61 LD_PRELOAD で既存の関数をラップする

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBMALLOC_LOG_LEVEL 5

static void *(*real_malloc)(size_t);
static void (*real_free)(void *);
static void *(*real_calloc)(size_t, size_t);
static void *(*real_realloc)(void *, size_t);

/// @brief Default vlog function.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @param fmt The vfprintf(3) format.
/// @param ap The vfprinf(3) arguments.
static void
debmalloc_vlog(
    int level, const char *file, long line, const char *func, const char *fmt,
    va_list ap
)
{
    fprintf(stderr, "%s:%ld:%s:%d:", file, line, func, level);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
}

/// @brief Default log function.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @param fmt The fprintf(3) format.
/// @param ... The fprintf(3) arguments.
static void
debmalloc_log(
    int level, const char *file, long line, const char *func, const char *fmt,
    ...
)
{
    va_list ap;
    va_start(ap, fmt);
    debmalloc_vlog(level, file, line, func, fmt, ap);
    va_end(ap);
}

/// @brief Initialize debmalloc.
void __attribute__((constructor))
init_debmalloc(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    real_free = dlsym(RTLD_NEXT, "free");
    real_calloc = dlsym(RTLD_NEXT, "calloc");
    real_realloc = dlsym(RTLD_NEXT, "realloc");
}

/// @brief The malloc(3) wrapper.
/// @param size Size.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of malloc(3).
/// @see malloc(3)
void *
deb_malloc(
    size_t size, int level, const char *file, long line, const char *func
)
{
    debmalloc_log(level, file, line, func, "malloc(%zu)", size);
    void *p = real_malloc(size);
    debmalloc_log(level, file, line, func, "malloc(%zu) = %p", size, p);
    return p;
}

/// @brief The default malloc(3) wrapper.
/// @param size
/// @return The return value of malloc(3).
/// @see malloc(3)
void *
malloc(size_t size)
{
    return deb_malloc(size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__);
}

/// @brief The calloc(3) wrapper.
/// @param nmemb The number of elements.
/// @param size The size of each element.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of calloc(3).
/// @see calloc(3)
void *
deb_calloc(
    size_t nmemb, size_t size, int level, const char *file, long line,
    const char *func
)
{
    debmalloc_log(level, file, line, func, "calloc(%zu, %zu)", nmemb, size);
    void *p = real_calloc(nmemb, size);
    debmalloc_log(
        level, file, line, func, "calloc(%zu, %zu) = %p", nmemb, size, p
    );
    return p;
}

/// @brief The default calloc(3) wrapper.
/// @param nmemb The number of elements.
/// @param size The size of each element.
/// @return The return value of calloc(3).
/// @see calloc(3)
void *
calloc(size_t nmemb, size_t size)
{
    return deb_calloc(
        nmemb, size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__
    );
}

/// @brief The realloc(3) wrapper.
/// @param ptr The previous pointer.
/// @param size The new size.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @return The return value of realloc(3).
/// @see realloc(3)
void *
deb_realloc(
    void *ptr, size_t size, int level, const char *file, long line,
    const char *func
)
{
    debmalloc_log(level, file, line, func, "realloc(%p, %zu)", ptr, size);
    void *p = real_realloc(ptr, size);
    debmalloc_log(
        level, file, line, func, "realloc(%p, %zu) = %p", ptr, size, p
    );
    return p;
}

/// @brief The default realloc(3) wrapper.
/// @param ptr The previous pointer.
/// @param size The new size.
/// @return The return value of realloc(3).
/// @see realloc(3)
void *
realloc(void *ptr, size_t size)
{
    return deb_realloc(
        ptr, size, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__
    );
}

/// @brief The free(3) wrapper.
/// @param ptr The pointer to free.
/// @param level The debug level.
/// @param file __FILE__.
/// @param line __LINE__.
/// @param func __func__.
/// @see free(3)
void
deb_free(void *ptr, int level, const char *file, long line, const char *func)
{
    debmalloc_log(level, file, line, func, "free(%p)", ptr);
    real_free(ptr);
}

/// @brief The default free(3) wrapper.
/// @param ptr The pointer to free.
/// @see free(3)
void
free(void *ptr)
{
    deb_free(ptr, DEBMALLOC_LOG_LEVEL, __FILE__, __LINE__, __func__);
}
