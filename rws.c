#include "echochamber.h"

//TODO: leave syscall wrapper functions here or include in echochamber.h ? otherwise conflicts with jupiter and or other future projects ??

internal uintptr read(int fd, void *buf, size_t count){

}

//open and or possbly create a file
internal uintptr open(){

}

//invoke close syscall on an given file descriptor
internal uintptr close(){

}

//TODO: make sure SIZE_T is available for this function
void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}