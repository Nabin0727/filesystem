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
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

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
	
	struct stat file_stat;
	while((list=readdir(dir_list) )!= NULL)
	{
		printf("%s\t", list->d_name);
		stat(list->d_name, &file_stat);

		struct passwd *pw = getpwuid(file_stat.st_uid);
		printf("\t%s ",pw->pw_name);
		
		struct group *gr = getgrgid(file_stat.st_gid);
		printf("\t%s ", gr->gr_name);

		printf("\t%jd ", file_stat.st_size);
		
		time_t mod_time = file_stat.st_mtime;
		printf("\t%s\n", ctime(&mod_time));



	
	}

	return 0;
}
