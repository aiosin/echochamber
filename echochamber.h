#define SYS_write 1
#define SYS_exit 60
#ifndef echochamber_h
#define echochamber_h

#define size_t unsigned int
#define internal static
#define stdout 1

typedef unsigned long int uintptr; /* size_t */
typedef long int intptr; /* ssize_t */

/********************************/
/****** function declaration*****/
/********************************/
internal uintptr strlen(char const* str);
internal uintptr puts(char const* str);
internal uintptr write(int fc, void const* data, uintptr bytes);

void* syscall5(
    void* number,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5
);

void* syscall4(
    void* number,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4
);

void* syscall3(
    uintptr number,
    void* arg1,
    void* arg2,
    void* arg3
);

void* syscall2(
    uintptr number,
    void* arg1,
    void* arg2
);
void* syscall1(
    uintptr number,
    void* arg1
);
#endif