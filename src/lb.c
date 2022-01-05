#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GLOBAL_CONFIG "/etc/.config/gitnames/"
#define LOCAL_CONFIG "/.config/gitnames/"

#define COMMAND_USER "git config user.name "
#define COMMAND_EMAIL "git config user.email "

#define MAX(a,b) (((a)>(b))?(a):(b))

struct Info {
    char * username;
    char * email;
};

struct Info get(char* name) {
    long namelen = strlen(name);
    char * filename = malloc(MAX((namelen+strlen(GLOBAL_CONFIG)),(namelen+strlen(LOCAL_CONFIG))));
    char * homedir = getenv("HOME");
    filename[0] = '\0';
    strcat(filename, homedir);
    strcat(filename, LOCAL_CONFIG);
    strcat(filename, name);
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        filename[0] = '\0';
        strcat(filename, GLOBAL_CONFIG);
        strcat(filename, name);
        f = fopen(filename, "rb");
        if (f == NULL) {
            struct Info info = { NULL, NULL };
            free(filename);
            return info;
        }
    }
    free(filename);
    
    // Read whole file to buffer
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    if (fsize == 0) {
        printf("file void\n");
        struct Info info = { NULL, NULL };
        return info;
    }
    fseek(f, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;

    // Cut string on '\n' symbol
    char * username = string;
    char * email = string;
    char cuted = 0;
    for (long i = 0; i < fsize; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
            if (cuted == 0) {
                email = string + i + 1;
                cuted = 1;
            }
        }
    }
    struct Info info = { username, email };
    return info;
}

void set(struct Info * info) {
    char * command = malloc(
        MAX(
            strlen(COMMAND_USER)+strlen(info->username),
            strlen(COMMAND_EMAIL)+strlen(info->email)
        )
    );
    command[0] = '\0';
    strcat(command, COMMAND_USER);
    strcat(command, info->username);
    system(command);
    command[0] = '\0';
    strcat(command, COMMAND_EMAIL);
    strcat(command, info->email);
    system(command);
    free(command);
}
