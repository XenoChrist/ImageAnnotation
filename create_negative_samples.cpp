//Program to create the negative samples file

#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc < 3)
	{
		cout << "USAGE:" << endl;
		cout << argv[0] << " <input_directory> <output_file> " << endl;
		return -1;
	}	
	string dir(argv[1]), filepath;
	DIR *dp;
	dirent *ent;
	struct stat filestat;
    ofstream ofs(argv[2],fstream::out);

    dp = opendir(dir.c_str());
    while(ent = readdir(dp))
    {
    	filepath = dir + "/" + ent->d_name;
    	if(stat(filepath.c_str() , &filestat))	continue;	//can't be opened
    	if(S_ISDIR(filestat.st_mode))			continue;	//a directory
    	if(ent->d_name[0] == '.') 				continue;	//hidden file
    	
    	cout << filepath << endl;
    	ofs << filepath << endl;
    }
    closedir(dp);
    ofs.close();
	return 0;
}