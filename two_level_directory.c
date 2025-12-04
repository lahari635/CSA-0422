// two_level_directory.c
#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 50
#define NAME_LEN 64

typedef struct {
    char filename[NAME_LEN];
} File;

typedef struct {
    char username[NAME_LEN];
    File files[MAX_FILES];
    int file_count;
} UserDir;

UserDir users[MAX_USERS];
int user_count = 0;

int create_user(const char *user){
    if(user_count >= MAX_USERS) return -1;
    strncpy(users[user_count].username, user, NAME_LEN-1);
    users[user_count].file_count = 0;
    return user_count++;
}

int find_user(const char *user){
    for(int i=0;i<user_count;i++) if(strcmp(users[i].username,user)==0) return i;
    return -1;
}

int create_file_for_user(const char *user, const char *fname){
    int idx = find_user(user);
    if(idx==-1) return -1;
    if(users[idx].file_count >= MAX_FILES) return -2;
    strncpy(users[idx].files[users[idx].file_count++].filename, fname, NAME_LEN-1);
    return 0;
}

void list_user_files(const char *user){
    int idx = find_user(user);
    if(idx==-1){ printf("User not found\n"); return; }
    printf("Files for %s:\n", user);
    for(int i=0;i<users[idx].file_count;i++) printf("%s\n", users[idx].files[i].filename);
}

int main(){
    create_user("alice");
    create_user("bob");
    create_file_for_user("alice","a1.txt");
    create_file_for_user("alice","a2.txt");
    create_file_for_user("bob","b1.doc");

    list_user_files("alice");
    list_user_files("bob");
    return 0;
}
