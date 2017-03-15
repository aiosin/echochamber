#include "hawkeye.h"

int main(int argc, char const *argv[]){
	int fd = open("testfile", O_RDWR); /*worked just fine*/
	int filesize = getFilesizeFD(fd); /*worked just fine*/
	char * filecontent;
	read(fd, &filecontent, filesize);
	close(fd);
	syscall1(60,(uintptr)0);
	return 0;
}