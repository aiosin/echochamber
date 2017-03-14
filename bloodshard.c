#include "echochamber.h"

//TODO: this will NOT compile ( and if it does that is quite alarming
	//I just want to see how the rought structure will end up loooking like
int main(int argc, char const *argv[]){
	int fd = open("testfile");
	int filesize = getfilesizeFD(fd);
	char * filecontent = read(fd, filesize);

	puts(filecontent);
	write(filecontent);


	return 0;
}