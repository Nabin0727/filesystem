// filesystem in c
// get current dir
// read dir
// get details
// ask user
// ...

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>

#define BUFFER 1000
int main()
{
	char *dir_name;
	size_t dir_size = BUFFER;

	dir_name = (char *) malloc(dir_size);

	if(getcwd(dir_name, dir_size) == NULL)
	{
		perror("get cwd failed");
		exit(1);
	}
	puts(dir_name);

	DIR *dir_list = opendir(dir_name);

	struct dirent *list;

	while((list=readdir(dir_list) )!= NULL)
	{
		printf("%s\n ", list->d_name);

	}

	return 0;
}
