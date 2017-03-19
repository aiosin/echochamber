#define internal static
#define stdout 1
#define O_ACCMODE	0003
#define O_RDONLY	  00
#define O_WRONLY	  01
#define O_RDWR		  02
#define O_CREAT		0100

/*read(int fd, void *buf, size_t count);*/
#define SYS_READ 0
/*ssize_t write(int fd, const void *buf, size_t count);*/
#define SYS_WRITE 1
/*int close(int fd);*/
#define SYS_CLOSE 3
/*int open(const char *pathname, int flags);*/
#define SYS_OPEN 2
/*int stat(const char *pathname, struct stat *buf);*/
#define SYS_STAT 4
/*int fstat(int fd, struct stat *buf);*/
#define SYS_FSTAT 5
/*void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);*/
#define SYS_MMAP 9
/*int mprotect(void *addr, size_t len, int prot);*/
#define SYS_MPROTECT 10
/*int munmap(void *addr, size_t length);*/
#define SYS_MUNMAP 11
#define SYS_exit 60

/*nop define for debugging purposes*/
#define NOP __asm__("nop")
/*In case I forget to replace size_t somewhere*/
#define size_t long unsigned int

/*FIXME: @future me, size_t is an uint long of at least 16 bits = ~65k or 130000k i forgot*/
typedef unsigned long int 	uintptr; /* size_t */
typedef long int 			intptr; /* ssize_t */


/*why does the kernel need so much types ?*/
typedef long int 			time_t;


typedef unsigned long int 	dev_t;
typedef unsigned long int 	ino_t;
typedef unsigned int 		mode_t;
typedef unsigned long 		nlink_t;
typedef unsigned int 		uid_t;
typedef unsigned int 		gid_t;
typedef long int 			off_t;
typedef long int 			blksize_t;
typedef long int 			blkcnt_t;

struct timespec{
	time_t tv_sec;
	time_t tv_nsec;
};


/*stat struct definition as needed by stat/fstat syscall*/
/* we also need presices defeinition of every type used here kill me pls*/
struct stat{
	dev_t     st_dev;         /* ID of device containing file */
	ino_t     st_ino;         /* inode number */
	nlink_t   st_nlink;       /* number of hard links */
	mode_t    st_mode;        /* file type and mode */
	uid_t     st_uid;         /* user ID of owner */
	gid_t     st_gid;         /* group ID of owner */
	int 	  pad;			  /* padding as specified in (x86_64) stat.h header*/
	dev_t     st_rdev;        /* device ID (if special file) */
	off_t     st_size;        /* total size, in bytes */
	blksize_t st_blksize;     /* blocksize for filesystem I/O */
	blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

	/* Since Linux 2.6, the kernel supports nanosecond
	precision for the following timestamp fields.
	For the details before Linux 2.6, see NOTES. */
	struct timespec  st_atim;  /* time of last access */
	struct timespec  st_mtim;  /* time of last modification */
	struct timespec  st_ctim;  /* time of last status change */
};



/********************************/
/****** FUNCTION DECLARATION*****/
/********************************/

/****SYSCALL WRAPPER FUNCTIONS***/
internal uintptr write(int fc, void const* data, uintptr bytes);
internal uintptr read(int fd, void *buf, uintptr count);
internal uintptr close(int fd);
internal uintptr stat(char* pathname, struct stat *buf);
internal uintptr fstat(int fd, struct stat *buf);
internal uintptr mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
internal uintptr munmap(void *addr, size_t length);
internal uintptr mprotect(void *addr, size_t len, int prot);



/*******PUBLIC  FUNCTIONS**********/
internal uintptr strlen(char const* str);
internal uintptr puts(char const* str);
void *memset(void *s, int c, size_t n);
void *malloc(uintptr size);
void *free(void* ptr);

/********************************/
/********************************/
/*SYSCALL FUNCTION DEFINITIONS***/
/********************************/
/********************************/
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

/********************************/
/****** WRAPPER FUNCTIONS *******/
/******** FOR SYSCALLS **********/
/********************************/


