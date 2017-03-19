#include "hawkeye.h"

int main(int argc, char const *argv[]){
	int fd = open("testfile", O_RDWR); /*worked just fine*/
	int filesize = getFilesizeFD(fd); /*worked just fine*/
	__asm__("nop");
	char filecontent[64];
	__asm__("nop");
	read(fd, &filecontent, filesize);
	close(fd);
	puts(filecontent);

	return 0;
}