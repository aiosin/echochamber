#include "echochamber.h"

internal uintptr strlen(char const* str){
    char const* p;
    for (p = str; *p; ++p);
        return p-str;
}

internal uintptr puts(char const* str){

    return write(stdout, str, strlen(str));
}

internal uintptr write(int fd, void const* data, uintptr nbytes){
    return (intptr)
        syscall5(
            (void*) SYS_write, /* SYS_write */
            (void*)(intptr)fd,
            (void*)data,
            (void*)nbytes,
            0, /* ignored */
            0  /* ignored */
        );
}



int main(int argc, char* argv[])
{
    puts("hello\n");

    return 0;
}