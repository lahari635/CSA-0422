// ls_sim.c
// Simple ls: lists filenames, size and type

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void print_mode(mode_t m) {
    char p[11] = "----------";
    if (S_ISDIR(m)) p[0] = 'd';
    if (m & S_IRUSR) p[1]='r';
    if (m & S_IWUSR) p[2]='w';
    if (m & S_IXUSR) p[3]='x';
    if (m & S_IRGRP) p[4]='r';
    if (m & S_IWGRP) p[5]='w';
    if (m & S_IXGRP) p[6]='x';
    if (m & S_IROTH) p[7]='r';
    if (m & S_IWOTH) p[8]='w';
    if (m & S_IXOTH) p[9]='x';
    printf("%s ", p);
}

int main(int argc, char *argv[]) {
    const char *dir = (argc>1)?argv[1]:".";
    DIR *d = opendir(dir);
    if (!d) { perror("opendir"); return 1; }
    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);
        struct stat st;
        if (stat(path, &st) == 0) {
            print_mode(st.st_mode);
            printf("%5lld %s\n", (long long)st.st_size, e->d_name);
        } else {
            printf("???????? %s\n", e->d_name);
        }
    }
    closedir(d);
    return 0;
}
