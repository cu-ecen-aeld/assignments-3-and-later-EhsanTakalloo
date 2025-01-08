#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syslog.h>

void create_directory(const char *dir_path) {
    struct stat st = {0};
    if (stat(dir_path, &st) == -1) {
        if (mkdir(dir_path, 0700) != 0) {
            perror("Error: Failed to create directory path");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    // Setup syslog
    openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR, LOG_USER);

    if (argc < 3) {
        syslog(LOG_ERR, "Error: Missing required arguments");
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return EXIT_FAILURE;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Create directory path if needed
    char *dir_path = strdup(writefile);
    if (dir_path == NULL) {
        perror("Error: Memory allocation failed");
        return EXIT_FAILURE;
    }
    char *last_slash = strrchr(dir_path, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';
        create_directory(dir_path);
    }
    free(dir_path);

    // Write content to file
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Failed to open file %s", writefile);
        closelog();
        return EXIT_FAILURE;
    }

    // Log the write operation
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error: Failed to write to file %s", writefile);
        fclose(file);
        closelog();
        return EXIT_FAILURE;
    }

    fclose(file);
    closelog();
    return EXIT_SUCCESS;
}