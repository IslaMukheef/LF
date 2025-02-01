#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>



int files_found = 0; // tracks the numbers of files
char *files_names[30]; //keeps track of at most 30 files!
struct stat buffer;

void printfiles(){
    for( int i =0; i <files_found; i++)
    {
        printf("%s\n", files_names[i]);
    }
}
void getUser(){
    struct passwd *pws;
    pws = getpwuid(buffer.st_uid);
    printf("%s ", pws->pw_name);
}
void getGroup(){
    struct group *gr;
    gr = getgrgid(buffer.st_gid);
    printf("%s ", gr->gr_name);
}
void convert_time(){
    char mtime[80];
    time_t t = buffer.st_mtime; // hold the time in time_t type
    struct tm lt;
    localtime_r(&t, &lt); // convert to struct tm
    strftime(mtime, sizeof mtime, "%a, %d %b %Y %T", &lt);
    printf("%s ", mtime);
}
//Long format. Displays detailed file information, including permissions, ownership, size, and modification time.
void Long_print(char file[30]){
// premmi & owner & group & size & modifcation data & file name

    printf("%3o ",buffer.st_mode & 0777); // print premis
    getUser();
    //printf("%d ", buffer.st_uid);         // prints the user id(owner)
    getGroup();
    //printf("%d ", buffer.st_gid);         // prints the group ID id(id of file group's)
    printf("%ld ", buffer.st_size);       // prints the size of the file
    convert_time(); // call function to convert the time and print
    //printf("%ld", buffer.st_mtime);
    printf("%s ", file);
    //printf("%s: %lu\n",file, buffer.st_ino);
    printf("\n");
}
void traversfiles(char *path, int long_format){
    // search the dir for files and then print them
    struct dirent *dir_entry;
    DIR *dir = opendir(path);
    

    if(dir == NULL) // if dir return null break and return to main
    {
        printf("Dir returned NULL");
        return;
    }
    
    while((dir_entry=readdir(dir))!=NULL)
    {
        //char full_patj[1024]; // temp that will hold the whole path in case the lf was called from different place
        files_names[files_found] = strdup(dir_entry->d_name); // give a copy of string(it should be freed after)
        if (lstat(files_names[files_found], &buffer) == -1) {
            perror("lstat");
            continue;
        }
        //printf("%s: %lu\n", dir_entry->d_name, buffer.st_ino);
        if(long_format){
            Long_print(dir_entry->d_name);
        }
        files_found++;
        if(files_found>=30) break; // make sure it never pass 30 but it should be changed to something better!
    }
    closedir(dir);// close the directory

    if(!long_format){
        printfiles();
    }

    //free the space we allocated for file_names with strdup
    for(int i=0; i<files_found;i++){
        free(files_names[i]);
    } 

}


int main(int argc, char *argv[]){
    char * path = ".";
    int long_format = 0; // flag to check if -l is provided
    if(argc > 1){
        if (strcmp(argv[1], "-l") == 0) { // check if the argument is -l
            long_format = 1; // set the flag to true
        }
    }
     traversfiles(path, long_format); // call traversfiles with the appropriate format
    

    
    return 0;
}
