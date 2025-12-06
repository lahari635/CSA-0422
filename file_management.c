// file_management.c
// Simple menu: copy, move (rename), delete using UNIX syscalls

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(const char *src, const char *dst) {
    int in = open(src, O_RDONLY);
    if (in < 0) { perror("open src"); return; }
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { perror("open dst"); close(in); return; }
    char buf[4096];
    ssize_t r;
    while ((r = read(in, buf, sizeof(buf))) > 0) {
        if (write(out, buf, r) != r) { perror("write"); break; }
    }
    if (r < 0) perror("read");
    close(in); close(out);
    printf("Copied %s -> %s\n", src, dst);
}

int main() {
    int choice;
    char a[256], b[256];
    while (1) {
        printf("\n1.Copy 2.Move(rename) 3.Delete 4.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 4) break;
        if (choice == 1) {
            printf("Source: "); scanf("%s", a);
            printf("Dest: "); scanf("%s", b);
            copy_file(a,b);
        } else if (choice == 2) {
            printf("Source: "); scanf("%s", a);
            printf("Dest: "); scanf("%s", b);
            if (rename(a,b) == 0) printf("Renamed %s -> %s\n", a,b); else perror("rename");
        } else if (choice == 3) {
            printf("File to delete: "); scanf("%s", a);
            if (unlink(a) == 0) printf("Deleted %s\n", a); else perror("unlink");
        } else printf("Invalid\n");
    }
    return 0;
}
