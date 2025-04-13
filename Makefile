#! /usr/bin/make -f

##
# @file
# @brief This is the Makefile for libdebmalloc
# @copyright
#   2025 Mitsutoshi Nakano <ItSANgo@gmail.com>
#   SPDX-License-Identifier: Apache-2.0

TARGETS=libdebmalloc.so
OBJS=debmalloc.o
SOURCES=$(OBJS:.o=.c)
DEPS=$(SOURCES:.c=.d)
HEADERS=debmalloc.h debmalloc_macros.h
CFLAGS=-Wall -Werror -Wextra -Wno-unused-function -Wno-unused-parameter\
	-Wno-use-after-free -fPIC -g

.PHONY: all format check clean

all: $(TARGETS)
libdebmalloc.so: $(OBJS)
	$(LD) -shared -o libdebmalloc.so $(OBJS)
$(OBJS): $(HEADERS)
%.d: %.c
	$(CC) $(CFLAGS) -MM -o $@ $<
check: $(TARGETS)
	make -f test_debmalloc.mk clean
	make -f test_debmalloc.mk USE_DEBMALLOC=1 all
	LD_LIBRARY_PATH=. ./test_debmalloc
	make -f test_debmalloc.mk clean
	make -f test_debmalloc.mk all
	./test_debmalloc
format:
	clang-format -i $(SOURCES) $(HEADERS)
	make -f test_debmalloc.mk format
clean:
	make -f test_debmalloc.mk clean
	$(RM) $(TARGETS) $(OBJS) $(DEPS)
-include $(DEPS)
