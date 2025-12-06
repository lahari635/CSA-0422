#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int in, out;
    char buffer[1024];
    int n;

    in = open("input.txt", O_RDONLY);
    out = open("output.txt", O_WRONLY | O_CREAT, 0644);

    while ((n = read(in, buffer, sizeof(buffer))) > 0) {
        write(out, buffer, n);
    }

    close(in);
    close(out);

    printf("File copied successfully!\n");
    return 0;
}