internal uintptr write(int fd, void const* data, uintptr nbytes){
    return (intptr)syscall5((void*) SYS_WRITE, 
							(void*)(intptr)fd,
							(void*)data,
							(void*)nbytes,
							0,0);
}


/*attempts to read n bytes from a file descriptor into a buffer*/
internal uintptr read(int fd, void *buf, uintptr count){
	return (uintptr)syscall3(SYS_READ, /*SYS_READ = 0 defined above*/
							(void*) (intptr)fd,
							(void*) buf,
							(void*) count);
}

/*open and or possbly create a file*/
/*returns a file descriptor*/
internal uintptr open(char* pathname, int flags){
	return (uintptr)syscall2(SYS_OPEN,
							(void*) pathname,
							(void*)(intptr) flags);
}

/*invoke close syscall on an given file descriptor*/
internal uintptr close(int fd){
	return (uintptr)syscall1(SYS_CLOSE,
							(void*)(intptr) fd);
}

/*invoke close syscall on an given file descriptor*/

internal uintptr stat(char* pathname, struct stat* buf ){
	
	return (uintptr)syscall2(SYS_STAT,
							(void*) pathname,
							(void*) buf);

}


/*invoke stat syscall but with filedescriptor*/
internal uintptr fstat(int fd, struct stat* buf){
	return (uintptr)syscall2(SYS_FSTAT,
							(void*)(intptr) fd,
							(void*) buf);
}

internal uintptr mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset){

}

internal uintptr munmap(void *addr, size_t length){

}
internal uintptr mprotect(void *addr, size_t len, int prot){

}


/***PUBLIC FUNCTIONS***/

/*returns size of file at path in n bytes*/

internal uintptr getFilesize(char* path){
	struct stat tempstat;
	stat(path, &tempstat);
	return (uintptr) tempstat.st_size;
}


internal uintptr getFilesizeFD(int fd){
	struct stat tempstat;
	fstat(fd, &tempstat);
	return (uintptr) tempstat.st_size;

}


internal uintptr strlen(char const* str){
    char const* p;
    for (p = str; *p; ++p);
        return p-str;
}

void* memset(void *s, int c, uintptr n){
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

internal uintptr puts(char const* str){

    return write(stdout, str, strlen(str));
}


void readFile(char* buffer, char* path){
	int fd = open(&path, O_RDWR);
	int filesize = getFilesizeFD(fd);
	read(fd, &buffer,filesize);
}
void readFileFD(char* buffer, int fd){
	int filesize = getFilesizeFD(fd);
	read(fd, );
}

/*Code only copy pasted, FIXME later*/
/*general ideas and improvement potential, mmap always allocates at least one memory page*/
/*one memory page (on my machine ) is 4kb, maybe we should allocate modulo 4kb since it wont make a difference (?)*/
/*TBC*/
/*Some observations:
You assume that int and size_t have the same size. If you want to store a size_t value at the head of the allocation, then why don't you just do that? Why introduce int?
This will very likely be quite inefficient, both in terms of memory usage and speed. There is significant overhead to mmap(), and typically allocations cannot be smaller than a "page". Most real allocators try to avoid calling OS-level functionality on every malloc(), in various ways.
If mmap() fails, it will return MAP_FAILED, and so should malloc(). Thus, you need to test for that before de-referencing the pointer returned by mmap().
Calling free(NULL) should be a valid thing to do; with your implementation it will very likely cause a crash since you don't NULL-check the argument before assuming it's valid.
*/
void* malloc(uintptr size){
	   int *plen;
    int len = size + sizeof( size ); // Add sizeof( size ) for holding length.

    plen = mmap( 0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    *plen = len;                     // First 4 bytes contain length.
    return (void*)(&plen[1]);        // Memory that is af
}

/*this does not make sense to me, get to the bottom of this before I end up using this*/
void free(void * ptr){
	 int *plen = (int*)ptr;
    int len;

    plen--;                          /* Reach top of memory*/
    len = *plen;                     /* Read length*/

    munmap( (void*)plen, len );
}