#define SYS_write 1
#define SYS_exit 60

#define size_t unsigned int
#define internal static
#define stdout 1

//read(int fd, void *buf, size_t count);
#define SYS_READ 0
//ssize_t write(int fd, const void *buf, size_t count);
#define SYS_WRITE 1
//int close(int fd);
#define SYS_CLOSE 3
//int open(const char *pathname, int flags);
#define SYS_OPEN 2

#define SYS_STAT 4
#define SYS_FSTAT 5

//FIXME: @future me, size_t is an uint long of at least 16 bits = ~65k
typedef unsigned long int uintptr; /* size_t */
typedef long int intptr; /* ssize_t */

/********************************/
/****** function declaration*****/
/********************************/
internal uintptr strlen(char const* str);
internal uintptr puts(char const* str);
internal uintptr write(int fc, void const* data, uintptr bytes);

void *memset(void *s, int c, size_t n);

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


internal uintptr strlen(char const* str){
    char const* p;
    for (p = str; *p; ++p);
        return p-str;
}

internal uintptr write(int fd, void const* data, uintptr nbytes){
    return (intptr)
        syscall5(
            (void*) SYS_WRITE, 
            (void*)(intptr)fd,
            (void*)data,
            (void*)nbytes,
            0, /* ignored */
            0  /* ignored */
        );
}

void *memset(void *s, int c, uintptr n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

//read from a file descriptor
internal uintptr read(int fd, void *buf, uintptr count){
	return NULL;
}

//open and or possbly create a file
internal uintptr open(){
	return NULL;
}

//invoke close syscall on an given file descriptor
internal uintptr close(){
	return NULL;
}