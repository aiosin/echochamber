#!/bin/sh

exename="bloodshard"

gcc -std=c89 -pedantic -s -O2 -Wall -Werror \
    -nostdlib \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    -fdata-sections \
    -Wl,--gc-sections \
    -Wl,--build-id=none \
    -Wa,--noexecstack \
    -fno-builtin \
    -fno-stack-protector \
    util.S bloodshard.c \
    -o $exename \
\
&& strip -R .comment $exename \
&& strip -R .note.gnu.build-id $exename \
&& strip --strip-unneeded