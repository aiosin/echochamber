#!/bin/sh

exename="a.out"

gcc -std=c89 -pedantic -s -O2 -Wall -Werror \
    -nostdlib \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    -fdata-sections \
    -Wl,--gc-sections \
    -Wa,--noexecstack \
    -fno-builtin \
    -fno-stack-protector \
    util.S jupiter.c \
    -o $exename \
\
&& strip -R .comment $exename