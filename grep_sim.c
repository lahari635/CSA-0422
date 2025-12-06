// grep_sim.c
// Very small grep: prints lines that contain the pattern

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) { fprintf(stderr, "Usage: %s PATTERN FILE\n", argv[0]); return 1; }
    const char *pat = argv[1];
    const char *file = argv[2];
    FILE *f = fopen(file, "r");
    if (!f) { perror("fopen"); return 1; }
    char *line = NULL; size_t n=0;
    long lineno = 0;
    while (getline(&line, &n, f) > 0) {
        lineno++;
        if (strstr(line, pat) != NULL) {
            printf("%s:%ld:%s", file, lineno, line);
        }
    }
    free(line);
    fclose(f);
    return 0;
}
