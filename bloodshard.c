#include "hawkeye.h"

int main(int argc, char const *argv[]){
	int fd = open("testfile", O_RDWR); /*worked just fine*/
	int filesize = getFilesizeFD(fd); /*worked just fine*/
	char filecontent[]= "AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDE";
	read(fd, &filecontent, filesize);
	close(fd);
	puts(filecontent);

	return 0;
}