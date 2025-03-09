/// @file
/// @brief The test code for the debmalloc.
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 1.0.0
/// @date 2025-03-09

#include <assert.h> ///< @see assert(3)
#include <stdio.h>  ///< @see fprintf(3)
#include <stdlib.h> ///< @see malloc(3)
#include <string.h> ///< @see strdup(3)

#include "debmalloc.h"

#define MESSAGE "Hello, World!"
#define PART_MESSAGE "Hel"
#define PART_MESSAGE_LENGTH 3

#define DEBMALLOC_PRIORITY 7
#include "debmalloc_macros.h"

/// @brief The function to use the debmalloc.
/// @param size The memory size to allocate.
static void
use_debmalloc(size_t size)
{
    fprintf(stderr, "Begin %s.\n", __func__);
    char *p1 = malloc(size);
    char *p2 = realloc(p1, size * 2);
    char *p3 = calloc(3, size);
    char *p4 = strdup(MESSAGE);
    char *p5 = strndup(MESSAGE, PART_MESSAGE_LENGTH);
    assert(strcmp(p5, PART_MESSAGE) == 0);
    free(p5);
    free(p4);
    free(p3);
    free(p2);
    fprintf(stderr, "End %s.\n", __func__);
}

#undef DEBMALLOC_PRIORITY
#include "debmalloc_macros.h"

/// @brief The function not to use the debmalloc.
/// @param size The memory size to allocate.
static void
dont_use_debmalloc(size_t size)
{
    fprintf(stderr, "Begin %s.\n", __func__);
    char *p1 = malloc(size);
    char *p2 = realloc(p1, size * 2);
    char *p3 = calloc(3, size);
    char *p4 = strdup(MESSAGE);
    char *p5 = strndup(MESSAGE, PART_MESSAGE_LENGTH);
    assert(strcmp(p5, PART_MESSAGE) == 0);
    free(p5);
    free(p4);
    free(p3);
    free(p2);
    fprintf(stderr, "End %s.\n", __func__);
}

/// @brief The main function.
/// @param argc The number of arguments.
/// @param argv[1] The memory size to allocate.
int
main(int argc, char *argv[])
{
    char *endp = NULL;
    size_t size = (argc > 1) ? (size_t)strtoull(argv[1], &endp, 10) : 8192;
    use_debmalloc(size);
    dont_use_debmalloc(size);
    exit(0);
}
