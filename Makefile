#! /usr/bin/make -f

##
# @file
# @brief This is the Makefile for libdebmalloc
# @copyright
#   2025 Mitsutoshi Nakano <ItSANgo@gmail.com>
#   SPDX-License-Identifier: Apache-2.0

TARGETS=libdebmalloc.so $(TEST_EXECUTABLE)
TEST_EXECUTABLE=test_debmalloc

libdebmalloc_so_SOURCES=debmalloc.c
libdebmalloc_so_HEADERS=debmalloc.h debmalloc_macros.h

test_debmalloc_SOURCES=test_debmalloc.c

CFLAGS=-Wall -Werror -Wextra -g
LIBRARY_CFLAGS=-fPIC -Wno-unused-function -Wno-unused-parameter\
	-Wno-use-after-free
EXECUTABLE_CFLAGS=-Wpedantic

ifdef USE_DEBMALLOC
CFLAGS+=-DUSE_DEBMALLOC=$(USE_DEBMALLOC)
test_debmalloc_OBJS+=libdebmalloc.so
LDLIBS+=-L. -ldebmalloc
endif # USE_DEBMALLOC

libdebmalloc_so_OBJS=$(libdebmalloc_so_SOURCES:.c=.o)
test_debmalloc_OBJS=$(test_debmalloc_SOURCES:.c=.o)

.PHONY: all format check clean

all: $(TARGETS)
libdebmalloc.so: $(libdebmalloc_so_OBJS)
	$(LD) -shared -o libdebmalloc.so $(libdebmalloc_so_OBJS)
$(libdebmalloc_so_OBJS): CFLAGS+=$(LIBRARY_CFLAGS)
$(libdebmalloc_so_OBJS): $(libdebmalloc_so_SOURCES)
$(test_debmalloc_OBJS): CFLAGS+=$(EXECUTABLE_CFLAGS)
test_debmalloc: $(test_debmalloc_OBJS)
$(test_debmalloc_OBJS): $(test_debmalloc_SOURCES) $(libdebmalloc_so_HEADERS)
check:
	make clean
	make USE_DEBMALLOC=1 all
	LD_LIBRARY_PATH=. ./test_debmalloc
	make clean
	make all
	./test_debmalloc
format:
	clang-format -i $(libdebmalloc_so_SOURCES) $(libdebmalloc_so_HEADERS)\
		$(test_debmalloc_SOURCES)
clean:
	$(RM) $(TARGETS) $(libdebmalloc_so_OBJS) $(test_debmalloc_OBJS)
