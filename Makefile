#! /usr/bin/make -f

##
# @file
# @brief This is the Makefile for libdebmalloc
# @copyright
#   2025 Mitsutoshi Nakano <ItSANgo@gmail.com>
#   SPDX-License-Identifier: Apache-2.0

TARGETS=libdebmalloc.so test_debmalloc

libdebmalloc_so_SOURCES=debmalloc.c
libdebmalloc_so_HEADERS=debmalloc.h

test_debmalloc_SOURCES=test_debmalloc.c

CFLAGS=-Wall -Werror -Wextra
LIBRARY_CFLAGS=-fPIC -Wno-unused-function -Wno-unused-parameter
EXECUTABLE_CFLAGS=-Wno-implicit-function-declaration -Wpedantic -DUSE_DEBMALLOC=1

libdebmalloc_so_OBJS=$(libdebmalloc_so_SOURCES:.c=.o)
test_debmalloc_OBJS=$(test_debmalloc_SOURCES:.c=.o)


.PHONY: all format check clean
all: $(TARGETS)
libdebmalloc.so: $(libdebmalloc_so_OBJS)
	$(LD) -shared -o libdebmalloc.so $(libdebmalloc_so_OBJS)
$(libdebmalloc_so_OBJS): CFLAGS+=$(LIBRARY_CFLAGS)
$(libdebmalloc_so_OBJS): $(libdebmalloc_so_SOURCES)
test_debmalloc: libdebmalloc.so $(test_debmalloc_OBJS)
	$(CC) -o test_debmalloc $(test_debmalloc_OBJS) -L. -ldebmalloc
$(test_debmalloc_OBJS): CFLAGS+=$(EXECUTABLE_CFLAGS)
$(test_debmalloc_OBJS): $(test_debmalloc_SOURCES) $(libdebmalloc_so_HEADERS)
check: test_debmalloc
	./test_debmalloc
format:
	clang-format -i $(libdebmalloc_so_SOURCES) $(libdebmalloc_so_HEADERS) $(test_debmalloc_SOURCES)
clean:
	$(RM) $(TARGETS) $(libdebmalloc_so_OBJS) $(test_debmalloc_OBJS)
