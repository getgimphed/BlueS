#include <iostream>
#include <stdint.h>
#include <string>
#include <bits/stdc++.h> 
#include <dirent.h>
#include "DetectArch.h"
using namespace std;

int main(int argc, char *argv[])
{
    char buffer[100];
    char path[255];
    int totalLibs = 0 ;   
	if(argv[1] == NULL)
    {
    	cout<<"No Command Line Path given, taking default \"test-input/\" Directory"<<endl<<endl;
    	char defaultpath[] = "test-input/";
		strncpy(path, defaultpath, strlen(defaultpath));
	}
	else
	{
		strncpy(path, argv[1], strlen(argv[1]));
		strcat(path, "/");
	}
	struct dirent *entry;
	DIR *dir = opendir(path);
	if (dir == NULL) 
	{
	    cout<<"Not a Dir";
		return 0;
	}
	
	while ((entry = readdir(dir)) != NULL) 
	{
	  char filePath[255] = "";
	  strncpy(filePath, path, strlen(path));
	  strcat(filePath, (entry->d_name));
	  totalLibs += DetectFileArch( filePath );
	}
	closedir(dir);
	//printing O/P from results.txt generated in DetectFileArch func 
	cout<<"Total number of libraries: "<<totalLibs<<endl<<endl;
	FILE* file = fopen("results.txt", "rb");

    while ( fgets (buffer , 100 , file) != NULL )
		cout<<buffer;	
    fclose(file);
    return 0;	
}
