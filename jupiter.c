#include "echochamber.h"

/*FIXME: i dont knwo it we use internal/static like this it will even compile, if nessecary jsut replace static/internal with void* or int*/
internal uintptr puts(char const* str){

    return write(stdout, str, strlen(str));
}

int main(int argc, char* argv[])
{
    puts("hello\n");

    return 0;
}