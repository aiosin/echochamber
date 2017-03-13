#include "echochamber.h"

internal uintptr puts(char const* str){

    return write(stdout, str, strlen(str));
}


int main(int argc, char* argv[])
{
    puts("hello\n");

    return 0;
}