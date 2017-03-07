##echochamber

###Building:

>./build.sh

###Size of executable Hello Wold Program (in bytes):

	wc -c a.out

>640 a.out

###Size of "Hello-World" with not extra flags/modifications by gcc:

	#include <stdio.h>

	int main(int argc, char const *argv[])
	{
		printf("hello world\n");
		return 0;
	}

> gcc test.c -o test && wc -c test
> 8600 test


More than 10x savings in space

Benefits:
- not dependant on stdlib, because we are implementing everythign we need ourselves
- 
