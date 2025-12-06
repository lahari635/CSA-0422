// io_syscalls.c
// Demonstrate fcntl, lseek, stat, opendir, readdir

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *dir = (argc > 1) ? argv[1] : ".";
    DIR *d = opendir(dir);
    if (!d) { perror("opendir"); return 1; }
    printf("Contents of %s:\n", dir);
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(d);

    const char *fname = "io_sample.txt";
    int fd = open(fname, O_RDWR | O_CREAT, 0644);
    if (fd < 0) { perror("open"); return 1; }
    // use fcntl to get flags
    int flags = fcntl(fd, F_GETFL);
    if (flags >= 0) printf("%s opened, flags = %d\n", fname, flags);
    else perror("fcntl");

    // write and lseek
    write(fd, "0123456789\n", 11);
    off_t pos = lseek(fd, 0, SEEK_SET);
    if (pos == (off_t)-1) perror("lseek");
    else printf("lseek back to %lld\n", (long long)pos);

    // stat
    struct stat st;
    if (fstat(fd, &st) == 0) {
        printf("%s size=%lld bytes, mode=%o\n", fname, (long long)st.st_size, st.st_mode & 0777);
    } else perror("fstat");

    close(fd);
    unlink(fname);
    return 0;
}
