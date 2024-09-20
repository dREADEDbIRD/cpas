#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "auth_data.txt"

void add_user(const char *username, const char *password) {
    FILE *file = fopen(FILE_NAME, "a"); 
        if (!file) {
            perror("Error opening file");
            return;
        }
        fprintf(file, "%s:%s\n", username, password);
        fclose(file);
        printf("User %s added\n", username);
}

void remove_user(const char *username) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;

    while(fgets(line, sizeof(line), file)) {
        char stored_username[128];
        sscanf(line, "%[^:]", stored_username);

        if (strcmp(stored_username, username) != 0) {
            fputs(line, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("User %s removed\n", username);
    } else {
        printf("User %s not found\n", username);
    }
}

void list_users() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    printf("Stored usernames and passwords:\n");

    while (fgets(line, sizeof(line), file)) {
        char username[128], password[128];
        sscanf(line, "%[^:]:%s", username, password);
        printf("Username: %s, Password: %s\n", username, password);
    }
    fclose(file);
}

void handle_args(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./auth -add <username> <password> | -remove <username> | -list\n");
        exit(1);
    }

    if (strcmp(argv[1], "-add") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./auth -add <username> <password>\n");
            exit(1);
        }
        add_user(argv[2], argv[3]);
    } else if (strcmp(argv[1], "-remove") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usave ./auth -remove <username>\n");
            exit(1);
        }
        remove_user(argv[2]);
    } else if (strcmp(argv[1], "-list") == 0) {
        list_users();
    } else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    handle_args(argc, argv);
    return 0;
}