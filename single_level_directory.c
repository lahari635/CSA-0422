// single_level_directory.c
#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define NAME_LEN 64

char directory[MAX_FILES][NAME_LEN];
int file_count = 0;

int create_file(const char *name){
    if(file_count >= MAX_FILES) return -1;
    for(int i=0;i<file_count;i++) if(strcmp(directory[i],name)==0) return -2; // exists
    strncpy(directory[file_count++], name, NAME_LEN-1);
    return 0;
}
int delete_file(const char *name){
    for(int i=0;i<file_count;i++){
        if(strcmp(directory[i],name)==0){
            for(int j=i;j<file_count-1;j++) strcpy(directory[j], directory[j+1]);
            file_count--;
            return 0;
        }
    }
    return -1;
}
int search_file(const char *name){
    for(int i=0;i<file_count;i++) if(strcmp(directory[i],name)==0) return i;
    return -1;
}
void list_files(){
    if(file_count==0) { printf("No files.\n"); return; }
    for(int i=0;i<file_count;i++) printf("%s\n", directory[i]);
}

int main(){
    create_file("notes.txt");
    create_file("prog.c");
    create_file("data.csv");
    printf("Files in root:\n");
    list_files();
    printf("\nSearching for prog.c => index = %d\n", search_file("prog.c"));
    delete_file("prog.c");
    printf("\nAfter deleting prog.c:\n");
    list_files();
    return 0;
}
