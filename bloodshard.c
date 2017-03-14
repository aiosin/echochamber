#include "echochamber.h"

int main(int argc, char const *argv[]){
	int fd = open("testfile", O_RDWR);
	int filesize = getFilesizeFD(fd);
	char * filecontent;
	read(fd, &filecontent, filesize);
	getFilesize("testfile");
	puts(filecontent);
	write(1,filecontent,filesize);
	close(fd);

	return 0;
}