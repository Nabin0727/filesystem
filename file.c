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
// get current working dirctory
void get_currentdir(){

}

// getting file type
char *getfile_type(mode_t mode)
{
	if (S_ISREG(mode))
		return "-"; // regular file
	
	if (S_ISDIR(mode))
		return "d"; // directory

	if (S_ISLNK(mode))
		return "l"; // symbolic link

	if (S_ISCHR(mode))
		return "c";

	if (S_ISBLK(mode))
		return "b";

	if (S_ISSOCK(mode))
		return "s";

	return "?";
}

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
	printf("TYPE\tPERMISSIONS\tOWNER\tGROUP\tSIZE\tMODIFIED\t\tNAME\n");

	while((list=readdir(dir_list) )!= NULL)
	{


		printf("%s ", getfile_type(file_stat.st_mode));
		
		printf("xxx-xxx-xxx ");
		
		stat(list->d_name, &file_stat);

		struct passwd *pw = getpwuid(file_stat.st_uid);
		printf("\t%s ",pw->pw_name);
		
		struct group *gr = getgrgid(file_stat.st_gid);
		printf("\t%s ", gr->gr_name);

		double size_kb = (double)file_stat.st_size / 1024;
		printf("\t%.2f KB ", size_kb);
		
		time_t mod_time = file_stat.st_mtime;
		printf("\t%s\n", ctime(&mod_time));

		printf("%s\t", list->d_name);


	
	}

	return 0;
}
