/// @file
/// @brief The debmalloc macros.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 1.0.0
/// @date 2025-03-09

#if defined(USE_DEBMALLOC) && defined(DEBMALLOC_PRIORITY)

#define malloc(size) \
    debmalloc_malloc(size, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__)
#define free(ptr) \
    debmalloc_free(ptr, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__)
#define calloc(nmemb, size) \
    debmalloc_calloc( \
        nmemb, size, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__ \
    )
#define realloc(ptr, size) \
    debmalloc_realloc( \
        ptr, size, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__ \
    )
#define strdup(s) \
    debmalloc_strdup(s, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__)
#define strndup(s, n) \
    debmalloc_strndup(s, n, DEBMALLOC_PRIORITY, __FILE__, __LINE__, __func__)

#else // defined(USE_DEBMALLOC) && defined(DEBMALLOC_PRIORITY)

#undef malloc
#undef free
#undef calloc
#undef realloc
#undef strdup
#undef strndup

#endif // defined(USE_DEBMALLOC) && defined(DEBMALLOC_PRIORITY)
