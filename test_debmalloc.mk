#! /usr/bin/make -f

##
# @file
# @brief The Makefile for the test code for the debmalloc.
# @copyright
#   2025 Mitsutoshi Nakano <ItSANgo@gmail.com>
#   SPDX-License-Identifier: Apache-2.0

TARGETS=test_debmalloc
OBJS=test_debmalloc.o
SOURCES=$(OBJS:.o=.c)
DEPS=$(SOURCES:.c=.dep)

CFLAGS=-Wall -Werror -Wextra -g
LDLIBS=-L. -ldebmalloc

ifdef USE_DEBMALLOC
CFLAGS+=-DUSE_DEBMALLOC=$(USE_DEBMALLOC)
LDLIBS+=-L. -ldebmalloc
endif # USE_DEBMALLOC

.PHONY: all clean

all: $(TARGETS)
test_debmalloc: $(OBJS)
%.dep: %.c
	$(CC) $(CFLAGS) -M -o $@ $<
format:
	clang-format -i $(SOURCES) $(HEADERS)
clean:
	$(RM) $(TARGETS) $(OBJS) $(DEPS)
-include $(DEPS)
